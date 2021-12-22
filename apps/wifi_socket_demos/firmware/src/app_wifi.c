
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
#include "app_wifi.h"


#define APP_WIFI_SSID       "DEMO_AP"
#define APP_WIFI_AUTH       WDRV_WINC_AUTH_TYPE_WPA_PSK
#define APP_WIFI_BOOTMODE   APP_AP_MODE
#define APP_WIFI_CHANNEL    1
#define APP_WIFI_PSK        "12345678" 
#define APP_WIFI_DHCP_SRV_ADDR      "192.168.1.1"
#define APP_WIFI_DHCP_SRV_NETMASK   "255.255.255.0"
#define APP_TCP_LISTEN_PORT         80
#define APP_TCP_BUFFER_SIZE         1460

typedef enum
{
    /* Example's state machine's initial state. */
    APP_WIFI_STA_STATE_INIT=0,
    APP_WIFI_STA_STATE_SCANNING,
    APP_WIFI_STA_STATE_SCAN_GET_RESULTS,
    APP_WIFI_STA_AP_STATE_CONFIG,
    APP_WIFI_STA_STATE_CONNECT_REQ,
    APP_WIFI_STA_STATE_CONNECTING,
    APP_WIFI_STA_STATE_CONNECTED,
    APP_WIFI_STA_STATE_DISCONNECTED,
    APP_WIFI_AP_STATE_START,
    APP_WIFI_AP_STATE_STARTED,
    APP_WIFI_AP_SOCKET_LISTENING,
    APP_WIFI_AP_STOPPED,
    APP_WIFI_STA_AP_STATE_ERROR,
} APP_WIFI_STA_AP_STATES;

APP_WIFI_STA_AP_STATES appSocketStaApState; 
bool appWifiCredsUpdate;


typedef enum 
{
    APP_AP_MODE = 1,
    APP_STA_MODE,     
}APP_BOOT_MODES;

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
static SOCKET serverSocket = -1;
static SOCKET tcpClientSocket = -1;
static uint8_t recvBuffer[APP_TCP_BUFFER_SIZE];
static WDRV_WINC_AUTH_CONTEXT authCtx;
static WDRV_WINC_BSS_CONTEXT bssCtx;
static bool foundBSS;
static APP_CALLBACK pAPPWiFiSocketCallback;

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
        SYS_CONSOLE_PRINT("Bootmode:%d\r\n",appWiFiConfig.bootmode);
        SYS_CONSOLE_PRINT("SSID:%s\r\n",appWiFiConfig.bss.ssid.name);
        SYS_CONSOLE_PRINT("Auth_type:%d\r\n",appWiFiConfig.auth.authType);
        if(appWiFiConfig.auth.authType == WDRV_WINC_AUTH_TYPE_WPA_PSK)
        {
            SYS_CONSOLE_PRINT("Password:%s\r\n",appWiFiConfig.auth.authInfo.WPAPerPSK.key);
        }
        else if(appWiFiConfig.auth.authType == WDRV_WINC_AUTH_TYPE_802_1X_MSCHAPV2)
        {
            SYS_CONSOLE_PRINT("Password:%s\r\n",appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.password);
            SYS_CONSOLE_PRINT("Username:%s\r\n",appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.domainUserName);
        }
    }
    else if(!strcmp(argv[1], "help"))
    {
        SYS_CONSOLE_PRINT("wifi set <bootmode> <ssid> <auth_type> <pwd> <username/index>\r\n");
        SYS_CONSOLE_PRINT("bootmode : 1 - AP Mode, 2 - STA Mode\r\n");
        SYS_CONSOLE_PRINT("ssid : SSID of the WiFi\r\n");
        SYS_CONSOLE_PRINT("auth_type : 2 - WPA, 3 - WEP, 5 - Enterprise_MSCHAPV\r\n");
        SYS_CONSOLE_PRINT("pwd : Password of the WiFi\r\n");
        SYS_CONSOLE_PRINT("username/index : Username if auth_type is Enterprise_MSCHAPV or Key Index if auth_type is WEP\r\n");
    }
    return 0;
}


static const SYS_CMD_DESCRIPTOR AppWiFiCmdTbl[] =
{
    {"wifi", (SYS_CMD_FNC) APP_WiFiCMDProcess, ": Wifi commands processing"},
    
};

