/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_trans_service.c

  Summary:
    This file contains the source code for the MPLAB Harmony BLE Transparent service application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/
 
 // DOM-IGNORE-BEGIN
 /*******************************************************************************
* Copyright (C) 2020-21 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#ifdef APP_BLE_TRANSPARENT_SERVICE
#include "app_trans_service.h"
#include "ble/ble_services/ble_mgr/ble_manager.h"
#include "wdrv_winc_client_api.h"
#include "ble/ble_services/trans_service/trans_service.h"
#include "ble/sio2host/uart/sio2host.h"


typedef enum
{
    /* BLE application Example's appState machine's initial appState. */
    APP_BLE_TRANS_STATE_INIT=0,
    APP_BLE_TRANS_STATE_IDLE,
    APP_BLE_TRANS_STATE_RUNNING,
    APP_BLE_TRANS_STATE_ERROR,
} APP_BLE_TRANS_STATES;

APP_BLE_TRANS_STATES appBleTransState;



/** @brief APP_TRANS_FAST_ADV between 0x0020 and 0x4000 in 0.625 ms units (20ms to 10.24s). */
#define APP_TRANS_FAST_ADV				(100) //100 ms

/** @brief APP_TRANS_ADV_TIMEOUT Advertising time-out between 0x0001 and 0x3FFF in seconds, 0x0000 disables time-out.*/
#define APP_TRANS_ADV_TIMEOUT				(1000) // 100 Secs

/** @brief scan_resp_len is the length of the scan response data */
#define TRANS_SCAN_RESP_LEN					(12)
/** @brief ADV_DATA_LEN */
#define TRANS_ADV_DATA_LEN					(28)
/** @brief ADV_TYPE_LEN */
#define ADV_TYPE_LEN					(0x01)
/** @brief TRANS_ADV_DATA_UUID_LEN the size of  TRANS service uuid */
#define TRANS_ADV_DATA_UUID_LEN			(16)

/** @brief TRANS_ADV_DATA_UUID_TYPE the total sizeof TRANS service uuid*/
#define TRANS_ADV_DATA_UUID_TYPE			(0x07)

/** @brief TRANS_ADV_DATA_NAME_LEN the  length of the device name */
#define TRANS_ADV_DATA_NAME_LEN			(8)

/** @brief TRANS_ADV_DATA_NAME_TYPE the gap ad data type */
#define TRANS_ADV_DATA_NAME_TYPE			(0x09)

#define TRANS_ADV_DATA_NAME_DATA			("uC-TRANS")

static const uint8_t SCAN_RESP_DATA[TRANS_SCAN_RESP_LEN] = {0x0b,0x08, 'M', 'C', 'H', 'P', '-', 'T', 'R', 'A', 'N', 'S'};


/****************************************************************************************
*							        Globals
*                                       *
****************************************************************************************/
extern uint8_t trans_tx_notification_flag;
extern uint8_t trans_ctrl_notification_flag;
extern uint8_t enable_credit_based_fc;
extern at_ble_uuid_t trans_service_uuid;

/* Data length to be send over the air */
uint16_t trans_send_length = 0;
/* Buffer data to be send over the air */
uint8_t trans_send_data[TRANS_APP_TX_BUF_SIZE];

static  gatt_service_handler_t trans_service_handler;

