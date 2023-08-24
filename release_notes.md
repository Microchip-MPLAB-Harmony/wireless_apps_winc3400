# Microchip MPLAB® Harmony 3 Release Notes

## Harmony 3 Wireless application examples for WINC3400 v3.7.0

### Development kit and demo application support

Following table provides number of Wireless examples available for different development kits.

|Development Kits|MPLABx applications|
|----------------|-------------------|
|SAMD21 with WINC3400 Xpro|8|
|SAME54 with WINC3400 Xpro|10|
|SAMA5D27-SOM1-EK1 with WINC3400 Wifi 8 Click board|2|
|PIC32MZ EF 2.0 curiosity board with WINC3400 Xpro|2|

### New Features

-   Developed WiFi Bypass Demos with SAMA5D27-SOM1-EK1 and WINC3400 Wifi 8 Click board with latest "wireless\_wifi" driver v3.9.0

-   Developed WiFi Bypass Demos and WiFi Socket Demos with PIC32MZ EF 2.0 curiosity board and WINC3400 Xpro with latest "wireless\_wifi" driver v3.9.0

-   Migrated all the host applications with latest "wireless\_wifi" driver v3.9.0


### Known Issues

-   WolfMQTT\(STA bypass mode\) demo application need to build "third\_party/wolfMQTT/mqtt\_socket.c" without xc32 option 'Make warnings into errors' as it uses the obsolete \#include <sys/errno.h\> file in WolfMQTT repo.

-   Additional known issues can be found at [WINC3400-known-issues](https://github.com/MicrochipTech/WINC3400-known-issues)


### Development Tools

-   [MPLAB® X IDE v6.15](https://www.microchip.com/mplab/mplab-x-ide)

-   MPLAB® X IDE plug-ins:

    -   MPLAB® Code Configurator \(MCC\) v5.1.17

-   [MPLAB® XC32 C/C++ Compiler v4.30](https://www.microchip.com/mplab/compilers)


