/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_cert_download_ota.c

  Summary:
    This file contains the source code for the MPLAB Harmony certificate download via OTA application.

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
#ifdef APP_CERT_DOWNLOAD_OTA
#include "wdrv_winc_client_api.h"
#include "app_cert_download_ota.h"
#include "iot/http/http_client.h"
#include "iot/sw_timer.h"
#include "wdrv_winc_common.h"

#include "root_tls_cert/root_setup.h"
#include "root_tls_cert/tls_setup.h"

#define APP_CERT_DOWNLOAD_MAX_URL_SIZE   100


typedef enum
{
    /* Example's state machine's initial state. */
    APP_CERT_DOWNLOAD_OTA_STATE_INIT=0,
    APP_CERT_DOWNLOAD_OTA_STATE_CONNECTING,
    APP_CERT_DOWNLOAD_OTA_STATE_CONNECTED,
    APP_CERT_DOWNLOAD_OTA_STATE_HTTP_DOWNLOAD_INIT,
    APP_CERT_DOWNLOAD_OTA_STATE_DOWNLOADING,            
    APP_CERT_DOWNLOAD_OTA_STATE_DOWNLOAD_COMPLETE,   
    APP_CERT_DOWNLOAD_OTA_STATE_DISCONNECTED,
    APP_CERT_DOWNLOAD_OTA_STATE_ERROR,
    APP_CERT_DOWNLOAD_OTA_STATE_DONE,
} APP_CERT_DOWNLOAD_OTA_STATES;

static APP_CERT_DOWNLOAD_OTA_STATES appCertState;

/** File download processing state. */
static download_state down_state = NOT_READY;
/** Http content length. */
static uint32_t http_file_size = 0;
/** Receiving content length. */
static uint32_t received_file_size = 0;
/** Certificates size. */
static uint32_t total_size = 0, cert_start_idx=0;
/** Stores all the certificates. */
static uint8_t certificate_bufer[CERTIFICATES_BUFFER_SIZE];

/** Instance of HTTP client module. */
struct http_client_module http_client_module_inst;

/** http URL **/
static char http_url[MAIN_MAX_FILE_NAME_LENGTH];

tstrFileInfo root_tls_certs[NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES];
static uint8_t cert_idx = 0;
static int8_t burn_certificates(void);


/** Root Certificates to be uploaded */
/** Chain of TLS Certificates and private key to be uploaded */
certFileInfo root_tls_certs_name[NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES]=
{
#ifdef ROOT_CERT_BUNDLE
{ROOT_CERT,0,(uint8_t*)"root_certs.bin"},
#else
{ROOT_CERT,0,(uint8_t*)"GlobalSignRoot.cer"},
{ROOT_CERT,0,(uint8_t*)"AmazonRootCA1.cer"},
{ROOT_CERT,0,(uint8_t*)"ISRGRootX1.cer"},
#endif
};


extern void http_client_socket_event_handler(SOCKET sock, uint8_t msg_type, void *msg_data);


char APP_CERT_DOWNLOAD_OTA_URL_Buffer[APP_CERT_DOWNLOAD_MAX_URL_SIZE];

static int APP_CertDownloadOtaCMDProcess
(
    SYS_CMD_DEVICE_NODE* pCmdIO, 
    int argc, 
    char** argv
) 
{
   if (argc != 2)
   {
       return -1;
   }
   
   if (!strcmp(argv[1], "help"))
   {
        SYS_CONSOLE_PRINT("cert <image url>\r\n");
        SYS_CONSOLE_PRINT("E.g: cert http://192.168.1.12/");
   }
   else
   {
       strncpy(APP_CERT_DOWNLOAD_OTA_URL_Buffer, argv[1], APP_CERT_DOWNLOAD_MAX_URL_SIZE);
       appCertState = APP_CERT_DOWNLOAD_OTA_STATE_INIT; 
   }
   return 0;
}

static const SYS_CMD_DESCRIPTOR APP_CertDownloadOtaCmdTbl[] =
{
    {"cert", (SYS_CMD_FNC) APP_CertDownloadOtaCMDProcess, "cert: Socket mode OTA commands processing"},   
};

