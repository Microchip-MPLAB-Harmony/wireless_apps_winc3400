/*******************************************************************************
  MPLAB Harmony Example Configuration File

  Company:
    Microchip Technology Inc.

  File Name:
    app_trans_service.h

  Summary:
    This header file provides configuration for the BLE transparent service application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2020-21 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END
#ifdef APP_BLE_TRANSPARENT_SERVICE

#include "stdio.h"
#include "at_ble_api.h"

/****************************************************************************************
*							        Macros	                                     							*
****************************************************************************************/
/**@brief Keypad debounce time */
#define KEY_PAD_DEBOUNCE_TIME	(200)

/**@brief Application maximum transmit buffer size */
#define TRANS_APP_TX_BUF_SIZE   (150)

/**@brief Enter button press to send data */
#define TRANS_ENTER_BUTTON_PRESS (13)

/**@brief Entered backspace button */
#define BACKSPACE_BUTTON_PRESS (8)

/**@brief Space bar */
#define TRANS_SPACE_BAR (32)

// Allows the main app to initialise the profile app including
// initialising services and callbacks
at_ble_status_t ble_trans_service_init(void);


void ble_trans_service_process_event(at_ble_events_t event, at_ble_event_parameter_t* params);

at_ble_status_t ble_trans_update_value_on_btnpress(uint8_t* trans_tx_value, uint8_t len);

void ble_trans_service_send_buf(void);

void ble_trans_service_send_data(uint8_t *trans_tx_value, uint8_t len);

void APP_BleTransTasks(DRV_HANDLE handle);

void APP_BleTransInitialize(APP_CALLBACK pAPPWiFiCallback);
#endif /* __TRANS_SERVICE_APP_H__ */
