/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
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


#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "definitions.h"
#include "system/console/sys_console.h"



// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END
    
#define APP_STA_AP
#define APP_SNTP
#define APP_SSL
#define APP_MQTT

typedef enum 
{
    APP_STA_AP_DEMO                 = 1 << 0,
    APP_TCP_CLIENT_DEMO             = 1 << 1,  
    APP_TCP_SERVER_DEMO             = 1 << 2, 
    APP_UDP_CLIENT_DEMO             = 1 << 3, 
    APP_UDP_SERVER_DEMO             = 1 << 4,       
    APP_WIFI_PROV_BLE_DEMO          = 1 << 5,
    APP_OTA_DEMO                    = 1 << 6, 
    APP_SSL_DEMO                    = 1 << 7,    
    APP_PING_DEMO                   = 1 << 8, 
    APP_IPERF_DEMO                  = 1 << 9,   
    APP_SNTP_DEMO                   = 1 << 10,
    APP_CSC_DEVICE_DEMO             = 1 << 11,
    APP_HEART_RATE_PROFILE_DEMO     = 1 << 12,
    APP_BATTERY_SERVICE_DEMO        = 1 << 13,
    APP_PROXIMITY_REPORTER_DEMO     = 1 << 14,
    APP_TRANSPARENT_SERVICE_DEMO    = 1 << 15,
    APP_WIFI_PROV_SOFTAP_DEMO       = 1 << 16,
    APP_MQTT_DEMO                   = 1 << 17,     
} APP_DEMOS;
extern APP_DEMOS appDemoId;

#ifdef APP_BLE_CSC
#define CSC_DEVICE 
#define CSCS_SERVICE
#endif

#ifdef APP_BLE_HEARTRATE
#define HEART_RATE_SERVICE
#endif

#ifdef APP_BLE_PROXIMITY
#define PROXIMITY_REPORTER  
#define LLS_GATT_SERVER
#define TXPS_GATT_SERVER
#define TXPS_SERVER
#define IMMEDIATE_ALERT_SERVICE
#define TX_POWER_SERVICE
#define LINK_LOSS_SERVICE
#define IAS_GATT_SERVER
#endif

#ifdef APP_BLE_TRANSPARENT_SERVICE
#define TRANSPARENT_SERVICE
#endif

typedef enum
{
    APP_WIFI_CONNECT ,
    APP_WIFI_DISCONNECT,
    APP_WIFI_PROVISION,
}APP_CALLBACK_NOTIFY;

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    /* Application's state machine's initial state. */
    APP_STATE_INIT=0,
    APP_STATE_WDRV_INIT_READY,
    APP_STATE_WDRV_OPEN,
    APP_STATE_WDRV_APP_LOOP
} APP_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_STATES state;

    SYS_CONSOLE_HANDLE consoleHandle;

} APP_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_Tasks( void );

void APP_ExampleInitialize(DRV_HANDLE handle,APP_DEMOS appdmeo);

void APP_ExampleTasks( DRV_HANDLE handle );

typedef void (*APP_CALLBACK) (APP_CALLBACK_NOTIFY value,void *data);

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_H */

/*******************************************************************************
 End of File
 */
