/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    ssl.c

  Summary:
    This file contains the source code for the MPLAB Harmony wifi ssl application.

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
#ifdef APP_SSL
#include "wdrv_winc_client_api.h"
#include "app_ssl.h"
#include "tcpip/tcpip.h"
#include <tcpip/src/hash_fnv.h>

typedef enum
{
    APP_WIFI_SSL_PARSE_URL = 0,
    APP_WIFI_SSL_STATE_WAIT_SNTP,
    APP_WIFI_SSL_STATE_START,
    APP_WIFI_SSL_STATE_RESOLVE_DNS,
    APP_WIFI_SSL_STATE_WAIT_ON_DNS,
    APP_WIFI_SSL_STATE_START_CONNECTION,
    APP_WIFI_SSL_STATE_WAIT_FOR_CONNECTION,
    APP_WIFI_SSL_STATE_WAIT_FOR_SSL_CONNECT,
    APP_WIFI_SSL_STATE_DONE,
    APP_WIFI_SSL_STATE_ERROR,
    APP_WIFI_SSL_STATE_IDLE
} APP_SSL_STATES;

static APP_SSL_STATES  appSslState; 

// Maximum milliseconds to wait for TCP connection success
#define TCP_CLIENT_CONNECTION_TIMEOUT_MS 	8000

// hash values for http vs https
#define APP_HTTP_FNV  0xc96448a5
#define APP_HTTPS_FNV 0xdedea8e2


/* MPLAB Harmony specific components */
NET_PRES_SKT_HANDLE_T net_pres_socket;
NET_PRES_SKT_ERROR_T net_pres_sock_error;
uint32_t sockConnTimeStamp;
IP_MULTI_ADDRESS hostAddress;
char * host;
char * path;
uint16_t port;
char APP_URL_Buffer[MAX_URL_SIZE];

int32_t _APP_ParseUrl(char *uri, char **host, char **path, uint16_t * port);

static int APP_WiFiSslCMDProcess
(
    SYS_CMD_DEVICE_NODE* pCmdIO, 
    int argc, 
    char** argv
) 
{
   if ((argc >= 1) && (!strcmp(argv[1], "help")))
   {
        SYS_CONSOLE_PRINT("Usage: ssl <url>\r\n");
        SYS_CONSOLE_PRINT("Ex: ssl https://www.google.com/\r\n");
   }
   else if (argc >= 1)
   {
       appSslState = APP_WIFI_SSL_PARSE_URL;
       strncpy(APP_URL_Buffer, argv[1], MAX_URL_SIZE);
   }
    
   return 0;
}
static const SYS_CMD_DESCRIPTOR AppWiFiSslCmdTbl[] =
{
    {"ssl", (SYS_CMD_FNC) APP_WiFiSslCMDProcess, ": Bypass mode SSL commands processing"},
    
};

void APP_SslInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    SYS_CMD_ADDGRP(AppWiFiSslCmdTbl, sizeof (AppWiFiSslCmdTbl) / sizeof (*AppWiFiSslCmdTbl), "ssl", ": Socket mode WiFi SSL commands"); 
    memset(APP_URL_Buffer, 0, MAX_URL_SIZE);
    net_pres_socket = NET_PRES_INVALID_SOCKET;
    sockConnTimeStamp = 0;
    appSslState = APP_WIFI_SSL_STATE_IDLE;
}


int32_t _APP_ParseUrl(char *uri, char **host, char **path, uint16_t * port) {
    char * pos;
    pos = strstr(uri, "://"); //Check to see if its a proper URL


    if (!pos) {
        return -1;
    }
    *pos = '\0';

    uint32_t protoHash = fnv_32a_hash(uri, strlen(uri));
    //SYS_CONSOLE_PRINT("Protocol Hash '%s' is 0x%x\r\n", uri, protoHash);

    switch (protoHash) {
        case APP_HTTP_FNV:
            *port = 80;
            break;
        case APP_HTTPS_FNV:
            *port = 443;
            break;
    }


    *host = pos + 3; // This is where the host should start
    pos = *host;
    if (**host == '[') {
        // IPv6 address
        pos = strchr(*host, ']');
        *host = *host + 1;
        *pos = '\0';
        pos++;
    } else {
        char * pos2 = strchr(pos, ':');
        if (pos2 != NULL) {
            pos = pos2;
        } else {
            pos2 = strchr(pos, '/');
            if (pos2 == NULL) {
                return -1;
            }
            pos = pos2;
        }
    }

    if (*pos != ':') {
        pos = strchr(pos, '/');
        if (!pos) {
            *path = NULL;
        } else {
            *pos = '\0';
            *path = pos + 1;
        }
    } else {
        *pos = '\0';
        char * portc = pos + 1;

        pos = strchr(portc, '/');
        if (!pos) {
            *path = NULL;
        } else {
            *pos = '\0';
            *path = pos + 1;
        }
        *port = atoi(portc);
    }
    return 0;
}


