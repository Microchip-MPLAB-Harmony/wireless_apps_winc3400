
/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    wifi.c

  Summary:
    This file contains the source code for the MPLAB Harmony wifi application.

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
#ifdef APP_STA_AP
#include <stdlib.h>
#include "wdrv_winc_client_api.h"
#include "tcpip/src/tcpip_manager_control.h"
#include "app_wifi.h"


#define APP_WIFI_SSID       "DEMO_AP"
#define APP_WIFI_AUTH       WDRV_WINC_AUTH_TYPE_WPA_PSK
#define APP_WIFI_BOOTMODE   APP_AP_MODE
#define APP_WIFI_CHANNEL    1
#define APP_WIFI_PSK        "12345678" 
#define APP_WIFI_DHCP_SRV_ADDR      "192.168.1.1"
#define APP_WIFI_DHCP_SRV_NETMASK   "255.255.255.0"
#define APP_TCP_LISTEN_PORT         6666//80
#define APP_TCP_BUFFER_SIZE         1460

typedef enum
{
    /* Example's state machine's initial state. */
    APP_WIFI_STA_STATE_INIT=0,
    APP_WIFI_STA_STATE_SCANNING,
    APP_WIFI_STA_STATE_SCAN_GET_RESULTS,
    APP_WIFI_STA_AP_STATE_CONFIG,
    APP_WIFI_STA_AP_STATE_TCP_INIT,
    APP_WIFI_STA_STATE_START,
    APP_WIFI_STA_STATE_CONNECTING,
    APP_WIFI_STA_STATE_CONNECTED,
    APP_WIFI_STA_STATE_DISCONNECTED,
    APP_WIFI_AP_STATE_START,
    APP_WIFI_AP_STATE_STARTED,
    APP_WIFI_AP_WAIT_FOR_STA_IP,
    APP_WIFI_AP_SOCKET_LISTENING,
    APP_WIFI_AP_STOPPED,
    APP_WIFI_STA_AP_STATE_DONE,        
    APP_WIFI_STA_AP_STATE_ERROR,
} APP_WIFI_STA_AP_STATES;

APP_WIFI_STA_AP_STATES appSocketStaApState; 
bool appWifiCredsUpdate;


typedef enum 
{
    APP_AP_MODE = 1,
    APP_STA_MODE,     
}APP_BOOT_MODES;

typedef enum 
{
    APP_SOCKET_MODE = 1,
    APP_BYPASS_MODE,
    APP_NONE
}APP_WINC_MODES;



typedef struct
{
    APP_BOOT_MODES    bootmode;
    WDRV_WINC_BSS_CONTEXT   bss;
    WDRV_WINC_AUTH_CONTEXT auth;
    
}APP_WIFI_CONFIG;


APP_WIFI_CONFIG appWiFiConfig;


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
static WDRV_WINC_AUTH_CONTEXT authCtx;
static WDRV_WINC_BSS_CONTEXT bssCtx;
static bool foundBSS;
static APP_CALLBACK pAPPWiFiSocketCallback;
static TCPIP_NET_HANDLE          netHdl;
static TCP_SOCKET                wifiProvSocket = INVALID_SOCKET;
static TCPIP_TCP_SIGNAL_HANDLE   wifiProvHdl;
static WDRV_WINC_NETWORK_ADDRESS peerAddress;
static IPV4_ADDR                 netIpWiFi;

static void APP_WiFiSocketCreate();

