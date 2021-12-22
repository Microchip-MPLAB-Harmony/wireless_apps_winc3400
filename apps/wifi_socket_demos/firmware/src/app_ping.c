/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ping.c

  Summary:
    This file contains the source code for the MPLAB Harmony wifi ping application.

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
#ifdef APP_PING
#include "wdrv_winc_client_api.h"
#include "app_ping.h"

#define APP_PING_ADDR    "192.168.169.64"
#define APP_PING_INTERVAL 10


typedef enum
{
    /* Example's state machine's initial state. */
    APP_WIFI_PING_STATE_START=0,
    APP_WIFI_PING_STATE_WAIT,
    APP_WIFI_PING_STATE_STOP,
} APP_WIFI_PING_STATES;

static APP_WIFI_PING_STATES appPingState; 

static uint32_t appPingReplyTime;
static uint32_t appPingIpAddr;      
static char appPingIpCnt = 0 ;

static int APP_WiFiPingCMDProcess
(
    SYS_CMD_DEVICE_NODE* pCmdIO, 
    int argc, 
    char** argv
) 
{
   if ((argc >= 1) && (!strcmp(argv[1], "help")))
   {
        SYS_CONSOLE_PRINT("ping <IP Address> <count>\r\n");
   }
   else
   {
       uint32_t appPingAddr[4];
       if (argc == 3)
            appPingIpCnt = strtol(argv[2], NULL, 0);
       else
            appPingIpCnt = 4; // default to 4
       char *p=strtok(argv[1],".");
       appPingAddr[0]=(strtol(p, NULL, 0));
       p=strtok(NULL,".");
       appPingAddr[1]=(strtol(p, NULL, 0)<<8);
       p=strtok(NULL,".");
       appPingAddr[2]=(strtol(p, NULL, 0)<<16);
       p=strtok(NULL,".");
       appPingAddr[3]=(strtol(p, NULL, 0)<<24);
       
       appPingState = APP_WIFI_PING_STATE_START;
       appPingIpAddr = (appPingAddr[0])|(appPingAddr[1])| (appPingAddr[2])|(appPingAddr[3]);
       
   }
   return 0;
}
static const SYS_CMD_DESCRIPTOR AppWiFiPingCmdTbl[] =
{
    {"sping", (SYS_CMD_FNC) APP_WiFiPingCMDProcess, ": Socket mode ping commands processing"},
    
};

static void APP_WiFiPingResponseCallback(DRV_HANDLE handle, uint32_t ipAddress, uint32_t RTT, WDRV_WINC_ICMP_ECHO_STATUS statusCode)
{
    /* Report the results of the ICMP echo request. */
    switch (statusCode)
    {
        case WDRV_WINC_ICMP_ECHO_STATUS_SUCCESS:
        {
            SYS_CONSOLE_PRINT("ICMP echo request successful; RTT = %ld ms\r\n", RTT);
            break;
        }

        case WDRV_WINC_ICMP_ECHO_STATUS_UNREACH:
        {
            SYS_CONSOLE_PRINT("ICMP echo request failed; destination unreachable\r\n");
            break;
        }

        case WDRV_WINC_ICMP_ECHO_STATUS_TIMEOUT:
        {
            SYS_CONSOLE_PRINT("ICMP echo request failed; timeout\r\n");
            break;
        }
    }
    /* Reduce the number of ICMP echo requests remaining and store the time
     this response was received. */
    appPingIpCnt --;
    if(appPingIpCnt > 0)
    {
       appPingReplyTime = SYS_TIME_CounterGet();
    }
    else
    {
        appPingState = APP_WIFI_PING_STATE_STOP;
    }
}


void APP_PingInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    SYS_CMD_ADDGRP(AppWiFiPingCmdTbl, sizeof (AppWiFiPingCmdTbl) / sizeof (*AppWiFiPingCmdTbl), "sping", ": Socket mode WiFi ping commands"); 
    appPingState = APP_WIFI_PING_STATE_STOP;
}

void APP_PingTasks(DRV_HANDLE handle)
{
    switch(appPingState)
    {
        case APP_WIFI_PING_STATE_START:
        {
            if (WDRV_WINC_STATUS_OK == WDRV_WINC_ICMPEchoRequest(handle, appPingIpAddr, 0, &APP_WiFiPingResponseCallback))
            {
                SYS_CONSOLE_PRINT("ICMP echo request sent\r\n");
                appPingState = APP_WIFI_PING_STATE_WAIT;
                
            }
            break;
        }
        case APP_WIFI_PING_STATE_WAIT:
        {
            /* Wait for the callback to set the ICMP echo reply time. */
            if (0 != appPingReplyTime)
            {
                /* Wait for the requested number of milliseconds before returning
                 to connected state to send the next ICMP echo request. */

                uint32_t appPingIntervalTime = (APP_PING_INTERVAL * SYS_TIME_FrequencyGet()) / 1000ul;

                if ((SYS_TIME_CounterGet() - appPingReplyTime) >= appPingIntervalTime)
                {   
                    appPingReplyTime = 0;
                    appPingState = APP_WIFI_PING_STATE_START;
                }                
            }
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
