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


#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "iperf.h"
#include "wdrv_winc_client_api.h"
#include "definitions.h"
#include "configuration.h"



//------------------------------------------------------------------------------
#define IPERF_MAX_UDP_STATE		4

struct sockaddr_in udp_client_addr;

typedef struct
{
	uint32_t u32H;
	uint32_t u32L;
} tstrIperfUint64;

typedef struct
{
	bool			bIsActive;
	bool			bIsPaused;
	SOCKET			sockParent;
	tstrIperfUint64	strTxBytes;
	tstrIperfUint64	strRxBytes;
	uint32_t			u32IPAddress;
	uint32_t			u32BytesLastPeriod;
	uint32_t			u32TxSQN;
	uint32_t  		u32RxPkts;
	int   		s32PktCount;
	uint32_t			u32PktByteCount;
	uint32_t  		u32PktLength;
	uint32_t			u32TimeStart;
	uint32_t  		u32LastTransmission;
	uint32_t			u32LastStatsTime;
	uint16_t  		u16MsPeriod;
	uint16_t			u16Port;
	uint8_t			u8PktsOutstanding;
	uint8_t			u8State;
} tstrIperfSocketInfo;

typedef struct
{
	bool			bIsActive;
	SOCKET			sockParent;
	tstrIperfUint64	strRxBytes;
	uint32_t			u32NextRxSeqNum;
	uint32_t			u32RxMissingPkts;
	uint32_t			u32TimeStart;
	uint32_t  		u32RxPkts;
	uint32_t			u32LastStatsTime;
	uint32_t			u32BytesLastPeriod;
	uint16_t			u16RxMissingPktsLastPeriod;
	uint16_t  		u16RxPktsLastPeriod;
	uint16_t			u16Port;
} tstrIperfUdpState;

typedef struct
{
	UDP_datagram	strUdpDatagram;
	client_hdr		strUdpClientHdr;
	uint8_t			gau8MsgBuffer[IPERF_BUFFER_SIZE];
} tstrIperfUdpMsg;

typedef struct 
{
	UDP_datagram	strUdpDatagram;
	server_hdr		strUdpServerHdr;
} tstrIperfUdpServerMsg;

SYS_TIME_HANDLE iperf_timer = SYS_TIME_HANDLE_INVALID;
static client_hdr iperf_tcp_serv;

extern uint32_t gu32IPAddress;
extern uint32_t clientIPAddress;
extern app_status iperf_app_stat;
extern SOCKET tcp_client_sock;
extern SOCKET udp_server_sock;
extern uint32_t tcp_serv_pack_recv;
extern uint32_t udp_serv_pack_recv;

static tstrIperfSocketInfo	gastrIperfSocketInfo[MAX_SOCKET];
static tstrIperfUdpState	gastrIperfUdpState[IPERF_MAX_UDP_STATE];

static tstrIperfUdpMsg gstrTxMsgBuffer;
static tstrIperfUdpMsg gstrRxMsgBuffer;
static tstrIperfUdpServerMsg gstrTxSrvMsg;

static uint8_t gu8NumSockets;

static uint32_t	u32msTicks;
static uint32_t u32LastStatsTime;

static uint32_t ntohl(uint32_t n)
{
  return ((n & 0xff) << 24) | ((n & 0xff00) << 8) | ((n & 0xff0000UL) >> 8) | ((n & 0xff000000UL) >> 24);
}

//------------------------------------------------------------------------------
static char *inet_ntoa(uint32_t in)
{
    static char b[18];
    uint8_t *ptr;
    ptr = (uint8_t *) &in;
    sprintf(b, "%d.%d.%d.%d", ptr[0], ptr[1], ptr[2], ptr[3]);
    //SYS_CONSOLE_PRINT( "%d.%d.%d.%d", ptr[0], ptr[1], ptr[2], ptr[3]);
    //memcpy(ptr,b,18);
    return b;
}

//------------------------------------------------------------------------------
static void Iperf1msTimerCB(void)
{
	u32msTicks++;
}

//------------------------------------------------------------------------------
static void IperfIncrementTimerUse(void)
{
	if(gu8NumSockets == 0)
	{
		u32msTicks = 0;
		u32LastStatsTime = 0;
		//nm_bsp_start_1ms_timer(Iperf1msTimerCB);
        iperf_timer = SYS_TIME_CallbackRegisterMS((void *)Iperf1msTimerCB, 0, 1,SYS_TIME_PERIODIC);
	}

	gu8NumSockets++;
}

//------------------------------------------------------------------------------
static void IperfDecrementTimerUse(void)
{
	if(gu8NumSockets == 0)
	{
		M2M_ERR("Attempt to decrement timer use when count is zero\r\n");
	}
	else
	{
		gu8NumSockets--;

		if(gu8NumSockets == 0)
            SYS_TIME_TimerDestroy(iperf_timer);//nm_bsp_stop_1ms_timer();
	}
}

//------------------------------------------------------------------------------
static uint32_t IperfCalculateBandwidthKbps(tstrIperfUint64 *pstrUint64, uint32_t u32Time)
{
	uint32_t u32Tmp;
	
	if(pstrUint64->u32H > 0)
	{
		uint32_t n = 32;
		uint32_t mask = 0x80000000;
		while ((pstrUint64->u32H & mask) == 0)
		{
			n -= 1;
			mask >>= 1;
		}
		u32Tmp = (pstrUint64->u32H << (32 - n)) | (pstrUint64->u32L >> n);
		u32Time >>= n;
		u32Tmp /= (u32Time / 8);
		return u32Tmp;
	}
	else if((pstrUint64->u32H == 0) && (pstrUint64->u32L >= 536870912))
	{
		return pstrUint64->u32L / (u32Time/8);
	}
	else
	{
		return (pstrUint64->u32L*8) / u32Time;
	}
}

//------------------------------------------------------------------------------
static void IperfAddUint64(tstrIperfUint64 *pstrUint64, uint32_t u32Inc)
{
	pstrUint64->u32L += u32Inc;
	if(pstrUint64->u32L < u32Inc)
		pstrUint64->u32H++;
}

