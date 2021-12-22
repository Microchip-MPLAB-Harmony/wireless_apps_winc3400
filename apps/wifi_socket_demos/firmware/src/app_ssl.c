/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ssl.c

  Summary:
    This file contains the source code for the MPLAB Harmony wifi SSL application.

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

#include "app.h"
#ifdef APP_SSL
#include "wdrv_winc_client_api.h"
#include "app_ssl.h"

#define SOCK_HOST_NAME              "www.google.com"
#define SOCK_HOST_PORT              443
#define SOCK_TCP_RECV_BUFFER_SIZE   1460
#define SOCK_SERVER_NAME            64

#define APP_URL_LENGTH              14
#define MAX_URL_SIZE                100

typedef enum {
    APP_SSL_STATE_PARSE_URL = 0,
    APP_SSL_STATE_INIT,
    APP_SSL_STATE_RESOLVE_IP,
    APP_SSL_STATE_WAITING_FOR_DNS_RESOLVE,
    APP_SSL_STATE_CONNECT,
    APP_SSL_STATE_CONNECTTING,
    APP_SSL_STATE_CONNECTED,
    APP_SSL_STATE_IDLE,
    APP_SSL_STATE_ERROR,
} APP_SSL_STATES;

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

typedef struct {
    uint32_t                    hostIp;
    APP_SSL_STATES              ssl_state;
    uint16_t                    hostPort;
    char                        hostName[SOCK_SERVER_NAME];
    uint8_t                     recvBuffer[SOCK_TCP_RECV_BUFFER_SIZE];    
}SOCKETMODE_SOCK_Config;

static SOCKETMODE_SOCK_Config  g_sSockConfig;
SOCKET                  ssl_g_clientSocket = -1;
uint32_t                ssl_g_u32SockStatus = 0;

char * host;
char * path;
uint16_t port;
char APP_URL_Buffer[MAX_URL_SIZE];

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************
static void SocketMode_ExampleSocketResolverCallback(uint8_t *pu8DomainName, uint32_t u32IP)
{
    char s[SOCK_SERVER_NAME];

    SYS_CONSOLE_PRINT("%s: IP address is %s\r\n", pu8DomainName, inet_ntop(AF_INET, &u32IP, s, sizeof(s)));

    g_sSockConfig.hostIp = u32IP;
    
    g_sSockConfig.ssl_state = APP_SSL_STATE_CONNECT;
    WDRV_MSDelay(1000);
}

static int8_t SocketMode_ExampleSocketConnect(void)
{
	struct sockaddr_in addr_in;

	addr_in.sin_family = AF_INET;
	addr_in.sin_port = _htons(SOCK_HOST_PORT);
	addr_in.sin_addr.s_addr = g_sSockConfig.hostIp;

	/* Create secure socket */
	if (ssl_g_clientSocket < 0) {
		ssl_g_clientSocket = socket(AF_INET, SOCK_STREAM, SOCKET_FLAGS_SSL);
	}

	/* Check if socket was created successfully */
	if (ssl_g_clientSocket == -1) {
		SYS_CONSOLE_PRINT("socket error.\r\n");
		shutdown(ssl_g_clientSocket);
		return -1;
	}

	/* If success, connect to socket */
	if (connect(ssl_g_clientSocket, (struct sockaddr *)&addr_in, sizeof(struct sockaddr_in)) != SOCK_ERR_NO_ERROR) {
		SYS_CONSOLE_PRINT("connect error.\r\n");
		return SOCK_ERR_INVALID;
	}

	/* Success */
	return SOCK_ERR_NO_ERROR;
}


static void SocketMode_ExampleSslClientEventCallback(SOCKET socket, uint8_t messageType, void *pMessage)
{
    switch(messageType)
    {
        case SOCKET_MSG_RECV:
        {
            tstrSocketRecvMsg *pRecvMessage = (tstrSocketRecvMsg*)pMessage;
            if ((NULL != pRecvMessage) && (pRecvMessage->s16BufferSize > 0))
            {
                if (strstr((char *)(pRecvMessage->pu8Buffer), "</html>") != 0) {
                    SYS_CONSOLE_PRINT("TcpClientCallback(): End of Html Page\r\n");
                    shutdown(ssl_g_clientSocket);
                    ssl_g_clientSocket = -1;
                    break;
                }
                memset(g_sSockConfig.recvBuffer, 0, SOCK_TCP_RECV_BUFFER_SIZE);
                recv(ssl_g_clientSocket, g_sSockConfig.recvBuffer, SOCK_TCP_RECV_BUFFER_SIZE, 0);
            }
            break;
        }

        case SOCKET_MSG_SEND:
        {
            int16_t *ps16Rcvd = (int16_t *)pMessage;
            if(*ps16Rcvd <= 0)
                SYS_CONSOLE_PRINT( "Socket %d send failed %d)\r\n", socket, *ps16Rcvd);
            break;
        }

        case SOCKET_MSG_CONNECT:
        {            
            tstrSocketConnectMsg *pstrConnMsg = (tstrSocketConnectMsg *)pMessage;
            char networkBuffer[256];
            if(pstrConnMsg->s8Error != 0)
            {
                SYS_CONSOLE_PRINT( "Socket %d Connect failed; Error = %d\r\n\n", socket, pstrConnMsg->s8Error);
                if (SOCK_ERR_CONN_ABORTED == pstrConnMsg->s8Error)
                {
                    shutdown(ssl_g_clientSocket);
                    ssl_g_clientSocket = -1;
                    break;
                }
            }
            
            SYS_CONSOLE_PRINT( "Socket %d Connected\r\n\n", socket);

            memset(networkBuffer, 0, sizeof(networkBuffer));
            sprintf(networkBuffer, "GET / HTTP/1.1\r\n"
                    "Host: %s\r\n"
                    "Connection: close\r\n\r\n", g_sSockConfig.hostName);
            recv(ssl_g_clientSocket, g_sSockConfig.recvBuffer, SOCK_TCP_RECV_BUFFER_SIZE, 0);
            if(send(ssl_g_clientSocket, (uint8_t*) networkBuffer, strlen(networkBuffer), 0) == SOCK_ERR_NO_ERROR)
            {
                SYS_CONSOLE_PRINT("TcpClientCallback(): Start of Html Page\r\n");
            }
            else
            {
                SYS_CONSOLE_PRINT( "Send() FAILED\r\n");                
            }
            
            g_sSockConfig.ssl_state = APP_SSL_STATE_CONNECTED;
            ssl_g_u32SockStatus = 1;
            
            break;
        }

        default:
        {
            break;
        }
    }
}

