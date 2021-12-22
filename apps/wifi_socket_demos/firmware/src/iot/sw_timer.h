/**
 * \file
 *
 * \brief SW Timer component for the IoT(Internet of things) service.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef IOT_SW_TIMER_H_INCLUDED
#define IOT_SW_TIMER_H_INCLUDED

#include <stdint.h>
#include "app_cert_download_ota.h"
#include "system/time/sys_time.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef Assert
#define Assert(expr) ((void) 0)
#endif


typedef struct {
    SYS_TIME_CALLBACK sysTmrCallback;
    SYS_TIME_HANDLE *tmrHndl;
    uintptr_t context;
}tmrContext_t;


SYS_TIME_HANDLE sw_timer_register_callback(SYS_TIME_CALLBACK callback, void *context, uint16_t period);

void sw_timer_enable_callback(SYS_TIME_HANDLE tmrHndl);

void sw_timer_disable_callback(SYS_TIME_HANDLE tmrHndl);

void sw_timer_destroy_callback(SYS_TIME_HANDLE tmrHndl);


#ifdef __cplusplus
}
#endif

#endif /* IOT_SW_TIMER_H_INCLUDED */