//------------------------------------------------------------------------------
static sint8 IperfUDP_SendTestPacket(SOCKET sock, struct sockaddr_in* paddr)
{
	sint8 ret;
	uint32_t		 u32secTicks;
	uint32_t		 u32usTicks;

	if((gastrIperfSocketInfo[sock].bIsActive == false) || (gastrIperfSocketInfo[sock].u8State != TEST_STATE_UDP_TX))
		return M2M_ERR_FAIL;

	if(gastrIperfSocketInfo[sock].u32TxSQN == 1)
	{
		SYS_CONSOLE_PRINT("[%3i] local %s port %d connected with", sock, inet_ntoa(gu32IPAddress), 0);
		SYS_CONSOLE_PRINT(" %s port %d\r\n", inet_ntoa(gastrIperfSocketInfo[sock].u32IPAddress), gastrIperfSocketInfo[sock].u16Port);
	}

	u32secTicks = u32msTicks / 1000;
	u32usTicks  = (u32msTicks % 1000)*1000;

	// For UDP Client: store datagram ID into the packet header
	gstrTxMsgBuffer.strUdpDatagram.id = _htonl(gastrIperfSocketInfo[sock].u32TxSQN);
	gstrTxMsgBuffer.strUdpDatagram.tv_sec  = _htonl(u32secTicks);
	gstrTxMsgBuffer.strUdpDatagram.tv_usec = _htonl(u32usTicks);
	gstrTxMsgBuffer.strUdpClientHdr.flags  = 0;

	if(paddr != NULL)
	{
		ret = sendto(sock, &gstrTxMsgBuffer, gastrIperfSocketInfo[sock].u32PktLength, 0, (struct sockaddr*)paddr, sizeof(struct sockaddr_in));
	}
	else
	{
		ret = send(sock, &gstrTxMsgBuffer, gastrIperfSocketInfo[sock].u32PktLength, 0);
	}

	if(ret < 0)
	{
		if(ret != SOCK_ERR_BUFFER_FULL)
			M2M_ERR("Socket send error : %d", ret);
		return ret;
	}

	if(gastrIperfSocketInfo[sock].s32PktCount > 0)
		gastrIperfSocketInfo[sock].s32PktCount--;

	// Update the TX SQN
	gastrIperfSocketInfo[sock].u32TxSQN++;
	IperfAddUint64(&gastrIperfSocketInfo[sock].strTxBytes, gastrIperfSocketInfo[sock].u32PktLength);
	gastrIperfSocketInfo[sock].u32BytesLastPeriod += gastrIperfSocketInfo[sock].u32PktLength;

	return M2M_SUCCESS;
}

//------------------------------------------------------------------------------
static sint8 IperfTCP_SendTestPacket(SOCKET sock)
{
	tstrIperfSocketInfo *pstrSock;
	sint8 ret;

	pstrSock = &gastrIperfSocketInfo[sock];

	ret = send(sock, gstrTxMsgBuffer.gau8MsgBuffer, pstrSock->u32PktLength, 0);

	if(ret < 0)
	{
		if(ret != SOCK_ERR_BUFFER_FULL)
			M2M_ERR("ERROR Sock %d %d\r\n",sock,ret);
	}
	else
	{
		if(pstrSock->u32TxSQN == 0)
		{
			pstrSock->u32TimeStart = u32msTicks;
			pstrSock->u32LastStatsTime	= pstrSock->u32TimeStart;
			pstrSock->u8PktsOutstanding = 1;
		}

		pstrSock->u32TxSQN++;
		IperfAddUint64(&pstrSock->strTxBytes, pstrSock->u32PktLength);
		pstrSock->u32BytesLastPeriod += pstrSock->u32PktLength;
	}

	return ret;
}

//------------------------------------------------------------------------------
static SOCKET IperfUDP_ClientStart(tstrIperfInit* pstrIperfInit, bool bIsPaused)
{
	struct sockaddr_in	addr;
	SOCKET sock;

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if(sock < 0)
		return M2M_ERR_FAIL;

	memset((uint8_t*)&gastrIperfSocketInfo[sock], 0, sizeof(tstrIperfSocketInfo));

	IperfIncrementTimerUse();

	gastrIperfSocketInfo[sock].bIsActive			= true;
	gastrIperfSocketInfo[sock].bIsPaused			= bIsPaused;
	gastrIperfSocketInfo[sock].u8State				= TEST_STATE_UDP_TX;
	gastrIperfSocketInfo[sock].s32PktCount			= pstrIperfInit->packets_to_send;
	gastrIperfSocketInfo[sock].u32PktLength			= pstrIperfInit->packet_len;
	gastrIperfSocketInfo[sock].u8PktsOutstanding	= 5;

	if(pstrIperfInit->data_rate > 0)
	{
		gastrIperfSocketInfo[sock].u16MsPeriod = (pstrIperfInit->packet_len*8*1000)/pstrIperfInit->data_rate;
	}

	addr.sin_family			= AF_INET;
	addr.sin_port			= _htons(pstrIperfInit->port);
	addr.sin_addr.s_addr	= _htonl((uint32_t) (pstrIperfInit->ip[0]<<24 | pstrIperfInit->ip[1]<<16 | pstrIperfInit->ip[2]<<8 | pstrIperfInit->ip[3]));

	gastrIperfSocketInfo[sock].u32IPAddress			= addr.sin_addr.s_addr;
	gastrIperfSocketInfo[sock].u16Port				= pstrIperfInit->port;
	
	iperf_app_stat.udp_client = MODE_START;

	if(bIsPaused == false)
	{
		gastrIperfSocketInfo[sock].u32TimeStart			= u32msTicks;
		gastrIperfSocketInfo[sock].u32LastTransmission	= gastrIperfSocketInfo[sock].u32TimeStart;
		gastrIperfSocketInfo[sock].u32LastStatsTime		= gastrIperfSocketInfo[sock].u32TimeStart;

		return IperfUDP_SendTestPacket(sock, &addr);
	}

	return M2M_SUCCESS;
}

