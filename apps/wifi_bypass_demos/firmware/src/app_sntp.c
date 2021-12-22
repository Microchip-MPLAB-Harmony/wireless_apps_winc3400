/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    sntp.c

  Summary:
    This file contains the source code for the MPLAB Harmony wifi sntp application.

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
#ifdef APP_SNTP
#include "wdrv_winc_client_api.h"
#include "app_sntp.h"
#include "tcpip/tcpip.h"
#include "time.h"

#define APP_MAIN_WORLDWIDE_NTP_POOL_HOSTNAME        "*.pool.ntp.org"

typedef enum
{
    /* Example's state machine's initial state. */
    APP_WIFI_SNTP_STATE_WAIT_INIT=0,
    APP_WIFI_SNTP_STATE_TIME_GET,
    APP_WIFI_SNTP_STATE_DONE,
    APP_WIFI_SNTP_STATE_ERROR,
} APP_WIFI_SNTP_STATES;

static APP_WIFI_SNTP_STATES appSntpState; 

static int APP_WiFiSntpCMDProcess
(
    SYS_CMD_DEVICE_NODE* pCmdIO, 
    int argc, 
    char** argv
) 
{
   if ((argc >= 1) && (!strcmp(argv[1], "help")))
   {
        SYS_CONSOLE_PRINT("sntp <get> : Get SNTP time\r\n");
   }
   else if ((argc >= 1) && (!strcmp(argv[1], "get")))
   {
       appSntpState = APP_WIFI_SNTP_STATE_WAIT_INIT;
       
   }
   return 0;
}
static const SYS_CMD_DESCRIPTOR AppWiFiSntpCmdTbl[] =
{
    {"sntp", (SYS_CMD_FNC) APP_WiFiSntpCMDProcess, ": Bypass mode SNTP commands processing"},
    
};

void APP_SntpInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    SYS_CMD_ADDGRP(AppWiFiSntpCmdTbl, sizeof (AppWiFiSntpCmdTbl) / sizeof (*AppWiFiSntpCmdTbl), "sntp", ": Socket mode WiFi SNTP commands"); 
    appSntpState = APP_WIFI_SNTP_STATE_DONE;
}

void APP_SntpTasks(DRV_HANDLE handle)
{
    switch(appSntpState)
    {
        case APP_WIFI_SNTP_STATE_WAIT_INIT:
        {
            TCPIP_SNTP_RESULT res = TCPIP_SNTP_TimeStampStatus();
            if(SNTP_RES_OK == res)
            {
                appSntpState = APP_WIFI_SNTP_STATE_TIME_GET;
            }
            break;
        }
        case APP_WIFI_SNTP_STATE_TIME_GET:
        {
            uint32_t pUTCSeconds = TCPIP_SNTP_UTCSecondsGet();

            if(0 == pUTCSeconds)
            { 
                SYS_CONSOLE_PRINT("SNTP failed\r\n");
                appSntpState = APP_WIFI_SNTP_STATE_ERROR;
            }
            else
            {
                //SYS_CONSOLE_PRINT("UTC Seconds: %lu\r\n", pUTCSeconds);
                // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
                tstrSystemTime pSysTime;
                WDRV_WINC_UTCToLocalTime(pUTCSeconds,&pSysTime);
                SYS_CONSOLE_PRINT("year=%d,month=%d,day=%d,hour=%d,minute=%d,second=%d GMT \r\n",
                                        pSysTime.u16Year,pSysTime.u8Month,pSysTime.u8Day,
                                        pSysTime.u8Hour,pSysTime.u8Minute,pSysTime.u8Second);

                appSntpState = APP_WIFI_SNTP_STATE_DONE;
            }
            
            break;
        }
        case APP_WIFI_SNTP_STATE_DONE:
        {
            break;
        }
        case APP_WIFI_SNTP_STATE_ERROR:
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
/* *****************************************************************************
 End of File
 */