/**
 * \brief Checking the USART buffer.
 *
 * Finding the new line character(\n or \r\n) in the USART buffer.
 * If buffer was overflowed, Sending the buffer.
 */


/**
 * \brief Initialize download state to not ready.
 */
//static void init_state(void)
//{       
//        down_state = NOT_READY;
//}

/**
 * \brief Clear state parameter at download processing state.
 * \param[in] mask Check download_state.
 */
static void clear_state(download_state mask)
{       
        down_state &= ~mask;
}

static void add_state(download_state mask)
{
        down_state |= mask;
}

/**
 * \brief File download processing state check.
 * \param[in] mask Check download_state.
 * \return true if this state is set, false otherwise.
 */

static inline bool is_state_set(download_state mask)
{
        return ((down_state & mask) != 0);
}

/**
 * \brief Start file download via HTTP connection.
 */
static void start_download(void)
{
        if (!is_state_set(WIFI_CONNECTED)) {
                SYS_CONSOLE_PRINT("start_download: Wi-Fi is not connected.\r\n");
                return;
        }

        if (is_state_set(GET_REQUESTED)) {
                SYS_CONSOLE_PRINT("start_download: request is sent already.\r\n");
                return;
        }

        if (is_state_set(DOWNLOADING)) {
                SYS_CONSOLE_PRINT("start_download: running download already.\r\n");
                return;
        }

        /* Send the HTTP request. */
        SYS_CONSOLE_PRINT("start_download: sending HTTP request...\r\n");
        http_client_module_inst.config.port = MAIN_HTTP_PORT_NUMBER;
        SYS_CONSOLE_PRINT("Client request: %d\r\n",http_client_send_request(&http_client_module_inst, http_url, HTTP_METHOD_GET, NULL, NULL));
}

/**
 * \brief Complete file received.
 * \param[in] data Packet data.
 * \param[in] length Packet data length.
 */
static void store_file_packet_complete(void)
{
        SYS_CONSOLE_PRINT("store_file_packet_complete: file downloaded successfully.\r\n");
        add_state(COMPLETED);
        clear_state(HTTP_DOWNLOAD_INITIATED);
        root_tls_certs[cert_idx].pu8FileData = &certificate_bufer[cert_start_idx];
        root_tls_certs[cert_idx].u32FileSz = received_file_size;
        cert_start_idx += received_file_size;
        cert_start_idx = WORD_ALIGN(cert_start_idx);
        cert_idx++;
}

/**
 * \brief Store received packet to file.
 * \param[in] data Packet data.
 * \param[in] length Packet data length.
 */
static void store_file_packet(char *data, uint32_t length)
{
        if ((data == NULL) || (length < 1)) {
                SYS_CONSOLE_PRINT("store_file_packet: empty data.\r\n");
                return;
        }

        if (!is_state_set(DOWNLOADING)) {
                received_file_size = 0;                
                add_state(DOWNLOADING);
        }

        if (data != NULL) {
                for(uint16_t idx=0;idx<length;idx++)
                  certificate_bufer[total_size++] = data[idx];
        received_file_size = received_file_size+length;

                SYS_CONSOLE_PRINT("store_file_packet: received[%d]\r\n", (unsigned long)length);
                if (received_file_size >= http_file_size) {
                  store_file_packet_complete();
                  total_size = cert_start_idx;
                }
        }
}

/**
 * \brief Callback of the HTTP client.
 *
 * \param[in]  module_inst     Module instance of HTTP client module.
 * \param[in]  type            Type of event.
 * \param[in]  data            Data structure of the event. \refer http_client_data
 */
