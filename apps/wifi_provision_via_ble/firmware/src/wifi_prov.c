/*******************************************************************************
  WINC Example Application

  File Name:
    wifi_prov.c

  Summary:

  Description:
*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
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

#include "app.h"
#include "wdrv_winc_client_api.h"
#include "at_ble_api.h"
#include "wifiprov_task.h"

extern APP_DATA appData;

typedef enum
{
    /* Example's state machine's initial state. */
    EXAMP_STATE_INIT=0,
    EXAMP_STATE_IDLE,
    EXAMP_STATE_RUNNING,
    EXAMP_STATE_ERROR,
} EXAMP_STATES;

typedef enum
{
    WIFI_STATE_IDLE,
    WIFI_STATE_WAIT_FOR_SCAN_REQUEST,
    WIFI_STATE_SCANNING,
    WIFI_STATE_SCAN_GET_RESULTS,
    WIFI_STATE_SCAN_DONE,
    WIFI_STATE_CONNECTING,
    WIFI_STATE_CONNECTED
} WIFI_STATES;

static EXAMP_STATES appState;
static WIFI_STATES wifiState;
static struct wifiprov_scanlist_ind scanList;
static WDRV_WINC_AUTH_CONTEXT authCtx;
static WDRV_WINC_BSS_CONTEXT bssCtx;

static void APP_ExampleConnectNotifyCallback(DRV_HANDLE handle, WDRV_WINC_ASSOC_HANDLE assocHandle, WDRV_WINC_CONN_STATE currentState, WDRV_WINC_CONN_ERROR errorCode)
{
    if (WDRV_WINC_CONN_STATE_CONNECTED == currentState)
    {
        SYS_CONSOLE_Print(appData.consoleHandle, "Wifi State :: CONNECTED ::\r\n");

        wifiState = WIFI_STATE_CONNECTED;

        wifiprov_wifi_con_update(WIFIPROV_CON_STATE_CONNECTED);
    }
    else if (WDRV_WINC_CONN_STATE_DISCONNECTED == currentState)
    {
        SYS_CONSOLE_Print(appData.consoleHandle, "Wifi State :: DISCONNECTED ::\r\n");

        wifiState = WIFI_STATE_IDLE;

        wifiprov_wifi_con_update(WIFIPROV_CON_STATE_DISCONNECTED);
    }
}

static void APP_ExampleDHCPAddressEventCallback(DRV_HANDLE handle, uint32_t ipAddress)
{
    char s[20];

    SYS_CONSOLE_Print(appData.consoleHandle, "DHCP IP address is %s\r\n", inet_ntop(AF_INET, &ipAddress, s, sizeof(s)));
}

void APP_ExampleInitialize(DRV_HANDLE handle)
{
    SYS_CONSOLE_Print(appData.consoleHandle, "\r\n");
    SYS_CONSOLE_Print(appData.consoleHandle, "======================================\r\n");
    SYS_CONSOLE_Print(appData.consoleHandle, "WINC3400 BLE WiFi Provisioning Example\r\n");
    SYS_CONSOLE_Print(appData.consoleHandle, "======================================\r\n");

    appState = EXAMP_STATE_INIT;
}