static at_ble_status_t ble_trans_service_advertise(void)
{
        uint8_t idx = 0;
        uint8_t adv_data [ TRANS_ADV_DATA_NAME_LEN + TRANS_ADV_DATA_UUID_LEN   + (2*2)];

        //DBG_LOG("BLE - trans_service_advertise - Start\r\n");

        adv_data[idx++] = TRANS_ADV_DATA_UUID_LEN + ADV_TYPE_LEN;
        adv_data[idx++] = TRANS_ADV_DATA_UUID_TYPE;

        /* Appending the UUID */
        memcpy(&adv_data[idx], trans_service_uuid.uuid, TRANS_ADV_DATA_UUID_LEN);
        idx += TRANS_ADV_DATA_UUID_LEN;

        //Appending the complete name to the Ad packet
        adv_data[idx++] = TRANS_ADV_DATA_NAME_LEN + ADV_TYPE_LEN;
        adv_data[idx++] = TRANS_ADV_DATA_NAME_TYPE;

        memcpy(&adv_data[idx], TRANS_ADV_DATA_NAME_DATA, TRANS_ADV_DATA_NAME_LEN );
        idx += TRANS_ADV_DATA_NAME_LEN;

        /* Adding the advertisement data and scan response data */
        if(!(at_ble_adv_data_set(adv_data, idx, SCAN_RESP_DATA, TRANS_SCAN_RESP_LEN) == AT_BLE_SUCCESS) )
        {
            DBG_LOG("Failed to set adv data\r\n");
        }

		at_ble_set_dev_config(AT_BLE_GAP_PERIPHERAL_SLV);

        /* Start of advertisement */
        if(at_ble_adv_start(AT_BLE_ADV_TYPE_UNDIRECTED, AT_BLE_ADV_GEN_DISCOVERABLE, NULL,
                    AT_BLE_ADV_FP_ANY, APP_TRANS_FAST_ADV, APP_TRANS_ADV_TIMEOUT, 0) == AT_BLE_SUCCESS)
        {
            DBG_LOG("BLE Started Adv\r\n");
            return AT_BLE_SUCCESS;
        }
        else
        {
            DBG_LOG("BLE Adv start Failed");
        }
        APP_DebugPrintf("BLE - trans_service_advertise - End\r\n");

        return AT_BLE_FAILURE;
}


/**@brief function to check the client characteristic configuration value.
 */
static at_ble_status_t ble_trans_char_changed_event(at_ble_characteristic_changed_t *char_changed)
{
	at_ble_status_t status = AT_BLE_SUCCESS;
	uint8_t cnt;
	//printf("\nChanged the character handle 0x%X to a value = \r\n", char_changed->char_handle);
	if(char_changed->char_len != 0)
       {
	    APP_DebugPrintf("Rx:");
	    for(cnt = 0; cnt < char_changed->char_len; cnt++)
	    {
		APP_DebugPrintf("%c", char_changed->char_new_value[cnt]);
	    }
           APP_DebugPrintf("\r\n");
       }
	if(char_changed->char_handle == trans_service_handler.serv_chars[0].client_config_handle)	/*If the peer is writing to CCCD handle of Transparent Tx*/
	{
		if(char_changed->char_new_value[0])
		{
			trans_tx_notification_flag = true;
			/* sending notification to the peer about change in the trans tx value */
			if((status = at_ble_notification_send(char_changed->conn_handle, trans_service_handler.serv_chars[0].char_val_handle)) != AT_BLE_SUCCESS) {
				DBG_LOG("sending trans tx notification failed%d",status);
				return status;
			}
			else {
				DBG_LOG_DEV("sending trans tx notification successful");
				return status;
			}
		}
		else
		{
			trans_tx_notification_flag = false;
		}

	}
	if(char_changed->char_handle == trans_service_handler.serv_chars[2].client_config_handle)	/*If the peer is writing to CCCD handle of Transparent CTRL*/
	{
		if(char_changed->char_new_value[0])
		{
			//DBG_LOG("Enabling Credit based Flow control Notification");
			trans_ctrl_notification_flag = true;
		}
		else
		{
			DBG_LOG("Disabling Credit based Flow control Notification");
			trans_ctrl_notification_flag = false;
		}

	}
	if(char_changed->char_handle == trans_service_handler.serv_chars[1].char_val_handle)	/*If the peer is writing to handle of Transparent Rx*/
	{
		uint8_t tlc_payload[5] = {0x00, 0x14, 0x17, 0x00, 0x01}; /* 0x00 -> Success 0x14 -> FC code 0x0200 is the max MTU, 0x01 -> buffers left*/
		trans_update_ctrl_char_value(&trans_service_handler, tlc_payload, 5);
	}

	if(char_changed->char_handle == trans_service_handler.serv_chars[2].char_val_handle)	/*If the peer is writing to handle of Transparent ctrl*/
	{
		if(char_changed->char_new_value[0] == 0x14)
		{
			//DBG_LOG("Enabling Credit based Flow control");
			enable_credit_based_fc = true;
		}
		else
		{
			DBG_LOG("Disabling Credit based Flow control");
			enable_credit_based_fc = false;
		}
	}



	return status;
}

