/*******************************************************************************
 Source file for the Net Pres Encryption glue functions to work with Harmony


  Summary:


  Description:

*******************************************************************************/

/*
Copyright (C) 2013-2025, Microchip Technology Inc., and its subsidiaries. All rights reserved.

The software and documentation is provided by microchip and its contributors
"as is" and any express, implied or statutory warranties, including, but not
limited to, the implied warranties of merchantability, fitness for a particular
purpose and non-infringement of third party intellectual property rights are
disclaimed to the fullest extent permitted by law. In no event shall microchip
or its contributors be liable for any direct, indirect, incidental, special,
exemplary, or consequential damages (including, but not limited to, procurement
of substitute goods or services; loss of use, data, or profits; or business
interruption) however caused and on any theory of liability, whether in contract,
strict liability, or tort (including negligence or otherwise) arising in any way
out of the use of the software and documentation, even if advised of the
possibility of such damage.

Except as expressly permitted hereunder and subject to the applicable license terms
for any third-party software incorporated in the software and any applicable open
source software license terms, no license or other rights, whether express or
implied, are granted under any patent or other intellectual property rights of
Microchip or any third party.
*/


#include "net_pres_enc_glue.h"
#include "net_pres/pres/net_pres_transportapi.h"
#include "net_pres/pres/net_pres_certstore.h"

#include "config.h"
#include "wolfssl/ssl.h"
#include "wolfssl/wolfcrypt/logging.h"
#include "wolfssl/wolfcrypt/random.h"

/* MISRA C-2012 Rule 8.5 deviated:1 Deviation record ID -  H3_MISRAC_2012_R_8_5_NET_DR_15 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma coverity compliance block deviate:1 "MISRA C-2012 Rule 8.5" "H3_MISRAC_2012_R_8_5_NET_DR_15" 
extern int CheckAvailableSize(WOLFSSL *ssl, int size);
#pragma coverity compliance end_block "MISRA C-2012 Rule 8.5"
#pragma GCC diagnostic pop
/* MISRAC 2012 deviation block end */


typedef struct 
{
    WOLFSSL_CTX* context;
    NET_PRES_TransportObject * transObject;
    bool isInited;
}net_pres_wolfsslInfo;

/* MISRA C-2012 Rule 8.4 deviated:1 Deviation record ID -  H3_MISRAC_2012_R_8_4_NET_DR_16 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma coverity compliance block deviate:1 "MISRA C-2012 Rule 8.4" "H3_MISRAC_2012_R_8_4_NET_DR_16" 
// Temporary fix till crypto library is upgraded to recent wolfssl versions.
int  InitRng(RNG* rng)
{
    return wc_InitRng(rng);
}
#pragma coverity compliance end_block "MISRA C-2012 Rule 8.4"
#pragma GCC diagnostic pop
/* MISRAC 2012 deviation block end */

Net_ProvObject net_ProvStreamClient0 = 
{
    .fpInit =    &Net_ProvStreamClientInit0,
    .fpDeinit =  &Net_ProvStreamClientDeinit0,
    .fpOpen =    &Net_ProvStreamClientOpen0,
    .fpConnect = &Net_ProvClientConnect0,
    .fpClose =   &Net_ProvConnectionClose0,
    .fpWrite =   &Net_ProvWrite0,
    .fpWriteReady =   &Net_ProvWriteReady0,
    .fpRead =    &Net_ProvRead0,
    .fpReadReady = &Net_ProvReadReady0,
    .fpPeek =    &Net_ProvPeek0,
    .fpIsInited = &Net_ProvStreamClientIsInited0,
    .fpOutputSize = &Net_ProvOutputSize0,
    .fpMaxOutputSize = &Net_ProvMaxOutputSize0,
};
	
static net_pres_wolfsslInfo net_pres_wolfSSLInfoStreamClient0;
	
