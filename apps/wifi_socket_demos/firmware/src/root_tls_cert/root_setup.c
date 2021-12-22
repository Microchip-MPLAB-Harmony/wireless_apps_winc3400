/**
 *
 * \file
 *
 * \brief Root certificate parser and downloader
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

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
INCLUDESS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "root_tls_cert/crypto/crypto_api.h"
#include "root_tls_cert/root_setup.h"
#include "root_tls_cert/pem.h"
#include "drv/spi_flash/spi_flash.h"

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
MACROS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
#define programmer_write_root_cert(buff)        spi_flash_write((uint8_t*)buff, M2M_TLS_ROOTCER_FLASH_OFFSET, M2M_TLS_SERVER_FLASH_SZ)
#define programmer_read_root_cert(buff)        spi_flash_read((uint8_t*)buff, M2M_TLS_ROOTCER_FLASH_OFFSET, M2M_TLS_SERVER_FLASH_SZ)
#define programmer_erase_root_cert(buff)        spi_flash_erase(M2M_TLS_ROOTCER_FLASH_OFFSET, M2M_TLS_SERVER_FLASH_SZ)

extern APP_DATA appData;

uint8_t gau8CertMem[M2M_TLS_SERVER_FLASH_SZ];

#define ROOT_CERT_FLASH_START_PATTERN_LENGTH		16

#define ROOT_CERT_FLASH_EMPTY_PATTERN \
{\
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, \
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF	\
}
	
/* tstrRootCertEntryHeader Format used in 19.4.x */
#define ROOT_CERT_FLASH_START_PATTERN_V0	\
{\
	0x01, 0xF1, 0x02, 0xF2, 0x03, 0xF3, 0x04, 0xF4,	\
	0x05, 0xF5, 0x06, 0xF6, 0x07, 0xF7, 0x08, 0xF8	\
}

/* tstrRootCertEntryHeader Format used in 19.5.x */
#define ROOT_CERT_FLASH_START_PATTERN	\
{\
	0x11, 0xF1, 0x12, 0xF2, 0x13, 0xF3, 0x14, 0xF4, \
	0x15, 0xF5, 0x16, 0xF6, 0x17, 0xF7, 0x18, 0xF8	\
}

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
DATA TYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
#if 0
typedef struct{
	uint8_t	au8StartPattern[ROOT_CERT_FLASH_START_PATTERN_LENGTH];
	uint32_t	u32nCerts;
}tstrRootCertFlashHeader;


typedef enum{
	ROOT_CERT_PUBKEY_RSA		= 1,
	ROOT_CERT_PUBKEY_ECDSA		= 2
}tenuRootCertPubKeyType;


typedef struct{
	uint16_t	u16NSz;
	uint16_t	u16ESz;
}tstrRootCertRsaKeyInfo;

typedef struct{
	uint16_t	u16CurveID;
	uint16_t	u16KeySz;
}tstrRootCertEcdsaKeyInfo;

typedef struct{
	uint32_t	u32PubKeyType;
	union{
		tstrRootCertRsaKeyInfo		strRsaKeyInfo;
		tstrRootCertEcdsaKeyInfo	strEcsdaKeyInfo;
	};
}tstrRootCertPubKeyInfo;


/*!
@struct
	tstrRootCertEntryHeader

@brief
	Header of a root certificate entry in flash.
*/	
typedef struct{
	uint8_t					au8SHA1NameHash[CRYPTO_SHA1_DIGEST_SIZE];
	tstrSystemTime			strStartDate;
	tstrSystemTime			strExpDate;
	tstrRootCertPubKeyInfo	strPubKey;
}tstrRootCertEntryHeader;
#endif
/**********************************************************************
Function
	GetRootCertificate

Description
	Get the root certificates from WINC SPI flash

Return
	Status
***********************************************************************/
static int GetRootCertificate(uint8_t *pu8RootCert, uint32_t u32RootCertSz, txtrX509CertInfo *pstrX509)
{
	int		ret;
	uint32_t	u32FileSize;
	uint8_t	*pcRootCertDER;

	/* Decode the certificate.
	*/
	ret = DecodeX509Certificate(pu8RootCert, u32RootCertSz, &pcRootCertDER, &u32FileSize);
	if(ret == M2M_SUCCESS)
	{
		ret = CryptoX509CertDecode(pcRootCertDER, (uint16_t)u32FileSize, pstrX509, 0);
		if(ret == M2M_SUCCESS)
		{
			SYS_CONSOLE_PRINT("\r\n>>>Found Certificate:\n");
			SYS_CONSOLE_PRINT(">>>\t%s\n", pstrX509->strSubject.acCmnName);
		}
	}
	else
	{
		SYS_CONSOLE_PRINT("\r\n>>>Invalid certificate!\n");
	}
	
	return ret;
}