//------------------------------------------------------------------------------
static sint8 IperfTCP_ClientStart(tstrIperfInit* pstrIperfInit, bool bIsPaused)
{
	struct sockaddr_in addr;
	SOCKET sock;

	sock = socket(AF_INET, SOCK_STREAM, (pstrIperfInit->tls) ? SOCKET_FLAGS_SSL : 0);

	if(sock < 0)
		return M2M_ERR_FAIL;

	addr.sin_family			= AF_INET;
	addr.sin_port			= _htons(pstrIperfInit->port); 
	addr.sin_addr.s_addr	= _htonl((uint32_t) (pstrIperfInit->ip[0]<<24 | pstrIperfInit->ip[1]<<16 | pstrIperfInit->ip[2]<<8 | pstrIperfInit->ip[3]));
	tcp_client_sock = sock;

	// Bind and Connect to Server.
	SYS_CONSOLE_PRINT("connecting to server....\r\n");
	if(connect(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0)
		return M2M_ERR_FAIL;

	memset((uint8_t*)&gastrIperfSocketInfo[sock], 0, sizeof(tstrIperfSocketInfo));

	gastrIperfSocketInfo[sock].bIsActive	= true;
	gastrIperfSocketInfo[sock].bIsPaused	= bIsPaused;
	gastrIperfSocketInfo[sock].u8State		= TEST_STATE_TCP_TX;
	gastrIperfSocketInfo[sock].s32PktCount	= pstrIperfInit->packets_to_send;
	gastrIperfSocketInfo[sock].u32PktLength	= pstrIperfInit->packet_len;
	gastrIperfSocketInfo[sock].u32IPAddress = addr.sin_addr.s_addr;
	gastrIperfSocketInfo[sock].u16Port      = pstrIperfInit->port;
 
	SYS_CONSOLE_PRINT("------------------------------------------------------------\r\n");
	SYS_CONSOLE_PRINT("Client connecting to %lu.%lu.%lu.%lu, TCP port %i\r\n",
	(addr.sin_addr.s_addr & 0xFF), (addr.sin_addr.s_addr & 0xFF00) >> 8,
	(addr.sin_addr.s_addr & 0xFF0000) >> 16, (addr.sin_addr.s_addr & 0xFF000000) >> 24,pstrIperfInit->port);
	SYS_CONSOLE_PRINT("TCP window size: 1 KByte\r\n");
	SYS_CONSOLE_PRINT("------------------------------------------------------------\r\n");

	return M2M_SUCCESS;
}

//------------------------------------------------------------------------------
static sint8 IperfUDP_WriteFIN(SOCKET sock)
{
	uint32_t		 u32secTicks;
	uint32_t		 u32usTicks;

	u32secTicks = u32msTicks / 1000;
	u32usTicks  = (u32msTicks % 1000)*1000;

	// Store Sequence Number into the datagram
	gstrTxMsgBuffer.strUdpDatagram.id		= _htonl(-gastrIperfSocketInfo[sock].u32TxSQN);
	gstrTxMsgBuffer.strUdpDatagram.tv_sec	= _htonl(u32secTicks);
	gstrTxMsgBuffer.strUdpDatagram.tv_usec	= _htonl(u32usTicks);
	gstrTxMsgBuffer.strUdpClientHdr.flags	= 0;

	return send(sock, &gstrTxMsgBuffer, gastrIperfSocketInfo[sock].u32PktLength, 0);
}

//------------------------------------------------------------------------------
static void IperfPrintUdpServerStats(SOCKET sock, uint8_t u8UdpStateIdx)
{
	uint32_t u32TimeDelta;
	uint32_t u32AvrData;
	uint32_t u32KBytes;

	if((gastrIperfUdpState[u8UdpStateIdx].bIsActive == true) && (gastrIperfUdpState[u8UdpStateIdx].sockParent == sock))
	{
		u32TimeDelta = u32msTicks - gastrIperfUdpState[u8UdpStateIdx].u32TimeStart;
		u32AvrData   = IperfCalculateBandwidthKbps(&gastrIperfUdpState[u8UdpStateIdx].strRxBytes, u32TimeDelta);

		u32KBytes = (gastrIperfUdpState[u8UdpStateIdx].strRxBytes.u32H << 22) | (gastrIperfUdpState[u8UdpStateIdx].strRxBytes.u32L >> 10);
		udp_serv_pack_recv = u32KBytes;

		SYS_CONSOLE_PRINT("[%i.%d] Server Report:\r\n", sock, u8UdpStateIdx);
		SYS_CONSOLE_PRINT("[%i.%d] 0-%5ld sec %5ld KBytes %5ld Kbits/sec %5ld/%5ld\n", sock, u8UdpStateIdx, (u32TimeDelta/1000), u32KBytes, u32AvrData, gastrIperfUdpState[u8UdpStateIdx].u32RxMissingPkts, gastrIperfUdpState[u8UdpStateIdx].u32RxPkts);
	}
}

//------------------------------------------------------------------------------
void IperfSocketEventHandler(SOCKET sock, uint8_t u8Msg, void *pvMsg)
{
	sint8 ret;
	tstrIperfSocketInfo *pstrSock;
	uint32_t u32TimeDelta;

	if(sock >= MAX_SOCKET)
		return;

	pstrSock = &gastrIperfSocketInfo[sock];

	if(pstrSock->u8State == TEST_STATE_UDP_TX)
	{
		if(u8Msg == SOCKET_MSG_RECVFROM)
		{
			tstrSocketRecvMsg		*pstrRx = (tstrSocketRecvMsg*)pvMsg;
			tstrIperfUdpServerMsg	*pstrServerHdr = (tstrIperfUdpServerMsg*)pstrRx->pu8Buffer;

			// After the UDP Client completes the data transfer, the server sends a Report to the client.
			// Wait to close the socket until receive it.

			if(pstrRx->u16RemainingSize == 0)
			{
				IperfPrintStats(sock);

				if(pstrServerHdr->strUdpServerHdr.flags == _htonl(0x80000000))
				{
					uint32_t u32AvrData;
					uint32_t u32KBytes;
					tstrIperfUint64 strRxBytes;

					u32TimeDelta = (_ntohl(pstrServerHdr->strUdpServerHdr.stop_sec)*1000) + (_ntohl(pstrServerHdr->strUdpServerHdr.stop_usec)/1000);
					strRxBytes.u32H = _ntohl(pstrServerHdr->strUdpServerHdr.total_len1);
					strRxBytes.u32L = _ntohl(pstrServerHdr->strUdpServerHdr.total_len2);
					u32AvrData   = IperfCalculateBandwidthKbps(&strRxBytes, u32TimeDelta);

					u32KBytes = (strRxBytes.u32H << 22) | (strRxBytes.u32L >> 10);

					SYS_CONSOLE_PRINT("[%3i] Server Report:\n", sock);
					SYS_CONSOLE_PRINT("[%3i]    0-%4ld sec %5ld KBytes %5ld Kbits/sec %5ld/%5ld\r\n", sock, (u32TimeDelta/1000), u32KBytes, u32AvrData, _ntohl(pstrServerHdr->strUdpServerHdr.error_cnt), _ntohl(pstrServerHdr->strUdpServerHdr.datagrams));
					SYS_CONSOLE_PRINT("[%3i] Sent %ld datagrams\n", sock, _ntohl(pstrServerHdr->strUdpServerHdr.datagrams));
				}

				IperfSocketClose(sock);
			}
		}
	}
	else if(pstrSock->u8State == TEST_STATE_UDP_RX)
	{
		switch(u8Msg)
		{
			case SOCKET_MSG_BIND:
			{
				tstrSocketBindMsg	*pstrBind = (tstrSocketBindMsg*)pvMsg;
				if(pstrBind != NULL)
				{
					if(pstrBind->status == 0)
					{
						iperf_app_stat.udp_server = MODE_START;
						recvfrom(sock, &gstrRxMsgBuffer.gau8MsgBuffer, IPERF_RX_BUFFER_SIZE,0);
					}
					else
					{
						M2M_ERR("[sock %d] Bind error.\r\n", sock);
						IperfSocketClose(sock);
					}
				}
			}
			break;
     		case SOCKET_MSG_RECVFROM:
			{
				uint32_t id = 0;
				tstrSocketRecvMsg	*pstrRx = (tstrSocketRecvMsg*)pvMsg;
				tstrIperfUdpState	*pstrUdpState = NULL;
				tstrIperfUdpState	*pstrFreeUdpState = NULL;
				uint8_t u8UdpStateIdx;
				for(u8UdpStateIdx=0; u8UdpStateIdx<IPERF_MAX_UDP_STATE; u8UdpStateIdx++)
				{
					if(gastrIperfUdpState[u8UdpStateIdx].bIsActive == true)
					{
						if((gastrIperfUdpState[u8UdpStateIdx].sockParent == sock) && (gastrIperfUdpState[u8UdpStateIdx].u16Port == pstrRx->strRemoteAddr.sin_port))
						{
							pstrUdpState = &gastrIperfUdpState[u8UdpStateIdx];
							break;
						}
					}
				}

				if(pstrRx->pu8Buffer != NULL)
				{
					UDP_datagram *pstrUDPhdr = (UDP_datagram*)pstrRx->pu8Buffer;

					id = _ntohl(pstrUDPhdr->id);

					if((id & NBIT31) == NBIT31)
					{
						if(pstrUdpState == NULL)
							break;

						gstrTxSrvMsg.strUdpDatagram.id = pstrUDPhdr->id;

						u32TimeDelta = u32msTicks - pstrUdpState->u32TimeStart;

						gstrTxSrvMsg.strUdpServerHdr.flags = _htonl(0x80000000);
						gstrTxSrvMsg.strUdpServerHdr.datagrams = _htonl(-id);
						gstrTxSrvMsg.strUdpServerHdr.error_cnt = _htonl(pstrUdpState->u32RxMissingPkts);
						gstrTxSrvMsg.strUdpServerHdr.jitter1 = 0;
						gstrTxSrvMsg.strUdpServerHdr.jitter2 = 0;
						gstrTxSrvMsg.strUdpServerHdr.outorder_cnt = 0;
						gstrTxSrvMsg.strUdpServerHdr.stop_sec = _htonl(u32TimeDelta/1000);
						gstrTxSrvMsg.strUdpServerHdr.stop_usec = _htonl(u32TimeDelta%1000)*1000;
						gstrTxSrvMsg.strUdpServerHdr.total_len1 = _htonl(pstrUdpState->strRxBytes.u32H);
						gstrTxSrvMsg.strUdpServerHdr.total_len2 = _htonl(pstrUdpState->strRxBytes.u32L);

						ret = sendto(sock, &gstrTxSrvMsg, sizeof(tstrIperfUdpServerMsg), 0, (struct sockaddr*)&pstrRx->strRemoteAddr, sizeof(struct sockaddr_in));
						if(ret != M2M_SUCCESS)
						{
							if(ret != SOCK_ERR_BUFFER_FULL)
                                SYS_CONSOLE_PRINT("sendto failed error = %d\r\n", ret);
						}
						IperfPrintUdpServerStats(sock, u8UdpStateIdx);
						memset((uint8_t*)pstrUdpState, 0, sizeof(tstrIperfUdpState));
						IperfDecrementTimerUse();
						udp_server_sock = sock;
						struct server_hdr *hdr = (struct server_hdr *)(pstrUDPhdr + 1);
						if (ntohl(hdr->flags) & HEADER_VERSION1)
						{
							iperf_app_stat.udp_server = MODE_WAIT;
						}
						else{
							iperf_app_stat.udp_server = MODE_FINISHED;
						}
					}
					else
					{
						if(pstrUdpState == NULL)
						{
							for(u8UdpStateIdx=0; u8UdpStateIdx<IPERF_MAX_UDP_STATE; u8UdpStateIdx++)
							{
								if(gastrIperfUdpState[u8UdpStateIdx].bIsActive == false)
								{
									pstrFreeUdpState = &gastrIperfUdpState[u8UdpStateIdx];
									break;
								}
							}

							if(pstrFreeUdpState != NULL)
							{
								udp_client_addr.sin_family = AF_INET;
								udp_client_addr.sin_port = pstrRx->strRemoteAddr.sin_port;
								udp_client_addr.sin_addr.s_addr = pstrRx->strRemoteAddr.sin_addr.s_addr;
								SYS_CONSOLE_PRINT("[%i.%d] local %s port %d connected with", sock, u8UdpStateIdx, inet_ntoa(pstrSock->u32IPAddress), pstrSock->u16Port);
								SYS_CONSOLE_PRINT(" %s port %d\r\r\n", inet_ntoa(pstrRx->strRemoteAddr.sin_addr.s_addr), _htons(pstrRx->strRemoteAddr.sin_port));

								memset((uint8_t*)pstrFreeUdpState, 0, sizeof(tstrIperfUdpState));

								pstrFreeUdpState->bIsActive = true;
								pstrFreeUdpState->sockParent = sock;
								pstrFreeUdpState->u16Port = pstrRx->strRemoteAddr.sin_port;

								IperfIncrementTimerUse();

								pstrUdpState = pstrFreeUdpState;
								pstrUdpState->u32NextRxSeqNum = 0;
								pstrUdpState->u32TimeStart = u32msTicks;
								pstrFreeUdpState->u32LastStatsTime = pstrUdpState->u32TimeStart;
							}
						}

						if(pstrUdpState == NULL)
							break;

						// Duplicate.
						if (pstrUdpState->u32NextRxSeqNum > id)
							break;

						if (pstrUdpState->u32NextRxSeqNum != id)
						{
							pstrUdpState->u32RxMissingPkts += id - pstrUdpState->u32NextRxSeqNum;
							pstrUdpState->u16RxMissingPktsLastPeriod += id - pstrUdpState->u32NextRxSeqNum;
						}

						pstrUdpState->u32NextRxSeqNum = id + 1;

						pstrSock->u32RxPkts++;
						pstrUdpState->u32RxPkts++;
						pstrUdpState->u16RxPktsLastPeriod++;

						if(pstrRx->s16BufferSize > 0)
						{
							IperfAddUint64(&pstrUdpState->strRxBytes, pstrRx->s16BufferSize + pstrRx->u16RemainingSize);
							pstrUdpState->u32BytesLastPeriod += (pstrRx->s16BufferSize + pstrRx->u16RemainingSize);
						}
					}

					recvfrom(sock, &gstrRxMsgBuffer.gau8MsgBuffer, IPERF_RX_BUFFER_SIZE, 0);
				}
				else if(pstrRx->s16BufferSize <= 0)
				{
					SYS_CONSOLE_PRINT("UDP server error %d\r\n", pstrRx->s16BufferSize);
					IperfSocketClose(sock);
				}
			}
			break;
		}
	}
	else if(pstrSock->u8State == TEST_STATE_TCP_RX)
	{
		switch(u8Msg)
		{
			case SOCKET_MSG_ACCEPT:
			{
				tstrSocketAcceptMsg *msg = (tstrSocketAcceptMsg*)pvMsg;

				accept(sock, NULL, 0);

				IperfIncrementTimerUse();

				SYS_CONSOLE_PRINT("[%3d] local %s port %d connected with", msg->sock, inet_ntoa(pstrSock->u32IPAddress), pstrSock->u16Port);

				pstrSock = &gastrIperfSocketInfo[msg->sock];

				memset((uint8_t*)pstrSock, 0, sizeof(tstrIperfSocketInfo));

				pstrSock->bIsActive			= true;
				pstrSock->u8State			= TEST_STATE_TCP_RX;
				pstrSock->sockParent		= sock;
				pstrSock->u32TimeStart		= u32msTicks;
				pstrSock->u32LastStatsTime	= pstrSock->u32TimeStart;
				pstrSock->u32IPAddress		= msg->strAddr.sin_addr.s_addr;
				pstrSock->u16Port			= _ntohs(msg->strAddr.sin_port);
								
				iperf_app_stat.tcp_server = MODE_START;
				clientIPAddress = pstrSock->u32IPAddress;

				ret = recv(msg->sock, gstrRxMsgBuffer.gau8MsgBuffer, IPERF_RX_BUFFER_SIZE, 0);

				SYS_CONSOLE_PRINT(" %s port %d\r\n", inet_ntoa(pstrSock->u32IPAddress), pstrSock->u16Port);
			}
			break;

			case SOCKET_MSG_RECV:
			{
				tstrSocketRecvMsg *msg = (tstrSocketRecvMsg*)pvMsg;
				
				if(msg ==0 || (msg->s16BufferSize <= 0))
				{
                    SYS_CONSOLE_PRINT("\nBuffersize:%d\n\r",msg->s16BufferSize);
                    IperfPrintStats(sock);
					IperfSocketClose(sock);
					pstrSock->bIsActive = false;
					/* Prepare TX test if demanded (-r option). */
					if (_ntohl(iperf_tcp_serv.flags) & HEADER_VERSION1)
					{
						iperf_app_stat.tcp_server = MODE_WAIT;
						iperf_app_stat.tcp_client = MODE_INIT;
					} 
					else
					{
						iperf_app_stat.tcp_server = MODE_FINISHED;
					}
				}
				else
				{
					if(pstrSock->sockParent >= 0)
					{
						IperfAddUint64(&gastrIperfSocketInfo[pstrSock->sockParent].strRxBytes, msg->s16BufferSize);
					}

					IperfAddUint64(&pstrSock->strRxBytes, msg->s16BufferSize);
					pstrSock->u32BytesLastPeriod += msg->s16BufferSize;

					pstrSock->u32PktByteCount += msg->s16BufferSize;
					if(pstrSock->u32PktByteCount >= pstrSock->u32PktLength)
					{
						pstrSock->u32RxPkts++;
						pstrSock->u32PktByteCount -= pstrSock->u32PktLength;
					}

					recv(sock, gstrRxMsgBuffer.gau8MsgBuffer, IPERF_RX_BUFFER_SIZE, 0);
				}
				
				if (iperf_app_stat.tcp_server == MODE_START)
				{
					iperf_app_stat.tcp_server = MODE_RUN;
					memcpy(&iperf_tcp_serv, gstrRxMsgBuffer.gau8MsgBuffer, sizeof(struct client_hdr));
					if (_ntohl(iperf_tcp_serv.flags) & RUN_NOW) {
						// --dualtest not implemented
						SYS_CONSOLE_PRINT("iperf_socket_handler: Unsupported options -d, closing connection...\n");
						while (1);
					}
				}
								
			}
			break;
		}
	}
	else if(pstrSock->u8State == TEST_STATE_TCP_TX)
	{
		switch(u8Msg)
		{
			case SOCKET_MSG_CONNECT:
			{
				tstrSocketConnectMsg *pstrConnect = (tstrSocketConnectMsg *)pvMsg;
				if (pstrConnect && pstrConnect->s8Error >= 0) {
					//printf("socket_cb: connect success! %d\r\n",pstrConnect->s8Error);
					SYS_CONSOLE_PRINT( "[%3i] local %s port %d connected with", sock, inet_ntoa(gu32IPAddress), 0);
					SYS_CONSOLE_PRINT( " %s port %d\r\n", inet_ntoa(pstrSock->u32IPAddress), pstrSock->u16Port);
					iperf_app_stat.tcp_client = MODE_START;
				} else 
                {
					SYS_CONSOLE_PRINT( "socket_cb: connect error!\r\n");
				}
			}
			break;

			case SOCKET_MSG_SEND:
			{
				short s16SentBytes = *((short*)pvMsg);
                

				if(pstrSock->bIsActive == true)
				{
					if(s16SentBytes < 0)
					{
						SYS_CONSOLE_PRINT("\nError %d: PIperf finished on: SOCKET   %02u    Next TX SQN = %04lu\r\n", s16SentBytes, sock, pstrSock->u32TxSQN);
						IperfPrintStats(sock);
						IperfSocketClose(sock);
					}
					else
					{
						pstrSock->u32PktByteCount += s16SentBytes;
                    	while(pstrSock->u32PktByteCount >= pstrSock->u32PktLength)
						{
							pstrSock->u32PktByteCount -= pstrSock->u32PktLength;
							pstrSock->u8PktsOutstanding--;

							if(pstrSock->s32PktCount > 0)
								pstrSock->s32PktCount--;
						}

						if(pstrSock->s32PktCount == 0)
						{
							IperfPrintStats(sock);
							IperfSocketClose(sock);
							pstrSock->bIsActive = false;
							iperf_app_stat.tcp_server = MODE_INIT;
							iperf_app_stat.tcp_client = MODE_FINISHED;
						}
						else
						{
    						while((pstrSock->u8PktsOutstanding < 5) && ((pstrSock->s32PktCount == -1 ) || (pstrSock->u8PktsOutstanding < pstrSock->s32PktCount)))
    						{
        						if(IperfTCP_SendTestPacket(sock) == 0)
        						pstrSock->u8PktsOutstanding++;
    						}
						}
					}
				}
			}
		}
	}
	//m2m_wifi_yield();
}

//------------------------------------------------------------------------------
static sint8 IperfUDP_ServerStart(tstrIperfInit* pstrIperfInit)
{
	struct sockaddr_in addr_in;
	SOCKET sock;

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if(sock < 0)
		return M2M_ERR_FAIL;

	addr_in.sin_family = AF_INET;
	addr_in.sin_port = _htons(pstrIperfInit->port);
	addr_in.sin_addr.s_addr = 0;

	if(bind(sock, (struct sockaddr*)&addr_in, sizeof(struct sockaddr_in)) < 0) {
		SYS_CONSOLE_PRINT("UDP socket binding failed\r\n reset the board");
		return M2M_ERR_FAIL;
	}

	memset((uint8_t*)&gastrIperfSocketInfo[sock], 0, sizeof(tstrIperfSocketInfo));

	gastrIperfSocketInfo[sock].bIsActive = true;
	gastrIperfSocketInfo[sock].u8State = TEST_STATE_UDP_RX;
	gastrIperfSocketInfo[sock].u32IPAddress = gu32IPAddress;
	gastrIperfSocketInfo[sock].u16Port = pstrIperfInit->port;
    
    SYS_CONSOLE_PRINT("\n\n\n------------------------------------------------------------\r\n");
	SYS_CONSOLE_PRINT("Server listening on UDP port 5001\r\n");
	//SYS_CONSOLE_PRINT("TCP window size: 1 KByte\r\n");
	SYS_CONSOLE_PRINT("------------------------------------------------------------\r\n");
	
	return M2M_SUCCESS;
}

//------------------------------------------------------------------------------
static sint8 IperfTCP_ServerStart(tstrIperfInit* pstrIperfInit)
{
	struct sockaddr_in addr_in;
	SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0)
		return M2M_ERR_FAIL;

	addr_in.sin_family = AF_INET;
	addr_in.sin_port = _htons(pstrIperfInit->port);
	addr_in.sin_addr.s_addr = 0;

	if(bind(sock, (struct sockaddr*)&addr_in, sizeof(struct sockaddr_in)) < 0)
		return M2M_ERR_FAIL;

	if(listen(sock, TCP_SOCK_MAX) < 0)
		return M2M_ERR_FAIL;

	if(accept(sock, NULL, 0) < 0)
		return M2M_ERR_FAIL;

	memset((uint8_t*)&gastrIperfSocketInfo[sock], 0, sizeof(tstrIperfSocketInfo));

	gastrIperfSocketInfo[sock].bIsActive = true;
	gastrIperfSocketInfo[sock].u8State = TEST_STATE_TCP_RX;
	gastrIperfSocketInfo[sock].sockParent = -1;
	gastrIperfSocketInfo[sock].u32IPAddress = gu32IPAddress;
	gastrIperfSocketInfo[sock].u16Port = pstrIperfInit->port;

	SYS_CONSOLE_PRINT("\n\n\n------------------------------------------------------------\r\n");
	SYS_CONSOLE_PRINT("Server listening on TCP/UDP port 5001\r\n");
	SYS_CONSOLE_PRINT("TCP window size: 1 KByte\r\n");
	SYS_CONSOLE_PRINT("------------------------------------------------------------\r\n");
				
	return M2M_SUCCESS;
}