static void APP_WiFiSocketEventCallback(SOCKET socket, uint8_t messageType, void *pMessage)
{
    switch(messageType)
    {
        case SOCKET_MSG_BIND:
        {
            tstrSocketBindMsg *pBindMessage = (tstrSocketBindMsg*)pMessage;

            if ((NULL != pBindMessage) && (0 == pBindMessage->status))
            {
                SYS_CONSOLE_PRINT("Bind on socket %d successful, server_socket = %d\r\n", socket, serverSocket);
                listen(serverSocket, 0);
            }
            else
            {
                SYS_CONSOLE_PRINT("Bind on socket %d failed\r\n", socket);

                shutdown(serverSocket);
                serverSocket =  -1;
                appSocketStaApState = APP_WIFI_STA_AP_STATE_ERROR;
            }
            break;
        }

        case SOCKET_MSG_LISTEN:
        {
            tstrSocketListenMsg *pListenMessage = (tstrSocketListenMsg*)pMessage;

            if ((NULL != pListenMessage) && (0 == pListenMessage->status))
            {
                SYS_CONSOLE_PRINT("Listen on socket %d successful\r\n", socket);
                accept(serverSocket, NULL, NULL);
            }
            else
            {
                SYS_CONSOLE_PRINT("Listen on socket %d failed\r\n", socket);

                shutdown(serverSocket);
                serverSocket =  -1;
                appSocketStaApState = APP_WIFI_STA_AP_STATE_ERROR;
            }
            break;
        }

        case SOCKET_MSG_ACCEPT:
        {
            tstrSocketAcceptMsg *pAcceptMessage = (tstrSocketAcceptMsg*)pMessage;

            if (NULL != pAcceptMessage)
            {
                char s[20];

                accept(serverSocket, NULL, 0);
                tcpClientSocket = pAcceptMessage->sock;

                SYS_CONSOLE_PRINT("Connection from  %s:%d\r\n", inet_ntop(AF_INET, &pAcceptMessage->strAddr.sin_addr.s_addr, s, sizeof(s)), _ntohs(pAcceptMessage->strAddr.sin_port));

                recv(tcpClientSocket, recvBuffer, APP_TCP_BUFFER_SIZE, 0);
            }
            break;
        }

        case SOCKET_MSG_RECV:
        {
            tstrSocketRecvMsg *pRecvMessage = (tstrSocketRecvMsg*)pMessage;
            tstrM2mWifiWepParams wep_parameters = {0,0,{0}};

            if ((NULL != pRecvMessage) && (pRecvMessage->s16BufferSize > 0))
            {
                char *p;

                p = strtok((char *)pRecvMessage->pu8Buffer, ",");
                if ((p != NULL) && (!strncmp(p, "apply", 5)))
                {
                    char str_ssid[M2M_MAX_SSID_LEN], str_pw[M2M_MAX_PSK_LEN];
                    unsigned char sec_type = 0;

                    p = strtok(NULL, ",");
                    if (p)
                    {
                        strcpy(str_ssid, p);
                    }

                    p = strtok(NULL, ",");
                    if (p)
                    {
                        sec_type = atoi(p);
                    }

                    p = strtok(NULL, ",");
                    if (p)
                    {
                        strcpy(str_pw, p);
                    }
                    if (sec_type == M2M_WIFI_SEC_WEP)
                    {
                        wep_parameters.u8KeyIndx = 1;
                        wep_parameters.u8KeySz   = strlen(str_pw)+1;
                        memcpy(wep_parameters.au8WepKey,str_pw,wep_parameters.u8KeySz);
                    }
                    appWiFiConfig.bootmode = APP_STA_MODE;
                    memcpy((uint8_t *)appWiFiConfig.bss.ssid.name,str_ssid,strlen(str_ssid)+1);
                    appWiFiConfig.auth.authType = sec_type;

                    if(appWiFiConfig.auth.authType == WDRV_WINC_AUTH_TYPE_WPA_PSK)
                    {
                        memcpy((uint8_t *)appWiFiConfig.auth.authInfo.WPAPerPSK.key,str_pw,strlen(str_pw)+1);
                    } 
                    appSocketStaApState = APP_WIFI_AP_STOPPED;
                    (*pAPPWiFiSocketCallback)(APP_WIFI_PROVISION,NULL);
                }    
            }    
            break;
        }

        case SOCKET_MSG_SEND:
        {
            SYS_CONSOLE_PRINT("Socket %d send completed\r\n", socket);
            break;
        }

        default:
        {
            break;
        }
    }
}

static void APP_WiFiAPConnectNotifyCallback(DRV_HANDLE handle, WDRV_WINC_ASSOC_HANDLE assocHandle, WDRV_WINC_CONN_STATE currentState, WDRV_WINC_CONN_ERROR errorCode)
{
    if (WDRV_WINC_CONN_STATE_CONNECTED == currentState)
    {
        SYS_CONSOLE_PRINT("AP Mode: Station connected\r\n");
        (*pAPPWiFiSocketCallback)(APP_WIFI_CONNECT,NULL);

    }
    else if (WDRV_WINC_CONN_STATE_DISCONNECTED == currentState)
    {
        SYS_CONSOLE_PRINT("AP Mode: Station disconnected\r\n");
        (*pAPPWiFiSocketCallback)(APP_WIFI_DISCONNECT,NULL);
    }
}