void http_client_callback(struct http_client_module *module_inst, int type, union http_client_data *data)
{
        switch (type) {
        case HTTP_CLIENT_CALLBACK_SOCK_CONNECTED:
                SYS_CONSOLE_PRINT("http_client_callback: HTTP client socket connected.\r\n");
                break;

        case HTTP_CLIENT_CALLBACK_REQUESTED:
                SYS_CONSOLE_PRINT("http_client_callback: request completed.\r\n");
                add_state(GET_REQUESTED);
                break;

        case HTTP_CLIENT_CALLBACK_RECV_RESPONSE:
                SYS_CONSOLE_PRINT("http_client_callback: received response %u\r\n",
                                (unsigned int)data->recv_response.response_code);
                if ((unsigned int)data->recv_response.response_code == 200) {
                        http_file_size = data->recv_response.content_length;
                        received_file_size = 0;
                }
                else {
                        add_state(CANCELED);
                        return;
                }
                if (data->recv_response.content_length <= MAIN_BUFFER_MAX_SIZE) {
                        store_file_packet(data->recv_response.content, data->recv_response.content_length);
                        add_state(COMPLETED);
                }
                break;

        case HTTP_CLIENT_CALLBACK_RECV_CHUNKED_DATA:
                store_file_packet(data->recv_chunked_data.data, data->recv_chunked_data.length);
                if (data->recv_chunked_data.is_complete) {
                        add_state(COMPLETED);
                }

                break;

        case HTTP_CLIENT_CALLBACK_RECV_NO_CONTENT_LENGTH_DATA:
            if(data->recv_chunked_data.is_complete)
                   store_file_packet_complete();
                else if ((unsigned int)data->recv_response.response_code == 200) {
                        SYS_CONSOLE_PRINT("http_client_callback: received response %u\r\n",
                                (unsigned int)data->recv_response.response_code);
                        http_file_size = 0xFFFFFFFF;  // There is no content length received
                        received_file_size = 0;
                }
        break;

        case HTTP_CLIENT_CALLBACK_DISCONNECTED:
                SYS_CONSOLE_PRINT("http_client_callback: disconnection reason:%d\r\n", data->disconnected.reason);

                /* If disconnect reason is equal to -ECONNRESET(-104),
                 * It means the server has closed the connection (timeout).
                 * This is normal operation.
                 */
                if (data->disconnected.reason == SOCK_ERR_CONN_ABORTED) {
                  add_state(CANCELED);
                }
                if (data->disconnected.reason == SOCK_ERR_TIMEOUT) {
                        /* Server has not responded. Retry immediately. */
                        if (is_state_set(DOWNLOADING)) {
                                clear_state(DOWNLOADING);
                        }

                        if (is_state_set(GET_REQUESTED)) {
                                clear_state(GET_REQUESTED);
                        }

                        start_download();
                }

                break;
        }
}

/**
 * \brief Program certificates to WINC1500 memory.
 */
static int8_t burn_certificates(void)
{
        int8_t   ret = 0;

        SYS_CONSOLE_PRINT(">> De-init WINC device to enter into download mode\r\n");   
        
        WDRV_WINC_Close(wdrvHandle);
        wdrvHandle = WDRV_WINC_Open(0,DRV_IO_INTENT_EXCLUSIVE); //Intend should be DRV_IO_INTENT_EXCLUSIVE to enter into download mode
            
        if (DRV_HANDLE_INVALID != wdrvHandle){
        
        }
        else
        {
            SYS_CONSOLE_PRINT("Unable to initialize bus, Press RESET button to try again.\r\n");
            while(1);
        }

        SYS_CONSOLE_PRINT(">> WINC entered into download mode\r\n");

        SYS_CONSOLE_PRINT("---> Start Certificate Upload on WINC\r\n");

        for (uint8_t idx=0; idx < NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES; idx++)
        {
           /* Write the Root certificates to WINC */
           if(root_tls_certs_name[idx].cert_type == ROOT_CERT){
		   #ifdef ROOT_CERT_BUNDLE
		   if ( WDRV_WINC_STATUS_OK !=WDRV_WINC_NVMEraseSector(wdrvHandle,WDRV_WINC_NVM_REGION_ROOT_CERTS,0,1))
           {
           SYS_CONSOLE_PRINT("Erase sector failed.\r\n");
           while(1);
           }
          if( WDRV_WINC_STATUS_OK != WDRV_WINC_NVMWrite(wdrvHandle,WDRV_WINC_NVM_REGION_ROOT_CERTS,(void*)root_tls_certs[0].pu8FileData,0,4096))
          {
            SYS_CONSOLE_PRINT("ROOT  CERT update failed, Press RESET button to try again.\r\n");
            while(1);
          }
		  else
		  {
		  	ret++;
		  }
            #else
            ret += WriteRootCertificate(root_tls_certs[idx].pu8FileData,root_tls_certs[idx].u32FileSz);
            #endif

            }
           /* Write the TLS RSA based certificates to WINC */
            if(root_tls_certs_name[idx].cert_type == TLS_RSA_CERT)
            {
                 ret += WriteTlsCertificate(root_tls_certs[idx].pu8FileData,root_tls_certs[idx].u32FileSz,
                  &root_tls_certs[idx+1],root_tls_certs_name[idx].numOfChainCert);
                  idx = idx + root_tls_certs_name[idx].numOfChainCert;
            }

                /* Write the TLS ECC based certificates to WINC */
            if(root_tls_certs_name[idx].cert_type == TLS_ECC_CERT)
            {
                    ret += WriteTlsCertificate(NULL,0,&root_tls_certs[idx],root_tls_certs_name[idx].numOfChainCert);
                        idx = idx + root_tls_certs_name[idx].numOfChainCert -1;
            }
    }
        SYS_CONSOLE_PRINT("ROOT  CERTs updated.\r\n");
        WDRV_WINC_Close(wdrvHandle);        
        
        SYS_RESET_SoftwareReset();
         return ret;
}

