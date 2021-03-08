/*******************************************************************************
  WINC Example Application

  File Name:
    example.c

  Summary:
    WINC Power Save Mode example.

  Description:
    This example demonstrates the power save mode of WINC

    The configuration defines for this demo are:
        MAIN_WLAN_SSID           -- BSS to create
        MAIN_WLAN_PSK            -- password of the SSID
        MAIN_PS_SLEEP_MODE       -- power save mode
        MAIN_REQUEST_SLEEP_TIME  -- sleep time in ms

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
#include "example_conf.h"
#include "m2m_periph.h"

extern APP_DATA appData;

/** PowerSave status */
#define MAIN_PS_WAKE                0
#define MAIN_PS_SLEEP               1
#define MAIN_PS_REQ_SLEEP           3

typedef enum
{
    /* Example's state machine's initial state. */
    EXAMP_STATE_INIT=0,
    EXAMP_STATE_CONNECT_AP,
    EXAMP_STATE_REQ_SLEEP,
    EXAMP_STATE_CONNECTED_AP,
    EXAMP_STATE_DISCONNECTED,
    EXAMP_STATE_ERROR,
} EXAMP_STATES;

static EXAMP_STATES state       = EXAMP_STATE_INIT;
static uint8_t gu8SleepStatus;
static bool gGetRssiFlag        = false;

static void disable_pullups(void)
{
    uint32_t pinmask;

    pinmask = (
        M2M_PERIPH_PULLUP_DIS_HOST_WAKEUP|
        M2M_PERIPH_PULLUP_DIS_GPIO_3|
        M2M_PERIPH_PULLUP_DIS_GPIO_5|
        M2M_PERIPH_PULLUP_DIS_SD_DAT0_SPI_TXD|
        M2M_PERIPH_PULLUP_DIS_GPIO_6);

    m2m_periph_pullup_ctrl(pinmask, 0);
}

static void timer_callback( uintptr_t context )
{
    SYS_CONSOLE_Print(appData.consoleHandle, "timer_callback...\r\n");
    gGetRssiFlag = true;
}

static void APP_ExamplpGetRssiCallback(DRV_HANDLE handle, int8_t rssi)
{
    SYS_CONSOLE_Print(appData.consoleHandle, "[%s] rssi = %d\r\n", __func__, rssi);
    gu8SleepStatus = MAIN_PS_REQ_SLEEP;
}

static void APP_ExampleSTAConnectNotifyCallback(DRV_HANDLE handle, WDRV_WINC_ASSOC_HANDLE assocHandle, WDRV_WINC_CONN_STATE currentState, WDRV_WINC_CONN_ERROR errorCode)
{
    gu8SleepStatus = MAIN_PS_WAKE;

    if (WDRV_WINC_CONN_STATE_CONNECTED == currentState)
    {
        SYS_CONSOLE_Print(appData.consoleHandle, "STA mode: Station connected\r\n");

        state = EXAMP_STATE_CONNECTED_AP;
    }
    else if (WDRV_WINC_CONN_STATE_DISCONNECTED == currentState)
    {
        SYS_CONSOLE_Print(appData.consoleHandle, "STA mode: Station disconnected\r\n");

        state = EXAMP_STATE_CONNECT_AP;
    }
}

static void APP_ExampleSTAModeDHCPAddressEventCallback(DRV_HANDLE handle, uint32_t ipAddress)
{
    char s[20];

    SYS_CONSOLE_Print(appData.consoleHandle, "STA Mode: Station IP address is %s\r\n", inet_ntop(AF_INET, &ipAddress, s, sizeof(s)));

    gu8SleepStatus = MAIN_PS_REQ_SLEEP;

    SYS_TIME_CallbackRegisterMS ( timer_callback, 0, MAIN_REQUEST_SLEEP_TIME, SYS_TIME_PERIODIC );

    SYS_CONSOLE_Print(appData.consoleHandle, "Start Timer\r\n");
}

void APP_ExampleInitialize(DRV_HANDLE handle)
{
    SYS_CONSOLE_Print(appData.consoleHandle, "\r\n");
    SYS_CONSOLE_Print(appData.consoleHandle, "==============================\r\n");
    SYS_CONSOLE_Print(appData.consoleHandle, "WINC Power Save Mode Example\r\n");
    SYS_CONSOLE_Print(appData.consoleHandle, "==============================\r\n");

    state = EXAMP_STATE_INIT;
}

