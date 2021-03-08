/*******************************************************************************
  MPLAB Harmony Example Configuration File

  Company:
    Microchip Technology Inc.

  File Name:
    example_conf.h

  Summary:
    This header file provides configuration for the example.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _EXAMPLE_CONF_H
#define _EXAMPLE_CONF_H

#define WLAN_SSID               "${APP_WIFI_SSID}"
#define WLAN_CHANNEL            ${APP_WIFI_CHANNEL}

<#if APP_WIFI_AUTH_METHOD_AP == "Open">
#define WLAN_AUTH_OPEN

<#elseif APP_WIFI_AUTH_METHOD_AP == "WEP">
#define WLAN_AUTH_WEP
#define WLAN_WEB_KEY_INDEX      ${APP_WIFI_WEP_KEY_IDX}
#define WLAN_WEB_KEY            "${APP_WIFI_WEP_KEY}"

</#if>
<#if APP_WIFI_TCP_SOCK_ENABLE>
#define TCP_LISTEN_PORT         ${APP_WIFI_TCP_SOCK_PORT}
#define TCP_BUFFER_SIZE         ${APP_WIFI_TCP_SOCK_BUF_SIZE}

</#if>
<#if APP_WIFI_AP_DHCP_SRV_ENABLE>
#define WLAN_DHCP_SRV_ADDR      "${APP_WIFI_AP_DHCP_SRV_ADDR}"
#define WLAN_DHCP_SRV_NETMASK   "${APP_WIFI_AP_DHCP_SRV_NETMASK}"

</#if>
#endif /* _EXAMPLE_CONF_H */

/*******************************************************************************
 End of File
 */
