/*******************************************************************************
 Header file for the wolfSSL glue functions to work with Harmony


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


#ifndef H_NET_TLS_WOLFSSL_GLUE_H_
#define H_NET_TLS_WOLFSSL_GLUE_H_

#include "configuration.h"
#include "net_pres/pres/net_pres.h"
#include "net_pres/pres/net_pres_encryptionproviderapi.h"
#ifdef __CPLUSPLUS
extern "C" {
#endif
extern Net_ProvObject net_ProvStreamServer0;
extern Net_ProvObject net_ProvStreamClient0;
bool Net_ProvStreamServerInit0(struct S_NET_PRES_TransportObject * transObject);
bool Net_ProvStreamServerDeinit0(void);
bool Net_ProvStreamServerOpen0(SYS_MODULE_OBJ obj, uintptr_t presHandle, uintptr_t transHandle, void * providerData);
bool Net_ProvStreamServerIsInited0(void);
bool Net_ProvStreamClientInit0(struct S_NET_PRES_TransportObject * transObject);
bool Net_ProvStreamClientDeinit0(void);
bool Net_ProvStreamClientOpen0(SYS_MODULE_OBJ obj, uintptr_t presHandle, uintptr_t transHandle, void * providerData);
bool Net_ProvStreamClientIsInited0(void);
NET_PRES_EncSessionStatus Net_ProvServerAccept0(void * providerData);
NET_PRES_EncSessionStatus Net_ProvClientConnect0(void * providerData);
NET_PRES_EncSessionStatus Net_ProvConnectionClose0(void * providerData);
int32_t Net_ProvWrite0(void * providerData, const uint8_t * dataBuff, uint16_t size);
uint16_t  Net_ProvWriteReady0(void * providerData, uint16_t reqSize, uint16_t minSize);
int32_t Net_ProvRead0(void * providerData, uint8_t * dataBuff, uint16_t size);
int32_t Net_ProvReadReady0(void * providerData);
int32_t Net_ProvPeek0(void * providerData, uint8_t * dataBuff, uint16_t size);
int32_t Net_ProvOutputSize0(void * providerData, int32_t inSize);
int32_t Net_ProvMaxOutputSize0(void * providerData);
#ifdef __CPLUSPLUS
}
#endif
#endif //H_NET_TLS_WOLFSSL_GLUE_H_
