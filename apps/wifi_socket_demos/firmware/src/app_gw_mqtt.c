
/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_gw_mqtt.c

  Summary:
    This file contains the source code for the MPLAB Harmony Gateway application's MQTT part.

  Description:
    This file contains the source code for the MPLAB Harmony Gateway application's MQTT part.
    It implements the logic of the MQTT application's state machine and it may call
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
#ifdef      APP_PUB_BLE_MQTT

#include "configuration.h"
#include "nm_common.h"
#include "wdrv_winc_client_api.h"
#include "app_gw_mqtt.h"
#include "app_gw_ble.h"

extern uint32_t g_u32SockStatus;
extern gateway_node_value_t g_gateway_node_list[GATEWAY_SUPPORTED_NODES_MAX];

APP_MQTT_Handle g_sSysMqttHandle;
MQTTMessage g_sMqttMsg;

/** User name of gateway. */
char mqttUser[64] = "Gateway";

#define MQTTPacket_willOptions_initializer { {'M', 'Q', 'T', 'W'}, 0, {NULL, {0, NULL}}, {NULL, {0, NULL}}, 0, 0 }

#define MQTTPacket_connectData_initializer { {'M', 'Q', 'T', 'C'}, 0, 4, {NULL, {0, NULL}}, 60, 1, 0, \
		MQTTPacket_willOptions_initializer, {NULL, {0, NULL}}, {NULL, {0, NULL}} }

#define APP_MQTT_BROKER_NAME            MQTT_BROKER_URL
#define APP_MQTT_BROKER_PORT            MQTT_BROKER_PORT

#define APP_MQTT_MAX_TX_BUFF_LEN        512
#define APP_MQTT_MAX_RX_BUFF_LEN        512

#define APP_MQTT_SUBSCRIBE_TOPIC_NAME   MQTT_SUB_TOPIC
#define APP_MQTT_SUBSCRIBE_QOS          1

#define APP_MQTT_PUBLISH_TOPIC_NAME     MQTT_PUB_TOPIC
#define APP_MQTT_PUBLISH_RETAIN         0
#define APP_MQTT_PUBLISH_QOS              1

#define APP_MQTT_MSG_MAX_LEN                        512

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

void APP_MQTT_SetInstStatus(APP_MQTT_Handle *hdl, APP_MQTT_STATUS status) {
    hdl->eStatus = status;
}

#define APP_MQTT_TIMEOUT_CONST (5000) //msec

extern void APP_Sock_Connect_Tasks(DRV_HANDLE wdrvHandle);
extern void APP_Sock_Connect_Initialize(DRV_HANDLE wdrvHandle, char *hostName, uint16_t port);
extern SOCKET g_clientSocket;

void APP_MQTT_Start_Timer(APP_MQTT_Handle *hdl, uint32_t timerInfo) {
    TimerInit(&hdl->timerInfo);
    TimerCountdownMS(&hdl->timerInfo, timerInfo);
}

bool APP_MQTT_Timer_Expired(APP_MQTT_Handle *hdl) {
    if (TimerIsExpired(&hdl->timerInfo))
        return true;
    else
        return false;
}

void APP_MQTT_Reset_Timer(APP_MQTT_Handle *hdl) {
    TimerInit(&hdl->timerInfo);
}

void APP_MQTT_Process_Timeout(APP_MQTT_Handle *hdl, APP_MQTT_STATUS nextStatus) {
    APP_MQTT_Reset_Timer(hdl);

    APP_MQTT_SetInstStatus(hdl, nextStatus);
}

