/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_iperf.c

  Summary:
    This file contains the source code for the MPLAB Harmony wifi iperf application.

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
#ifdef APP_IPERF
#include "wdrv_winc_client_api.h"
#include "app_iperf.h"
#include "iperf.h"



typedef enum
{
    /* Example's state machine's initial state. */
    APP_WIFI_IPERF_EXAMP_STATE_INIT=0,
    APP_WIFI_IPERF_EXAMP_STATE_START,
    APP_WIFI_IPERF_EXAMP_STATE_ERROR,
} APP_WIFI_IPERF_EXAMP_STATES;

uint32_t	 gu32IPAddress;
uint32_t	 clientIPAddress;
uint32_t	 tcp_serv_pack_recv = 0;
uint32_t	 udp_serv_pack_recv = 0;
SOCKET tcp_client_sock = -1;
SOCKET udp_server_sock = -1;
app_status iperf_app_stat = {0,0,0,0};
tstrIperfInit pstrIperfInit;


static APP_WIFI_IPERF_EXAMP_STATES appWiFiIperfState;


static int APP_IperfCMDProcess
(
    SYS_CMD_DEVICE_NODE* pCmdIO, 
    int argc, 
    char** argv
) 
{
    if ((argc >= 1) && (!strcmp(argv[1], "tcp")))
    {
        iperf_app_stat.tcp_server = MODE_INIT;
    }
    else if ((argc >= 1) && (!strcmp(argv[1], "udp")))
    {
        iperf_app_stat.udp_server = MODE_INIT;
    }
    
    return 0;
}

static const SYS_CMD_DESCRIPTOR AppIperfCmdTbl[] =
{
    {"siperf", (SYS_CMD_FNC) APP_IperfCMDProcess, ": iperf commands processing"},
};


void APP_IperfInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    SYS_CMD_ADDGRP(AppIperfCmdTbl, sizeof (AppIperfCmdTbl) / sizeof (*AppIperfCmdTbl), "siperf", ": Iperf commands"); 
    appWiFiIperfState = APP_WIFI_IPERF_EXAMP_STATE_INIT;
}



