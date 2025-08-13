![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Harmony 3 Wireless application examples for WINC3400

MPLAB® Harmony 3 is an extension of the MPLAB® ecosystem for creating embedded firmware solutions for Microchip 32-bit SAM and PIC® microcontroller and microprocessor devices. Refer to the following links for more information.

-   [Microchip 32-bit MCUs](https://www.microchip.com/design-centers/32-bit)

-   [Microchip 32-bit MPUs](https://www.microchip.com/design-centers/32-bit-mpus)

-   [Microchip MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)

-   [Microchip MPLAB® Harmony](https://www.microchip.com/mplab/mplab-harmony)

-   [Microchip MPLAB® Harmony Pages](https://microchip-mplab-harmony.github.io/)


This repository contains the MPLAB® Harmony 3 Wireless application examples for WINC3400

-   [Release Notes](release_notes.md)

-   [MPLAB® Harmony License](License.md)


To clone or download these applications from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400) and then click **Clone** button to clone this repository or download as zip file.<br />This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

## Contents Summary

|Folder|Description|
|------|-----------|
|apps|Contains Wireless service example applications.|
|docs|Contains documentation in html format for offline viewing \(to be used only after cloning this repository onto a local machine\). Use [github pages](https://microchip-mplab-harmony.github.io/wireless_apps_winc3400/) of this repository for viewing it online.|

## Code Examples

The following applications are provided to demonstrate the typical or interesting usage models of one or more wireless usecases.

|Name|Description|
|----|-----------|
|[AP Scan \(Socket mode\)](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_ap_scan&redirect=true)|Demonstrates scan of near by HomeAP’s and connects to configured HomeAP|
|[TCP Client \(Socket mode\)](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_tcp_client&redirect=true)|Demonstrates WINC3400 TCP Client example application|
|[TCP Server \(Socket mode\)](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_tcp_server_in_softap&redirect=true)|Demonstrates WINC3400 TCP Server example application|
|[Wi-Fi Provisioning using SoftAP \(Socket mode\)](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_wifi_prov_via_softap&redirect=true)|Demonstrates WINC3400 HomeAP Provisioning using SoftAP|
|[Wi-Fi Provisioning using WPS \(Socket mode\)](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_wifi_prov_via_wps&redirect=true)|Demonstrates WINC3400 HomeAP Provisioning using WPS|
|[Wi-Fi Provisioning using BLE \(Socket mode\)](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_wifi_prov_via_ble&redirect=true)|Demonstrates WINC3400 HomeAP Provisioning using BLE|
|[Wi-Fi STA \(Bypass/Ethernet mode\)](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_wifi_winc_sta_bypass&redirect=true)|Demonstrates WINC3400 STA Bypass\\Ethenet mode application|
|[Power Save Mode](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_power_save_mode&redirect=true)|Demonstrates WINC3400 low power modes|
|[Wi-Fi Bypass Mode Demos](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_wifi_bypass_demos&redirect=true)|Demonstrates the below WINC3400 applications in Bypass Mode. WiFi station mode/Access point mode demo, SSL Demo, Ping Demo, Iperf Demo, SNTP Demo, MQTT Demo, WiFi Provisioning Demo|
|[Wi-Fi Socket Mode Demos](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_socket_demos&redirect=true)|Demonstrates the below WINC3400 applications in Socket Mode. WiFi station mode/Access point mode demo, SSL Demo, Ping Demo, Iperf Demo, SNTP Demo, MQTT Demo, OTA Demo, WiFi Provisioning Demo, WiFi Provisioning via BLE , Custom serial Chat Demo, Heart Rate Profile Demo, Battery Service Demo, Proximity Reporter Demo, Transparent Service Demo, Certificate Download OTA Demo, WiFi BLE Connectionless Gateway Demo|

## Documentation

|Mode|Document|Description|
|----|--------|-----------|
||[Create WINC Project - Getting Started](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_create_winc_project_scratch&redirect=true)|This is a getting-started guide for MPLABX IDE|
||[Firmware Upgrade of WINC Devices](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_fw_upgrade&redirect=true)|This document explains in detail downloading procedure of firmware, certificate, and gain values into WINC serial flash through different supported serial interfaces like UART/I2C.|
||[Supported Modes In WINC devices](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_supported_modes&redirect=true)|Describes the supported modes in WINC devices|
|Socket Mode|[WINC3400+SAMD21](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_samd21_socketmode_scratch&redirect=true)|This document explains a step by step approach to create a WINC3400 Socket mode project with SAMD21 host.|
|Socket Mode|[WINC3400+SAME54](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_same54_socketmode_scratch&redirect=true)|This document explains a step by step approach to create a WINC3400 Socket mode project with SAME54 host.|
|Bypass Mode|[WINC3400+SAME54](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_same54_bypassmode_scratch&redirect=true)|This document explains a step by step approach to create a WINC3400 Bypass mode project with SAME54 host.|


Click [here](https://onlinedocs.microchip.com/v2/keyword-lookup?keyword=wireless_apps_winc3400_introduction&redirect=true) to view the online documentation of code examples hosted in this repository.

To view the documentation offline, follow these steps:

- Download the publication as a [zip](https://onlinedocs.microchip.com/download/GUID-AD5B776E-19C6-49CD-A7CF-B692D58694C2?type=webhelp) file from here.
- Extract the zip file into a folder.
- Navigate to the folder and open index.html in a web browser of your choice.

____

[![License](https://img.shields.io/badge/license-Harmony%20license-orange.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/blob/master/Microchip_SLA001.md)
[![Latest release](https://img.shields.io/github/release/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/releases/latest)
[![Latest release date](https://img.shields.io/github/release-date/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/releases/latest)
[![Commit activity](https://img.shields.io/github/commit-activity/y/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/graphs/commit-activity)
[![Contributors](https://img.shields.io/github/contributors-anon/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)]()

____

[![Developer Help](https://img.shields.io/badge/Youtube-Developer%20Help-red.svg)](https://www.youtube.com/MicrochipDeveloperHelp)
[![Developer Help](https://img.shields.io/badge/XWiki-Developer%20Help-torquiose.svg)](https://developerhelp.microchip.com/xwiki/bin/view/software-tools/harmony/)
[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/user/MicrochipTechnology)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/microchip-technology)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/microchiptechnology/)
[![Follow us on Twitter](https://img.shields.io/twitter/follow/MicrochipTech.svg?style=social)](https://twitter.com/MicrochipTech)

[![](https://img.shields.io/github/stars/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg?style=social)]()
[![](https://img.shields.io/github/watchers/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg?style=social)]()