void APP_ExampleTasks(DRV_HANDLE handle)
{
    static WDRV_WINC_AUTH_CONTEXT  authCtx;
    static WDRV_WINC_BSS_CONTEXT   bssCtx;

    switch (state)
    {
        case EXAMP_STATE_INIT:
        {
            /* Preset the error state incase any following operations fail. */

            state = EXAMP_STATE_ERROR;

            /* Create the BSS context using default values and then set SSID
             and channel. */

            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BSSCtxSetDefaults(&bssCtx))
            {
                break;
            }

            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BSSCtxSetSSID(&bssCtx, (uint8_t*)MAIN_WLAN_SSID, strlen(MAIN_WLAN_SSID)))
            {
                break;
            }

#if defined(WLAN_AUTH_OPEN)
            /* Create authentication context for Open. */

            if (WDRV_WINC_STATUS_OK != WDRV_WINC_AuthCtxSetOpen(&authCtx))
            {
                break;
            }
#elif defined(WLAN_AUTH_WEP)
            /* Create authentication context for WEP. */

            if (WDRV_WINC_STATUS_OK != WDRV_WINC_AuthCtxSetWEP(&authCtx, WLAN_WEB_KEY_INDEX, (uint8_t*)WLAN_WEB_KEY, strlen(WLAN_WEB_KEY)))
            {
                break;
            }
#elif defined(WLAN_AUTH_WPA)
            /* Create authentication context for WPA. */

            if (WDRV_WINC_STATUS_OK != WDRV_WINC_AuthCtxSetWPA(&authCtx, (uint8_t*)MAIN_WLAN_PSK, strlen(MAIN_WLAN_PSK)))
            {
                SYS_CONSOLE_Print(appData.consoleHandle, "Fail to set Auth WPAPSK....\r\n");
                break;
            }
#endif

            disable_pullups();

#ifdef WDRV_WINC_DEVICE_WINC1500
            /* Set defined sleep mode */
            if (MAIN_PS_SLEEP_MODE == WDRV_WINC_PS_MODE_MANUAL)
            {
                SYS_CONSOLE_Print(appData.consoleHandle, "WDRV_WINC_PS_MODE_MANUAL\r\n");

                if (WDRV_WINC_STATUS_OK != WDRV_WINC_PowerSaveSetMode(handle, WDRV_WINC_PS_MODE_MANUAL ))
                {
                    break;
                }
            }
#endif
            if (MAIN_PS_SLEEP_MODE == WDRV_WINC_PS_MODE_AUTO_LOW_POWER)
            {
                SYS_CONSOLE_Print(appData.consoleHandle, "WDRV_WINC_PS_MODE_AUTO_LOW_POWER\r\n");

                if (WDRV_WINC_STATUS_OK !=  WDRV_WINC_PowerSaveSetBeaconInterval(handle, 1))
                {
                    break;
                }

                if (WDRV_WINC_STATUS_OK != WDRV_WINC_PowerSaveSetMode(handle, WDRV_WINC_PS_MODE_AUTO_LOW_POWER))
                {
                    break;
                }
            }
            else if (MAIN_PS_SLEEP_MODE == WDRV_WINC_PS_MODE_OFF)
            {
                SYS_CONSOLE_Print(appData.consoleHandle, "WDRV_WINC_PS_MODE_OFF\r\n");
            }

            state = EXAMP_STATE_CONNECT_AP;
            break;
        }

        case EXAMP_STATE_CONNECT_AP:
        {
            /* Preset the error state incase any following operations fail. */
            state = EXAMP_STATE_ERROR;

            if (WDRV_WINC_STATUS_OK != WDRV_WINC_IPUseDHCPSet(handle, &APP_ExampleSTAModeDHCPAddressEventCallback))
            {
                SYS_CONSOLE_Print(appData.consoleHandle, "WDRV_WINC_IPUseDHCPSet() fail ...\r\n");
                break;
            }

            if (WDRV_WINC_STATUS_OK != WDRV_WINC_BSSConnect(handle, &bssCtx, &authCtx, &APP_ExampleSTAConnectNotifyCallback))
            {
                SYS_CONSOLE_Print(appData.consoleHandle, "WDRV_WINC_BSSConnect() failed ...\r\n");
                break;
            }

            state = EXAMP_STATE_REQ_SLEEP;
            break;
        }

        case EXAMP_STATE_REQ_SLEEP:
        case EXAMP_STATE_CONNECTED_AP:
        {
            int8_t rssi;

            if (gu8SleepStatus == MAIN_PS_REQ_SLEEP)
            {
#ifdef WDRV_WINC_DEVICE_WINC1500
                if (MAIN_PS_SLEEP_MODE == WDRV_WINC_PS_MODE_MANUAL)
                {
                    SYS_CONSOLE_Print(appData.consoleHandle, "WDRV_WINC_PowerSaveManualSleep() is called ...\r\n");

                    if (WDRV_WINC_STATUS_OK != WDRV_WINC_PowerSaveManualSleep(handle, MAIN_REQUEST_SLEEP_TIME))
                    {
                        break;
                    }

                    gu8SleepStatus = MAIN_PS_SLEEP;
                }
#endif
            }

            if (gGetRssiFlag)
            {
                gGetRssiFlag = false;

                SYS_CONSOLE_Print(appData.consoleHandle, "WDRV_WINC_AssociationRSSIGet() is called ...\r\n");

                if (WDRV_WINC_STATUS_OK != WDRV_WINC_AssociationRSSIGet(handle, &rssi, &APP_ExamplpGetRssiCallback))
                {
                    break;
                }
            }
            break;
        }

        case EXAMP_STATE_ERROR:
        {
            break;
        }

        default:
        {
            break;
        }
    }
}