void APP_iperfTasks(DRV_HANDLE handle)
{
    //WDRV_WINC_STATUS status;

    switch (appWiFiIperfState)
    {
        case APP_WIFI_IPERF_EXAMP_STATE_INIT:
        {
            /* Initialize iperf and register the callback */
            SYS_CONSOLE_PRINT( "Initilaizing iperf\r\n"); 
            registerSocketCallback(IperfSocketEventHandler, NULL);
            IperfInit();
            appWiFiIperfState = APP_WIFI_IPERF_EXAMP_STATE_START;
            break;
        }
        case APP_WIFI_IPERF_EXAMP_STATE_START:
        {
            /* Wait for the IP link to become active. */
            if (false == WDRV_WINC_IPLinkActive(handle))
            {
                break;
            }
            if ((iperf_app_stat.udp_server == MODE_INIT) || (iperf_app_stat.udp_server == MODE_FINISHED))
            {
                //SYS_CONSOLE_Print(appData.consoleHandle, "Mode Init\r\n");
                if (iperf_app_stat.udp_server == MODE_FINISHED)
                {
                    //SYS_CONSOLE_PRINT("Mode Finished\r\n");
                    IperfSocketClose(udp_server_sock);
                    iperf_app_stat.udp_server = MODE_INIT; 
                    SYS_CONSOLE_PRINT( "\n\n\n------------------------------------------------------------\r\n");
                    SYS_CONSOLE_PRINT( "Server listening on TCP/UDP port 5001\r\n");
                    SYS_CONSOLE_PRINT( "TCP window size: 1 KByte\r\n");
                    SYS_CONSOLE_PRINT( "------------------------------------------------------------\r\n");
                }
                SYS_CONSOLE_PRINT("Init UDP server\r\n");
                iperf_app_stat.udp_server = MODE_INIT_DONE;
                pstrIperfInit.port = IPERF_WIFI_M2M_SERVER_PORT;
                pstrIperfInit.operating_mode = MODE_UDP_SERVER;
                IperfCreate(&pstrIperfInit, true);
            }
            else if (iperf_app_stat.udp_server == MODE_WAIT)
            {
                SYS_CONSOLE_PRINT("UDP client Init\r\n");
                iperf_app_stat.udp_server = MODE_STOP;
                IperfSocketClose(udp_server_sock);
                SYS_CONSOLE_PRINT( "------------------------------------------------------------\r\n");
                SYS_CONSOLE_PRINT( "Client connecting to %lu.%lu.%lu.%lu, UDP port 5001\r\n",
                (udp_client_addr.sin_addr.s_addr & 0xFF), (udp_client_addr.sin_addr.s_addr & 0xFF00) >> 8,
                (udp_client_addr.sin_addr.s_addr & 0xFF0000) >> 16, (udp_client_addr.sin_addr.s_addr & 0xFF000000) >> 24);
                SYS_CONSOLE_PRINT( "Sending %d byte datagrams\r\n", IPERF_TX_BUFFER_SIZE);
                SYS_CONSOLE_PRINT( "------------------------------------------------------------\r\n");
                iperf_app_stat.udp_client = MODE_INIT;
            }
            else if (iperf_app_stat.udp_client == MODE_INIT) 
            {
                iperf_app_stat.udp_client = MODE_INIT_DONE;
                pstrIperfInit.port = IPERF_WIFI_M2M_SERVER_PORT;
                pstrIperfInit.operating_mode = MODE_UDP_CLIENT;
                memcpy(&pstrIperfInit.ip,&udp_client_addr.sin_addr.s_addr,sizeof(uint32_t));	
                if (udp_serv_pack_recv == 0) {
                    SYS_CONSOLE_PRINT( "sending packet indefinitely\r\n");
                    pstrIperfInit.packets_to_send = -1; // Send indefinitely
                } else {
                    pstrIperfInit.packets_to_send = udp_serv_pack_recv;
                }
                pstrIperfInit.packet_len = IPERF_TX_BUFFER_SIZE;
                pstrIperfInit.tls = 0;
                IperfCreate(&pstrIperfInit, false);					
            }
            else if (iperf_app_stat.udp_client == MODE_STOP) 
            {
                iperf_app_stat.udp_client = MODE_FINISHED;
            }

            if ((iperf_app_stat.tcp_server == MODE_INIT) || (iperf_app_stat.tcp_server == MODE_FINISHED))
            {
                iperf_app_stat.tcp_server = MODE_INIT_DONE;
                pstrIperfInit.port = IPERF_WIFI_M2M_SERVER_PORT;
                pstrIperfInit.operating_mode = MODE_TCP_SERVER;
                IperfCreate(&pstrIperfInit, true);			
            }
            if ((iperf_app_stat.tcp_client == MODE_INIT))
            {
                SYS_CONSOLE_PRINT("TCP client Init\r\n");
                iperf_app_stat.tcp_client = MODE_INIT_DONE;
                pstrIperfInit.port = IPERF_WIFI_M2M_SERVER_PORT;
                pstrIperfInit.operating_mode = MODE_TCP_CLIENT;
                memcpy(&pstrIperfInit.ip,&clientIPAddress,sizeof(clientIPAddress));
                if (tcp_serv_pack_recv == 0) {
                    SYS_CONSOLE_PRINT( "sending packet indefinitely\r\n");
                    pstrIperfInit.packets_to_send = -1; // Send indefinitely
                } else {
                    pstrIperfInit.packets_to_send = tcp_serv_pack_recv;
                }
                pstrIperfInit.packet_len = IPERF_TX_BUFFER_SIZE;
                pstrIperfInit.tls = 0;
                IperfCreate(&pstrIperfInit, false);
            }
            else if (iperf_app_stat.tcp_client == MODE_START) 
            {
                iperf_app_stat.tcp_client = MODE_RUN;
                IperfTCP_Client_SendTestPacket();
            }
            IperfUpdate();
            break;
        }
        case APP_WIFI_IPERF_EXAMP_STATE_ERROR:
        {
            break;
        }

        default:
        {
            break;
        }
    }
}
#endif