// Non-blocking function for DNS lookup and starting TCP connection
void resolve_host_and_connect(DRV_HANDLE handle)
{
    switch ( appSslState )
    {
        case APP_WIFI_SSL_PARSE_URL:
        {
            if (APP_URL_Buffer[0] != '\0')
            {
                if(_APP_ParseUrl(APP_URL_Buffer, &host, &path, &port) != 0)
                {
                    SYS_CONSOLE_PRINT("Could not parse URL '%s'\r\n", APP_URL_Buffer);
                    appSslState = APP_WIFI_SSL_STATE_ERROR;
                    memset(APP_URL_Buffer, 0, MAX_URL_SIZE);
                }
                else
                {
                    appSslState = APP_WIFI_SSL_STATE_WAIT_SNTP;
                }
            }
            break;
        }
        case APP_WIFI_SSL_STATE_WAIT_SNTP:
        {
            TCPIP_SNTP_RESULT res = TCPIP_SNTP_TimeStampStatus();
            if(SNTP_RES_OK == res)
            {
                appSslState = APP_WIFI_SSL_STATE_START;
            }
            break;
        }
        case APP_WIFI_SSL_STATE_START:
        {
            /* First check to see if host is an IPv4 address*/
            if (TCPIP_Helper_StringToIPAddress(host, &hostAddress.v4Add))
            {
                SYS_CONSOLE_PRINT("Using IPv4 Address: %d.%d.%d.%d for host '%s'\r\n", 
                        hostAddress.v4Add.v[0], hostAddress.v4Add.v[1], 
                        hostAddress.v4Add.v[2], hostAddress.v4Add.v[3], host);
                appSslState = APP_WIFI_SSL_STATE_START_CONNECTION;
            }
            else
            {
                appSslState = APP_WIFI_SSL_STATE_RESOLVE_DNS;
            }
            break;
        }
        
        case APP_WIFI_SSL_STATE_RESOLVE_DNS:
        {
            TCPIP_DNS_RESULT result;
            SYS_CONSOLE_PRINT("Using DNS to Resolve host: '%s'\r\n",host);
            result = TCPIP_DNS_Resolve(host, TCPIP_DNS_TYPE_A);
            SYS_ASSERT(result != TCPIP_DNS_RES_NAME_IS_IPADDRESS, "DNS Result is TCPIP_DNS_RES_NAME_IS_IPADDRESS, which should not happen since we already checked");
            if (result >= 0)
            {
                appSslState = APP_WIFI_SSL_STATE_WAIT_ON_DNS;
            }
            else
            {
                SYS_CONSOLE_PRINT("DNS Query returned %d Aborting\r\n",result);
                appSslState = APP_WIFI_SSL_STATE_ERROR;
            }            
            break;
        }

        case APP_WIFI_SSL_STATE_WAIT_ON_DNS:
        {
            TCPIP_DNS_RESULT result = TCPIP_DNS_IsResolved(host, &hostAddress, IP_ADDRESS_TYPE_IPV4);
            switch (result)
            {
                case TCPIP_DNS_RES_PENDING:
                {
                    break;
                }
                
                case TCPIP_DNS_RES_OK:
                {
                    SYS_CONSOLE_PRINT("Host IPv4 Address: %d.%d.%d.%d\r\n",
                        hostAddress.v4Add.v[0], hostAddress.v4Add.v[1], 
                        hostAddress.v4Add.v[2], hostAddress.v4Add.v[3]);
                    appSslState = APP_WIFI_SSL_STATE_START_CONNECTION;
                    break;
                }
                
                case TCPIP_DNS_RES_SERVER_TMO:
                case TCPIP_DNS_RES_NO_IP_ENTRY:
                default:
                {
                    SYS_CONSOLE_PRINT("TCPIP_DNS_IsResolved returned failure\r\n");
                    appSslState = APP_WIFI_SSL_STATE_ERROR;
                    break;
                }
            }
            break;
        }        

        case APP_WIFI_SSL_STATE_START_CONNECTION:
        {
            // If we're here it means that we have a proper address.
            // check if the socket handle is available
            if (net_pres_socket == NET_PRES_INVALID_SOCKET)
            {
                net_pres_socket = NET_PRES_SocketOpen(0, NET_PRES_SKT_UNENCRYPTED_STREAM_CLIENT, 
                        IP_ADDRESS_TYPE_IPV4, port, (NET_PRES_ADDRESS *)&hostAddress, 
                        &net_pres_sock_error);
                NET_PRES_SocketWasReset(net_pres_socket);
                if (net_pres_socket == NET_PRES_INVALID_SOCKET)
                {
                    SYS_CONSOLE_PRINT("Error %d: Could not create socket - aborting\r\n",net_pres_sock_error);
                    appSslState = APP_WIFI_SSL_STATE_ERROR;
                }
                else
                {
                    SYS_CONSOLE_PRINT("Starting connection on port: %d\r\n",port);
                    appSslState = APP_WIFI_SSL_STATE_WAIT_FOR_CONNECTION;
                    sockConnTimeStamp = SYS_TIME_CounterGet();
                }
            }
            else
            {
                SYS_CONSOLE_PRINT("Sorry! This demo only shows one active connection\r\n");
                appSslState = APP_WIFI_SSL_STATE_DONE;
            }
            break;
        }
        
        case APP_WIFI_SSL_STATE_WAIT_FOR_CONNECTION:
        {
            if (NET_PRES_SocketIsConnected(net_pres_socket))
            {
                // connected                
                SYS_CONSOLE_PRINT("Connection Opened\r\n");
                
                // check if this is https url
                if (APP_URL_Buffer[4] == 's')
                {
                    SYS_CONSOLE_MESSAGE("Starting SSL Negotiation\r\n");
                    if (!NET_PRES_SocketEncryptSocket(net_pres_socket)) 
                    {
                        SYS_CONSOLE_PRINT("SSL Create Connection Failed - Aborting\r\n");
                        appSslState = APP_WIFI_SSL_STATE_ERROR;
                    } 
                    else 
                    {
                        appSslState = APP_WIFI_SSL_STATE_WAIT_FOR_SSL_CONNECT;
                    } 
                }
                else
                {
                    appSslState = APP_WIFI_SSL_STATE_DONE;
                }
                
            }
            else if (SYS_TIME_CountToMS(SYS_TIME_CounterGet() - sockConnTimeStamp) >= TCP_CLIENT_CONNECTION_TIMEOUT_MS)
            {
                SYS_CONSOLE_PRINT("Socket connect timeout!\r\n");
                appSslState = APP_WIFI_SSL_STATE_ERROR;
                NET_PRES_SocketClose(net_pres_socket);
            }
            
            break;
        }
        
        case APP_WIFI_SSL_STATE_WAIT_FOR_SSL_CONNECT:
        {
            if (NET_PRES_SocketIsNegotiatingEncryption(net_pres_socket)) 
            {
                break;
            }
            if (!NET_PRES_SocketIsSecure(net_pres_socket)) 
            {
                SYS_CONSOLE_PRINT("SSL Connection Negotiation Failed - Aborting\r\n");
                appSslState = APP_WIFI_SSL_STATE_ERROR;
                break;
            }
            SYS_CONSOLE_PRINT("SSL Connection Complete\r\n");
            appSslState = APP_WIFI_SSL_STATE_DONE;
            break;
        }

        case APP_WIFI_SSL_STATE_DONE:
        {
            // Secure client socket connected                
            SYS_CONSOLE_PRINT("Closing socket\r\n");
            NET_PRES_SocketClose(net_pres_socket);
            net_pres_socket = NET_PRES_INVALID_SOCKET;
            appSslState = APP_WIFI_SSL_STATE_IDLE;
            break;
        }

        case APP_WIFI_SSL_STATE_ERROR:
        {
            // either dns or socket connection error
            SYS_CONSOLE_PRINT("Closing socket\r\n");
            NET_PRES_SocketClose(net_pres_socket);
            net_pres_socket = NET_PRES_INVALID_SOCKET;
            appSslState = APP_WIFI_SSL_STATE_IDLE;
            break;
        }
        
        case APP_WIFI_SSL_STATE_IDLE:
        {
            break;
        }

        /* The default state should never be executed. */
        default:
        {
            SYS_CONSOLE_PRINT("NET PRES state machine error: default executed\r\n");
            appSslState = APP_WIFI_SSL_STATE_ERROR;
        }
    }        
    
}

void APP_SslTasks(DRV_HANDLE handle)
{
    resolve_host_and_connect(handle);
}
#endif 
/* *****************************************************************************
 End of File
 */
