/**
 * \file
 *
 * \brief Header file for cryptographic algorithms.
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

#ifndef __CRYPTO_API_H__
#define __CRYPTO_API_H__

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
INCLUDES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "drv/common/nm_common.h"
#include "drv/driver/m2m_types.h"

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
MACROS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
/*! Maximum of two values */
#define M2M_MAX(A, B)   (((A) > (B)) ? (A) : (B))

/*! Align to next multiple of 4 */
#define WORD_ALIGN(val) ((val & 0x03) ? (((val) + 4) - (val & 0x03)) : (val))


#define CRYPTO_SHA1_DIGEST_SIZE			(20)
#define ECC_POINT_MAX					(72)

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
DATA TYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

/*!
@enum\
	tenuCertPubKeyType
*/
typedef enum{
	X509_CERT_PUBKEY_RSA	= 1,
	X509_CERT_PUBKEY_ECDSA	= 2
}tenuCertPubKeyType;


/*!
@struct	\
	tstrRsaPrivateKey
*/
typedef struct{
	uint16_t	u16NSize;
	uint16_t	u16eSize;
	uint16_t	u16dSize;
	uint16_t	u16PSize;
	uint16_t	u16QSize;
	uint16_t	u16dPSize;
	uint16_t	u16dQSize;
	uint16_t	u16QInvSize;
	uint32_t	u32Version;
	uint8_t	*pu8N;
	uint8_t	*pu8e;
	uint8_t	*pu8d;
	uint8_t	*pu8p;
	uint8_t	*pu8q;
	uint8_t	*pu8dP;
	uint8_t	*pu8dQ;
	uint8_t	*pu8QInv;
}tstrRsaPrivateKey;


/*!
@struct	\
	tstrASN1RsaPrivateKey

@brief	RSA Private Key Elements

	The structure contains the elements of the RSA Private key as decoded from
	the supplied private key file (PEM Format).
*/
typedef struct{
	tstrRsaPrivateKey	strRsaPrivKey;
	uint8_t				*pu8AllocPtr;
	uint16_t				u16KeyBufSz;
}tstrASN1RSAPrivateKey;


/*!
@struct	\
	tstrRSAPubKey
*/
typedef struct{
	uint16_t	u16NSize;
	uint16_t	u16ESize;
	uint8_t	*pu8N;
	uint8_t	*pu8E;
}tstrRSAPubKey;


/*!
@struct	\
	tstrECDSAPubKey
*/
typedef struct{
	uint16_t	u16CurveID;
	uint16_t	u16EcPointSz;
	uint8_t	au8EcPoint[ECC_POINT_MAX * 2];
}tstrECDSAPubKey;


/*!
@struct	\
	tstrX509CertPublicKey
*/
typedef struct{
	tenuCertPubKeyType	enuCertKeyType;
	union{
		tstrRSAPubKey	strRsaPub;
		tstrECDSAPubKey	strEcdsaPub;
	};
}tstrX509CertPublicKey;


/*!
@struct	\
	tstrX520Name

@brief
*/
typedef struct{
	char	acCmnName[64];
	uint8_t	au8NameSHA1[20];
}tstrX509Name;


/*!
@struct	\
	txtrX509CertInfo
*/
typedef struct{
	uint8_t					u8SerialNumberLength;
	uint8_t					au8SerialNo[64];
	tstrX509Name			strIssuer;
	tstrSystemTime			strExpiryDate;
	tstrSystemTime			strStartDate;
	tstrX509Name			strSubject;
	tstrX509CertPublicKey	strPubKey;
	void					*pvPrivate;
}txtrX509CertInfo;

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
FUNCTION PROTOTYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

int8_t CryptoX509CertDecode(uint8_t *pu8X509CertBuf, uint16_t u16X509CertBuffer, txtrX509CertInfo *pstrCert, uint8_t bDumpCert);
void CryptoX509DeleteContext(txtrX509CertInfo *pstrCert);
int8_t CryptoDecodeRsaPrivKey(uint8_t *pu8RsaKeyFile, uint32_t u32KeySize, tstrASN1RSAPrivateKey *pstrRsaPrivKey);
#endif /* __CRYPTO_API_H__ */