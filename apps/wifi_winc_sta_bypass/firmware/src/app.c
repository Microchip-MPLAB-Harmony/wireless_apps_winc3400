/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdarg.h>
#include "app.h"
#include "wdrv_winc_client_api.h"
#include "tcpip/src/tcpip_manager_control.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

/* TODO: Set Wireless AP Info below */

#define WLAN_SSID           "MY_SSID" /* WINC1500's SSID */
#define WLAN_CHANNEL        WDRV_WINC_ALL_CHANNELS /* WINC1500's Working Channel e.g. 1, 6, 11 or WDRV_WINC_ALL_CHANNELS*/
#define WLAN_AUTH           WDRV_WINC_AUTH_TYPE_WPA_PSK /* WINC1500's Security, e.g. WDRV_WINC_AUTH_TYPE_OPEN, WDRV_WINC_AUTH_TYPE_WPA_PSK or WDRV_WINC_AUTH_TYPE_WEP */
#define WLAN_WEP_KEY        "1234567890" /* Key for WEP Security */
#define WLAN_WEP_KEY_INDEX  1 /* Key Index for WEP Security */
#define WLAN_WPA_PASSPHRASE "MY_PASSPHRASE" /* target AP's passphrase */

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

APP_DATA appData;

SYS_CONSOLE_HANDLE consoleHandle;

static DRV_HANDLE wdrvHandle;

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
void _APP_TrackIPAddr( void )
{
    IPV4_ADDR dwNewIP;

    /* Obtain the IPv4 address of the network interface */
    dwNewIP.Val = TCPIP_STACK_NetAddress(appData.netHandleWiFi);

    /* Check if the IP address has changed */
    if(dwNewIP.Val != appData.netIpWiFi.Val)
    {
        /* save the new IP address in appData */
        appData.netIpWiFi.Val = dwNewIP.Val;
        SYS_CONSOLE_PRINT("app[%d]: DHCP Client has received IP Address: %d.%d.%d.%d\r\n",
                appData.state,dwNewIP.v[0], dwNewIP.v[1], dwNewIP.v[2], dwNewIP.v[3]);
    }
}

void _APP_LinkMonitor( void )
{
    //Link Monitor-------------------------------------------------------------------------------------------------------------------------
    //Check if the network interface has become disconnected.

    if (appData.state > APP_STATE_WAIT_FOR_LINK && appData.state < APP_STATE_ERROR)
    {
        if(appData.netHandleWiFi && TCPIP_STACK_NetIsLinked(appData.netHandleWiFi) == false)
        {
            SYS_CONSOLE_PRINT("APP[M]: Network Link is Down\r\n");
            appData.state = APP_STATE_WAIT_FOR_LINK;
        }
    }
}