int32_t APP_MQTT_Send_Msg(char *topicName, char *message, uint16_t message_len, uint8_t qos, uint8_t retain) {
    int rc = 0;

    memset(&g_sMqttMsg, 0, sizeof (g_sMqttMsg));

    g_sMqttMsg.dup = 0;

    g_sMqttMsg.id = 1;

    g_sMqttMsg.payload = message;

    g_sMqttMsg.payloadlen = message_len;

    g_sMqttMsg.qos = qos;

    g_sMqttMsg.retained = retain;

    rc = MQTTPublish(&(g_sSysMqttHandle.sPahoInfo.sPahoClient), topicName, &g_sMqttMsg);

    if (rc != 0) {
        SYS_CONSOLE_PRINT("MQTTPublish() Failed (%d)\r\n", rc);

        return -1;
    }

    APP_MQTT_Start_Timer(&g_sSysMqttHandle, APP_MQTT_TIMEOUT_CONST);

    if (qos != 0) {
        APP_MQTT_SetInstStatus(&g_sSysMqttHandle, APP_MQTT_STATUS_WAIT_FOR_MQTT_PUBACK);
    }

    SYS_CONSOLE_PRINT("Published to Topic (%s)\r\n", topicName);

    return 0;
}

/* Callback registered with Paho SW to get the messages received on the subscribed topic */
void APP_MQTT_messageCb(MessageData* data) {
    char *msg = data->message->payload;

    char topic[32] = {0};

    strncpy(topic, (char *) data->topicName->lenstring.data, data->topicName->lenstring.len);

    topic[data->topicName->lenstring.len] = 0;

    SYS_CONSOLE_PRINT("\nTopic = %s ; Message = %s\r\n", topic, msg);
}

void APP_GwMQTT_Initialize(void) {
    strcpy(g_sSysMqttHandle.sCfgInfo.sBrokerConfig.brokerName, APP_MQTT_BROKER_NAME);

    g_sSysMqttHandle.sCfgInfo.sBrokerConfig.serverPort = APP_MQTT_BROKER_PORT;

    g_sSysMqttHandle.sCfgInfo.subscribeCount = 1;

    strcpy(g_sSysMqttHandle.sCfgInfo.sSubscribeConfig[0].topicName, APP_MQTT_SUBSCRIBE_TOPIC_NAME);

    g_sSysMqttHandle.sCfgInfo.sSubscribeConfig[0].qos = APP_MQTT_SUBSCRIBE_QOS;

    //SYS_CMD_ADDGRP(AppMqttCmdTbl, sizeof (AppMqttCmdTbl) / sizeof (*AppMqttCmdTbl), "mqtt", ": Socket mode MQTT commands"); 

    APP_MQTT_SetInstStatus(&g_sSysMqttHandle, APP_MQTT_STATUS_LOWER_LAYER_DOWN);
}

