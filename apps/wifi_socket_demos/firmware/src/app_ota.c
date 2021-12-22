/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_ota.c

  Summary:
    This file contains the source code for the MPLAB Harmony WINC OTA application.

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
#ifdef APP_OTA
#include "wdrv_winc_client_api.h"
#include "app_ota.h"

#define APP_OTA_URL    "http://192.168.43.87:8000/m2m_ota_3400.bin"

#define APP_OTA_MAX_URL_SIZE    100

typedef enum
{
    /* Example's state machine's initial state. */
    APP_OTA_STATE_START=0,
    APP_OTA_STATE_BUSY,
    APP_OTA_STATE_DONE,
    APP_OTA_STATE_ERROR
} APP_OTA_STATES;

static APP_OTA_STATES appOtaState; 

char APP_OTA_URL_Buffer[APP_OTA_MAX_URL_SIZE];

static int APP_OtaCMDProcess
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
        SYS_CONSOLE_PRINT("ota <image url>\r\n");
        SYS_CONSOLE_PRINT("E.g: ota http://192.168.1.12:8000/m2m_ota_3400.bin");
   }
   else
   {
       strncpy(APP_OTA_URL_Buffer, argv[1], APP_OTA_MAX_URL_SIZE);
       appOtaState = APP_OTA_STATE_START; 
   }
   return 0;
}

static const SYS_CMD_DESCRIPTOR AppOtaCmdTbl[] =
{
    {"ota", (SYS_CMD_FNC) APP_OtaCMDProcess, ": Socket mode OTA commands processing"},
    
};

static void APP_OtaSwitchCallback(DRV_HANDLE handle, WDRV_WINC_OTA_UPDATE_STATUS status)
{
    if(WDRV_WINC_OTA_STATUS_COMPLETE == status)
    {
        SYS_CONSOLE_PRINT("OTA firmware switch complete\r\n");
        appOtaState = APP_OTA_STATE_DONE;
    }
    else
    {
        SYS_CONSOLE_PRINT("OTA firmware switch Error=%d\r\n", status);
        appOtaState = APP_OTA_STATE_ERROR;
    }
}

static void APP_OtaCallback(DRV_HANDLE handle, WDRV_WINC_OTA_UPDATE_STATUS status)
{
    WDRV_WINC_STATUS ret;
    if(WDRV_WINC_OTA_STATUS_COMPLETE == status)
    {
        SYS_CONSOLE_PRINT("OTA update complete\r\nSwitching image...\r\n");
        ret = WDRV_WINC_SwitchActiveFirmwareImage(handle, APP_OtaSwitchCallback);
        if (WDRV_WINC_STATUS_OK == ret)
        {
            appOtaState = APP_OTA_STATE_BUSY;
        }
        else
        {
            SYS_CONSOLE_PRINT("OTA firmware switch init failed; Err=%d\r\n", ret);
            appOtaState = APP_OTA_STATE_ERROR;
        }
    }
    else
    {
        SYS_CONSOLE_PRINT("OTA Error=%d\r\n", status);
        appOtaState = APP_OTA_STATE_ERROR;
    }
}


void APP_OtaInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    SYS_CMD_ADDGRP(AppOtaCmdTbl, sizeof (AppOtaCmdTbl) / sizeof (*AppOtaCmdTbl), "ota", ": Socket mode OTA commands"); 
    memset(APP_OTA_URL_Buffer, 0, APP_OTA_MAX_URL_SIZE);
    appOtaState = APP_OTA_STATE_DONE;
}

void APP_OtaTasks(DRV_HANDLE handle)
{
    WDRV_WINC_STATUS status;
    
    switch(appOtaState)
    {
        case APP_OTA_STATE_START:
        {
            //status = WDRV_WINC_OTAUpdateFromURL(handle, (char *)APP_OTA_URL, APP_OtaCallback);
            status = WDRV_WINC_OTAUpdateFromURL(handle, (char *) APP_OTA_URL_Buffer, APP_OtaCallback);
            if (WDRV_WINC_STATUS_OK == status)
            {
                SYS_CONSOLE_PRINT("OTA started...\r\n");
                appOtaState = APP_OTA_STATE_BUSY;
                
            }
            else
            {
                SYS_CONSOLE_PRINT("OTA start failed; Err=%d\r\n", status);
                appOtaState = APP_OTA_STATE_ERROR;
            }
            break;
        }
        case APP_OTA_STATE_BUSY:
        {
            /* Wait for the OTA process to complete */
            break;
        }
        case APP_OTA_STATE_DONE:
        {
            /* Wait for the OTA process to complete */
            break;
        }
        case APP_OTA_STATE_ERROR:
        {
            /* Wait for the OTA process to complete */
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
