/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_pxp_reporter.c

  Summary:
    This file contains the source code for the MPLAB Harmony BLE Proximity Reporter application.

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
#ifdef APP_BLE_PROXIMITY

#include "wdrv_winc_client_api.h"
#include "ble/ble_profiles/pxp_reporter/pxp_reporter.h"
#include "ble/ble_services/immediate_alert/immediate_alert.h"
#include "ble/ble_services/link_loss/link_loss.h"

typedef enum
{
    /* BLE application Example's appState machine's initial appState. */
    APP_BLE_PROXIMITY_STATE_INIT=0,
    APP_BLE_PROXIMITY_STATE_IDLE,
    APP_BLE_PROXIMITY_STATE_RUNNING,
    APP_BLE_PROXIMITY_STATE_ERROR,
} APP_BLE_PROXIMITY_STATES;

APP_BLE_PROXIMITY_STATES appBleProximityState;


#define LED0_PIN    PORT_PIN_PB30

// Initial timer value
#define PXP_REPORTER_INIT_TIMER_INTERVAL		(60)
#define PXP_REPORTER_LL_INTERVAL_MEDIUM			(255)
#define PXP_REPORTER_LL_INTERVAL_FAST			(60)
#define PXP_REPORTER_PL_INTERVAL_MEDIUM			(255)
#define PXP_REPORTER_PL_INTERVAL_FAST			(60)


SYS_TIME_HANDLE timer = SYS_TIME_HANDLE_INVALID;

void led_init(void)
{
    PORT_PinOutputEnable(LED0_PIN);
	// clear LED
	PORT_PinSet(LED0_PIN);
}

static void led_clear(void)
{
	PORT_PinSet(LED0_PIN);
    SYS_TIME_TimerDestroy(timer);
}

void led_toggle(unsigned int context)
{
	PORT_PinToggle(LED0_PIN);
}

static void led_flash(uint32_t interval_ms)
{
    timer = SYS_TIME_CallbackRegisterMS(led_toggle, 0, interval_ms, SYS_TIME_PERIODIC);
}

// Callback to this profile app on pathloss
static void ble_pxp_handle_pathloss(uint8_t alert_val)
{
	switch (alert_val)
	{
		case IAS_HIGH_ALERT:
		{
			M2M_INFO("\nPathloss : High Alert");
			led_flash(PXP_REPORTER_PL_INTERVAL_FAST);
			break;
		}
		case IAS_MID_ALERT:
		{
			M2M_INFO("\nPathloss : Mild Alert");
			led_flash(PXP_REPORTER_PL_INTERVAL_MEDIUM);
			break;
		}
		case IAS_NO_ALERT:
		{
			M2M_INFO("\nPathloss : No Alert");
			led_clear();
			break;
		}
	}
}

// Callback to this profile app on linkloss
static void ble_pxp_handle_linkloss(uint8_t alert_val)
{
	switch(alert_val)
	{
		case LLS_HIGH_ALERT:
		{
			M2M_INFO("\nLink loss : High Alert ");
			led_flash(PXP_REPORTER_LL_INTERVAL_FAST);
			break;
		}
		case LLS_MILD_ALERT:
		{
			M2M_INFO("\nLink loss : Mild Alert  ");
			led_flash(PXP_REPORTER_LL_INTERVAL_MEDIUM);
			break;
		}
		case LLS_NO_ALERT:
		{
			M2M_INFO("\nLink loss : No Alert  ");
			led_clear();
			break;
		}
	}
}

static void ble_pxp_handle_conn_update(uint8_t conn_state)
{
	led_clear();
}

static void ble_pxp_profile_init(void)
{
	register_pathloss_handler(ble_pxp_handle_pathloss);
	register_linkloss_handler(ble_pxp_handle_linkloss);
	register_conn_update_handler(ble_pxp_handle_conn_update);
}

at_ble_status_t ble_pxp_init(void)
{
	// pxp_reporter_init is called from ble_device_init()
	ble_device_init(NULL,APP_PXP_ENABLED);

	ble_pxp_profile_init();
    
    return AT_BLE_SUCCESS;
}

void ble_pxp_process_event(at_ble_events_t event, void* params)
{
	if (event != AT_BLE_UNDEFINED_EVENT)
	{
		// Feed the received event into BlueSDK stack.
		ble_event_manager(event, params,APP_PXP_ENABLED);
	}
}


void APP_BleProximityInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    appBleProximityState = APP_BLE_PROXIMITY_STATE_INIT;   
}


void APP_BleProximityTasks(DRV_HANDLE handle)
{
    switch (appBleProximityState)
    {
        case APP_BLE_PROXIMITY_STATE_INIT:
        {
            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BLEStart(handle))
            {
                SYS_CONSOLE_PRINT("Failed to start BLE\r\n");
                appBleProximityState = APP_BLE_PROXIMITY_STATE_ERROR;
                break;
            }
            if (AT_BLE_SUCCESS != ble_pxp_init())
            {
                APP_DebugPrintf("Failed to configure BLE proximity\r\n");
                led_init();
                appBleProximityState = APP_BLE_PROXIMITY_STATE_ERROR;
                break;
            }
            appBleProximityState = APP_BLE_PROXIMITY_STATE_RUNNING;
            break;
        }
        case APP_BLE_PROXIMITY_STATE_IDLE:
        {
            break;
        }
        case APP_BLE_PROXIMITY_STATE_RUNNING:
        {
            at_ble_events_t             bleEvent;
            at_ble_event_parameter_t    bleParams;
            
            if (AT_BLE_SUCCESS == at_ble_event_get(&bleEvent, &bleParams, 0))
            {
                ble_pxp_process_event(bleEvent, &bleParams);
            }
            else
            {
                bleEvent = AT_BLE_UNDEFINED_EVENT;
            }
            break;
        }
        case APP_BLE_PROXIMITY_STATE_ERROR:
        {
            appBleProximityState = APP_BLE_PROXIMITY_STATE_IDLE;
            break;
        }

        default:
        {
            appBleProximityState = APP_BLE_PROXIMITY_STATE_INIT;
            break;
        }
    }
       
}

#endif//#ifdef APP_BLE_PROXIMITY
