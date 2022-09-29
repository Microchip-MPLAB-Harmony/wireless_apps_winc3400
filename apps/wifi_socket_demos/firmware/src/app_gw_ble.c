
/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_gw_ble.c

  Summary:
    This file contains the source code for the MPLAB Harmony Gateway application's BLE part.

  Description:
    This file contains the source code for the MPLAB Harmony Gateway application's BLE part. It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware. However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called. That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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
#ifdef APP_PUB_BLE_MQTT

#include "app_gw_ble.h"
#include "app_gw_mqtt.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

extern APP_DATA appData;
extern APP_MQTT_Handle g_sSysMqttHandle;
extern uint8_t scan_response_count;

/*              Gateway Node Alive flag             */
uint32_t gu32NodeAliveFlag;

APP_MQTT_Handle *hdl = &g_sSysMqttHandle;
static _BLE_APP_STATES bleState;
gateway_node_value_t g_gateway_node_list[GATEWAY_SUPPORTED_NODES_MAX];


// *****************************************************************************
// *****************************************************************************
// Section:Function Definitions 
// *****************************************************************************
// *****************************************************************************

void APP_GwBLE_Initialize(void) {

    /* TODO: Initialize your application's state machine and other
     * parameters.
     */

    bleState = BLE_INIT;
}

/* To check free index in the gateway node list and save an entry for new discovered BLE node's address */
uint8_t get_free_node(gateway_ble_addr_t *node_addr) {
    uint8_t count;
    for (count = 0; count < GATEWAY_SUPPORTED_NODES_MAX; count++) {
        if (g_gateway_node_list[count].node_alive == 0) {
            g_gateway_node_list[count].node_addr.bd_addr_h = node_addr->bd_addr_h;
            g_gateway_node_list[count].node_addr.bd_addr_m = node_addr->bd_addr_m;
            g_gateway_node_list[count].node_addr.bd_addr_l = node_addr->bd_addr_l;

            SYS_CONSOLE_Print(appData.consoleHandle, "\r\n The BD Address = 0x%04X:0x%04X:0x%04X \r\n", g_gateway_node_list[count].node_addr.bd_addr_l, g_gateway_node_list[count].node_addr.bd_addr_m, g_gateway_node_list[count].node_addr.bd_addr_h);
            break;
        }
    }
    return count;
}

/* Check the advertisement data header and confirm if it's gateway application data */
uint8_t * extract_ble_node_data(uint8_t *advData) {

    if (*((int32_t *) (advData + 4)) == GATEWAY_NODE_FRAME_HEADER) {
        return (advData + 8);
    } else {
        return NULL;
    }
}

/* To get an index of the received BD address in the gateway node list*/
uint8_t get_node_table_index(gateway_ble_addr_t *node_addr) {
    uint8_t count;
    for (count = 0; count < GATEWAY_SUPPORTED_NODES_MAX; count++) {
        if ((g_gateway_node_list[count].node_addr.bd_addr_h == node_addr->bd_addr_h) &&
                (g_gateway_node_list[count].node_addr.bd_addr_m == node_addr->bd_addr_m) &&
                (g_gateway_node_list[count].node_addr.bd_addr_l == node_addr->bd_addr_l)) {
            return count;
        }
    }
    return get_free_node(node_addr);
}

/* To save the BLE node's advertisement data */
void save_ble_node_data(uint8_t* bt_addr, uint8_t *advData, uint8_t advLen) {
#if 1
    uint8_t index;
    uint8_t *nodeData = NULL;
    nodeData = extract_ble_node_data(advData);
    if (nodeData) {
        index = get_node_table_index((gateway_ble_addr_t *) bt_addr);
        if (index < GATEWAY_SUPPORTED_NODES_MAX) {
            memcpy(&g_gateway_node_list[index].node_data, (uint8_t *) nodeData, sizeof (gateway_node_data_t));
            g_gateway_node_list[index].node_alive = 1;
            gu32NodeAliveFlag |= (0x01 << index);
        }
    }
#else
    uint8_t index;

    gateway_node_data_t tmpData = {.name_len = 0x05,
        .node_name = "Node1",
        .node_value = "Hello",
        .value_len = 0x05};
    uint8_t *nodeData = &tmpData;

    //#define DBG_ADV_DATA
#ifdef DBG_ADV_DATA
    printf("\r\nADV Data [%02X:%02X:%02X:%02X:%02X:%02X]\r\n", bt_addr[0], bt_addr[1], bt_addr[2], bt_addr[3], bt_addr[4], bt_addr[5]);
    for (index = 0; index < advLen; index++)
        printf("%02X ", advData[index]);
#endif
    port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
    //nodeData = extract_ble_node_data(advData, advLen);

    if (nodeData) {
        index = get_node_table_index((gateway_ble_addr_t *) bt_addr);
        if (index < GATEWAY_SUPPORTED_NODES_MAX) {
            memcpy(&g_gateway_node_list[index].node_data, (uint8_t *) nodeData, sizeof (gateway_node_data_t));
            g_gateway_node_list[index].node_alive = 1;
            gu32NodeAliveFlag |= (0x01 << index);

        }
    }

#endif	
}

