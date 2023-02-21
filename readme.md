# Harmony 3 Wireless application examples for WINC3400

MPLAB® Harmony 3 is an extension of the MPLAB® ecosystem for creating embedded firmware solutions for Microchip 32-bit SAM and PIC® microcontroller and microprocessor devices. Refer to the following links for more information.

-   [Microchip 32-bit MCUs](https://www.microchip.com/design-centers/32-bit)

-   [Microchip 32-bit MPUs](https://www.microchip.com/design-centers/32-bit-mpus)

-   [Microchip MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)

-   [Microchip MPLAB® Harmony](https://www.microchip.com/mplab/mplab-harmony)

-   [Microchip MPLAB® Harmony Pages](https://microchip-mplab-harmony.github.io/)


This repository contains the MPLAB® Harmony 3 Wireless application examples for WINC3400

-   [Release Notes](release_notes.md)

-   [MPLAB® Harmony License](mplab_harmony_license.md)


To clone or download these applications from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400) and then click **Clone** button to clone this repository or download as zip file. This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

-   **[WINC STA Bypass Demo Application](apps/wifi_winc_sta_bypass/readme.md)**  

-   **[TCP Server in SoftAP](apps/wifi_tcp_server_in_softap/readme.md)**  

-   **[Wifi Provisioning via WPS](apps/wifi_provisioning_via_wps/readme.md)**  

-   **[Wifi Provisioning via SoftAP](apps/wifi_provisioning_via_softap/readme.md)**  

-   **[Wi-Fi provisioning using BLE](apps/wifi_provision_via_ble/readme.md)**  

-   **[TCP Client](apps/tcp_client/readme.md)**  

-   **[Power Save Mode](apps/power_save_mode_example/readme.md)**  

-   **[AP Scan](apps/ap_scan/readme.md)**  

-   **[WINC3400 Bypass Mode Demo Applications](apps/wifi_bypass_demos/readme.md)**  

-   **[Create your first WINC3400 Bypass mode example using Harmony TCP/IP stack](apps/wifi_bypass_demos/docs/GUID-4ABAE224-6F7D-47D1-ACBE-5DE2FD598301.md)**  

-   **[WINC3400 Socket Mode Demo Applications](apps/wifi_socket_demos/readme.md)**  

-   **[Example project creation - WINC3400 Socket mode project with SAMD21](apps/wifi_socket_demos/docs/GUID-D13DB96E-629F-4533-A72D-FA069843DEE9.md)**  

-   **[Example project creation - WINC3400 Socket mode project with SAME54](apps/wifi_socket_demos/docs/GUID-0CD99E9B-6954-42F9-8CA8-5E92D55DAEB8.md)**  

-   **[Create WINC Project - Getting Started](apps/getting_started/GUID-862E7BA5-9BC0-413B-8702-BE39DD70C671.md)**  

-   **[WINC Devices – Integrated Serial Flash Memory Download Procedure](apps/getting_started/GUID-98974C20-3195-4C76-84CF-C5DD8C246505.md)**  

-   **[Supported Network Modes in WINC](apps/getting_started/GUID-E20D971E-D45E-41BE-8598-2DFA10C5FF8A.md)**  


## Contents Summary

|Folder|Description|
|------|-----------|
|apps|Contains Wireless service example applications.|
|docs|Contains documentation in html format for offline viewing \(to be used only after cloning this repository onto a local machine\). Use [github pages](https://microchip-mplab-harmony.github.io/wireless_apps_winc3400/) of this repository for viewing it online.|

## Code Examples

The following applications are provided to demonstrate the typical or interesting usage models of one or more wireless usecases.

|Name|Description|
|----|-----------|
|AP Scan \(Socket mode\)|Demonstrates scan of near by HomeAP’s and connects to configured HomeAP|
|TCP Client \(Socket mode\)|Demonstrates WINC3400 TCP Client example application|
|TCP Server \(Socket mode\)|Demonstrates WINC3400 TCP Server example application|
|Wi-Fi Provisioning using SoftAP \(Socket mode\)|Demonstrates WINC3400 HomeAP Provisioning using SoftAP|
|Wi-Fi Provisioning using WPS \(Socket mode\)|Demonstrates WINC3400 HomeAP Provisioning using WPS|
|Wi-Fi Provisioning using BLE \(Socket mode\)|Demonstrates WINC3400 HomeAP Provisioning using BLE|
|Wi-Fi STA \(Bypass/Ethernet mode\)|Demonstrates WINC3400 STA Bypass\\Ethenet mode application|
|Power Save Mode|Demonstrates WINC3400 low power modes|
|Wi-Fi Bypass Mode Demos|Demonstrates the below WINC3400 applications in Bypass Mode. WiFi station mode/Access point mode demo, SSL Demo, Ping Demo, Iperf Demo, SNTP Demo, MQTT Demo, WiFi Provisioning Demo|
|Wi-Fi Socket Mode Demos|Demonstrates the below WINC3400 applications in Socket Mode. WiFi station mode/Access point mode demo, SSL Demo, Ping Demo, Iperf Demo, SNTP Demo, MQTT Demo, OTA Demo, WiFi Provisioning Demo, WiFi Provisioning via BLE , Custom serial Chat Demo, Heart Rate Profile Demo, Battery Service Demo, Proximity Reporter Demo, Transparent Service Demo, Certificate Download OTA Demo, WiFi BLE Connectionless Gateway Demo|

## Documentation

|Mode|Document|Description|
|----|--------|-----------|
||Create WINC Project - Getting Started|This is a getting-started guide for MPLABX IDE|
||Firmware Upgrade of WINC Devices|This document explains in detail downloading procedure of firmware, certificate, and gain values into WINC serial flash through different supported serial interfaces like UART/I2C.|
||Supported Modes In WINC devices|Describes the supported modes in WINC devices|
|Socket Mode|WINC3400+SAMD21|This document explains a step by step approach to create a WINC3400 Socket mode project with SAMD21 host.|
|Socket Mode|WINC3400+SAME54|This document explains a step by step approach to create a WINC3400 Socket mode project with SAME54 host.|
|Bypass Mode|WINC3400+SAME54|This document explains a step by step approach to create a WINC3400 Bypass mode project with SAME54 host.|

