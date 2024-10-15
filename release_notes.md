# Microchip MPLAB® Harmony 3 Release Notes

## Harmony 3 Wireless application examples for WINC3400 v3.7.1

### Development kit and demo application support

Following table provides number of Wireless examples available for different development kits.

| Development Kits           | MPLABx applications |
|:--------------------------:|:-------------------:|
| SAMD21 with WINC3400 Xpro  |       8             |
| SAME54 with WINC3400 Xpro  |       10            |
| SAMA5D27-SOM1-EK1 with WINC3400 Wifi 8 Click board |   2                |
| PIC32MZ EF 2.0 curiosity board with WINC3400 Xpro |   2                |

### New Features

- Migrated all the host applications with latest "wireless_wifi" driver v3.11.1

### Known Issues

- WolfMQTT(STA bypass mode) demo application need to build "third_party/wolfMQTT/mqtt_socket.c" without xc32 option 'Make warnings into errors' as it uses the obsolete #include <sys/errno.h> file in WolfMQTT repo.

- User may face connectivity issue with the SSL demo of bypass mode with FreeRTOS. Please use SSL demo of bypass mode without FreeRTOS.

- Additional known issues can be found at [WINC3400-known-issues](https://github.com/MicrochipTech/WINC3400-known-issues)

### Development Tools

- [MPLAB® X IDE v6.20](https://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® X IDE plug-ins:
  - MPLAB® Code Configurator (MCC) v5.5.1
- [MPLAB® XC32 C/C++ Compiler v4.45](https://www.microchip.com/mplab/compilers)