/**
 * \brief initiate https download and write the cerficates to WINC.
 */
static uint8_t certificate_download(void)
{
        /* Initiate certificate download from server */
        
        if (is_state_set(WIFI_CONNECTED) && !is_state_set(HTTP_DOWNLOAD_INITIATED))
        {
                if(cert_idx >= NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES)
                {
                    return 1;
                }
        /* append certificate file name with URL */
            strcpy(http_url,APP_CERT_DOWNLOAD_OTA_URL_Buffer);
                strncat(http_url,(char*)root_tls_certs_name[cert_idx].filename,strlen((char*)root_tls_certs_name[cert_idx].filename));

                add_state(HTTP_DOWNLOAD_INITIATED);
                clear_state(GET_REQUESTED);
                clear_state(DOWNLOADING);

                start_download();
        }
        return 0;
}

void APP_CertDownloadOtaSocketEventCallback(SOCKET socket, uint8_t messageType, void *pMessage)
{

    http_client_socket_event_handler(socket, messageType, pMessage);
    
    switch(messageType)
    {
        case SOCKET_MSG_CONNECT:
        {
            tstrSocketConnectMsg *pConnectMessage = (tstrSocketConnectMsg*)pMessage;

            if ((NULL != pConnectMessage) && (pConnectMessage->s8Error >= 0))
            {
                SYS_CONSOLE_PRINT("Socket %d connect success\r\n", socket);

            }
            else
            {
                SYS_CONSOLE_PRINT("Socket %d connect error %d\r\n", socket, pConnectMessage->s8Error);
            }
            break;
        }

        case SOCKET_MSG_RECV:
        {
            tstrSocketRecvMsg *pRecvMessage = (tstrSocketRecvMsg*)pMessage;

            if ((NULL != pRecvMessage) && (pRecvMessage->s16BufferSize > 0))
            {
                SYS_CONSOLE_PRINT("Socket receive, size = %d bytes \r\n", pRecvMessage->s16BufferSize);
                
            }
            else
            {
                SYS_CONSOLE_PRINT("Receive on socket %d failed\r\n", socket);

            }
            break;
        }

        case SOCKET_MSG_SEND:
        {
            SYS_CONSOLE_PRINT("Socket %d send completed\r\n", socket);
            break;
        }

        default:
        {
            break;
        }
    }
}




/**
 * \brief Configure HTTP client module.
 */
