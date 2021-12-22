/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_blewifi_prov.c

  Summary:
    This file contains the source code for the MPLAB Harmony wifi provisioning via BLE application.

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
#ifdef APP_BLE_WIFI_PROV
#include "wdrv_winc_client_api.h"
#include "at_ble_api.h"
#include "wifiprov_task.h"
#include "app_blewifi_prov.h"



typedef enum
{
    /* Example's state machine's initial state. */
    APP_BLE_STATE_INIT=0,
    APP_BLE_STATE_START,
    APP_BLE_STATE_READ,
    APP_BLE_STATE_STOP,
    APP_BLE_STATE_DONE,        
    APP_BLE_STATE_ERROR
} APP_BLE_STATES;

static APP_BLE_STATES appBleState;
static char appblename[25];
/* Use 6-pin key to provision. */
static uint8_t appPinCode[6] = {1, 2, 3, 4, 5, 6};
static APP_CALLBACK pAPPWiFiProvCallback;

static int APP_BleCMDProcess
(
    SYS_CMD_DEVICE_NODE* pCmdIO, 
    int argc, 
    char** argv
) 
{
   if ((argc >= 1) && (!strcmp(argv[1], "help")))
   {
        SYS_CONSOLE_PRINT("wifiprov <name>\r\n");
   }
   else
   {
       appBleState = APP_BLE_STATE_INIT;
       if(argc <= 2)
       {
            strcpy(appblename,argv[1]);
            appblename[strlen(appblename)+1]='\0';
        }
   }
   return 0;
}
static const SYS_CMD_DESCRIPTOR AppBleCmdTbl[] =
{
    {"wifiprov", (SYS_CMD_FNC) APP_BleCMDProcess, ": WiFi Provisioning commands processing"},
    
};

void APP_BleWiFiProvInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    strcpy(appblename,"WiFi Prov");
    appblename[10]='\0';
    pAPPWiFiProvCallback = pAPPWiFiCallback;
    
    SYS_CMD_ADDGRP(AppBleCmdTbl, sizeof (AppBleCmdTbl) / sizeof (*AppBleCmdTbl), "wifiprov", ": WiFi Provisioning commands"); 
 }

void APP_BleWiFiProvTasks(DRV_HANDLE handle)
{
    at_ble_events_t             bleEvent;
    at_ble_event_parameter_t    bleParams;
    switch(appBleState)
    {
        case APP_BLE_STATE_INIT:
        {
            
            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BLEStart(handle))
            {
                SYS_CONSOLE_PRINT("Failed to start BLE\r\n");
                appBleState = APP_BLE_STATE_ERROR;
                break;
            }
            if (AT_BLE_SUCCESS != wifiprov_configure_provisioning((uint8_t *)"WiFi Prov", AT_BLE_AUTH_MITM_NO_BOND))
            {
                SYS_CONSOLE_PRINT("Failed to configure BLE provisioning\r\n");
                appBleState = APP_BLE_STATE_ERROR;
                break;
            }
            
            if (AT_BLE_SUCCESS != wifiprov_create_db())
            {
               SYS_CONSOLE_PRINT("Failed to create BLE provisioning database\r\n");
               appBleState = APP_BLE_STATE_ERROR;
                break;
            }
            appBleState = APP_BLE_STATE_START;
            break;
        }
        case APP_BLE_STATE_START:
        { 
            if (AT_BLE_SUCCESS == at_ble_event_get(&bleEvent, &bleParams, 0))
            {
                SYS_CONSOLE_PRINT("BLE event received: %d\r\n", bleEvent);
            }
            if (AT_BLE_SUCCESS == wifiprov_start(appPinCode, sizeof(appPinCode)))
            {
                appBleState = APP_BLE_STATE_READ;
            }
            break;
        }
        
        case APP_BLE_STATE_READ:
        {

           if (AT_BLE_SUCCESS == at_ble_event_get(&bleEvent, &bleParams, 0))
            {
                SYS_CONSOLE_PRINT("BLE event received: %d\r\n", bleEvent);
            }
           
            if (AT_BLE_WIFIPROV_SCAN_MODE_CHANGE_IND == bleEvent)
            {
                at_ble_wifiprov_scan_mode_change_ind_t *pScanModeInd = (at_ble_wifiprov_scan_mode_change_ind_t *)&bleParams;

                SYS_CONSOLE_PRINT("AT_BLE_WIFIPROV_SCAN_MODE_CHANGE_IND :%d\r\n", pScanModeInd->scanmode);
            }
            else if(AT_BLE_WIFIPROV_COMPLETE_IND == bleEvent)
            {
                at_ble_wifiprov_complete_ind *pWiFiProvInfo = (at_ble_wifiprov_complete_ind *)&bleParams;
                SYS_CONSOLE_PRINT("AT_BLE_WIFIPROV_COMPLETE_IND :%s:%s:%d\n", pWiFiProvInfo->ssid,pWiFiProvInfo->passphrase,pWiFiProvInfo->sec_type);
                (*pAPPWiFiProvCallback)(APP_WIFI_PROVISION,pWiFiProvInfo);
                appBleState = APP_BLE_STATE_STOP;
            }
            break;
        }
        case APP_BLE_STATE_STOP:
        {
            wifiprov_disable();
            WDRV_WINC_BLEStop(handle);
            appBleState = APP_BLE_STATE_DONE;            
            break;
        }
        
        default:
        {
            break;
        }        
    }    
}
#endif 
/* *****************************************************************************
 End of File
 */
