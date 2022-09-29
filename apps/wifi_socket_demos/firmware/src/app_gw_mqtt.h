/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_gw_mqtt.h

  Summary:
    This header file provides prototypes and definitions for the MQTT part of the gateway application.

  Description:
    This header file provides function prototypes and data type definitions for
    the Gateway application's MQTT part. Some of these are required by the system (such as the
    "APP_GwMQTT_Initialize" and "APP_GwMQTT_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).
    Both are defined here for convenience.
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

#ifdef APP_PUB_BLE_MQTT

#include "third_party/paho.mqtt.embedded-c/MQTTClient-C/src/MQTTClient.h" 
#include "third_party/paho.mqtt.embedded-c/MQTTClient-C/Platforms/MCHP_winc.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define MQTT_BROKER_PORT                  MQTT_LOCAL_PORT
#define MQTT_BROKER_URL                    MQTT_LOCAL_URL
#define MQTT_SOCKET_TYPE                  0
#define MQTT_USER_NAME                    MQTT_LOCAL_USERNAME
#define MQTT_PUB_TOPIC                        MQTT_LOCAL_PUB_TOPIC
#define MQTT_SUB_TOPIC                        MQTT_LOCAL_SUB_TOPIC    

#define MQTT_LOCAL_URL                  "broker.hivemq.com" /*It's a local LAN MQTT server */
#define MQTT_LOCAL_PORT			1883 
#define MQTT_LOCAL_USERNAME		"WINC3400-GateWay"
#define MQTT_LOCAL_PUB_TOPIC	"devices/"MQTT_LOCAL_USERNAME"/events"
#define MQTT_LOCAL_SUB_TOPIC	"devices/"MQTT_LOCAL_USERNAME"/messages/#"

#define APP_MQTT_SUBSCRIBE_TOPIC_NAME_MAX_LEN       128
#define APP_MQTT_SUB_MAX_TOPICS                     1    
#define APP_MQTT_PAHO_MAX_TX_BUFF_LEN  512
#define APP_MQTT_PAHO_MAX_RX_BUFF_LEN  512
#define APP_MQTT_CLIENT_ID_MAX_LEN                  256    
#define APP_MQTT_MAX_BROKER_NAME_LEN                256    

    typedef enum {
        //    APP_MQTT_STATUS_IDLE = 0, // Idle
        APP_MQTT_STATUS_LOWER_LAYER_DOWN, // Lower Layer is DOWN
        APP_MQTT_STATUS_SOCK_CLIENT_CONNECTING, // Net Client connecting to Net Server
        APP_MQTT_STATUS_SOCK_CONNECTED, // Net Instance connected to the peer
        APP_MQTT_STATUS_MQTT_CONNECTED, // Lower Layer is DOWN
        APP_MQTT_STATUS_MQTT_DISCONNECTING, // Net Instance in disconnected state
        APP_MQTT_STATUS_MQTT_DISCONNECTED, // Net Instance in disconnected state
        APP_MQTT_STATUS_MQTT_CONN_FAILED, // Lower Layer is DOWN
        APP_MQTT_STATUS_WAIT_FOR_MQTT_CONACK, // Wait for Connect Ack from Broker
        APP_MQTT_STATUS_WAIT_FOR_MQTT_SUBACK, // Wait for Subscribe Ack from Broker         
        APP_MQTT_STATUS_PUBLISH_NODE_DATA, // publishes the node data to MQTT Broker
        APP_MQTT_STATUS_WAIT_FOR_MQTT_PUBACK, // Wait for Publish Ack from Broker
    } APP_MQTT_STATUS;

    typedef struct {
        uint8_t entryValid;
        uint8_t qos; //Qos (0/ 1/ 2)
        char topicName[APP_MQTT_SUBSCRIBE_TOPIC_NAME_MAX_LEN]; //Name of the Topic Subscribing to
    } APP_MQTT_SubscribeConfig;

    typedef struct {
        char brokerName[APP_MQTT_MAX_BROKER_NAME_LEN]; // MQTT Broker/ Server Name
        uint16_t serverPort; // MQTT Server Port
        uint16_t keepAliveInterval; // Keep Alive Interval for the Mqtt Session
        char clientId[APP_MQTT_CLIENT_ID_MAX_LEN]; // MQTT Client ID
    } APP_MQTT_BrokerConfig;

    typedef struct {
        APP_MQTT_BrokerConfig sBrokerConfig; //MQTT Broker Configuration
        uint8_t subscribeCount; //Number of Topis Subscribed to (0-APP_MQTT_MAX_TOPICS)
        APP_MQTT_SubscribeConfig sSubscribeConfig[APP_MQTT_SUB_MAX_TOPICS]; //Config for all the Topics Subscribed to
    } APP_MQTT_Config;

    typedef struct {
        Network sPahoNetwork;
        MQTTClient sPahoClient;
        unsigned char sendbuf[APP_MQTT_PAHO_MAX_TX_BUFF_LEN];
        unsigned char recvbuf[APP_MQTT_PAHO_MAX_RX_BUFF_LEN];
    } APP_MQTT_PahoInfo;

    typedef struct {
        APP_MQTT_Config sCfgInfo;
        APP_MQTT_PahoInfo sPahoInfo; /* Info related to - Paho */
        APP_MQTT_STATUS eStatus; /* Current state of the service */
        Timer timerInfo;
    } APP_MQTT_Handle;

    void APP_GwMQTT_Initialize(void);

    void APP_GwMQTT_Tasks(DRV_HANDLE wdrvHandle);

    void APP_MQTT_SetInstStatus(APP_MQTT_Handle *hdl, APP_MQTT_STATUS status);


#ifdef	__cplusplus
}
#endif

#endif      /* APP_PUB_BLE_MQTT */

/*******************************************************************************
 End of File
 */