/**********************************************************************
Function
	writeRootCertEntry

Description
	Adds the new root certificate to the buffer

Return
	Size of the certificate
***********************************************************************/
static uint16_t writeRootCertEntry(uint8_t *pu8WriteBuff, txtrX509CertInfo *pstrRootCert)
{
	uint16_t u16WriteSz = 0;

	if((pu8WriteBuff != NULL) && (pstrRootCert != NULL))
	{
		tstrRootCertEntryHeader		*pstrEntryHdr	= (tstrRootCertEntryHeader*)pu8WriteBuff;
		uint8_t						*pu8KeyMem		= &pu8WriteBuff[sizeof(tstrRootCertEntryHeader)];

		u16WriteSz = sizeof(tstrRootCertEntryHeader);
		
		memset((uint8_t*)pstrEntryHdr, 0, sizeof(tstrRootCertEntryHeader));

		/* 
			Write Root Certificate Entry Header
		*/
		memcpy(pstrEntryHdr->au8SHA1NameHash, pstrRootCert->strSubject.au8NameSHA1, CRYPTO_SHA1_DIGEST_SIZE);		// Subject Name SHA1
		//memcpy((uint8_t*)&pstrEntryHdr->strStartDate, (uint8_t*)&pstrRootCert->strStartDate, sizeof(tstrSystemTime));	// Cert. Start Date.
		memcpy((uint8_t*)&pstrEntryHdr->strExpDate, (uint8_t*)&pstrRootCert->strExpiryDate, sizeof(tstrSystemTime));	// Cert. Expiration Date.

		/*
			Write the certificate public key
		*/
		if(pstrRootCert->strPubKey.enuCertKeyType == X509_CERT_PUBKEY_RSA)
		{
			/*
				RSA Public Key
			*/
			tstrRSAPubKey	*pstrKey = &pstrRootCert->strPubKey.strRsaPub;

			pstrEntryHdr->strPubKey.u32PubKeyType			= ROOT_CERT_PUBKEY_RSA;
			pstrEntryHdr->strPubKey.strRsaKeyInfo.u16NSz	= pstrKey->u16NSize;
			pstrEntryHdr->strPubKey.strRsaKeyInfo.u16ESz	= pstrKey->u16ESize;

			/* N */
			memcpy(pu8KeyMem, pstrKey->pu8N, pstrKey->u16NSize);
			pu8KeyMem += pstrKey->u16NSize;

			/* E */
			memcpy(pu8KeyMem, pstrKey->pu8E, pstrKey->u16ESize);
			u16WriteSz += WORD_ALIGN(pstrKey->u16ESize) + WORD_ALIGN(pstrKey->u16NSize);
		}
		else if(pstrRootCert->strPubKey.enuCertKeyType == X509_CERT_PUBKEY_ECDSA)
		{
			tstrECDSAPubKey	*pstrKey = &pstrRootCert->strPubKey.strEcdsaPub;

			pstrEntryHdr->strPubKey.u32PubKeyType				= ROOT_CERT_PUBKEY_ECDSA;
			pstrEntryHdr->strPubKey.strEcsdaKeyInfo.u16CurveID	= pstrKey->u16CurveID;
			pstrEntryHdr->strPubKey.strEcsdaKeyInfo.u16KeySz	= pstrKey->u16EcPointSz;
			memcpy(pu8KeyMem, pstrKey->au8EcPoint, pstrKey->u16EcPointSz * 2);
			u16WriteSz += pstrKey->u16EcPointSz * 2;
		}
	}
	return u16WriteSz;
}