static int NET_Glue_StreamClientReceiveCb0(void *sslin, char *buf, int sz, void *ctx)
{
    int fd = *(int *)ctx;
    uint16_t bufferSize;
    bufferSize = (*net_pres_wolfSSLInfoStreamClient0.transObject->fpReadyToRead)((uintptr_t)fd);
    if (bufferSize == 0U)
    {
        return (int)WOLFSSL_CBIO_ERR_WANT_READ;
    }
    bufferSize = (*net_pres_wolfSSLInfoStreamClient0.transObject->fpRead)((uintptr_t)fd, (uint8_t*)buf, sz);
    return (int)bufferSize;
}
static int NET_Glue_StreamClientSendCb0(void *sslin, char *buf, int sz, void *ctx)
{
    int fd = *(int *)ctx;
    uint16_t bufferSize;
    bufferSize = (*net_pres_wolfSSLInfoStreamClient0.transObject->fpReadyToWrite)((uintptr_t)fd);
    if (bufferSize == 0U)
    {
        return (int)WOLFSSL_CBIO_ERR_WANT_WRITE;
    }

    bufferSize =  (*net_pres_wolfSSLInfoStreamClient0.transObject->fpWrite)((uintptr_t)fd, (uint8_t*)buf, (uint16_t)sz);
    return (int)bufferSize;
}
	
static uint8_t net_pres_wolfsslUsers = 0U;

		
bool Net_ProvStreamClientInit0(struct S_NET_PRES_TransportObject * transObject)
{
    const uint8_t * caCertsPtr;
    int32_t caCertsLen;
    if (!NET_PRES_CertStoreGetCACerts(&caCertsPtr, &caCertsLen, 0))
    {
        return false;
    }
    if (net_pres_wolfsslUsers == 0U)
    {
        (void)wolfSSL_Init();
        net_pres_wolfsslUsers++;
    }
    net_pres_wolfSSLInfoStreamClient0.transObject = transObject;
	net_pres_wolfSSLInfoStreamClient0.context = wolfSSL_CTX_new(wolfSSLv23_client_method());
    if (net_pres_wolfSSLInfoStreamClient0.context == NULL)
    {
        return false;
    }
    // Turn off verification, because SNTP is usually blocked by a firewall
    wolfSSL_CTX_set_verify(net_pres_wolfSSLInfoStreamClient0.context, SSL_VERIFY_NONE, NULL);
	
    union
    {
        int (*receiveCb)(void *sslin, char *buf, int sz, void *ctx);
        CallbackIORecv ioRecv;
        int (*sendCb)(void *sslin, char *buf, int sz, void *ctx);
        CallbackIOSend ioSend;
    }U_RCV_CBACK;
    U_RCV_CBACK.receiveCb = &NET_Glue_StreamClientReceiveCb0;
    wolfSSL_SetIORecv(net_pres_wolfSSLInfoStreamClient0.context, U_RCV_CBACK.ioRecv);
    U_RCV_CBACK.sendCb = &NET_Glue_StreamClientSendCb0;
    wolfSSL_SetIOSend(net_pres_wolfSSLInfoStreamClient0.context, U_RCV_CBACK.ioSend);
    if (wolfSSL_CTX_load_verify_buffer(net_pres_wolfSSLInfoStreamClient0.context, caCertsPtr, caCertsLen, SSL_FILETYPE_ASN1) != SSL_SUCCESS)
    {
        // Couldn't load the CA certificates
        //SYS_CONSOLE_MESSAGE("Something went wrong loading the CA certificates\r\n");
        wolfSSL_CTX_free(net_pres_wolfSSLInfoStreamClient0.context);
        return false;
    }
    net_pres_wolfSSLInfoStreamClient0.isInited = true;
    return true;
}
bool Net_ProvStreamClientDeinit0(void)
{
    wolfSSL_CTX_free(net_pres_wolfSSLInfoStreamClient0.context);
    net_pres_wolfSSLInfoStreamClient0.isInited = false;
    net_pres_wolfsslUsers--;
    if (net_pres_wolfsslUsers == 0U)
    {
        (void)wolfSSL_Cleanup();
    }
    return true;
}
bool Net_ProvStreamClientOpen0(SYS_MODULE_OBJ obj, uintptr_t presHandle, uintptr_t transHandle, void * providerData)
{
    WOLFSSL* ssl = wolfSSL_new(net_pres_wolfSSLInfoStreamClient0.context);
    if (ssl == NULL)
    {
        return false;
    }
    if (wolfSSL_set_fd(ssl, (int)transHandle) != SSL_SUCCESS)
    {
        wolfSSL_free(ssl);
        return false;
    }
    (void)memcpy(providerData, (void*)&ssl, sizeof(WOLFSSL*));
    return true;
}
bool Net_ProvStreamClientIsInited0(void)
{
    return net_pres_wolfSSLInfoStreamClient0.isInited;
}
NET_PRES_EncSessionStatus Net_ProvClientConnect0(void * providerData)
{
    WOLFSSL* ssl;
    (void)memcpy((void*)&ssl, providerData, sizeof(WOLFSSL*));
    int result = wolfSSL_connect(ssl);
    if(result == SSL_SUCCESS)
    {
        return NET_PRES_ENC_SS_OPEN;
    }
    else
    {
        int error = wolfSSL_get_error(ssl, result);
        if(error == SSL_ERROR_WANT_READ || error == SSL_ERROR_WANT_WRITE)
        {
            return NET_PRES_ENC_SS_SERVER_NEGOTIATING;
        }
        else
        {
            return NET_PRES_ENC_SS_FAILED;
        }
    }
}
NET_PRES_EncSessionStatus Net_ProvConnectionClose0(void * providerData)
{
    WOLFSSL* ssl;
    (void)memcpy((void*)&ssl, providerData, sizeof(WOLFSSL*));
    wolfSSL_free(ssl);
    return NET_PRES_ENC_SS_CLOSED;
}
int32_t Net_ProvWrite0(void * providerData, const uint8_t * dataBuff, uint16_t size)
{
    WOLFSSL* ssl;
    (void)memcpy((void*)&ssl, providerData, sizeof(WOLFSSL*));
    int ret = wolfSSL_write(ssl, dataBuff, (int)size);
    if (ret < 0)
    {
        return 0;
    }    
    return ret;
}
uint16_t Net_ProvWriteReady0(void * providerData, uint16_t reqSize, uint16_t minSize)
{
    
    char dataBuff = '\0';
    WOLFSSL* ssl;
    (void)memcpy((void*)&ssl, providerData, sizeof(WOLFSSL*));

    int ret = wolfSSL_write(ssl, &dataBuff, 0);
    if(ret < 0)
    {
        return 0;
    }

    ret = CheckAvailableSize(ssl, (int)reqSize);
    if(ret == 0)
    {   // success
        return reqSize;
    }
    if(minSize != 0U)
    {
        ret = CheckAvailableSize(ssl, (int)minSize);
        if(ret == 0)
        {   // success
            return minSize;
        }
    }

    return 0;
}
int32_t Net_ProvRead0(void * providerData, uint8_t * dataBuff, uint16_t size)
{
    WOLFSSL* ssl;
    (void)memcpy((void*)&ssl, providerData, sizeof(WOLFSSL*));
    int ret = wolfSSL_read(ssl, dataBuff, (int)size);
    if (ret < 0)
    {
        return 0;
    } 
    return ret;
}

