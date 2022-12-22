/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_battery.c

  Summary:
    This file contains the source code for the MPLAB Harmony Battery application.

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

/*- Includes -----------------------------------------------------------------------*/
#include "app.h"
#ifdef APP_BLE_BATTERY
#include "app_battery.h"
#include "ble/ble_services/ble_mgr/ble_manager.h"
#include "ble/ble_services/battery/battery.h"
#include "wdrv_winc_client_api.h"
//#include "at_ble_api.h"



typedef enum
{
    /* BLE application Example's appState machine's initial appState. */
    APP_BLE_BATTERY_STATE_INIT=0,
    APP_BLE_BATTERY_STATE_IDLE,
    APP_BLE_BATTERY_STATE_RUNNING,
    APP_BLE_BATTERY_STATE_ERROR,
} APP_BLE_BATTERY_STATES;

APP_BLE_BATTERY_STATES appBleBatteryState;

#define LED0_PIN     SYS_PORT_PIN_PB30

SYS_TIME_HANDLE battery_timer = SYS_TIME_HANDLE_INVALID;


#define APP_BAS_FAST_ADV				(100) //100 ms
/** @brief APP_BAS_ADV_TIMEOUT Advertising time-out between 0x0001 and 0x3FFF in seconds, 0x0000 disables time-out.*/
#define APP_BAS_ADV_TIMEOUT				(1000) // 100 Secs
/** @brief scan_resp_len is the length of the scan response data */
#define BAS_SCAN_RESP_LEN					(10)
/** @brief ADV_DATA_LEN */
#define BAS_ADV_DATA_LEN					(18)
/** @brief ADV_TYPE_LEN */
#define ADV_TYPE_LEN					(0x01)
/** @brief BAS_ADV_DATA_UUID_LEN the size of  BAS service uuid */
#define BAS_ADV_DATA_UUID_LEN			(2)
/** @brief BAS_ADV_DATA_UUID_TYPE the total sizeof BAS service uuid*/
#define BAS_ADV_DATA_UUID_TYPE			(0x03)
/** @brief BAS_ADV_DATA_NAME_TYPE the gap ad data type */
#define BAS_ADV_DATA_NAME_TYPE			(0x09)
/* @brief BAS_ADV_DATA_NAME_DATA the actual name of device */
#define BAS_ADV_DATA_NAME_DATA			("MCHP-BAS")
/** @brief BAS_ADV_DATA_NAME_LEN the length of the device name */
#define BAS_ADV_DATA_NAME_LEN			(9)

static const uint8_t SCAN_RESP_DATA[BAS_SCAN_RESP_LEN] = {0x09,0xff, 0x00, 0x06, 0xd6, 0xb2, 0xf0, 0x05, 0xf0, 0xf8};


#define BATTERY_UPDATE_INTERVAL	(188)
#define BATTERY_MAX_LEVEL		(100)


static bool volatile timer_cb_done;
static uint8_t led_toggle;
static uint8_t battery_level;
static 	gatt_service_handler_t bas_service_handler;


static at_ble_status_t ble_bat_start_advertise(void)
{
	uint8_t idx = 0;
	uint8_t adv_data [ BAS_ADV_DATA_NAME_LEN + BAS_ADV_DATA_UUID_LEN   + (2*2)];

	adv_data[idx++] = BAS_ADV_DATA_UUID_LEN + ADV_TYPE_LEN;
	adv_data[idx++] = BAS_ADV_DATA_UUID_TYPE;

	/* Appending the UUID */
	adv_data[idx++] = (uint8_t)BAT_SERVICE_UUID;
	adv_data[idx++] = (uint8_t)(BAT_SERVICE_UUID >> 8);

	//Appending the complete name to the Ad packet
	adv_data[idx++] = BAS_ADV_DATA_NAME_LEN + ADV_TYPE_LEN;
	adv_data[idx++] = BAS_ADV_DATA_NAME_TYPE;

	memcpy(&adv_data[idx], BAS_ADV_DATA_NAME_DATA, BAS_ADV_DATA_NAME_LEN);
	idx += BAS_ADV_DATA_NAME_LEN;

	/* Adding the advertisement data and scan response data */
	if (at_ble_adv_data_set(adv_data, idx, SCAN_RESP_DATA, BAS_SCAN_RESP_LEN) != AT_BLE_SUCCESS)
	{
		DBG_LOG("Failed to set adv data");
		return AT_BLE_FAILURE;
	}

	at_ble_set_dev_config(AT_BLE_GAP_PERIPHERAL_SLV);

	/* Start of advertisement */
	if (at_ble_adv_start(AT_BLE_ADV_TYPE_UNDIRECTED, AT_BLE_ADV_GEN_DISCOVERABLE, NULL,
			AT_BLE_ADV_FP_ANY, APP_BAS_FAST_ADV, APP_BAS_ADV_TIMEOUT, 0) != AT_BLE_SUCCESS)
	{
		DBG_LOG("BLE Adv start Failed");
		return AT_BLE_FAILURE;
	}

	DBG_LOG("BLE Started Adv\n");
	return AT_BLE_SUCCESS;
}

