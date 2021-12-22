/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_csc.c

  Summary:
    This file contains the source code for the MPLAB Harmony BLE Custom serial chat application.

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
#ifdef APP_BLE_CSC
#include "wdrv_winc_client_api.h"
#include "at_ble_api.h"
#include "ble/ble_services/ble_mgr/ble_manager.h"
#include "ble/ble_profiles/cscp/cscp.h"
#include "ble/ble_services/cscs/cscs.h"
#include "app_csc.h"
#include "m2m_periph.h"



typedef enum
{
    /* CSC application Example's appState machine's initial appState. */
    APP_BLE_CSC_STATE_INIT=0,
    APP_BLE_CSC_STATE_IDLE,
    APP_BLE_CSC_STATE_RUNNING,
    APP_BLE_CSC_STATE_ERROR,
} APP_BLE_CSC_STATES;

APP_BLE_CSC_STATES appBleCscState;

/* =========================== GLOBALS ============================================================ */

/* Received notification data structure */
csc_report_ntf_t recv_ntf_info;

/* Data length to be send over the air */
uint16_t send_length = 0;

/* Buffer data to be send over the air */
uint8_t send_data[APP_TX_BUF_SIZE];


/* Function used for receive data */
static void csc_app_recv_buf(uint8_t *recv_data, uint8_t recv_len)
{
	if (recv_len){
		DBG_LOG("Rx: ");
			APP_DebugPrint(recv_data, recv_len);
		DBG_LOG("\r\n");
	}
}

/* Callback called for new data from remote device */
static void csc_prf_report_ntf_cb(csc_report_ntf_t *report_info)
{
	csc_app_recv_buf(report_info->recv_buff, report_info->recv_buff_len);
}

void csc_app_send_data(uint8_t *buff,int len)
{
    csc_prf_send_data(buff,len);
}

/* Function used for send data */
void csc_app_send_buf(void)
{
	uint16_t ind = 0;
	uint16_t len = 0;
	uint8_t buff = 0;
	len = APP_ConsoleRead(&buff, 1);
	if (len){
		for (ind = 0; ind < len; ind++)
		{
			if(buff != CSC_ENTER_BUTTON_PRESS)
			{
				if (!send_length)
				{
					DBG_LOG("TX:");
				}
				APP_DebugPrint(&buff, 1);
				if (buff == BACKSPACE_BUTTON_PRESS)
				{
					APP_DebugPrint((uint8_t *)' ', 1);//(CSC_SPACE_BAR);
					APP_DebugPrint(&buff, 1);
					if(send_length)
						send_length--;
				}

				if(send_length < APP_TX_BUF_SIZE)
				{
					if(buff != BACKSPACE_BUTTON_PRESS)
						send_data[send_length++] = buff;
				}
				else
				{
					csc_prf_send_data(&send_data[0], send_length);
					send_length = 0;
				}
			}
			else
			{ // User press enter to send data
				if(send_length)
				{
					ind = send_length;
					send_length = 0;
					csc_prf_send_data(&send_data[0], ind);
					DBG_LOG("\r\n");
				}
			}
		}
	}
}

void ble_csc_process_event(at_ble_events_t event, void* params)
{
	if (event != AT_BLE_UNDEFINED_EVENT)
	{
		// Feed the received event into BlueSDK stack.
		ble_event_manager(event, params,APP_CSC_ENABLED);
	}
}

/*bool app_exec = true;*/
at_ble_status_t ble_csc_init(void )
{
	DBG_LOG("Initializing Custom Serial Chat Application");

	/* Initialize the buffer address and buffer length based on user input */
	csc_prf_buf_init(&send_data[0], APP_TX_BUF_SIZE);

	/* initialize the ble chip and Set the device mac address */
	ble_device_init(NULL,APP_CSC_ENABLED);

	/* Register the notification handler */
	notify_recv_ntf_handler(csc_prf_report_ntf_cb);
    
    return AT_BLE_SUCCESS;

}




static int APP_CscCMDProcess
(
    SYS_CMD_DEVICE_NODE* pCmdIO, 
    int argc, 
    char** argv
) 
{
    if ((argc >= 1) && (!strcmp(argv[1], "send")))
    {
        csc_app_send_data((uint8_t*)argv[2],strlen(argv[2])); 
    }
    return 0;
}

static const SYS_CMD_DESCRIPTOR AppCscCmdTbl[] =
{
    {"csc", (SYS_CMD_FNC) APP_CscCMDProcess, ": CSC commands processing"},
    
};



void APP_BleCscInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    SYS_CMD_ADDGRP(AppCscCmdTbl, sizeof (AppCscCmdTbl) / sizeof (*AppCscCmdTbl), "csc", ": CSC commands"); 
    appBleCscState = APP_BLE_CSC_STATE_INIT;   
}



void APP_BleCscTasks(DRV_HANDLE handle)
{ 
    switch (appBleCscState)
    {
        case APP_BLE_CSC_STATE_INIT:
        {
            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BLEStart(handle))
            {
                SYS_CONSOLE_PRINT("Failed to start BLE\r\n");
                appBleCscState = APP_BLE_CSC_STATE_ERROR;
                break;
            }
            if (AT_BLE_SUCCESS != ble_csc_init())
            {
                APP_DebugPrintf("Failed to configure BLE Custom Serial Chat\r\n");
                appBleCscState = APP_BLE_CSC_STATE_ERROR;
                break;
            }
            appBleCscState = APP_BLE_CSC_STATE_RUNNING;
            break;
        }
        case APP_BLE_CSC_STATE_RUNNING:
        {
            at_ble_events_t             bleEvent;
            at_ble_event_parameter_t    bleParams;
            
            if (AT_BLE_SUCCESS == at_ble_event_get(&bleEvent, &bleParams, 0))
            {
                //APP_DebugPrintf("\r\nBLE event received: %d", bleEvent);
                ble_csc_process_event(bleEvent, &bleParams);
            }
            else
            {
                bleEvent = AT_BLE_UNDEFINED_EVENT;
            }
            break;
        }
        case APP_BLE_CSC_STATE_ERROR:
        {
            appBleCscState = APP_BLE_CSC_STATE_IDLE;
            break;
        }
        default:
        {
            break;
        }
    }
}
#endif