//------------------------------------------------------------------------------
static sint8 IperfSocketStop(SOCKET sock)
{
	if(gastrIperfSocketInfo[sock].u8State == TEST_STATE_UDP_TX)
	{
		gastrIperfSocketInfo[sock].s32PktCount = 0;
	}
	else
	{
		IperfPrintStats(sock);
		return IperfSocketClose(sock);
	}

	return M2M_SUCCESS;
}

//------------------------------------------------------------------------------
void IperfInit(void)
{
	uint16_t u16Len;

	gu8NumSockets = 0;

	memset((uint8_t*)&gastrIperfSocketInfo, 0, sizeof(gastrIperfSocketInfo));
	memset((uint8_t*)&gastrIperfUdpState, 0, sizeof(gastrIperfUdpState));

	u16Len = IPERF_BUFFER_SIZE;

    while(u16Len-- > 0)
        gstrTxMsgBuffer.gau8MsgBuffer[u16Len] = (u16Len % 10) + '0';
}

//------------------------------------------------------------------------------
void IperfPrintStats(SOCKET sock)
{
	uint8_t u8UdpStateIdx;
	uint32_t u32TimeDelta;
	uint32_t u32AvrData;
	uint32_t u32KBytes;

	if(gastrIperfSocketInfo[sock].bIsActive == false)
		return;

	switch(gastrIperfSocketInfo[sock].u8State)
	{
		case TEST_STATE_UDP_RX:
			for(u8UdpStateIdx=0; u8UdpStateIdx<IPERF_MAX_UDP_STATE; u8UdpStateIdx++)
				IperfPrintUdpServerStats(sock, u8UdpStateIdx);
			break;

		case TEST_STATE_TCP_RX:
			u32TimeDelta = u32msTicks - gastrIperfSocketInfo[sock].u32TimeStart;
			u32AvrData   = IperfCalculateBandwidthKbps(&gastrIperfSocketInfo[sock].strRxBytes, u32TimeDelta);

			tcp_serv_pack_recv = (u32TimeDelta/1000)<<9;
			u32KBytes = (gastrIperfSocketInfo[sock].strRxBytes.u32H << 22) | (gastrIperfSocketInfo[sock].strRxBytes.u32L >> 10);

			SYS_CONSOLE_PRINT("[%3i] Server Report:\n", sock);
			SYS_CONSOLE_PRINT("[%3i]    0-%4ld sec %5ld KBytes %5ld Kbits/sec\r\n", sock, (u32TimeDelta/1000), u32KBytes, u32AvrData);
			break;

		case TEST_STATE_UDP_TX:
			u32TimeDelta = u32msTicks - gastrIperfSocketInfo[sock].u32TimeStart;
			u32AvrData   = IperfCalculateBandwidthKbps(&gastrIperfSocketInfo[sock].strTxBytes, u32TimeDelta);

			u32KBytes = (gastrIperfSocketInfo[sock].strTxBytes.u32H << 22) | (gastrIperfSocketInfo[sock].strTxBytes.u32L >> 10);

			SYS_CONSOLE_PRINT("[%3i] Client Report:\r\n", sock);
			SYS_CONSOLE_PRINT("[%3i]    0-%4ld sec %5ld KBytes %5ld Kbits/sec\r\n", sock, (u32TimeDelta/1000), u32KBytes, u32AvrData);
			iperf_app_stat.udp_client = MODE_STOP;
			iperf_app_stat.udp_server = MODE_INIT;
			break;

		case TEST_STATE_TCP_TX:
			u32TimeDelta = u32msTicks - gastrIperfSocketInfo[sock].u32TimeStart;
			u32AvrData   = IperfCalculateBandwidthKbps(&gastrIperfSocketInfo[sock].strTxBytes, u32TimeDelta);

			u32KBytes = (gastrIperfSocketInfo[sock].strTxBytes.u32H << 22) | (gastrIperfSocketInfo[sock].strTxBytes.u32L >> 10);

			SYS_CONSOLE_PRINT("[%3i] Client Report:\r\n", sock);
			SYS_CONSOLE_PRINT("[%3i]    0-%4ld sec %5ld KBytes %5ld Kbits/sec\r\n", sock, (u32TimeDelta/1000), u32KBytes, u32AvrData);
			break;
			
		default:
			break;
	}
}