static void configure_http_client(void)
{
        struct http_client_config httpc_conf;
        int ret;

        http_client_get_config_defaults(&httpc_conf);

        httpc_conf.recv_buffer_size = MAIN_BUFFER_MAX_SIZE;
        httpc_conf.tls = 1;

        ret = http_client_init(&http_client_module_inst, &httpc_conf);
        if (ret < 0) {
                SYS_CONSOLE_PRINT("configure_http_client: HTTP client initialization failed! (res %d)\r\n", ret);
                while (1) {
                } /* Loop forever. */
        }
        
        
        http_client_register_callback(&http_client_module_inst, http_client_callback);
}

void APP_CertDownloadOtaInitialize(APP_CALLBACK pAPPWiFiCallback)
{
    configure_http_client();
    SYS_CMD_ADDGRP(APP_CertDownloadOtaCmdTbl, sizeof (APP_CertDownloadOtaCmdTbl) / sizeof (*APP_CertDownloadOtaCmdTbl), "Certificate download OTA", ": Socket mode commands for the OTA certificate download"); 
    memset(APP_CERT_DOWNLOAD_OTA_URL_Buffer, 0, APP_CERT_DOWNLOAD_MAX_URL_SIZE);
    appCertState = APP_CERT_DOWNLOAD_OTA_STATE_DONE;
}

void APP_CertDownloadOtaTasks(DRV_HANDLE handle)
{
    switch (appCertState)
    {
        case APP_CERT_DOWNLOAD_OTA_STATE_INIT:
        {
            /* Register callback for socket events. */

            WDRV_WINC_SocketRegisterEventCallback(handle, &APP_CertDownloadOtaSocketEventCallback);
            appCertState = APP_CERT_DOWNLOAD_OTA_STATE_CONNECTED;
            break;
        }
        
        case APP_CERT_DOWNLOAD_OTA_STATE_CONNECTING:
        {
            /* Wait for the BSS connect to trigger the callback and update
             the connection state. */
            break;
        }

        case APP_CERT_DOWNLOAD_OTA_STATE_CONNECTED:
        {
            /* Wait for the IP link to become active. */
            if (false == WDRV_WINC_IPLinkActive(handle))
            {           
                break;
            }

            add_state(WIFI_CONNECTED);
            appCertState = APP_CERT_DOWNLOAD_OTA_STATE_HTTP_DOWNLOAD_INIT;
            
            break;
        }
        case APP_CERT_DOWNLOAD_OTA_STATE_DOWNLOADING:
        {
            //Add indication if required
            //DONT add BREAK, as we need to keep calling 
            //certificate_download() until it returns 1
        }    
        case APP_CERT_DOWNLOAD_OTA_STATE_HTTP_DOWNLOAD_INIT:
        {
            if(certificate_download() == 1)
                appCertState = APP_CERT_DOWNLOAD_OTA_STATE_DOWNLOAD_COMPLETE;
            else
                appCertState = APP_CERT_DOWNLOAD_OTA_STATE_DOWNLOADING;                          
            break;
        }
        case APP_CERT_DOWNLOAD_OTA_STATE_DOWNLOAD_COMPLETE:
        {
            if (burn_certificates() != M2M_SUCCESS)
                    SYS_CONSOLE_PRINT(">> ERROR in Writing the certificates\r\n");
                else
                {
                    SYS_CONSOLE_PRINT(">> All the certificates written\r\n");
                    SYS_CONSOLE_PRINT(">> Re-init the WINC to start Wi-Fi Operations\r\n");
                    appCertState = APP_CERT_DOWNLOAD_OTA_STATE_ERROR;
                }
            break;
        }    
 
        case APP_CERT_DOWNLOAD_OTA_STATE_DISCONNECTED:
        {
            /* If we become disconnected, trigger a reconnection. */

//            if (WDRV_WINC_STATUS_OK == WDRV_WINC_BSSReconnect(handle, &APP_ExampleConnectNotifyCallback))
//            {
//                appCertState = APP_CERT_DOWNLOAD_OTA_STATE_CONNECTING;
//            }
            break;
        }

        case APP_CERT_DOWNLOAD_OTA_STATE_ERROR:
        {
            
            break;
        }
        case APP_CERT_DOWNLOAD_OTA_STATE_DONE:
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