static int APP_WiFiCMDProcess
(
    SYS_CMD_DEVICE_NODE* pCmdIO, 
    int argc, 
    char** argv
) 
{
    if ((argc >= 1) && (!strcmp(argv[1], "set")))
    {
        appWiFiConfig.bootmode = strtol(argv[2], NULL, 0);
        
        memcpy((uint8_t *)appWiFiConfig.bss.ssid.name,argv[3],strlen(argv[3])+1);
        appWiFiConfig.auth.authType = strtol(argv[4], NULL, 0);
        
        if(appWiFiConfig.auth.authType == WDRV_WINC_AUTH_TYPE_WPA_PSK)
        {
            
            memcpy((uint8_t *)appWiFiConfig.auth.authInfo.WPAPerPSK.key,argv[5],strlen(argv[5])+1);
            
        } 
        else if(appWiFiConfig.auth.authType == WDRV_WINC_AUTH_TYPE_802_1X_MSCHAPV2)
        {
            memcpy((uint8_t *)appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.domainUserName,argv[6],strlen(argv[6])+1);
            memcpy((uint8_t *)appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.password,argv[5],strlen(argv[5])+1);
        }
        
        appSocketStaApState = APP_WIFI_STA_STATE_INIT;
        appWifiCredsUpdate = true;

    }
    else if(!strcmp(argv[1], "get")) //only for wifi get, print the data structure values
    {
        SYS_CONSOLE_PRINT( "Bootmode:%d\r\n",appWiFiConfig.bootmode);
        SYS_CONSOLE_PRINT( "SSID:%s\r\n",appWiFiConfig.bss.ssid.name);
        SYS_CONSOLE_PRINT( "Auth_type:%d\r\n",appWiFiConfig.auth.authType);
        if(appWiFiConfig.auth.authType == WDRV_WINC_AUTH_TYPE_WPA_PSK)
        {
            SYS_CONSOLE_PRINT( "Password:%s\r\n",appWiFiConfig.auth.authInfo.WPAPerPSK.key);
        }
        else if(appWiFiConfig.auth.authType == WDRV_WINC_AUTH_TYPE_802_1X_MSCHAPV2)
        {
            SYS_CONSOLE_PRINT( "Password:%s\r\n",appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.password);
            SYS_CONSOLE_PRINT( "Username:%s\r\n",appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.domainUserName);
        }
        SYS_CONSOLE_PRINT( "appSocketStaApState:%d\r\n",appSocketStaApState);
    }
    else if(!strcmp(argv[1], "help"))
    {
        SYS_CONSOLE_PRINT( "wifi set <bootmode>\r\n");
        SYS_CONSOLE_PRINT( "bootmode : 1 - Serial Chat\r\n");
    }
    return 0;
}


static const SYS_CMD_DESCRIPTOR AppWiFiCmdTbl[] =
{
    {"wifi", (SYS_CMD_FNC) APP_WiFiCMDProcess, ": APP commands processing"},
    
};
static void APP_WiFiAPAssocCallback(DRV_HANDLE handle, WDRV_WINC_ASSOC_HANDLE assocHandle, const WDRV_WINC_SSID *const pSSID, const WDRV_WINC_NETWORK_ADDRESS *const pPeerAddress, WDRV_WINC_AUTH_TYPE authType, int8_t rssi)
{
    memcpy(&peerAddress,pPeerAddress,sizeof(WDRV_WINC_NETWORK_ADDRESS));    
    
    appSocketStaApState = APP_WIFI_AP_WAIT_FOR_STA_IP;
}
static void APP_WiFiAPConnectNotifyCallback(DRV_HANDLE handle, WDRV_WINC_ASSOC_HANDLE assocHandle, WDRV_WINC_CONN_STATE currentState, WDRV_WINC_CONN_ERROR errorCode)
{
    if (WDRV_WINC_CONN_STATE_CONNECTED == currentState)
    {
        SYS_CONSOLE_PRINT("Connected\r\r");
        WDRV_WINC_AssocPeerAddressGet(assocHandle, &peerAddress,&APP_WiFiAPAssocCallback);        
    }
    else if (WDRV_WINC_CONN_STATE_DISCONNECTED == currentState)
    {
        SYS_CONSOLE_PRINT("Disconnected\r\r");
        (*pAPPWiFiSocketCallback)(APP_WIFI_DISCONNECT, NULL);
    }
}