static void APP_WiFiDHCPAddressEventCallback(DRV_HANDLE handle, uint32_t ipAddress)
{
    char s[20];
    (*pAPPWiFiSocketCallback)(APP_WIFI_CONNECT,NULL);
    SYS_CONSOLE_PRINT("IP address is %s\r\n", inet_ntop(AF_INET, &ipAddress, s, sizeof(s)));
}

static void APP_WiFiConnectNotifyCallback(DRV_HANDLE handle, WDRV_WINC_ASSOC_HANDLE assocHandle, WDRV_WINC_CONN_STATE currentState, WDRV_WINC_CONN_ERROR errorCode)
{
    if (WDRV_WINC_CONN_STATE_CONNECTED == currentState)
    {
        /* When connected reset the ICMP echo request counter and state. */
        SYS_CONSOLE_PRINT("Connected\r\n");
        //(*pAPPWiFiSocketCallback)(APP_WIFI_CONNECT,NULL);
        appSocketStaApState = APP_WIFI_STA_STATE_CONNECTED;
        appWifiCredsUpdate = false;
    }
    else if (WDRV_WINC_CONN_STATE_DISCONNECTED == currentState)
    {
        SYS_CONSOLE_PRINT("Disconnected\r\n");
        (*pAPPWiFiSocketCallback)(APP_WIFI_DISCONNECT,NULL);
        if (appWifiCredsUpdate == false)
        {
            appSocketStaApState = APP_WIFI_STA_STATE_CONNECT_REQ;
        }
//        if (WDRV_WINC_STATUS_OK == WDRV_WINC_BSSConnect(handle, &bssCtx, &authCtx, &APP_WiFiConnectNotifyCallback))
//        {
//            appSocketStaApState = APP_WIFI_STA_STATE_CONNECTING;
//        }
    }
}

void APP_WiFiProvision(uint8_t auth,uint8_t *ssid,uint8_t *psk)
{
    appWiFiConfig.bootmode = APP_STA_MODE;
    appWiFiConfig.auth.authType = auth;
    strcpy((char *)appWiFiConfig.bss.ssid.name,(const char *)ssid);
    strcpy((char *)appWiFiConfig.auth.authInfo.WPAPerPSK.key,(const char *)psk);
    appSocketStaApState = APP_WIFI_STA_STATE_INIT;
}