/**********************************************************************
Function
	UpdateRootList

Description
	Update the root certificate list

Return
	Status
***********************************************************************/
static int8_t UpdateRootList(txtrX509CertInfo *pstrRootCert)
{
	uint32_t					u32Idx;
	uint8_t					bIncrement			= 0;
	uint32_t					u32nStoredCerts		= 0;
	uint8_t					au8StartPattern[]	= M2M_TLS_ROOTCER_FLASH_SIG;
	uint8_t                   au8EmptyPattern[]	= ROOT_CERT_FLASH_EMPTY_PATTERN;
	tstrRootCertFlashHeader	*pstrRootFlashHdr;
	tstrRootCertEntryHeader	*pstrEntryHdr;
	uint16_t					u16Offset;
	uint16_t					u16WriteSize;
	tstrRootCertPubKeyInfo	*pstrKey;

	pstrRootFlashHdr	= (tstrRootCertFlashHeader*)((void *)gau8CertMem);
	u16Offset			= sizeof(tstrRootCertFlashHeader);

	/* Check if the flash has been written before.
	*/
	if(memcmp(au8EmptyPattern, pstrRootFlashHdr->au8StartPattern, M2M_TLS_ROOTCER_FLASH_SIG_LENGTH) != 0)
	{
		u32nStoredCerts = pstrRootFlashHdr->u32nCerts;
		bIncrement = 1;

		for(u32Idx = 0 ; u32Idx < u32nStoredCerts ; u32Idx ++)
		{
			pstrEntryHdr	= (tstrRootCertEntryHeader*)((void *)&gau8CertMem[u16Offset]);
			pstrKey			= &pstrEntryHdr->strPubKey;

			/* Check for match (equivalent NameSHA1). 
			*/
			if(!memcmp(pstrRootCert->strSubject.au8NameSHA1, pstrEntryHdr->au8SHA1NameHash, 20))
			{
				/* The current entry will be overwritten.
				*/
				bIncrement = 0;
				break;
			}
			u16Offset += sizeof(tstrRootCertEntryHeader);
			u16Offset += (pstrKey->u32PubKeyType == ROOT_CERT_PUBKEY_RSA) ? 
				(WORD_ALIGN(pstrKey->strRsaKeyInfo.u16NSz) + WORD_ALIGN(pstrKey->strRsaKeyInfo.u16ESz)) : (WORD_ALIGN(pstrKey->strEcsdaKeyInfo.u16KeySz) * 2);
		}
	}
	else
	{
		pstrRootFlashHdr->u32nCerts = 0;
		memcpy(pstrRootFlashHdr->au8StartPattern, au8StartPattern, M2M_TLS_ROOTCER_FLASH_SIG_LENGTH);
		bIncrement = 1;
	}

	u16WriteSize = writeRootCertEntry(&gau8CertMem[u16Offset], pstrRootCert);

	if(bIncrement)
	{
		/* A new certificate is to be inserted into the flash.
		Increment the number of stored Certificates. 
		*/
		if(u16Offset + u16WriteSize > M2M_TLS_ROOTCER_FLASH_SZ)
		{
			SYS_CONSOLE_PRINT("(ERROR) Root Certificate Flash is Full\n");
			return -1;
		}
		pstrRootFlashHdr->u32nCerts ++;
	}
	return 0;
}

/**********************************************************************
*	@fn			int WriteRootCertificate
*	@brief		Write a given Root Certificate on the WINC1500 FLASH Root certificate Store. 
*	@param[in]	pu8RootCert
*					Buffer hoilding the root certificate (Both DER and PEM formats are valid).
*
*   @param [in]	u32RootCertSz
*					Size of the root certificate buffer
*
*	@return		writing status
**********************************************************************/
int WriteRootCertificate(uint8_t *pu8RootCert, uint32_t u32RootCertSz)
{
	txtrX509CertInfo	strX509Root;
	int					ret = -1;

	/* Read Certificate File.
	*/ 
	memset(gau8CertMem, 0, M2M_TLS_ROOTCER_FLASH_SZ);
	if(GetRootCertificate(pu8RootCert, u32RootCertSz, &strX509Root) == 0)
	{
		programmer_read_root_cert(gau8CertMem);
		if(UpdateRootList(&strX509Root) == 0)
		{			
			/* Erase memory. 
			*/
			ret = programmer_erase_root_cert();
			if(M2M_SUCCESS != ret) goto END;
			/* Write.
			*/
			SYS_CONSOLE_PRINT("\r\n>> Writing the Root Certificate to SPI flash...\r\n");
			ret = programmer_write_root_cert(gau8CertMem);
			if(M2M_SUCCESS != ret) goto END;
			SYS_CONSOLE_PRINT("--- Root Certificate written to SPI flash ---\r\n\r\n");
			//nm_bsp_sleep(50);

#ifdef ENABLE_VERIFICATION //Enable verification or print array

			{
				uint32_t			u32Idx;

				memset(gau8Verify, 0, M2M_TLS_ROOTCER_FLASH_SZ);
				programmer_read_root_cert(gau8Verify);

				for(u32Idx = 0; u32Idx < M2M_TLS_ROOTCER_FLASH_SZ; u32Idx ++)
				{
					if(gau8CertMem[u32Idx] != gau8Verify[u32Idx])
					{
						SYS_CONSOLE_PRINT(">> ERROR Root certificate verification failed\r\n");
						ret = -1;
						break;
					}
				}
				SYS_CONSOLE_PRINT(">> Root Certificates Verified OK\r\n");
			}

#endif //Enable verification or print array 
		}
		CryptoX509DeleteContext(&strX509Root);
	}
END:
	return ret;
}