//------------------------------------------------------------------------------
sint8 IperfSocketClose(SOCKET sock)
{
	int i;

	if (sock > MAX_SOCKET)
		return M2M_ERR_FAIL;

	if(gastrIperfSocketInfo[sock].bIsActive == false)
		return M2M_ERR_FAIL;

	if((gastrIperfSocketInfo[sock].u8State == TEST_STATE_TCP_RX) && (gastrIperfSocketInfo[sock].sockParent == -1))
	{
		for(i=0;i<TCP_SOCK_MAX;i++)
		{
			if(gastrIperfSocketInfo[i].bIsActive == false)
				continue;

			if((gastrIperfSocketInfo[i].u8State == TEST_STATE_TCP_RX) && (gastrIperfSocketInfo[i].sockParent == sock))
			{
				IperfPrintStats(i);
				IperfSocketClose(i);
			}
		}
	}
	else if(gastrIperfSocketInfo[sock].u8State != TEST_STATE_UDP_RX)
		IperfDecrementTimerUse();

	if((gastrIperfSocketInfo[sock].u8State == TEST_STATE_UDP_RX) && (gastrIperfSocketInfo[sock].bIsActive == true))
	{
		for(i=0; i<IPERF_MAX_UDP_STATE; i++)
		{
			if((gastrIperfUdpState[i].bIsActive == true) && (gastrIperfUdpState[i].sockParent == sock))
			{
				memset((uint8_t*)&gastrIperfUdpState[i], 0, sizeof(tstrIperfUdpState));
				IperfDecrementTimerUse();
			}
		}
	}

	memset((uint8_t*)&gastrIperfSocketInfo[sock], 0, sizeof(tstrIperfSocketInfo));

	SYS_CONSOLE_PRINT("Closing socket %i\r\n",sock);

	return shutdown(sock);
}