static void _APP_ConnectNotifyCallback(DRV_HANDLE handle, WDRV_WINC_ASSOC_HANDLE assocHandle, WDRV_WINC_CONN_STATE currentState, WDRV_WINC_CONN_ERROR errorCode)
{
    if (WDRV_WINC_CONN_STATE_CONNECTED == currentState)
    {
        SYS_CONSOLE_Print(consoleHandle, "Connected\r\n");
    }
    else if (WDRV_WINC_CONN_STATE_DISCONNECTED == currentState)
    {
        SYS_CONSOLE_Print(consoleHandle, "Disconnected\r\n");
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    appData.netIpWiFi.Val = 0;
    appData.netHandleWiFi = NULL;

    /* Initialize WINC MAC */
//    _APP_WINCInit();
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    /* Stay ready to read console for user's input */
    SYS_CMD_READY_TO_READ();

    /* Keep checking the network link state */
    _APP_LinkMonitor();

    /* Check the application's current state. */
    switch ( appData.state )
    {
        case APP_STATE_INIT:
        {
            if (SYS_STATUS_READY == WDRV_WINC_Status(sysObj.drvWifiWinc))
            {
                appData.state = APP_STATE_WDRV_INIT_READY;
            }
            break;
        }

        case APP_STATE_WDRV_INIT_READY:
        {
            wdrvHandle = WDRV_WINC_Open(0, 0);

            if (DRV_HANDLE_INVALID != wdrvHandle)
            {
                WDRV_WINC_AUTH_CONTEXT authCtx;
                WDRV_WINC_BSS_CONTEXT  bssCtx;

                /* Reset the internal BSS context */
                WDRV_WINC_BSSCtxSetDefaults(&bssCtx);

                /* Prepare the BSS context with desired AP's parameters */
                WDRV_WINC_BSSCtxSetChannel(&bssCtx, WLAN_CHANNEL);
                WDRV_WINC_BSSCtxSetSSID(&bssCtx, (uint8_t*)WLAN_SSID, strlen(WLAN_SSID));

                /* Reset the internal Auth context */
                WDRV_WINC_AuthCtxSetDefaults(&authCtx);

                /* Prepare the Auth context with desired AP's Security settings */
                if (WDRV_WINC_AUTH_TYPE_OPEN == WLAN_AUTH)
                {
                    WDRV_WINC_AuthCtxSetOpen(&authCtx);
                }
                else if (WDRV_WINC_AUTH_TYPE_WPA_PSK == WLAN_AUTH)
                {
                    WDRV_WINC_AuthCtxSetWPA(&authCtx, (uint8_t*)WLAN_WPA_PASSPHRASE, strlen(WLAN_WPA_PASSPHRASE));
                }
                else if (WDRV_WINC_AUTH_TYPE_WEP == WLAN_AUTH)
                {
                    WDRV_WINC_AuthCtxSetWEP(&authCtx, WLAN_WEP_KEY_INDEX, (uint8_t*)WLAN_WEP_KEY, strlen(WLAN_WEP_KEY));
                }
                else
                {
                    // other type not considered for this demo. default to open.
                    WDRV_WINC_AuthCtxSetOpen(&authCtx);
                }

                if (WDRV_WINC_STATUS_OK == WDRV_WINC_BSSConnect(wdrvHandle, &bssCtx, &authCtx, &_APP_ConnectNotifyCallback))
                {
                    appData.state = APP_STATE_WAIT_FOR_TCPIP_INIT;
                }
            }
            break;
        }

        case APP_STATE_WAIT_FOR_TCPIP_INIT:
        {
            //Wait for the TCPIP Stack to become initialized
            if (TCPIP_STACK_Status(sysObj.tcpip) == SYS_STATUS_READY)
            {
                //Get a handle to the network interface
                //For this application only one interface is used - WINC
                appData.netHandleWiFi = TCPIP_STACK_IndexToNet(0);

                SYS_CONSOLE_PRINT("app[%d]: TCPIP Stack is Ready on %s Interface\r\n", appData.state,
                                  TCPIP_STACK_NetNameGet(appData.netHandleWiFi));
                SYS_CONSOLE_PRINT("app[%d]: Host name is %s\r\n", appData.state,
                                  TCPIP_STACK_NetBIOSName(appData.netHandleWiFi));
                SYS_CONSOLE_PRINT("app[%d]: DHCP Client is enabled on %s interface\r\n", appData.state,
                                  TCPIP_STACK_NetNameGet(appData.netHandleWiFi));

                appData.state = APP_STATE_WAIT_FOR_LINK;
            }
            break;
        }

        case APP_STATE_WAIT_FOR_LINK:
        {
            //Determine if the network interface is linked
            if (TCPIP_STACK_NetIsReady(appData.netHandleWiFi))
            {
                SYS_CONSOLE_PRINT("app[%d]: Network Link is Up\r\n", appData.state);
                SYS_CONSOLE_PRINT("app[%d]: Waiting for IP address ...\r\n", appData.state);
                appData.state = APP_STATE_WAIT_FOR_DHCP;
            }

            break;
        }

        case APP_STATE_WAIT_FOR_DHCP:
        {
            /* check if DHCP client has obtained a valid IP address from DHCP server */
            if (TCPIP_DHCP_IsBound(appData.netHandleWiFi))
            {
                _APP_TrackIPAddr();
                SYS_CONSOLE_PRINT("app[%d]: Demo complete\r\n", appData.state);
                appData.state = APP_STATE_DONE;
            }

            break;
        }

        case APP_STATE_DONE:
        {
            /* Sit idle but keep checking if interface IP address has changed */
            _APP_TrackIPAddr();
            break;
        }

        case APP_STATE_ERROR:
        {
            while(1); // during debugging, put a breakpoint here to check reason of error
            break;
        }

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

/*******************************************************************************
 End of File
 */