void APP_ExampleTasks(DRV_HANDLE handle)
{
    WDRV_WINC_STATUS status;

    switch (appState)
    {
        case EXAMP_STATE_INIT:
        {
            WDRV_WINC_AuthCtxSetDefaults(&authCtx);
            WDRV_WINC_BSSCtxSetDefaults(&bssCtx);

            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BLEStart(handle))
            {
                SYS_CONSOLE_Print(appData.consoleHandle, "Failed to start BLE\r\n");

                appState = EXAMP_STATE_ERROR;
                break;
            }

#ifdef WDRV_WINC_DEVICE_BLE_API_REV_2
            if (AT_BLE_SUCCESS != wifiprov_configure_provisioning((uint8_t *)"WiFi Prov", AT_BLE_AUTH_MITM_NO_BOND))
#else
            if (AT_BLE_SUCCESS != wifiprov_configure_provisioning((uint8_t *)"WiFi Prov"))
#endif
            {
                SYS_CONSOLE_Print(appData.consoleHandle, "Failed to configure BLE provisioning\r\n");

                appState = EXAMP_STATE_ERROR;
                break;
            }

            if (AT_BLE_SUCCESS != wifiprov_create_db())
            {
                SYS_CONSOLE_Print(appData.consoleHandle, "Failed to create BLE provisioning database\r\n");

                appState = EXAMP_STATE_ERROR;
                break;
            }

            /* Enable use of DHCP for network configuration, DHCP is the default
             but this also registers the callback for notifications. */

            WDRV_WINC_IPUseDHCPSet(handle, &APP_ExampleDHCPAddressEventCallback);

            appState = EXAMP_STATE_IDLE;
            break;
        }

        case EXAMP_STATE_IDLE:
        {
            if (false == WDRV_WINC_BLEIsStarted(handle))
            {
                if (WDRV_WINC_STATUS_OK != WDRV_WINC_BLEStart(handle))
                {
                    SYS_CONSOLE_Print(appData.consoleHandle, "Failed to start BLE\r\n");

                    appState = EXAMP_STATE_ERROR;
                    break;
                }
            }

            wifiprov_scan_mode_change_ind_send(WIFIPROV_SCANMODE_INIT);

            wifiState = WIFI_STATE_IDLE;

            appState = EXAMP_STATE_RUNNING;
            break;
        }

        case EXAMP_STATE_RUNNING:
        {
            at_ble_events_t             bleEvent;
            at_ble_event_parameter_t    bleParams;

            if (AT_BLE_SUCCESS == at_ble_event_get(&bleEvent, &bleParams, 0))
            {
                SYS_CONSOLE_Print(appData.consoleHandle, "BLE event received: %d\r\n", bleEvent);
            }
            else
            {
                bleEvent = AT_BLE_UNDEFINED_EVENT;
            }

            switch (wifiState)
            {
                case WIFI_STATE_IDLE:
                {

                    /* Use 6-pin key to provision. */

                    uint8_t pinCode[6] = {1, 2, 3, 4, 5, 6};

                    WDRV_WINC_BSSDisconnect(handle);

                    if (AT_BLE_SUCCESS == wifiprov_start(pinCode, sizeof(pinCode)))
                    {
                        SYS_CONSOLE_Print(appData.consoleHandle, "BLE provisioning started\r\n");

                        wifiState = WIFI_STATE_WAIT_FOR_SCAN_REQUEST;
                    }
                    else
                    {
                        SYS_CONSOLE_Print(appData.consoleHandle, "Failed to start BLE provisioning\r\n");

                        appState = EXAMP_STATE_ERROR;
                    }

                    break;
                }

                case WIFI_STATE_WAIT_FOR_SCAN_REQUEST:
                {
                    if (AT_BLE_WIFIPROV_SCAN_MODE_CHANGE_IND == bleEvent)
                    {
                        at_ble_wifiprov_scan_mode_change_ind_t *pScanModeInd = (at_ble_wifiprov_scan_mode_change_ind_t *)&bleParams;

                        SYS_CONSOLE_Print(appData.consoleHandle, "AT_BLE_WIFIPROV_SCAN_MODE_CHANGE_IND :%x\r\n", pScanModeInd->scanmode);

                        if (WIFIPROV_SCANMODE_SCANNING == pScanModeInd->scanmode)
                        {
                            if (false == WDRV_WINC_BSSFindInProgress(handle))
                            {
                                if (WDRV_WINC_STATUS_OK != WDRV_WINC_BSSFindFirst(handle, WDRV_WINC_ALL_CHANNELS, true, NULL, NULL))
                                {
                                    SYS_CONSOLE_Print(appData.consoleHandle, "Failed to start BSS scanning\r\n");

                                    appState = EXAMP_STATE_ERROR;

                                    break;
                                }

                                scanList.num_valid = 0;

                                wifiprov_scan_mode_change_ind_send(WIFIPROV_SCANMODE_SCANNING);

                                SYS_CONSOLE_Print(appData.consoleHandle, "Scanning for BSSs\r\n");

                                wifiState = WIFI_STATE_SCANNING;
                            }
                        }
                    }
                    else if (AT_BLE_WIFIPROV_COMPLETE_IND == bleEvent)
                    {
                        at_ble_wifiprov_complete_ind *pWiFiProvInfo = (at_ble_wifiprov_complete_ind *)&bleParams;

                        SYS_CONSOLE_Print(appData.consoleHandle, "AT_BLE_WIFIPROV_COMPLETE_IND :%x\n", pWiFiProvInfo->status);

                        WDRV_WINC_AuthCtxSetDefaults(&authCtx);
                        WDRV_WINC_BSSCtxSetDefaults(&bssCtx);

                        if (AT_BLE_SUCCESS == pWiFiProvInfo->status)
                        {
                            SYS_CONSOLE_Print(appData.consoleHandle, "Provisioning data received\r\n");

                            switch (pWiFiProvInfo->sec_type)
                            {
                                case M2M_WIFI_SEC_OPEN:
                                {
                                    status = WDRV_WINC_AuthCtxSetOpen(&authCtx);
                                    break;
                                }

                                case M2M_WIFI_SEC_WPA_PSK:
                                {
                                    status = WDRV_WINC_AuthCtxSetWPA(&authCtx, pWiFiProvInfo->passphrase, pWiFiProvInfo->passphrase_length);
                                    break;
                                }

                                case M2M_WIFI_SEC_WEP:
                                {
                                    status = WDRV_WINC_AuthCtxSetWEP(&authCtx, 1, pWiFiProvInfo->passphrase, pWiFiProvInfo->passphrase_length);
                                    break;
                                }

                                default:
                                {
                                    SYS_CONSOLE_Print(appData.consoleHandle, "Unsupported security type %d\r\n", pWiFiProvInfo->sec_type);
                                    appState = EXAMP_STATE_ERROR;

                                    status = WDRV_WINC_STATUS_INVALID_ARG;
                                    break;
                                }
                            }

                            if (WDRV_WINC_STATUS_OK != status)
                            {
                                SYS_CONSOLE_Print(appData.consoleHandle, "Invalid security information\r\n");
                                appState = EXAMP_STATE_ERROR;
                                break;
                            }

                            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BSSCtxSetSSID(&bssCtx, pWiFiProvInfo->ssid, pWiFiProvInfo->ssid_length))
                            {
                                SYS_CONSOLE_Print(appData.consoleHandle, "Invalid BSS information\r\n");
                                appState = EXAMP_STATE_ERROR;
                                break;
                            }

                            SYS_CONSOLE_Print(appData.consoleHandle, "Connecting to %s\r\n", pWiFiProvInfo->ssid);

                            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BSSConnect(handle, &bssCtx, &authCtx, APP_ExampleConnectNotifyCallback))
                            {
                                SYS_CONSOLE_Print(appData.consoleHandle, "Connection failed\r\n");
                                appState = EXAMP_STATE_ERROR;
                                break;
                            }

                            wifiState = WIFI_STATE_CONNECTING;
                        }
                        else
                        {
                            SYS_CONSOLE_Print(appData.consoleHandle, "Provisioning Failed\r\n");

                            appState = EXAMP_STATE_ERROR;
                        }
                    }
                    break;
                }

                case WIFI_STATE_SCANNING:
                {
                    if (false == WDRV_WINC_BSSFindInProgress(handle))
                    {
                        uint8_t numBSSs;

                        numBSSs = WDRV_WINC_BSSFindGetNumBSSResults(handle);

                        SYS_CONSOLE_Print(appData.consoleHandle, "Scan complete, %d BSS(s) found\r\n", numBSSs);

                        if (0 == numBSSs)
                        {
                            wifiprov_scan_mode_change_ind_send(WIFIPROV_SCANMODE_DONE);

                            wifiState = WIFI_STATE_WAIT_FOR_SCAN_REQUEST;
                        }
                        else
                        {
                            wifiState = WIFI_STATE_SCAN_GET_RESULTS;
                        }
                    }

                    break;
                }

                case WIFI_STATE_SCAN_GET_RESULTS:
                {
                    WDRV_WINC_BSS_INFO bssInfo;

                    /* Request the current BSS find results. */

                    if (WDRV_WINC_STATUS_OK == WDRV_WINC_BSSFindGetInfo(handle, &bssInfo))
                    {
                        SYS_CONSOLE_Print(appData.consoleHandle, "BSS found: RSSI: %d %s\r\n", bssInfo.rssi, bssInfo.ctx.ssid.name);

                        if ((scanList.num_valid < MAX_WIPROVTASK_AP_NUM) && (0 != bssInfo.ctx.ssid.name[0]))
                        {
                            uint8_t idx = scanList.num_valid;

                            scanList.scandetails[idx].sec_type = bssInfo.authType;
                            scanList.scandetails[idx].rssi     = bssInfo.rssi;
                            memset(scanList.scandetails[idx].ssid, 0, MAX_WIPROVTASK_SSID_LENGTH);
                            memcpy(scanList.scandetails[idx].ssid, bssInfo.ctx.ssid.name, bssInfo.ctx.ssid.length);

                            scanList.num_valid++;
                        }

                        /* Request the next set of BSS find results. */

                        status = WDRV_WINC_BSSFindNext(handle, NULL);

                        if (WDRV_WINC_STATUS_BSS_FIND_END == status)
                        {
                            wifiState = WIFI_STATE_SCAN_DONE;
                        }
                        else if ((WDRV_WINC_STATUS_NOT_OPEN == status) || (WDRV_WINC_STATUS_INVALID_ARG == status))
                        {
                            /* An error occurred requesting results. */

                            appState = EXAMP_STATE_ERROR;
                        }
                    }
                    break;
                }

                case WIFI_STATE_SCAN_DONE:
                {
                    wifiprov_scan_list_ind_send(&scanList);

                    wifiState = WIFI_STATE_WAIT_FOR_SCAN_REQUEST;
                    break;
                }

                case WIFI_STATE_CONNECTING:
                {
                    break;
                }

                default:
                {
                    break;
                }
            }

            break;
        }

        case EXAMP_STATE_ERROR:
        {
            wifiprov_disable();
            WDRV_WINC_BSSDisconnect(handle);
            WDRV_WINC_BLEStop(handle);

            appState = EXAMP_STATE_IDLE;
            break;
        }

        default:
        {
            break;
        }
    }
}