int32_t _APP_ParseUrl(char *uri, char **host, char **path, uint16_t * port) {
    char * pos;
    pos = strstr(uri, "://"); //Check to see if its a proper URL


    if (!pos) {
        return -1;
    }
    *pos = '\0';

//    uint32_t protoHash = fnv_32a_hash(uri, strlen(uri));
//    //SYS_CONSOLE_PRINT("Protocol Hash '%s' is 0x%x\r\n", uri, protoHash);
//
//    switch (protoHash) {
//        case APP_HTTP_FNV:
//            *port = 80;
//            break;
//        case APP_HTTPS_FNV:
//            *port = 443;
//            break;
//    }


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
            SYS_CONSOLE_PRINT("pos_2\r\n");
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

static int APP_SslCMDProcess
(
    SYS_CMD_DEVICE_NODE* pCmdIO, 
    int argc, 
    char** argv
) 
{
   if (argc != 2)
   {
       return -1;
   }
   
   if (!strcmp(argv[1], "help"))
   {
        SYS_CONSOLE_PRINT("ssl <url>\r\n");
   }
   else
   {
       strncpy(APP_URL_Buffer, argv[1], MAX_URL_SIZE);
       g_sSockConfig.ssl_state = APP_SSL_STATE_PARSE_URL;
   }
   return 0;
}

static const SYS_CMD_DESCRIPTOR AppSslCmdTbl[] =
{
    {"ssl", (SYS_CMD_FNC) APP_SslCMDProcess, ": Socket mode SSL commands processing"},
    
};


void APP_SSL_Initialize(APP_CALLBACK pfAPPWiFiCallback)
{
    g_sSockConfig.hostPort = SOCK_HOST_PORT;
    ssl_g_clientSocket = -1;
    memset(APP_URL_Buffer, 0, MAX_URL_SIZE);
    SYS_CMD_ADDGRP(AppSslCmdTbl, sizeof (AppSslCmdTbl) / sizeof (*AppSslCmdTbl), "ssl", ": Socket mode SSL commands"); 
    g_sSockConfig.ssl_state = APP_SSL_STATE_IDLE;
}




// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

void APP_SSL_Tasks(DRV_HANDLE wdrvHandle)
{
    switch (g_sSockConfig.ssl_state)
    {
        case APP_SSL_STATE_PARSE_URL:
        {
            if (APP_URL_Buffer[0] != '\0')
            {
                memset(g_sSockConfig.hostName,0,SOCK_SERVER_NAME);
                memcpy(g_sSockConfig.hostName,&APP_URL_Buffer[8],strlen(APP_URL_Buffer)-9);
                g_sSockConfig.ssl_state = APP_SSL_STATE_INIT;
            }
            break;
        }
        case APP_SSL_STATE_INIT:
        {
            if (false == WDRV_WINC_IPLinkActive(wdrvHandle))
            {
                break;
            }
            
            WDRV_WINC_SocketRegisterResolverCallback(wdrvHandle, &SocketMode_ExampleSocketResolverCallback);
            g_sSockConfig.ssl_state = APP_SSL_STATE_RESOLVE_IP;
        }
        break;
        
        case APP_SSL_STATE_RESOLVE_IP:
        {
            if (gethostbyname(g_sSockConfig.hostName) == SOCK_ERR_NO_ERROR)
            {
                g_sSockConfig.ssl_state = APP_SSL_STATE_WAITING_FOR_DNS_RESOLVE;
            }
        }
        break;
        
        case APP_SSL_STATE_WAITING_FOR_DNS_RESOLVE:
        {
            
        }
        break;            

        case APP_SSL_STATE_CONNECT:
        {
            /* Register callback for socket events. */
            WDRV_WINC_SocketRegisterEventCallback(wdrvHandle, &SocketMode_ExampleSslClientEventCallback);
            
            SocketMode_ExampleSocketConnect();
            
            g_sSockConfig.ssl_state = APP_SSL_STATE_CONNECTTING;
        }
        break;            
        
        case APP_SSL_STATE_CONNECTTING:
        {
            
        }
        break;            
        
        case APP_SSL_STATE_CONNECTED:
        {
            
        }
        break; 
        case APP_SSL_STATE_IDLE:
        {
            
        }
        break; 
        
        case APP_SSL_STATE_ERROR:
        {
            
        }
        break;            
    }
}
#endif//#ifdef APP_SSL
/*******************************************************************************
 End of File
 */
