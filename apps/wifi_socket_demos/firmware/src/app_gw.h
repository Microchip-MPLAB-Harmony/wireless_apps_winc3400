
/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_gw.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition). Both
    are defined here for convenience.
 *******************************************************************************/

#ifdef APP_PUB_BLE_MQTT
#ifndef APP_GW_H
#define	APP_GW_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************



// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
    // DOM-IGNORE-END

    /* Gateway application frame header size */
#define GATEWAY_DATA_FRAME_HDR_SIZE                   0x03 	/* 2 bytes MFG ID and 1 byte application code*/

    /* Manufacturer identifier in the beacon data	*/
#define GATEWAY_NODE_BEACON_MFG_ID_LB		0x00	/* Application code in the beacon frame */

    /* Manufacturer identifier in the beacon data	*/
#define GATEWAY_NODE_BEACON_MFG_ID_HB		0xCD /* Application code in the beacon frame */

    /*The 1 byte value specifies the application code */
#define GATEWAY_NODE_BEACON_APP_CODE             0xAA

    /* The node data max size */
#define GATEWAY_NODE_NAME_SIZE_MAX                    0x0C

    /* The node data max size */
#define GATEWAY_NODE_DATA_SIZE_MAX                     0x08

    /* The length of the BLE ADV packet */
#define GATEWAY_BLE_ADV_DATA_LEN                         0x1E

#define GATEWAY_NODE_FRAME_HEADER		((GATEWAY_NODE_BEACON_APP_CODE << 24) | (GATEWAY_NODE_BEACON_MFG_ID_HB << 16) | (GATEWAY_NODE_BEACON_MFG_ID_LB << 8) | 0xFF)    

#define DBG_FUNCTION_PRINT                                      M2M_INFO("\n\r%s", __FUNCTION__)    


    //==============================================================================================  
    //                                                                             Structures
    //============================================================================================== 

    typedef enum {
        GW_APP_INIT,
        GW_APP_WiFi_CONNECTED,
        GW_APP_MQTT_CONNECTED,
        GW_APP_BLE_SCAN_STARTED,
    } GATEWAY_APP_STATUS_t;

    typedef struct {
        uint16_t bd_addr_h;
        uint16_t bd_addr_m;
        uint16_t bd_addr_l;
    } gateway_ble_addr_t;

    /**
     * \brief  Gateway demo BLE advertisement data format 
     *
     *  The format of data present in the BLE advertisement packets from each node
     *  The user is free to choose application specific format by modifying these structures
     * */
    typedef struct {
        uint8_t name_len;
        uint8_t node_name[GATEWAY_NODE_NAME_SIZE_MAX];
        uint8_t value_len;
        uint8_t node_value[GATEWAY_NODE_DATA_SIZE_MAX];
    } gateway_node_data_t;

    /**
     * \brief   Gateway demo BLE node data structure, each node data is stored with these details
     *
     *	The each node data is stored locally in this format. The static array of @ref GATEWAY_NODE_DATA_SIZE_MAX nodes  
     *	is used to store each node data. 
     */
    typedef struct {
        gateway_node_data_t node_data;
        gateway_ble_addr_t node_addr;
        uint16_t node_alive;
    } gateway_node_value_t;

    typedef struct {
        uint8_t dataLen;
        uint8_t manufType;
        uint16_t manufId;
        uint8_t gwAppCode;
    } gateway_node_hdr_t;

    /* Gateway application states

      Summary:
           Wi-Fi-BLE Gateway application states enumeration

      Description:
           This enumeration defines the valid application states. These states
           determine the behavior of the application at various times.
     */

    typedef enum {
        /* Gateway application's state machine's initial state. */
        APP_GW_STATE_INIT = 0,
        APP_GW_STATE_WDRV_INIT_READY,
        APP_GW_STATE_WDRV_OPEN,
        /* TODO: Define states used by the application state machine. */

    } APP_GW_STATES;
    
    /*******************************************************************************
      Function:
        void APP_GatewayTasks ( void )

      Summary:
        MPLAB Harmony Demo application tasks function

      Description:
        This routine is the Harmony Demo application's tasks function. It
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
    void APP_GatewayTasks(DRV_HANDLE wdrvHandle);

    /*******************************************************************************
      Function:
        void APP_GatewayInitialize ( APP_CALLBACK pAPPWiFiCallback )

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
    void APP_GatewayInitialize();

    // *****************************************************************************
    // *****************************************************************************
    // Section: Type Definitions
    // *****************************************************************************
    // *****************************************************************************

    /* Application Data

      Summary:
        Holds application data

      Description:
        This structure holds the application's data.

      Remarks:
        Application strings and buffers are be defined outside this structure.
     */

    typedef struct {
        /* The application's current state */
        APP_GW_STATES state;

        /* TODO: Define any additional data used by the application. */
        SYS_CONSOLE_HANDLE consoleHandle;

    } APP_GW_DATA;

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

    //DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif	
#endif      /* APP_PUB_BLE_MQTT */

/*******************************************************************************
 End of File
 */