void APP_GwMQTT_Tasks(DRV_HANDLE wdrvHandle) {
    APP_MQTT_Handle *hdl = &g_sSysMqttHandle;

    if (APP_MQTT_STATUS_LOWER_LAYER_DOWN != hdl->eStatus) {
        APP_Sock_Connect_Tasks(wdrvHandle);
    }

    switch (hdl->eStatus) {
            /* Lower Layer is Down */
        case APP_MQTT_STATUS_LOWER_LAYER_DOWN:
        {
            APP_Sock_Connect_Initialize(wdrvHandle, hdl->sCfgInfo.sBrokerConfig.brokerName, hdl->sCfgInfo.sBrokerConfig.serverPort);
            APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_SOCK_CLIENT_CONNECTING);
        }
            break;

        case APP_MQTT_STATUS_SOCK_CLIENT_CONNECTING:
        {
            /* Poll for status of TCP Socket */
            if (g_u32SockStatus) {
                APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_SOCK_CONNECTED);

                hdl->sPahoInfo.sPahoNetwork.socket = g_clientSocket;
            }
        }
            break;

            /* Socket Connection up */
        case APP_MQTT_STATUS_SOCK_CONNECTED:
        {
            int rc = 0;

            char buffer[80];

            memset(buffer, 0, sizeof (buffer));

            /* Open the MQTT Connection */
            NetworkInit(&(hdl->sPahoInfo.sPahoNetwork));

            MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;

            MQTTClientInit(&(hdl->sPahoInfo.sPahoClient),
                    &(hdl->sPahoInfo.sPahoNetwork),
                    60000,
                    hdl->sPahoInfo.sendbuf,
                    APP_MQTT_MAX_TX_BUFF_LEN,
                    hdl->sPahoInfo.recvbuf,
                    APP_MQTT_MAX_RX_BUFF_LEN);

            connectData.MQTTVersion = 4; //use protocol version 3.1.1

            if (strlen(hdl->sCfgInfo.sBrokerConfig.clientId) == 0) {
                uint8_t au8MacAddr[6] = {0};

                if (m2m_wifi_get_mac_address(au8MacAddr) == M2M_SUCCESS) {
                    sprintf(hdl->sCfgInfo.sBrokerConfig.clientId, "MCHP_%.2x%.2x%.2x",
                            *(au8MacAddr + 3), *(au8MacAddr + 4), *(au8MacAddr + 5));

                    hdl->sCfgInfo.sBrokerConfig.clientId[11] = 0;
                } else {
                    strcpy(hdl->sCfgInfo.sBrokerConfig.clientId, "mchp");

                    hdl->sCfgInfo.sBrokerConfig.clientId[strlen("mchp")] = 0;
                }
            }

            connectData.clientID.cstring = (char *) &(hdl->sCfgInfo.sBrokerConfig.clientId);

            connectData.keepAliveInterval = hdl->sCfgInfo.sBrokerConfig.keepAliveInterval;

            /*
             ** In case we have username/ password scenario
            {
                connectData.username.cstring = ?

                connectData.password.cstring = ?
            }
             */

            /*
             ** In case we have to configure LWT
            {
                connectData.willFlag = 1;

                connectData.will.message.cstring = ?;

                connectData.will.topicName.cstring = ?;

                connectData.will.qos = ?

                connectData.will.retained = ?;
            }
             */

            if ((rc = MQTTConnect(&(hdl->sPahoInfo.sPahoClient), &connectData)) != 0) {
                SYS_CONSOLE_PRINT("MQTTConnect() failed (%d)\r\n", rc);

                APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_MQTT_CONN_FAILED);

                return;
            }

            APP_MQTT_Start_Timer(hdl, APP_MQTT_TIMEOUT_CONST);

            APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_WAIT_FOR_MQTT_CONACK);
        }
            break;

            /* Waiting for Connection Ack */
        case APP_MQTT_STATUS_WAIT_FOR_MQTT_CONACK:
        {
            /* Wait for the MQTT Connection Ack from the MQTT Server */
            int rc = MQTTWaitForConnect(&(hdl->sPahoInfo.sPahoClient));
            if (rc == SUCCESS) {
                APP_MQTT_Reset_Timer(hdl);

                APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_MQTT_CONNECTED);

                SYS_CONSOLE_PRINT("MQTT Connected\r\n");
                SYS_CONSOLE_PRINT("User : %s\r\n\n", mqttUser);

                /* Check if the Application configured a Topic to 
                 * Subscribe to while opening the MQTT Service */
                if (hdl->sCfgInfo.subscribeCount) {
                    SYS_CONSOLE_PRINT("Subscribing to Topic = %s\r\n", hdl->sCfgInfo.sSubscribeConfig[0].topicName);

                    if ((rc = MQTTSubscribe(&(hdl->sPahoInfo.sPahoClient),
                            hdl->sCfgInfo.sSubscribeConfig[0].topicName,
                            (enum QoS)(hdl->sCfgInfo.sSubscribeConfig[0].qos),
                            APP_MQTT_messageCb)) != 0) {
                        SYS_CONSOLE_PRINT("MQTTSubscribe() failed (%d)\r\n", rc);

                        return;
                    }

                    APP_MQTT_Start_Timer(hdl, APP_MQTT_TIMEOUT_CONST);

                    APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_WAIT_FOR_MQTT_SUBACK);
                }
            } else {
                if (APP_MQTT_Timer_Expired(hdl) == true)
                    APP_MQTT_Process_Timeout(hdl, APP_MQTT_STATUS_MQTT_CONN_FAILED);
            }
        }
            break;

            /* Waiting for Sub Ack */
        case APP_MQTT_STATUS_WAIT_FOR_MQTT_SUBACK:
        {
            /* Wait for the MQTT Subscribe Ack */
            int rc = MQTTWaitForSubscribeAck(&(hdl->sPahoInfo.sPahoClient),
                    APP_MQTT_SUBSCRIBE_TOPIC_NAME,
                    APP_MQTT_messageCb);
            if (rc == SUCCESS) {
                APP_MQTT_SubscribeConfig sMqttSubCfg;

                APP_MQTT_Reset_Timer(hdl);

                memset(&sMqttSubCfg, 0, sizeof (sMqttSubCfg));

                strcpy(sMqttSubCfg.topicName, APP_MQTT_SUBSCRIBE_TOPIC_NAME);
                ((*hdl).sPahoInfo.sPahoClient.isSubAckRx) = 1; //setting a flag to identify if subAck is received
                SYS_CONSOLE_PRINT("Suback received for Topic (%s)\r\n\n", APP_MQTT_SUBSCRIBE_TOPIC_NAME);

                APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_MQTT_CONNECTED);

            } else {
                if (APP_MQTT_Timer_Expired(hdl) == true)
                    APP_MQTT_Process_Timeout(hdl, APP_MQTT_STATUS_MQTT_CONNECTED);
            }
        }
            break;

        case APP_MQTT_STATUS_PUBLISH_NODE_DATA:
        {
            {
                MQTTMessage messageMqtt;

                messageMqtt.qos = QOS1;
                messageMqtt.retained = APP_MQTT_PUBLISH_RETAIN;
                messageMqtt.payload = (char *) g_gateway_node_list;

                messageMqtt.payloadlen = sizeof (gateway_node_value_t);


                APP_MQTT_Send_Msg(APP_MQTT_PUBLISH_TOPIC_NAME, messageMqtt.payload, messageMqtt.payloadlen, messageMqtt.qos, messageMqtt.retained);
            }
            APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_WAIT_FOR_MQTT_PUBACK);
        }
            break;

        case APP_MQTT_STATUS_WAIT_FOR_MQTT_PUBACK:
        {
            /* Wait for the MQTT Publish Ack */
            int rc = MQTTWaitForPublishAck(&(hdl->sPahoInfo.sPahoClient),
                    &g_sMqttMsg);
            if (rc == SUCCESS) {
                APP_MQTT_Reset_Timer(hdl);

                APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_MQTT_CONNECTED);

                SYS_CONSOLE_PRINT("Puback received\r\n\n");
            } else {
                if (APP_MQTT_Timer_Expired(hdl) == true)
                    APP_MQTT_Process_Timeout(hdl, APP_MQTT_STATUS_MQTT_CONNECTED);
            }
        }
            break;

            /* MQTT Connection Up */
        case APP_MQTT_STATUS_MQTT_CONNECTED:
        {
            /* Poll for status of TCP Socket */
            if (g_u32SockStatus == 0) {
                APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_MQTT_DISCONNECTING);
            }

            /* Wait for any message on the Subscribed Topics */
            int rc = MQTTYield(&(hdl->sPahoInfo.sPahoClient), 50);
            if (rc == SUCCESS) {
            }
        }
            break;

            /* MQTT Disconnected */
        case APP_MQTT_STATUS_MQTT_DISCONNECTING:
        {
            APP_MQTT_SetInstStatus(hdl, APP_MQTT_STATUS_MQTT_DISCONNECTED);
        }
            break;

        case APP_MQTT_STATUS_MQTT_DISCONNECTED:
        {

        }
            break;

        case APP_MQTT_STATUS_MQTT_CONN_FAILED:
        {

        }
            break;
    }
}
#endif          /* APP_PUB_BLE_MQTT */
/*******************************************************************************
 End of File
 */