int32_t Net_ProvReadReady0(void * providerData)
{
    WOLFSSL* ssl;
    (void)memcpy((void*)&ssl, providerData, sizeof(WOLFSSL*));
    int32_t ret = wolfSSL_pending(ssl);
    if (ret == 0) // wolfSSL_pending() doesn't check the underlying layer.
    {
        char dataBuff = '\0';
        if (wolfSSL_peek(ssl, &dataBuff, 1) == 0)
        {
            return 0;
        }
        ret = wolfSSL_pending(ssl);
    }
    return ret;
}
        
int32_t Net_ProvPeek0(void * providerData, uint8_t * dataBuff, uint16_t size)
{
    WOLFSSL* ssl;
    (void)memcpy((void*)&ssl, providerData, sizeof(WOLFSSL*));
    int ret = wolfSSL_peek(ssl, dataBuff, (int)size);
    if (ret < 0)
    {
        return 0;
    }  
    return ret;
}
int32_t Net_ProvOutputSize0(void * providerData, int32_t inSize)
{
    WOLFSSL* ssl;
    (void)memcpy((void*)&ssl, providerData, sizeof(WOLFSSL*));
    int ret = wolfSSL_GetOutputSize(ssl, inSize);
    if (ret < 0)
    {
        return 0;
    }  
    return ret;
}
int32_t Net_ProvMaxOutputSize0(void * providerData)
{
    WOLFSSL* ssl;
    (void)memcpy((void*)&ssl, providerData, sizeof(WOLFSSL*));
    int ret = wolfSSL_GetMaxOutputSize(ssl);
    if (ret < 0)
    {
        return 0;
    }  
    return ret;
}
