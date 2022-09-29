/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
  Microchip Technology Inc.

  File Name:
  app_gw_ble.h

  Summary:
  This header file provides prototypes and definitions for the BLE part of the gateway application.

  Description:
    This header file provides function prototypes and data type definitions for
    the Gateway application's BLE part. Some of these are required by the system (such as the
    "APP_GwBLE_Initialize" and "APP_GwBLE_Tasks" prototypes along with other BLE part specific functions) 
    and some of them are only used internally by the application (such as the "BLE_APP_STATES" definition). 
    Both are defined here for convenience.
 *******************************************************************************/

#ifndef _APP_BLE_H
#define _APP_BLE_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#ifdef APP_PUB_BLE_MQTT

#include "at_ble_api.h" 
#include "wdrv_winc_client_api.h"
#include "app_gw.h"
#include "ble/ble_services/ble_mgr/ble_manager.h"

//******************************************************************************

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
    // DOM-IGNORE-END

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
            This enumeration defines the valid BLE application states. These states
            determine the behavior of the application at various times.
     */

    typedef enum {
        BLE_INIT = 0,
        BLE_STARTED,
        BLE_NODE_SCAN_STARTED,
        BLE_NODE_SCAN_STOP,
        BLE_IDLE,
    } _BLE_APP_STATES;

    /* The maximum nodes supported */
#define GATEWAY_SUPPORTED_NODES_MAX	10

    // *****************************************************************************
    // *****************************************************************************
    //                                  Function Declarations
    // *****************************************************************************
    // *****************************************************************************

    void save_ble_node_data(uint8_t * bt_addr, uint8_t *advData, uint8_t advLen);
    uint8_t* extract_ble_node_data(uint8_t *advData);
    uint8_t get_free_node(gateway_ble_addr_t *node_addr);
    uint8_t get_node_table_index(gateway_ble_addr_t *node_addr);
    void update_node_list(void);

    /*******************************************************************************
          Function:
            void APP_GwBLE_Initialize ( void )

          Summary:
             MPLAB Harmony application initialization routine.

          Description:
            This function initializes the BLE functionality in this application. It places the
            BLE application in its initial state and prepares it to run so that its
            APP_GwBLE_Tasks function can be called.

          Precondition:
            All other system initialization routines should be called before calling
            this routine (in "SYS_Initialize").

          Parameters:
            None.

          Returns:
            None.

          Example:
            <code>
            APP_GwBLE_Initialize(void);
            </code>

          Remarks:
            This routine must be called from the SYS_Initialize function.
     */

    void APP_GwBLE_Initialize(void);

    /*******************************************************************************
          Function:
            void APP_GwBLE_Tasks ( void )

          Summary:
            MPLAB BLE application's tasks function

          Description:
            This routine is the BLE application's tasks function.  It
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
            APP_BLE_Tasks();
            </code>

          Remarks:
            This routine must be called from SYS_Tasks() routine.
     */

    void APP_GwBLE_Tasks(DRV_HANDLE handle);

    //*******************************************************************************

    //DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif      /* APP_PUB_BLE_MQTT */

#endif /* _APP_BLE_H */

/*******************************************************************************
 End of File
 */