void ble_trans_service_send_data(uint8_t *trans_tx_value, uint8_t len)
{
    trans_update_tx_char_value(&trans_service_handler, trans_tx_value, len);
}


void ble_trans_service_send_buf(void)
{
	uint16_t ind = 0;
	uint16_t len = 0;
	uint8_t buff = 0;
	uint8_t len_to_send = 20, tx_offset=0;
	//len = sio2host_rx(&buff, 1); //ToDo
    #if (defined __SAMD21J18A__)
    len = SERCOM3_USART_Read(&buff,1);
    #endif
    #if (defined __SAME54P20A__)
    len = SERCOM2_USART_Read(&buff,1);
    #endif
    
	if (len)
	{
		for (ind = 0; ind < len; ind++)
        {
			if(buff != TRANS_ENTER_BUTTON_PRESS)
            {
				if (!trans_send_length)
				{
					DBG_LOG("TX:");
                }
				//sio2host_putchar(buff); //ToDo
                #if (defined __SAMD21J18A__)
                SERCOM3_USART_Write(&buff, 1);
                #endif
                #if (defined __SAME54P20A__)
                SERCOM2_USART_Write(&buff, 1);
                #endif
				if (buff == BACKSPACE_BUTTON_PRESS)
				{
					//sio2host_putchar(TRANS_SPACE_BAR); //ToDo
                    #if (defined __SAMD21J18A__)
                    SERCOM3_USART_Write((uint8_t *)TRANS_SPACE_BAR, 1);
                    SERCOM3_USART_Write(&buff, 1);
                    #endif
                    //sio2host_putchar(buff); //ToDo
                    #if (defined __SAME54P20A__)
                    SERCOM2_USART_Write((uint8_t *)TRANS_SPACE_BAR, 1);
                    SERCOM2_USART_Write(&buff, 1);
                    #endif
					if(trans_send_length)
					trans_send_length--;
				}
				if(trans_send_length < TRANS_APP_TX_BUF_SIZE)
                {
					if(buff != BACKSPACE_BUTTON_PRESS)
					trans_send_data[trans_send_length++] = buff;
				}
                else
                {
					//csc_prf_send_data(&trans_send_data[0], trans_send_length);
					while(trans_send_length > 0)
					{
						if(trans_send_length < len_to_send)
							len_to_send = trans_send_length;
						trans_update_tx_char_value(&trans_service_handler, &trans_send_data[tx_offset], len_to_send);
						tx_offset += len_to_send;
						trans_send_length -= len_to_send;
					}
					trans_send_length = 0;
			    }
		    }//end if(buff != TRANS_ENTER_BUTTON_PRESS)
            else
            { // User press enter to send data
				if(trans_send_length){
					ind = trans_send_length;
					//csc_prf_send_data(&trans_send_data[0], ind);
                    APP_DebugPrintf("Send_length:%d",trans_send_length);
					while(trans_send_length > 0)
					{
						if(trans_send_length < len_to_send)
						len_to_send = trans_send_length;
						trans_update_tx_char_value(&trans_service_handler, &trans_send_data[tx_offset], len_to_send);
						tx_offset += len_to_send;
						trans_send_length -= len_to_send;
					}
					DBG_LOG("\r\n");
					trans_send_length = 0;
				}
		    }//end else
		}//end for (ind = 0; ind < len; ind++)
	}//end if (len)
}

static void ble_trans_service_handle_disconnect_event(at_ble_handle_t conn_handle)
{
    ble_trans_service_advertise();
}

