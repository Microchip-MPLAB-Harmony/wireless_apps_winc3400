---
title: Release notes
nav_order: 99
---

![Microchip logo](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_logo.png)
![Harmony logo small](https://raw.githubusercontent.com/wiki/Microchip-MPLAB-Harmony/Microchip-MPLAB-Harmony.github.io/images/microchip_mplab_harmony_logo_small.png)

# Microchip MPLAB® Harmony 3 Release Notes

## Harmony 3 Wireless application examples for WINC3400 v3.5.0

### Development kit and demo application support

Following table provides number of Wireless examples available for different development kits.

| Development Kits           | MPLABx applications |
|:--------------------------:|:-------------------:|
| SAMD21 with WINC3400 Xpro  |       8             |
|:--------------------------:|:-------------------:|
| SAME54 with WINC3400 Xpro  |       10            |
|:--------------------------:|:-------------------:|

### New Features

-   All applications have been migrated from MHC to MCC.


### Bug fixes

-   "wireless_wifi_apps_winc3400" applications are upgraded with latest "wireless_wifi" driver v3.7.0.

### Known Issues

-   WolfMQTT\(STA bypass mode\) demo application need to build "third\_party/wolfMQTT/mqtt\_socket.c" without xc32 option 'Make warnings into errors' as it uses the obsolete \#include <sys/errno.h\> file in WolfMQTT repo.

-   Additional known issues can be found at [WINC3400-known-issues](https://github.com/MicrochipTech/WINC3400-known-issues)


### Development Tools

-   [MPLAB® X IDE v6.00](https://www.microchip.com/mplab/mplab-x-ide)

-   MPLAB® X IDE plug-ins:

    -   MPLAB® Code Configurator \(MCC\) v5.1.17

-   [MPLAB® XC32 C/C++ Compiler v4.10](https://www.microchip.com/mplab/compilers)


