/**
 *
 * \file
 *
 * \brief TLS certificate and private key parser and downloader
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
#include "tls_setup.h"
#include "drv/spi_flash/spi_flash.h"

#define programmer_read(pu8Buf, u32Offset, u32sz)   spi_flash_read(pu8Buf, u32Offset, u32sz)

#define programmer_write_tls_cert_store(buff)        spi_flash_write((uint8_t*)buff, M2M_TLS_SERVER_FLASH_OFFSET, M2M_TLS_SERVER_FLASH_SZ)
#define programmer_read_tls_cert_store(buff)        spi_flash_read((uint8_t*)buff, M2M_TLS_SERVER_FLASH_OFFSET, M2M_TLS_SERVER_FLASH_SZ)
#define programmer_erase_tls_cert_store(buff)        spi_flash_erase(M2M_TLS_SERVER_FLASH_OFFSET, M2M_TLS_SERVER_FLASH_SZ)

extern APP_DATA appData;

extern uint8_t gau8CertMem[M2M_TLS_SERVER_FLASH_SZ];
/**********************************************************************
Function
	WriteTlsCertificate

Description
	Update the tls certificate to WINC SPI flash

Return
	Status
***********************************************************************/
int WriteTlsCertificate(uint8_t *pu8PrivKey, uint32_t u32PrivKeySz, tstrFileInfo *astrCertList, uint8_t u8nCerts)
{
	int	ret = -1;
	uint32_t pu32SecSz;

	/* Read already loaded TLS Certificates from Flash.
	*/ 
	memset(gau8CertMem, 0, M2M_TLS_SERVER_FLASH_SZ);
	ret = programmer_read_tls_cert_store(gau8CertMem);
	if(M2M_SUCCESS != ret) goto END;
	
	/*Modify the TLS Certificate Store Contents.
	*/
	ret = TlsSrvSecWriteCertChain(pu8PrivKey, u32PrivKeySz, astrCertList, u8nCerts, gau8CertMem, &pu32SecSz, TLS_SRV_SEC_MODE_WRITE);	
	if(M2M_SUCCESS != ret) goto END;

	/*
	Erase the TLS Certificate Section
	*/
	ret = programmer_erase_tls_cert_store();
	if(M2M_SUCCESS != ret) goto END;

	/*
	Write the TLS Certificate Section buffer to WINC stacked flash directly.
	*/
	SYS_CONSOLE_PRINT("\r\n>> Writing the TLS Certificate to SPI flash...\r\n");
	ret = programmer_write_tls_cert_store(gau8CertMem);
	if(M2M_SUCCESS != ret) goto END;
	SYS_CONSOLE_PRINT("--- TLS Certificate written to SPI flash ---\r\n\r\n");
#ifdef ENABLE_VERIFICATION //Enable verification

		{
			uint32_t			u32Idx;

			/* Verify Sector 1 */
			memset(gau8Verify, 0, FLASH_SECTOR_SZ);
			programmer_read(gau8Verify,M2M_TLS_SERVER_FLASH_OFFSET,FLASH_SECTOR_SZ);
	        
			for(u32Idx = 0; u32Idx < FLASH_SECTOR_SZ; u32Idx ++)
			{
				if(gau8CertMem[u32Idx] != gau8Verify[u32Idx])
				{
					SYS_CONSOLE_PRINT(">> ERROR TLS Cert verification failed at Sector 1\n");
					ret = -1;
					break;
				}
			}

			/* Verify Sector 2 */
			memset(gau8Verify, 0, FLASH_SECTOR_SZ);
			programmer_read(gau8Verify,M2M_TLS_SERVER_FLASH_OFFSET+FLASH_SECTOR_SZ,FLASH_SECTOR_SZ);
			
			for(u32Idx = 0; u32Idx < FLASH_SECTOR_SZ; u32Idx ++)
			{
				if(gau8CertMem[u32Idx+FLASH_SECTOR_SZ] != gau8Verify[u32Idx])
				{
					SYS_CONSOLE_PRINT(">> ERROR TLS Cert verification failed at Sector 2\n");
					ret = -1;
					break;
				}
			}
			SYS_CONSOLE_PRINT(">> TLS Certificates Verified OK\r\n");
		}

#endif //Enable verification
	
END:
	return ret;
}