// Allows the main app to initialise the profile app including
// initialising services and callbacks
static at_ble_status_t ble_trans_service_profile_init(void)
{
	//trans_service_init(&trans_service_handler);
	if(trans_service_primary_service_define(&trans_service_handler) != AT_BLE_SUCCESS)
    {
            APP_DebugPrintf("ble_trans_service_profile_init: failed to define the primary service!\r\n");
            return AT_BLE_FAILURE;
        } 
    else 
        {
            //APP_DebugPrintf("ble_trans_service_profile_init: primary service defined.\r\n");
        }

	/* Set trans advertisement data. */
	if (ble_trans_service_advertise() != AT_BLE_SUCCESS) 
    {
		APP_DebugPrintf("ble_trans_service_profile_init: failed to set BLE beacon advertisement data!\r\n");
        return AT_BLE_FAILURE;
	} 
    else 
    {
		//APP_DebugPrintf("ble_trans_service_profile_init: advertisement data set.\r\n");
	}

	/* Register callback for characteristic changed event */
	register_ble_characteristic_changed_cb(ble_trans_char_changed_event);
    register_ble_disconnected_event_cb(ble_trans_service_handle_disconnect_event);
    return AT_BLE_SUCCESS;
}

at_ble_status_t ble_trans_service_init(void)
{
	/* Initialize the buffer address and buffer length based on user input */
    //	trans_service_buf_init(&trans_send_data[0], TRANS_APP_TX_BUF_SIZE);
    DBG_LOG("Initializing Transparent Service Application");
	/* initialize the ble chip  and Set the device mac address */
	ble_device_init(NULL,APP_ENABLED);
    
    ble_trans_service_profile_init();
	
    return AT_BLE_SUCCESS;
}

at_ble_status_t ble_trans_update_value_on_btnpress(uint8_t* trans_tx_value, uint8_t len)
{
    return(trans_update_tx_char_value(&trans_service_handler, trans_tx_value, len));
}

void ble_trans_service_process_event(at_ble_events_t event, at_ble_event_parameter_t *params)
{
	if (event != AT_BLE_UNDEFINED_EVENT)
	{
		// Feed the received event into BlueSDK stack.
		ble_event_manager(event, params,APP_ENABLED);
	}
}

static int APP_TransCMDProcess
(
    SYS_CMD_DEVICE_NODE* pCmdIO, 
    int argc, 
    char** argv
) 
{
    if ((argc >= 1) && (!strcmp(argv[1], "send")))
    {
        ble_trans_service_send_data((uint8_t*)argv[2], strlen(argv[2]));
    }
    return 0;
}

static const SYS_CMD_DESCRIPTOR AppTransCmdTbl[] =
{
    {"trans", (SYS_CMD_FNC) APP_TransCMDProcess, ": Transparent service commands processing"},
    
};



void APP_BleTransInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    SYS_CMD_ADDGRP(AppTransCmdTbl, sizeof (AppTransCmdTbl) / sizeof (*AppTransCmdTbl), "trans", ": Transparent service commands"); 
    appBleTransState = APP_BLE_TRANS_STATE_INIT;   
}



void APP_BleTransTasks(DRV_HANDLE handle)
{    
    switch (appBleTransState)
    {
        case APP_BLE_TRANS_STATE_INIT:
        {
            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BLEStart(handle))
            {
                SYS_CONSOLE_PRINT("Failed to start BLE\r\n");
                appBleTransState = APP_BLE_TRANS_STATE_ERROR;
                break;
            }
            if (AT_BLE_SUCCESS != ble_trans_service_init())
            {
                APP_DebugPrintf("Failed to configure BLE Transparent Service\r\n");

                appBleTransState = APP_BLE_TRANS_STATE_ERROR;
                break;
            }
            appBleTransState = APP_BLE_TRANS_STATE_RUNNING;
            break;
        }
        case APP_BLE_TRANS_STATE_RUNNING:
        {
            at_ble_events_t             bleEvent;
            at_ble_event_parameter_t    bleParams;
            
            if (AT_BLE_SUCCESS == at_ble_event_get(&bleEvent, &bleParams, 0))
            {
                ble_trans_service_process_event(bleEvent, &bleParams);
            }
            else
            {
                bleEvent = AT_BLE_UNDEFINED_EVENT;
            }
            break;
        }
        case APP_BLE_TRANS_STATE_ERROR:
        {
            appBleTransState = APP_BLE_TRANS_STATE_IDLE;
            break;
        }
        default:
        {
            appBleTransState = APP_BLE_TRANS_STATE_INIT;
            break;
        }
    }  
}

#endif