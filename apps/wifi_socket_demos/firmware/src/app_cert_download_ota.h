/*******************************************************************************
  MPLAB Harmony Example Configuration File

  Company:
    Microchip Technology Inc.

  File Name:
    app_cert_download.h

  Summary:
    This header file provides configuration for the wifi certificate download via OTA application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2020-21 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END

#include "app.h"
#ifdef APP_CERT_DOWNLOAD_OTA
#ifndef _APP_CERT_DOWNLOAD_OTA_H
#define _APP_CERT_DOWNLOAD_OTA_H


#define MAIN_HTTP_PORT_NUMBER                (80)

/** Maximum size for packet buffer. */
#define MAIN_BUFFER_MAX_SIZE                 (1446)
/** Maximum file name length. */
#define MAIN_MAX_FILE_NAME_LENGTH            (100)
#define CERTIFICATES_BUFFER_SIZE             (6000)

/** No of certificates to be written to WINC **/
#define NUM_OF_ROOT_TLS_CHAIN_CERTIFICATES  3

typedef enum {
        NOT_READY = 0, /*!< Not ready. */
        WIFI_CONNECTED = 0x01, /*!< Wi-Fi is connected. */
        HTTP_DOWNLOAD_INITIATED = 0x02, /*!< Start download is called */
        GET_REQUESTED = 0x04, /*!< GET request is sent. */
        DOWNLOADING = 0x08, /*!< Running to download. */
        COMPLETED = 0x10, /*!< Download completed. */
        CANCELED = 0x20, /*!< Download canceled. */
        ROOT_CERT_DOWNLOAD = 0x40, /*!< Root cert Download. */
        TLS_CERT_DOWNLOAD = 0x80 /*!< TLS cert Download. */
} download_state;

typedef enum {
        ROOT_CERT = 1,
        TLS_RSA_CERT = 2,
        TLS_ECC_CERT = 3,
} cert_type_t;

typedef struct
{
        cert_type_t cert_type;
        uint8_t numOfChainCert;
        uint8_t *filename;
} certFileInfo;

void APP_CertDownloadOtaTasks(DRV_HANDLE handle);

void APP_CertDownloadOtaInitialize(APP_CALLBACK pAPPWiFiCallback);

#endif /* _EXAMPLE_CONF_H */

/*******************************************************************************
 End of File
 */

#endif