void APP_WiFiInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    
    appWiFiConfig.bootmode = APP_WIFI_BOOTMODE;
    pAPPWiFiSocketCallback = pAPPWiFiCallback;
    memcpy((uint8_t *)appWiFiConfig.bss.ssid.name,APP_WIFI_SSID,sizeof(APP_WIFI_SSID));
    appWiFiConfig.auth.authType = APP_WIFI_AUTH;
    memcpy((uint8_t *)appWiFiConfig.auth.authInfo.WPAPerPSK.key,APP_WIFI_PSK,sizeof(APP_WIFI_PSK));
    SYS_CMD_ADDGRP(AppWiFiCmdTbl, sizeof (AppWiFiCmdTbl) / sizeof (*AppWiFiCmdTbl), "wifi", ": WiFi commands"); 
    appSocketStaApState = APP_WIFI_STA_STATE_INIT;
    appWifiCredsUpdate = false;
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
                /* Enable use of DHCP for network configuration, DHCP is the default
                 but this also registers the callback for notifications. */

                WDRV_WINC_IPUseDHCPSet(handle, &APP_WiFiDHCPAddressEventCallback);

                /* Start a BSS find operation on all channels. */
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
                SYS_CONSOLE_PRINT("Scan complete, %d AP(s) found\r\n", WDRV_WINC_BSSFindGetNumBSSResults(handle));
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
                SYS_CONSOLE_PRINT("AP found: RSSI: %d %s\r\n", BSSInfo.rssi, BSSInfo.ctx.ssid.name);

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
                        SYS_CONSOLE_PRINT("Target AP found, trying to connect\r\n");
                        appSocketStaApState = APP_WIFI_STA_AP_STATE_CONFIG;
                    }
                    else
                    {
                        SYS_CONSOLE_PRINT("Target BSS not found\r\n");
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
            appSocketStaApState = APP_WIFI_STA_AP_STATE_ERROR;

            /* Initialize the BSS context to use default values. */

            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BSSCtxSetDefaults(&bssCtx))
            {
                break;
            }

            /* Update BSS context with target SSID for connection. */

            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BSSCtxSetSSID(&bssCtx, (uint8_t*)appWiFiConfig.bss.ssid.name, strlen((const char*)appWiFiConfig.bss.ssid.name)))
            {
                break;
            }

            switch (appWiFiConfig.auth.authType)
            {
                case WDRV_WINC_AUTH_TYPE_OPEN:
                {
                    /* Initialize the authentication context for open mode. */

                    if (WDRV_WINC_STATUS_OK != WDRV_WINC_AuthCtxSetOpen(&authCtx))
                    {
                        break;
                    }
                    break;
                }
                case WDRV_WINC_AUTH_TYPE_WPA_PSK:
                {
                    /* Initialize the authentication context for WPA. */

                    if (WDRV_WINC_STATUS_OK != WDRV_WINC_AuthCtxSetWPA(&authCtx, (uint8_t*)appWiFiConfig.auth.authInfo.WPAPerPSK.key, strlen((const char*)appWiFiConfig.auth.authInfo.WPAPerPSK.key)))
                    {
                        break;
                    }
                    break;
                }
                case WDRV_WINC_AUTH_TYPE_802_1X_MSCHAPV2:
                {
                    /* Initialize the authentication context for WPA. */

                    if (WDRV_WINC_STATUS_OK != WDRV_WINC_AuthCtxSetWPAEnterpriseMSCHAPv2(&authCtx, (char*)appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.domainUserName, (uint8_t*)appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.password, strlen((const char *)appWiFiConfig.auth.authInfo.WPAEntMSCHAPv2.password), false))
                    {
                        break;
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
            
            if( APP_AP_MODE == appWiFiConfig.bootmode)
            {
                if (WDRV_WINC_STATUS_OK != WDRV_WINC_BSSCtxSetChannel(&bssCtx, APP_WIFI_CHANNEL))
                {
                    break;
                }
                /* Enable use of DHCP for network configuration, DHCP is the default
                 but this also registers the callback for notifications. */

                if (WDRV_WINC_STATUS_OK != WDRV_WINC_IPDHCPServerConfigure(handle, inet_addr(APP_WIFI_DHCP_SRV_ADDR), inet_addr(APP_WIFI_DHCP_SRV_NETMASK), &APP_WiFiDHCPAddressEventCallback))
                {
                    break;
                }
                appSocketStaApState = APP_WIFI_AP_STATE_START;
            }
            else
            {
                appSocketStaApState = APP_WIFI_STA_STATE_CONNECT_REQ;
            }
            
            break;
        }
        
        case APP_WIFI_STA_STATE_CONNECT_REQ:
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
            /* Wait for the BSS connect to trigger the callback and update
             the connection state. */
            break;
        }

        case APP_WIFI_STA_STATE_CONNECTED:
        {
            /* Wait for the IP link to become active. */

            if (false == WDRV_WINC_IPLinkActive(handle))
            {
                break;
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

        case APP_WIFI_STA_AP_STATE_ERROR:
        {
            break;
        }
        case APP_WIFI_AP_STATE_START:
        {
            /* Preset the error state incase any following operations fail. */
            appSocketStaApState = APP_WIFI_STA_AP_STATE_ERROR;
            
            /* Register callback for socket events. */
            WDRV_WINC_SocketRegisterEventCallback(handle, &APP_WiFiSocketEventCallback);
            
            /* Create the AP using the BSS and authentication context. */
            if (WDRV_WINC_STATUS_OK == WDRV_WINC_APStart(handle, &bssCtx, &authCtx, NULL, &APP_WiFiAPConnectNotifyCallback))
            {
                SYS_CONSOLE_PRINT("AP started, you can connect to %s\r\n", appWiFiConfig.bss.ssid.name);
                SYS_CONSOLE_PRINT("On the android device, connect to %s then run setting app\r\n", appWiFiConfig.bss.ssid.name);
                
                appSocketStaApState = APP_WIFI_AP_STATE_STARTED;
            }
            break;
        }

        case  APP_WIFI_AP_STATE_STARTED:
        {
           /* Create the server socket. */

            serverSocket = socket(AF_INET, SOCK_STREAM, 0);

            if (serverSocket >= 0)
            {
                struct sockaddr_in addr;

                /* Listen on the socket. */

                addr.sin_family = AF_INET;
                addr.sin_port = _htons(APP_TCP_LISTEN_PORT);
                addr.sin_addr.s_addr = 0;

                bind(serverSocket, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));

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
                if (-1 != serverSocket)
                {
                    shutdown(serverSocket);
                    serverSocket = -1;
                }
                appSocketStaApState = APP_WIFI_STA_STATE_INIT;         
            }

            WDRV_MSDelay(500);
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