//------------------------------------------------------------------------------
void IperfUpdate(void)
{
	int i, j;
	uint32_t u32TimeDelta;
	uint32_t u32AvrData;
	uint32_t u32T1;
	tstrIperfSocketInfo *pstrSock;
	tstrIperfUdpState   *pstrUdpState;

	for(i=TCP_SOCK_MAX; i<MAX_SOCKET; i++)
	{
		pstrSock = &gastrIperfSocketInfo[i];

		if(pstrSock->bIsActive && !pstrSock->bIsPaused && (pstrSock->u8State == TEST_STATE_UDP_TX))
		{
			if(pstrSock->s32PktCount == 0)
			{
				if(pstrSock->u8PktsOutstanding-- > 0)
				{
					if(IperfUDP_WriteFIN(i) == M2M_SUCCESS)
					{
						recvfrom(i, &gstrRxMsgBuffer.gau8MsgBuffer, IPERF_RX_BUFFER_SIZE, 0);
					}
				}
				else
				{
					IperfPrintStats(i);
					IperfSocketClose(i);
				}
			}
			else
			{
				u32TimeDelta = u32msTicks - pstrSock->u32LastTransmission;

				if(!pstrSock->u16MsPeriod || (u32TimeDelta > pstrSock->u16MsPeriod))
				{
					IperfUDP_SendTestPacket(i, NULL);
					pstrSock->u32LastTransmission += pstrSock->u16MsPeriod;
				}
			}
		}
	}
	
	u32TimeDelta = u32msTicks - u32LastStatsTime;
	if(u32TimeDelta >= 1000)
	{
        //SYS_CONSOLE_PRINT("Time_delta:%d",u32TimeDelta);
		u32LastStatsTime += 1000;
		
		uint32_t u32SumBytesLastPeriod = 0;
		uint32_t u32SumT1 = 0;
		uint32_t u32SumTimeDelta = 0;
		uint8_t u8StreamCount = 0;

		for(i=0; i<MAX_SOCKET; i++)
		{
			pstrSock = &gastrIperfSocketInfo[i];

			if(pstrSock->bIsActive && !pstrSock->bIsPaused)
			{
				if((pstrSock->u8State == TEST_STATE_UDP_TX) || (pstrSock->u8State == TEST_STATE_TCP_TX) || ((pstrSock->u8State == TEST_STATE_TCP_RX) && (pstrSock->sockParent != -1)))
				{
					u32AvrData = (pstrSock->u32BytesLastPeriod*8) / u32TimeDelta;
					u32T1 = (u32LastStatsTime - pstrSock->u32TimeStart) / 1000;

					if(u8StreamCount == 0)
					{
						u32SumTimeDelta = u32msTicks - pstrSock->u32TimeStart;
						u32SumT1 = u32T1;
					}
					
					u8StreamCount++;
					
					u32SumBytesLastPeriod += pstrSock->u32BytesLastPeriod;

					SYS_CONSOLE_PRINT("[%3d] %4lu-%4ld sec %5ld KBytes %5ld Kbits/sec\r\n", i, u32T1, ((u32msTicks - pstrSock->u32TimeStart)/1000), pstrSock->u32BytesLastPeriod / 1024, u32AvrData);

					pstrSock->u32BytesLastPeriod = 0;
				}
				else if(pstrSock->u8State == TEST_STATE_UDP_RX)
				{
					for(j=0; j<IPERF_MAX_UDP_STATE; j++)
					{
						pstrUdpState = &gastrIperfUdpState[j];
	
						if((pstrUdpState->bIsActive == true) && (pstrUdpState->sockParent == i))
						{
							u32AvrData = (pstrUdpState->u32BytesLastPeriod * 8) / u32TimeDelta;
							u32T1 = (u32LastStatsTime - pstrUdpState->u32TimeStart) / 1000;

							if(u8StreamCount == 0)
							{
								u32SumTimeDelta = u32msTicks - pstrUdpState->u32TimeStart;
								u32SumT1 = u32T1; // Use the time from the first stream for the the SUM
							}
								
							u8StreamCount++;

							u32SumBytesLastPeriod += pstrUdpState->u32BytesLastPeriod;

							SYS_CONSOLE_PRINT("[%d.%d] %4lu-%4d sec %5ld KBytes %5ld Kbits/sec %5d/%5d\r\n", i, j, u32T1, (uint16_t)((u32msTicks - pstrUdpState->u32TimeStart)/1000), pstrUdpState->u32BytesLastPeriod / 1024, u32AvrData, pstrUdpState->u16RxMissingPktsLastPeriod, pstrUdpState->u16RxPktsLastPeriod);
							pstrUdpState->u32BytesLastPeriod = 0;
							pstrUdpState->u16RxMissingPktsLastPeriod = 0;
							pstrUdpState->u16RxPktsLastPeriod = 0;
						}
					}
				}
			}
		}
		
		if(u8StreamCount > 1)
		{
            u32AvrData = (u32SumBytesLastPeriod*8) / u32TimeDelta;
			SYS_CONSOLE_PRINT("[SUM] %4lu-%4d sec %5ld KBytes %5ld Kbits/sec\n", u32SumT1, (uint16_t)(u32SumTimeDelta/1000), u32SumBytesLastPeriod / 1024, u32AvrData);
		}
	}
}

