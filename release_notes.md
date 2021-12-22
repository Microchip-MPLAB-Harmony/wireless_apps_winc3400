---
title: Release notes
nav_order: 99
---

![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip MPLAB® Harmony 3 Release Notes

## Harmony 3 Wireless application examples for WINC3400 v3.4.2

### Development kit and demo application support

Following table provides number of Wireless examples available for different development kits.

| Development Kits           | MPLABx applications |
|:--------------------------:|:-------------------:|
| SAMD21 with WINC3400 Xpro  |       8             |
|:--------------------------:|:-------------------:|
| SAME54 with WINC3400 Xpro  |       10            |
|:--------------------------:|:-------------------:|

### New Features
- New MQTT, SSL, SNTP and OTA demos added for Bypass mode.
- New MQTT, SSL, SNTP, OTA Certificate download and OTA demos added for Socket mode.
    
### Bug fixes
- "wireless_wifi_apps_winc3400" applications are upgraded with Countermeasures for ‘Fragattack’ vulnerabilities.

### Known Issues
- Due to an issue in the underlying `net` repo, you need to turn off `-Werror` for the `icmp.c` file in your projects.
- User may face connectivity issue with the SSL demo of bypass mode with FreeRTOS. Please use SSL demo of bypass mode without FreeRTOS.
- "wireless_wifi" Serial bridge application needs to be regenerated before using it for firmware update.
Additional known issues can be found at [WINC3400-known-issues](https://github.com/MicrochipTech/WINC3400-known-issues)

### Development Tools

- [MPLAB® X IDE v5.50](https://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® X IDE plug-ins:
  - MPLAB® Harmony Configurator (MHC) v3.8.2
- [MPLAB® XC32 C/C++ Compiler v3.01](https://www.microchip.com/mplab/compilers)