static void APP_WiFiConnectNotifyCallback(DRV_HANDLE handle, WDRV_WINC_ASSOC_HANDLE assocHandle, WDRV_WINC_CONN_STATE currentState, WDRV_WINC_CONN_ERROR errorCode)
{
    if (WDRV_WINC_CONN_STATE_CONNECTED == currentState)
    {
        /* When connected reset the ICMP echo request counter and state. */
        SYS_CONSOLE_PRINT("Connected\r\n");
        appSocketStaApState = APP_WIFI_STA_STATE_CONNECTED;
        appWifiCredsUpdate = false;
    }
    else if (WDRV_WINC_CONN_STATE_DISCONNECTED == currentState)
    {
        SYS_CONSOLE_PRINT( "Disconnected\r\n");
        (*pAPPWiFiSocketCallback)(APP_WIFI_DISCONNECT, NULL);
        if (appWifiCredsUpdate == false)
        {
            appSocketStaApState = APP_WIFI_STA_STATE_START;//APP_WIFI_STA_STATE_DISCONNECTED;
        }
    }
}
static void APP_WiFiTrackIPAddr( void )
{
    IPV4_ADDR dwNewIP;
    
    /* Obtain the IPv4 address of the network interface */
    dwNewIP.Val = TCPIP_STACK_NetAddress(netHdl);

    /* Check if the IP address has changed */
    if(dwNewIP.Val != netIpWiFi.Val)
    {
        /* save the new IP address in appData */
        netIpWiFi.Val = dwNewIP.Val;
        SYS_CONSOLE_PRINT("app: DHCP Client has received IP Address: %d.%d.%d.%d\r\n",
                          dwNewIP.v[0], dwNewIP.v[1], dwNewIP.v[2], dwNewIP.v[3]);
    }
}
static void APP_WiFiSocketDataProcess(uint8_t buffer[]) 
{
   SYS_CONSOLE_PRINT("app: buffer:%s\r\n",buffer);
    if (buffer && (!strncmp((const char *) buffer, "apply", 5))) 
    {        
        char * p = strtok((char *) buffer, ",");
        p = strtok(NULL, ",");
        if (p)
        {
            strcpy((char *)appWiFiConfig.bss.ssid.name, p);
        }

        p = strtok(NULL, ",");
        if (p) 
            {
            char appAuthType = *p - '0';
            if (appAuthType == 1) /* 1-Open */
            { 
                appWiFiConfig.auth.authType = WDRV_WINC_AUTH_TYPE_OPEN;
            } 
            else if (appAuthType == 2) /* 2-WPA2 */
            {
                appWiFiConfig.auth.authType = WDRV_WINC_AUTH_TYPE_WPA_PSK;
                p = strtok(NULL, ",");
                if (p) 
                {
                    strcpy((char *)appWiFiConfig.auth.authInfo.WPAPerPSK.key, p);
                }
            } 
        }
        appWiFiConfig.bootmode = APP_STA_MODE;
        appSocketStaApState = APP_WIFI_AP_STOPPED; 
        (*pAPPWiFiSocketCallback)(APP_WIFI_PROVISION,NULL);
    }
}

static void APP_WiFiSocketCallback(TCP_SOCKET hTCP, TCPIP_NET_HANDLE hNet, TCPIP_TCP_SIGNAL_TYPE sigType, const void* param) 
{
    uint8_t buffer[512];
    switch (sigType) 
    {
        case TCPIP_TCP_SIGNAL_RX_DATA:
        {
            memset(buffer, 0, sizeof (buffer));
            /* Reading the TCP Rx data */
            uint8_t byte = TCPIP_TCP_ArrayGet(wifiProvSocket, buffer, sizeof (buffer));
            if (byte) 
            {
                APP_WiFiSocketDataProcess(buffer);
            }
            TCPIP_TCP_Discard(wifiProvSocket);
            break;
        }

        case TCPIP_TCP_SIGNAL_RX_FIN:
        {
            /* TCP client has sent the TCP RX FIN received  */
            TCPIP_TCP_Close(wifiProvSocket);
            wifiProvSocket = INVALID_SOCKET;
            /* Reopen the Socket to enable TCP Server again */
            APP_WiFiSocketCreate();
            break;
        }

        default:
        {
            break;
        }
    }
}
static void APP_WiFiSocketCreate()
{
        /* Open the TCP server socket */
        wifiProvSocket = TCPIP_TCP_ServerOpen(IP_ADDRESS_TYPE_IPV4, APP_TCP_LISTEN_PORT, 0);
        if (wifiProvSocket == INVALID_SOCKET) 
        {
            SYS_CONSOLE_MESSAGE("Couldn't open Wi-Fi Provision service server socket \r\n");
        }
        /* Register TCP data callback with enabling event  
           TCPIP_TCP_SIGNAL_RX_DATA and TCPIP_TCP_SIGNAL_RX_FIN  */
        wifiProvHdl = TCPIP_TCP_SignalHandlerRegister(wifiProvSocket, TCPIP_TCP_SIGNAL_RX_DATA | TCPIP_TCP_SIGNAL_RX_FIN, APP_WiFiSocketCallback, NULL);
        if (wifiProvHdl == NULL) 
        {
            SYS_CONSOLE_MESSAGE("Couldn't create socket handle\r\n");
        }
}