//------------------------------------------------------------------------------
sint8 IperfCreate(tstrIperfInit* pstrIperfInit, bool bIsPaused)
{
	sint8 ret = M2M_ERR_FAIL;

	switch(pstrIperfInit->operating_mode)
	{
		case MODE_TCP_SERVER:
           	ret = IperfTCP_ServerStart(pstrIperfInit);
			break;

		case MODE_UDP_SERVER:
			ret = IperfUDP_ServerStart(pstrIperfInit);
            SYS_CONSOLE_PRINT("UDP server start\r\n");
			break;

		case MODE_UDP_CLIENT:
			ret = IperfUDP_ClientStart(pstrIperfInit, bIsPaused);
			break;

		case MODE_TCP_CLIENT:
			ret = IperfTCP_ClientStart(pstrIperfInit, bIsPaused);
			break;
	}
	if (ret == M2M_ERR_FAIL)
		SYS_CONSOLE_PRINT("Failed to create the socket\r\n");
	
	return ret;
}

//------------------------------------------------------------------------------
sint8 IperfStart(void)
{
	int i;
	tstrIperfSocketInfo *pstrSock;

	for(i=0; i<MAX_SOCKET; i++)
	{
		pstrSock = &gastrIperfSocketInfo[i];

		if(pstrSock->bIsActive && pstrSock->bIsPaused)
		{
			if(pstrSock->u8State == TEST_STATE_TCP_TX)
			{
				pstrSock->bIsPaused = false;
				IperfTCP_SendTestPacket(i);
			}
			else if(pstrSock->u8State == TEST_STATE_UDP_TX)
			{
				struct sockaddr_in addr;

				pstrSock->bIsPaused = false;

				addr.sin_family			= AF_INET;
				addr.sin_port			= _htons(pstrSock->u16Port);
				addr.sin_addr.s_addr	= pstrSock->u32IPAddress;

				pstrSock->u32TimeStart			= u32msTicks;
				pstrSock->u32LastTransmission	= pstrSock->u32TimeStart;
				pstrSock->u32LastStatsTime		= pstrSock->u32TimeStart;

				IperfUDP_SendTestPacket(i, &addr);
			}
		}
	}

	return M2M_SUCCESS;
}

//------------------------------------------------------------------------------
sint8 IperfStop(SOCKET sock)
{
	int i;

	if (sock > MAX_SOCKET)
		return M2M_ERR_FAIL;

	if(sock == -1)
	{
		for(i=0; i<MAX_SOCKET; i++)
			IperfSocketStop(i);
	}
	else
	{
		return IperfSocketStop(sock);
	}

	return M2M_SUCCESS;
}

void IperfTCP_Client_SendTestPacket(void)
{
	IperfIncrementTimerUse();
	IperfTCP_SendTestPacket(tcp_client_sock);
}
