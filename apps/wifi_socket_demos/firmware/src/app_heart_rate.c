/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_heart_rate.c

  Summary:
    This file contains the source code for the MPLAB Harmony BLE Heart rate service application.

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

#ifdef APP_BLE_HEARTRATE
#include "app_heart_rate.h"
#include "ble/ble_services/ble_mgr/ble_manager.h"
#include "wdrv_winc_client_api.h"
#include "ble/ble_services/heart_rate/heart_rate.h"
#include "ble/ble_profiles/hr_sensor/hr_sensor.h"


typedef enum
{
    /* BLE application Example's appState machine's initial appState. */
    APP_BLE_HEART_RATE_STATE_INIT=0,
    APP_BLE_HEART_RATE_STATE_IDLE,
    APP_BLE_HEART_RATE_STATE_RUNNING,
    APP_BLE_HEART_RATE_STATE_ERROR,
} APP_BLE_HEART_RATE_STATES;

APP_BLE_HEART_RATE_STATES appBleHeartrateState;


/****************************************************************************************
*							        Globals
*                                       *
****************************************************************************************/
uint16_t rr_interval_value = RR_VALUE_MIN; /*!< to count the rr interval value*/


// Update the service about Heart Rate
static void ble_heart_rate_process(void)
{
	uint8_t hr_data[HR_CHAR_VALUE_LEN];
	uint8_t idx = 0;

       if (timer_cb_done)
       {
		timer_cb_done = false;
	    if ((energy_expended_val == ENERGY_RESET) || (second_counter % 10 == energy_inclusion)) {
		hr_data[idx] = (RR_INTERVAL_VALUE_PRESENT | ENERGY_EXPENDED_FIELD_PRESENT);

		/* To send energy expended after 10 notifications after reset */
		if (energy_expended_val == ENERGY_RESET) {
			energy_inclusion = second_counter % 10 ;
		}
	    } else {
		hr_data[idx] = RR_INTERVAL_VALUE_PRESENT ;
	    }
	    idx += 1;
	    DBG_LOG("Heart Rate: %d bpm", heart_rate_value);
		if(inc_changer == HEART_RATE_INCREMENT_VALUE)
		{
			heart_rate_value += HEART_RATE_INCREMENT_VALUE;
		}
		else
		{
			heart_rate_value -= HEART_RATE_INCREMENT_VALUE;
		}

	    /* Heart Rate Value 8bit*/
	    hr_data[idx++] = (uint8_t)heart_rate_value ;
	    if (hr_data[0] & ENERGY_EXPENDED_FIELD_PRESENT) {
		memcpy(&hr_data[idx], &energy_expended_val, 2);
		idx += 2;
	    }

	    /* Appending RR interval values*/
	    if (rr_interval_value >= RR_VALUE_MAX) {
		rr_interval_value = (uint8_t) RR_VALUE_MIN;
	    }
	    DBG_LOG_CONT("\tRR Values:(%d,%d)msec",
		        		rr_interval_value, rr_interval_value + 200);
	    memcpy(&hr_data[idx], &rr_interval_value, 2);
	    idx += 2;
	    rr_interval_value += 200;
	    memcpy(&hr_data[idx], &rr_interval_value, 2);
	    idx += 2;
	    rr_interval_value += 200;

	    /*printing the user activity,simulation*/
	    switch(activity) {
	        case ACTIVITY_NORMAL:
		    DBG_LOG_CONT(" User Status:Idle");
		    break;

	        case ACTIVITY_WALKING:
		    DBG_LOG_CONT(" User Status:Walking");
		    break;

	        case ACTIVITY_BRISK_WALKING:
		    DBG_LOG_CONT(" User status:Brisk walking");
		    break;

	        case ACTIVITY_RUNNING:
		    DBG_LOG_CONT(" User status:Running");
		    break;

	        case ACTIVITY_FAST_RUNNING:
		    DBG_LOG_CONT(" User Status:Fast Running");
		    break;
	    }

	    /* Printing the energy*/
	    if ((hr_data[0] & ENERGY_EXPENDED_FIELD_PRESENT)) {
		DBG_LOG("Energy Expended :%d KJ\n", energy_expended_val);
		energy_expended_val += energy_incrementor;
	    }

	    /* Sending the data for notifications*/
           heart_rate_send_notification(hr_data, idx);
       }
}

at_ble_status_t ble_heart_rate_init(void)
{
	ble_device_init(NULL,APP_ENABLED);

    ble_heart_rate_profile_init();

    return AT_BLE_SUCCESS;
}

void ble_heart_rate_process_event(at_ble_events_t event, at_ble_event_parameter_t *params)
{
	if (event != AT_BLE_UNDEFINED_EVENT)
	{
		// Feed the received event into BlueSDK stack.
		ble_event_manager(event, params,APP_ENABLED);
	}
	ble_heart_rate_process();
}

void APP_BleHeartrateInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    appBleHeartrateState = APP_BLE_HEART_RATE_STATE_INIT;   
}

void APP_BleHeartrateTasks(DRV_HANDLE handle)
{    
    switch (appBleHeartrateState)
    {
        case APP_BLE_HEART_RATE_STATE_INIT:
        {
            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BLEStart(handle))
            {
                SYS_CONSOLE_PRINT("Failed to start BLE\r\n");
                appBleHeartrateState = APP_BLE_HEART_RATE_STATE_ERROR;
                break;
            }
            if (AT_BLE_SUCCESS != ble_heart_rate_init())
            {
                APP_DebugPrintf("Failed to configure BLE Heart Rate\r\n");

                appBleHeartrateState = APP_BLE_HEART_RATE_STATE_ERROR;
                break;
            }
            appBleHeartrateState = APP_BLE_HEART_RATE_STATE_RUNNING;
            break;
        }
        case APP_BLE_HEART_RATE_STATE_RUNNING:
        {
            at_ble_events_t             bleEvent;
            at_ble_event_parameter_t    bleParams;
            
            if (AT_BLE_SUCCESS == at_ble_event_get(&bleEvent, &bleParams, 0))
            {   
                ble_heart_rate_process_event(bleEvent, &bleParams);
            }
            else
            {
                bleEvent = AT_BLE_UNDEFINED_EVENT;
            }
            break;
        }
        case APP_BLE_HEART_RATE_STATE_ERROR:
        {
            appBleHeartrateState = APP_BLE_HEART_RATE_STATE_IDLE;
            break;
        }
        default:
        {
            appBleHeartrateState = APP_BLE_HEART_RATE_STATE_INIT;
            break;
        }
    }
}


#endif//#ifdef APP_BLE_HEART_RATE