void APP_WiFiInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    
    appWiFiConfig.bootmode = APP_WIFI_BOOTMODE;
    pAPPWiFiSocketCallback = pAPPWiFiCallback;
    memcpy((uint8_t *)appWiFiConfig.bss.ssid.name,APP_WIFI_SSID,sizeof(APP_WIFI_SSID));
    appWiFiConfig.auth.authType = APP_WIFI_AUTH;
    memcpy((uint8_t *)appWiFiConfig.auth.authInfo.WPAPerPSK.key,APP_WIFI_PSK,sizeof(APP_WIFI_PSK));
    SYS_CMD_ADDGRP(AppWiFiCmdTbl, sizeof (AppWiFiCmdTbl) / sizeof (*AppWiFiCmdTbl), "wifi", ": WiFi commands"); 
    appWifiCredsUpdate = false;
    appSocketStaApState = APP_WIFI_STA_AP_STATE_DONE;
}

void APP_WiFiTasks(DRV_HANDLE handle)
{
    
    WDRV_WINC_STATUS status;

    switch (appSocketStaApState)
    {
        case APP_WIFI_STA_STATE_INIT:
        {
            if( APP_AP_MODE == appWiFiConfig.bootmode)
            {
                appSocketStaApState = APP_WIFI_STA_AP_STATE_CONFIG;
            }
            else
            {
                if (WDRV_WINC_STATUS_OK == WDRV_WINC_BSSFindFirst(handle, WDRV_WINC_ALL_CHANNELS, true, NULL, NULL))
                {
                    appSocketStaApState = APP_WIFI_STA_STATE_SCANNING;
                    foundBSS = false;
                }
            }
            break;
        }

        case APP_WIFI_STA_STATE_SCANNING:
        {
            /* Wait for BSS find operation to complete, then report the number
             of results found. */

            if (false == WDRV_WINC_BSSFindInProgress(handle))
            {
                SYS_CONSOLE_PRINT( "Scan complete, %d AP(s) found\r\n", WDRV_WINC_BSSFindGetNumBSSResults(handle));
                appSocketStaApState = APP_WIFI_STA_STATE_SCAN_GET_RESULTS;
            }
            break;
        }

        case APP_WIFI_STA_STATE_SCAN_GET_RESULTS:
        {
            WDRV_WINC_BSS_INFO BSSInfo;

            /* Request the current BSS find results. */

            if (WDRV_WINC_STATUS_OK == WDRV_WINC_BSSFindGetInfo(handle, &BSSInfo))
            {
                SYS_CONSOLE_PRINT( "AP found: RSSI: %d %s\r\n", BSSInfo.rssi, BSSInfo.ctx.ssid.name);

                /* Check if this SSID matches the search target SSID. */
                
                if (((strlen((const char*)appWiFiConfig.bss.ssid.name)) == BSSInfo.ctx.ssid.length) && (0 == memcmp(BSSInfo.ctx.ssid.name, appWiFiConfig.bss.ssid.name, BSSInfo.ctx.ssid.length)))
                {
           
                    foundBSS = true;
                }

                /* Request the next set of BSS find results. */

                status = WDRV_WINC_BSSFindNext(handle, NULL);

                if (WDRV_WINC_STATUS_BSS_FIND_END == status)
                {
                    /* If there are no more results available check if the target
                     SSID has been found. */

                    if (true == foundBSS)
                    {
                        SYS_CONSOLE_PRINT( "Target AP found, trying to connect\r\n");
                        appSocketStaApState = APP_WIFI_STA_AP_STATE_CONFIG;
                    }
                    else
                    {
                        SYS_CONSOLE_PRINT( "Target BSS not found\r\n");
                        appSocketStaApState = APP_WIFI_STA_AP_STATE_ERROR;
                    }
                }
                else if ((WDRV_WINC_STATUS_NOT_OPEN == status) || (WDRV_WINC_STATUS_INVALID_ARG == status))
                {
                    /* An error occurred requesting results. */

                    appSocketStaApState = APP_WIFI_STA_AP_STATE_ERROR;
                }
            }
            break;
        }

        case APP_WIFI_STA_AP_STATE_CONFIG:
        {
            /* Preset the error appSocketStaApState incase any following operations fail. */
            /* Reset the internal BSS context */
            WDRV_WINC_BSSCtxSetDefaults(&bssCtx);
            if( APP_AP_MODE == appWiFiConfig.bootmode)
            {
                if (WDRV_WINC_STATUS_OK != WDRV_WINC_BSSCtxSetChannel(&bssCtx, APP_WIFI_CHANNEL))
                {
                    break;
                }
            }
            WDRV_WINC_BSSCtxSetSSID(&bssCtx, (uint8_t*)appWiFiConfig.bss.ssid.name, strlen((const char *)appWiFiConfig.bss.ssid.name));
            
            /* Reset the internal Auth context */
            WDRV_WINC_AuthCtxSetDefaults(&authCtx);

            /* Prepare the Auth context with desired AP's Security settings */
            if (WDRV_WINC_AUTH_TYPE_OPEN == appWiFiConfig.auth.authType)
            {
                WDRV_WINC_AuthCtxSetOpen(&authCtx);
            }
            else if (WDRV_WINC_AUTH_TYPE_WPA_PSK == appWiFiConfig.auth.authType)
            {
                WDRV_WINC_AuthCtxSetWPA(&authCtx, (uint8_t*)appWiFiConfig.auth.authInfo.WPAPerPSK.key, strlen((const char *)appWiFiConfig.auth.authInfo.WPAPerPSK.key));
            }
            else if (WDRV_WINC_AUTH_TYPE_802_1X_MSCHAPV2 == appWiFiConfig.auth.authType)
            {
                WDRV_WINC_AuthCtxSetWPAEnterpriseMSCHAPv2(&authCtx, (char*)appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.domainUserName, (uint8_t*)appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.password, strlen((const char *)appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.password), false);
            }
            
            appSocketStaApState = APP_WIFI_STA_AP_STATE_TCP_INIT;
            
            break;
        }

        case APP_WIFI_STA_AP_STATE_TCP_INIT:
        {
                        /* WINC network handle*/
            netHdl = TCPIP_STACK_NetHandleGet("WINC");
            if(APP_STA_MODE == appWiFiConfig.bootmode)
            {
                if (true == TCPIP_DHCPS_IsEnabled(netHdl)) 
                {
                    TCPIP_DHCPS_Disable(netHdl);
                }
                /* Enable DHCP client in STA mode */
                TCPIP_DHCP_Enable(netHdl);
                appSocketStaApState = APP_WIFI_STA_STATE_START;
            } 
            else if(APP_AP_MODE == appWiFiConfig.bootmode)
            {                
                if (true == TCPIP_DHCP_IsEnabled(netHdl)) 
                {
                    TCPIP_DHCP_Disable(netHdl);
                }
                /* Enable DHCP Server in AP mode */
                TCPIP_DHCPS_Enable(netHdl);
                appSocketStaApState = APP_WIFI_AP_STATE_START;
            }        
            break;
        }

        case APP_WIFI_STA_STATE_START:
        {
                /* Connect to the target BSS with the chosen authentication. */
                if (WDRV_WINC_STATUS_OK == WDRV_WINC_BSSConnect(handle, &bssCtx, &authCtx, &APP_WiFiConnectNotifyCallback))
                {
                    appSocketStaApState = APP_WIFI_STA_STATE_CONNECTING;
                }

            break;
        }
        
        case APP_WIFI_STA_STATE_CONNECTING:
        {
            break;
        }

        case APP_WIFI_STA_STATE_CONNECTED:
        {
              //Wait for the TCPIP Stack to become initialized
            if (TCPIP_STACK_Status(sysObj.tcpip) == SYS_STATUS_READY)
            {
                if (TCPIP_STACK_NetIsReady(netHdl) && TCPIP_DHCP_IsBound(netHdl))
                {
                    if(APP_STA_MODE == appWiFiConfig.bootmode)
                    {
                        SYS_CONSOLE_PRINT("app: TCPIP Stack is Ready on %s Interface\r\n",
                                    TCPIP_STACK_NetNameGet(netHdl));
                        SYS_CONSOLE_PRINT("app: Host name is %s\r\n", 
                                    TCPIP_STACK_NetBIOSName(netHdl));
                        SYS_CONSOLE_PRINT("app: DHCP Client is enabled on %s interface\r\n",
                                    TCPIP_STACK_NetNameGet(netHdl));
                        APP_WiFiTrackIPAddr();
                        (*pAPPWiFiSocketCallback)(APP_WIFI_CONNECT,NULL);
                        appSocketStaApState = APP_WIFI_STA_AP_STATE_DONE;
                    }
                    break;
                }
            }
            break;
        }
        
        case APP_WIFI_STA_STATE_DISCONNECTED:
        {
            /* If we become disconnected, trigger a reconnection. */

            if (WDRV_WINC_STATUS_OK == WDRV_WINC_BSSReconnect(handle, &APP_WiFiConnectNotifyCallback))
            {
                appSocketStaApState = APP_WIFI_STA_STATE_CONNECTING;
            }
            break;
        }
        
        case APP_WIFI_AP_STATE_START:
        {
            /* Preset the error state incase any following operations fail. */
                        
            /* Create the AP using the BSS and authentication context. */
            if (WDRV_WINC_STATUS_OK == WDRV_WINC_APStart(handle, &bssCtx, &authCtx, NULL, &APP_WiFiAPConnectNotifyCallback))
            {
                SYS_CONSOLE_PRINT( "AP started, you can connect to %s\r\n", appWiFiConfig.bss.ssid.name);
                SYS_CONSOLE_PRINT( "On the android device, connect to %s then run setting app\r\n", appWiFiConfig.bss.ssid.name);
                
                appSocketStaApState = APP_WIFI_AP_STATE_STARTED;
            }
            break;
        }
        case  APP_WIFI_AP_STATE_STARTED:
        {
            IPV4_ADDR                    apLastIp = {-1};
            IPV4_ADDR                    apIpAddr;
            apIpAddr.Val = TCPIP_STACK_NetAddress(netHdl);
            if ((apLastIp.Val != apIpAddr.Val) && (apLastIp.Val != 0))
            {
                apLastIp.Val = apIpAddr.Val;
                SYS_CONSOLE_MESSAGE(TCPIP_STACK_NetNameGet(netHdl));
                SYS_CONSOLE_MESSAGE("WINC AP Mode IP Address: ");
                SYS_CONSOLE_PRINT("%d.%d.%d.%d \r\n", apIpAddr.v[0], apIpAddr.v[1], apIpAddr.v[2], apIpAddr.v[3]);  
                APP_WiFiSocketCreate();
                appSocketStaApState = APP_WIFI_STA_AP_STATE_DONE;
            }              
            break;
        }
        case APP_WIFI_AP_WAIT_FOR_STA_IP:
        {  
            TCPIP_DHCPS_LEASE_HANDLE dhcpsLease = 0;
            TCPIP_DHCPS_LEASE_ENTRY dhcpsLeaseEntry;
            
            dhcpsLease = TCPIP_DHCPS_LeaseEntryGet(netHdl, &dhcpsLeaseEntry, dhcpsLease);

            if ((0 != dhcpsLease) && (0 == memcmp(dhcpsLeaseEntry.hwAdd.v, peerAddress.macAddress.addr, WDRV_WINC_MAC_ADDR_LEN)))
            {
                SYS_CONSOLE_PRINT("\r\n Connected STA MAC:%x:%x:%x:%x:%x:%x \r\n", dhcpsLeaseEntry.hwAdd.v[0], dhcpsLeaseEntry.hwAdd.v[1], dhcpsLeaseEntry.hwAdd.v[2], dhcpsLeaseEntry.hwAdd.v[3],dhcpsLeaseEntry.hwAdd.v[4],dhcpsLeaseEntry.hwAdd.v[5]);
                SYS_CONSOLE_PRINT("\r\n Connected STA IP:%d.%d.%d.%d \r\n", dhcpsLeaseEntry.ipAddress.v[0], dhcpsLeaseEntry.ipAddress.v[1], dhcpsLeaseEntry.ipAddress.v[2], dhcpsLeaseEntry.ipAddress.v[3]);
                appSocketStaApState = APP_WIFI_AP_SOCKET_LISTENING;
            }

            break;
        }
        
        case APP_WIFI_AP_SOCKET_LISTENING:
        {
            break;
        }

        case APP_WIFI_AP_STOPPED:
        {
            if (WDRV_WINC_STATUS_OK == WDRV_WINC_APStop(handle))
            {
                appSocketStaApState = APP_WIFI_STA_STATE_INIT;        
            }

            WDRV_MSDelay(500);
            break;
        }
        
        case APP_WIFI_STA_AP_STATE_DONE:
        {
            break;
        }
        
        case APP_WIFI_STA_AP_STATE_ERROR:
        {
            break;
        }
        
        default:
        {
            break;
        }     
    }
  
}
#endif


/*******************************************************************************
 End of File
 */

