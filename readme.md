---
title: Harmony 3 Wireless application examples for WINC3400
nav_order: 1
has_children: true
has_toc: false
---
[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# Harmony 3 Wireless application examples for WINC3400

MPLAB® Harmony 3 is an extension of the MPLAB® ecosystem for creating embedded firmware solutions for Microchip 32-bit SAM and PIC® microcontroller and microprocessor devices.  Refer to the following links for more information.

- [Microchip 32-bit MCUs](https://www.microchip.com/design-centers/32-bit)
- [Microchip 32-bit MPUs](https://www.microchip.com/design-centers/32-bit-mpus)
- [Microchip MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide)
- [Microchip MPLAB® Harmony](https://www.microchip.com/mplab/mplab-harmony)
- [Microchip MPLAB® Harmony Pages](https://microchip-mplab-harmony.github.io/)

This repository contains the MPLAB® Harmony 3 Wireless application examples for WINC3400
- [Release Notes](release_notes.md)
- [MPLAB® Harmony License](mplab_harmony_license.md)

To clone or download these applications from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400) and then click **Clone** button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

## Contents Summary

| Folder     | Description                             |
| ---        | ---                                     |
| apps       | Contains Wireless service example applications. |
| docs       | Contains documentation in html format for offline viewing (to be used only after cloning this repository onto a local machine). Use [github pages](https://microchip-mplab-harmony.github.io/wireless_apps_winc3400/) of this repository for viewing it online. |


## Code Examples

The following applications are provided to demonstrate the typical or interesting usage models of one or more wireless usecases.

| Name | Description |
| ---- | ----------- |
|[AP Scan (Socket mode)](apps/ap_scan/readme.md)|Demonstrates scan of near by HomeAP’s and connects to configured HomeAP|
|[TCP Client (Socket mode)](apps/tcp_client/readme.md)|Demonstrates WINC3400 TCP Client example application|
|[TCP Server (Socket mode) ](apps/wifi_tcp_server_in_softap/readme.md)|Demonstrates WINC3400 TCP Server example application|
|[Wi-Fi Provisioning using SoftAP (Socket mode)](apps/wifi_provisioning_via_softap/readme.md)|Demonstrates WINC3400 HomeAP Provisioning using SoftAP |
|[Wi-Fi Provisioning using WPS (Socket mode)](apps/wifi_provisioning_via_wps/readme.md)|Demonstrates WINC3400 HomeAP Provisioning using WPS|
|[Wi-Fi Provisioning using BLE (Socket mode)](apps/wifi_provision_via_ble/readme.md)|Demonstrates WINC3400 HomeAP Provisioning using BLE|
|[Wi-Fi STA (Bypass/Ethernet mode)](apps/wifi_winc_sta_bypass/readme.md)|Demonstrates WINC3400 STA Bypass\Ethenet mode application|
|[Power Save Mode](apps/power_save_mode_example/readme.md)|Demonstrates WINC3400 low power modes|
|[Wi-Fi Bypass Mode Demos](apps/wifi_bypass_demos/readme.md)|Demonstrates the below WINC3400 applications in Bypass Mode. <br>WiFi station mode/Access point mode demo <br>SSL Demo <br>Ping Demo <br>Iperf Demo <br>SNTP Demo <br>MQTT Demo <br>WiFi Provisioning Demo|
|[Wi-Fi Socket Mode Demos](apps/wifi_socket_demos/readme.md)|Demonstrates the below WINC3400 applications in Socket Mode. <br>WiFi station mode/Access point mode demo <br>SSL Demo <br>Ping Demo <br>Iperf Demo <br>SNTP Demo <br>MQTT Demo <br>OTA Demo <br>WiFi Provisioning Demo <br>WiFi Provisioning via BLE <br>Custom serial Chat Demo <br>Heart Rate Profile Demo <br>Battery Service Demo <br>Proximity Reporter Demo <br>Transparent Service Demo <br> Certificate Download OTA Demo <br> |

## Documentation

| Mode       | Document| Description                             |
| ----        | ----    |---                                 |
| | [Create WINC Project - Getting Started](apps/getting_started/create_winc_project_from_scratch.md)  | This is a getting-started guide for MPLABX IDE |
| | [Firmware Upgrade of WINC Devices ](apps/getting_started/winc_firmware_upgrade.md) | This document explains in detail downloading procedure of firmware, certificate, and gain values into WINC serial flash through different supported serial interfaces like UART/I2C. |
| | [Supported Modes In WINC devices](apps/getting_started/winc_supported_modes.md) | Describes the supported modes in WINC devices |
|Socket Mode| [WINC3400+SAMD21](apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.md)| This document explains a step by step approach to create a WINC3400 Socket mode project with SAMD21 host.|
|Socket Mode|[WINC3400+SAME54](apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.md)|This document explains a step by step approach to create a WINC3400 Socket mode project with SAME54 host.|
|Bypass Mode|[WINC3400+SAME54](apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.md)|This document explains a step by step approach to create a WINC3400 Bypass mode project with SAME54 host. |


____

[![License](https://img.shields.io/badge/license-Harmony%20license-orange.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/blob/master/mplab_harmony_license.md)
[![Latest release](https://img.shields.io/github/release/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/releases/latest)
[![Latest release date](https://img.shields.io/github/release-date/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/releases/latest)
[![Commit activity](https://img.shields.io/github/commit-activity/y/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/graphs/commit-activity)
[![Contributors](https://img.shields.io/github/contributors-anon/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)]()

____

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/user/MicrochipTechnology)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/microchip-technology)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/microchiptechnology/)
[![Follow us on Twitter](https://img.shields.io/twitter/follow/MicrochipTech.svg?style=social)](https://twitter.com/MicrochipTech)

[![](https://img.shields.io/github/stars/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg?style=social)]()
[![](https://img.shields.io/github/watchers/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg?style=social)]()