void ble_bat_handle_timer_event(unsigned int context)
{
	if (led_toggle == true)
		SYS_PORT_PinToggle(LED0_PIN);
	else
		SYS_PORT_PinSet(LED0_PIN);	// LED OFF

	timer_cb_done = true;
}

static void ble_bat_handle_paired_event(at_ble_handle_t conn_handle)
{
	timer_cb_done = false;
    SYS_TIME_TimerDestroy(battery_timer);
    battery_timer = SYS_TIME_CallbackRegisterMS(ble_bat_handle_timer_event, 0, BATTERY_UPDATE_INTERVAL, SYS_TIME_PERIODIC);
}

static void ble_bat_handle_disconnect_event(at_ble_handle_t conn_handle)
{
	timer_cb_done = false;
    SYS_TIME_TimerDestroy(battery_timer);
	ble_bat_start_advertise();
}

// Update the service about battery status
static void ble_bat_process(void)
{
	if (timer_cb_done)
	{
		timer_cb_done = false;

		battery_level = (battery_level % BATTERY_MAX_LEVEL);

		// blinking when battery less than 60%
		led_toggle = (battery_level < 60)? true:false;

		/* send the notification and Update the battery level  */
		if (bat_update_char_value(&bas_service_handler, battery_level) == AT_BLE_SUCCESS)
		{
			DBG_LOG("Battery Level:%d%%", battery_level);
		}
		battery_level++;
	}
}

// Allows the main app to initialise the profile app including
// initialising services and callbacks
static void ble_bat_profile_init(void)
{
	timer_cb_done = false;
	led_toggle = false;
	battery_level = BATTERY_MAX_LEVEL;

	DBG_LOG("Initializing Battery Service Application");

	bat_init_service(&bas_service_handler, &battery_level);
    bat_primary_service_define(&bas_service_handler);

	register_ble_paired_event_cb(ble_bat_handle_paired_event);
	register_ble_disconnected_event_cb(ble_bat_handle_disconnect_event);
    ble_bat_start_advertise();

}

at_ble_status_t ble_bat_init(void)
{
	ble_device_init(NULL,APP_ENABLED);
    ble_bat_profile_init();
    return AT_BLE_SUCCESS;
}

void ble_bat_process_event(at_ble_events_t event, at_ble_event_parameter_t *params)
{
	if (event != AT_BLE_UNDEFINED_EVENT)
	{
		// Feed the received event into BlueSDK stack.
		ble_event_manager(event, params,APP_ENABLED);
	}

	ble_bat_process();
}


#if 0
static void led_init(void)
{
     PORT_PinOutputEnable(LED0_PIN);
	// clear LED
     PORT_PinSet(LED0_PIN);
}
#endif


void APP_BleBatteryInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    appBleBatteryState = APP_BLE_BATTERY_STATE_INIT;   
}


void APP_BleBatteryTasks(DRV_HANDLE handle)
{    
    switch (appBleBatteryState)
    {
        case APP_BLE_BATTERY_STATE_INIT:
        {
            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BLEStart(handle))
            {
                SYS_CONSOLE_PRINT("Failed to start BLE\r\n");
                appBleBatteryState = APP_BLE_BATTERY_STATE_ERROR;
                break;
            }
            if (AT_BLE_SUCCESS != ble_bat_init())
            {
                APP_DebugPrintf("Failed to configure BLE Battery Service\r\n");

                appBleBatteryState = APP_BLE_BATTERY_STATE_ERROR;
                break;
            }
            appBleBatteryState = APP_BLE_BATTERY_STATE_RUNNING;
            break;
        }
        case APP_BLE_BATTERY_STATE_RUNNING:
        {
            at_ble_events_t             bleEvent;
            at_ble_event_parameter_t    bleParams;
            
            if (AT_BLE_SUCCESS == at_ble_event_get(&bleEvent, &bleParams, 0))
            {
                ble_bat_process_event(bleEvent, &bleParams);
            }
            else
            {
                bleEvent = AT_BLE_UNDEFINED_EVENT;
            }
            break;
        }
        case APP_BLE_BATTERY_STATE_ERROR:
        {
            appBleBatteryState = APP_BLE_BATTERY_STATE_IDLE;
            break;
        }
        default:
        {
            appBleBatteryState = APP_BLE_BATTERY_STATE_INIT;
            break;
        }
    }
    
    
}


#endif
