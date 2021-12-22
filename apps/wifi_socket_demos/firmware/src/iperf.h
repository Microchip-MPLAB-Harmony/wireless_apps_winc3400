/**
 * \file
 *
 * \brief WINC1500 iperf.
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */



#ifndef IPERF_H_INCLUDED
#define IPERF_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "wdrv_winc_client_api.h"
#include "definitions.h"
#include "configuration.h"


// #define IPERF_WIFI_M2M_TX_TIME				(9999)

#define IPERF_WIFI_M2M_SERVER_PORT			(5001)
#define IPERF_WIFI_M2M_SERVER_IP           0x6800A8C0//0xC0A80068//0xFFFFFFFF //0xC0A8646C   //FFFFFFFF /* 255.255.255.255 */

/** iPerf Settings */
#define HEADER_VERSION1						0x80000000
#define RUN_NOW								0x00000001

#define TEST_STATE_UDP_TX			1
#define TEST_STATE_UDP_RX			2
#define TEST_STATE_TCP_TX			3
#define TEST_STATE_TCP_RX			4

#define IPERF_TX_BUFFER_SIZE		1400
#define IPERF_RX_BUFFER_SIZE		1600
#define IPERF_BUFFER_SIZE			((IPERF_RX_BUFFER_SIZE > IPERF_TX_BUFFER_SIZE) ? IPERF_RX_BUFFER_SIZE : IPERF_TX_BUFFER_SIZE)
    
#define sint8 char
    

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
DATA TYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

// used to reference the 4 byte ID number Iperf place in UDP datagrams
typedef struct UDP_datagram
{
    uint32_t id;
    uint32_t tv_sec;
    uint32_t tv_usec;
} UDP_datagram;

/*
 * The client_hdr structure is sent from clients
 * to servers to alert them of things that need
 * to happen. Order must be perserved in all
 * future releases for backward compatibility.
 * 1.7 has flags, numThreads, mPort, and bufferlen
 */
typedef struct client_hdr {

    /*
     * flags is a bitmap for different options
     * the most significant bits are for determining
     * which information is available. So 1.7 uses
     * 0x80000000 and the next time information is added
     * the 1.7 bit will be set and 0x40000000 will be
     * set signifying additional information. If no
     * information bits are set then the header is ignored.
     * The lowest order diferentiates between dualtest and
     * tradeoff modes, wheither the speaker needs to start
     * immediately or after the audience finishes.
     */
    int32_t flags;
    int32_t numThreads;
    int32_t mPort;
    int32_t bufferlen;
    int32_t mWinBand;
    int32_t mAmount;
} client_hdr;

/*
 * The server_hdr structure facilitates the server
 * report of jitter and loss on the client side.
 * It piggy_backs on the existing clear to close
 * packet.
 */
typedef struct server_hdr {
    /*
     * flags is a bitmap for different options
     * the most significant bits are for determining
     * which information is available. So 1.7 uses
     * 0x80000000 and the next time information is added
     * the 1.7 bit will be set and 0x40000000 will be
     * set signifying additional information. If no
     * information bits are set then the header is ignored.
     */
    int32_t flags;
    int32_t total_len1;
    int32_t total_len2;
    int32_t stop_sec;
    int32_t stop_usec;
    int32_t error_cnt;
    int32_t outorder_cnt;
    int32_t datagrams;
    int32_t jitter1;
    int32_t jitter2;

} server_hdr;

typedef enum{
	MODE_TCP_CLIENT,
	MODE_TCP_SERVER,
	MODE_UDP_CLIENT,
	MODE_UDP_SERVER
}tenuNMI_IperfMode;

typedef struct{
	tenuNMI_IperfMode	operating_mode;
	uint32_t			packets_to_send;
	uint32_t			data_rate;
	uint32_t			packet_len;
	uint8_t				ip[4];
	uint16_t			port;
	uint8_t				tls;
}tstrIperfInit;

typedef enum{
	MODE_UNDEF,
	MODE_INIT,
	MODE_INIT_DONE,
	MODE_START,
	MODE_RUN,
	MODE_WAIT,
	MODE_FINISHED,
	MODE_STOP
}app_mode;

typedef struct app_status{

    uint8_t tcp_server;
	uint8_t udp_server;
	uint8_t tcp_client;
	uint8_t udp_client;
}app_status;



extern struct sockaddr_in udp_client_addr;
	
void IperfSocketEventHandler(SOCKET sock, uint8_t u8Msg, void *pvMsg);

void IperfInit(void);

sint8 IperfSocketClose(SOCKET sock);

sint8 IperfRemoteSocketClose(void);

void IperfPrintStats(SOCKET sock);

void IperfUpdate(void);
sint8 IperfCreate(tstrIperfInit* pstrIperfInit, bool bIsPaused);

void IperfTCP_Client_SendTestPacket(void);

#ifdef __cplusplus
}
#endif

#endif /* IPERF_H_INCLUDED */