/* Need to be called at regular interval to update the node list */
void update_node_list(void) {
    /* if node_alive is not 0, increment the node_alive at regular interval depending on the node data frequency */
    uint8_t count;
    for (count = 0; count < GATEWAY_SUPPORTED_NODES_MAX; count++) {
        if (g_gateway_node_list[count].node_alive) {
            g_gateway_node_list[count].node_alive = g_gateway_node_list[count].node_alive << 1;
        } else {
            gu32NodeAliveFlag &= ~(0x01 << count);
        }
    }
}

/** @brief instructs device to stop scanning */
at_ble_status_t gateway_node_scan_stop(void) {
    return (at_ble_scan_stop());
}

/******************************************************************************
  Function:
    void APP_GwBLE_Tasks ( void )

  Remarks:
    See prototype in app_gw_ble.h
 */
void APP_GwBLE_Tasks(DRV_HANDLE handle) {

    switch (bleState) {
        case BLE_INIT:
        {
                if (WDRV_WINC_STATUS_OK != WDRV_WINC_BLEStart(handle)) {
                    SYS_CONSOLE_Print(appData.consoleHandle, "Failed to start BLE\r\n");
                    bleState = BLE_INIT;
                    break;
                } else {
                    bleState = BLE_STARTED;
                    SYS_CONSOLE_Print(appData.consoleHandle, "BLE Started Successfully!\r\n");
                }
                bleState = BLE_STARTED;
                SYS_CONSOLE_Print(appData.consoleHandle, "Initial: BLE Started Successfully!\r\n");
        }
            break;

        case BLE_STARTED:
        {
            /* check if the MQTT Broker is connected and if subAck is received */
            if (((*hdl).sPahoInfo.sPahoClient.isconnected) && ((*hdl).sPahoInfo.sPahoClient.isSubAckRx)) {
                register_ble_scan_info_event_cb(ble_gateway_scan_handler);
                at_ble_set_dev_config(AT_BLE_GAP_CENTRAL_MST);

                gateway_node_scan_start(SCAN_INTERVAL, SCAN_WINDOW, SCAN_TYPE);
                bleState = BLE_NODE_SCAN_STARTED;
            } else {
                bleState = BLE_STARTED;
            }
        }
            break;

        case BLE_NODE_SCAN_STARTED:
        {
            ble_event_task();

            //update BLE_node_list Function
            update_node_list();

            //checking if the node list is updated
            if (gu32NodeAliveFlag) {
                /* To meet the GATEWAY_SUPPORTED_NODES_MAX criterion */
                if ((scan_response_count >= 1) && (scan_response_count <= 10)) {
                    //checking if the MQTT Broker is connected
                    if ((*hdl).sPahoInfo.sPahoClient.isconnected) {
                        APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_PUBLISH_NODE_DATA);
                    }
                }
            } else if (scan_response_count >= 11) {
                SYS_CONSOLE_Print(appData.consoleHandle, "gateway_node_scan_stop::Scanning...Stopped\r\n");
                SYS_CONSOLE_Print(appData.consoleHandle, "About to exit the Gateway Demo. Use the command \"appdemo stop\" to stop this demo completely.\r\n");
                bleState = BLE_NODE_SCAN_STOP;
            }
        }
            break;

        case BLE_NODE_SCAN_STOP:
        {
            gateway_node_scan_stop();
            bleState = BLE_IDLE;
        }
            break;

        case BLE_IDLE:
        {
            // Do nothing
        }
            break;
    }
}

#endif          /* APP_PUB_BLE_MQTT */
/*******************************************************************************
 End of File
 */