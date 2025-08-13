# Microchip MPLAB® Harmony 3 Release Notes

## Harmony 3 Wireless application examples for WINC3400 v3.7.2

### Development kit and demo application support

Following table provides number of Wireless examples available for different development kits.

| Development Kits           | MPLABx applications |
|:--------------------------:|:-------------------:|
| SAMD21 with WINC3400 Xpro  |       8             |
| SAME54 with WINC3400 Xpro  |       10            |
| SAMA5D27-SOM1-EK1 with WINC3400 Wifi 8 Click board |   2                |
| PIC32MZ EF 2.0 curiosity board with WINC3400 Xpro |   2                |

### New Features

- Migrated all the host applications with latest "wireless_wifi" driver v3.12.1

### Bug fixes and Improvements

- Updated the "wifi_socket_demos" utilities with latest version of BLEDK3 apk.
- Resolved the SSL connection negotiation failure in the "wifi_bypass_demo" application.
- Corrected the LED behavior in the Proximity Reporter Application.

### Known Issues

- The "wireless_apps_winc3400" repository should be placed alongside other dependency repositories to prevent MCC loading failures.
- Additional known issues can be found at [WINC3400-known-issues](https://github.com/MicrochipTech/WINC3400-known-issues)

### Development Tools

- [MPLAB® X IDE v6.25](https://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® X IDE plug-ins:
- MPLAB® Code Configurator (MCC) v5.6.2
- [MPLAB® XC32 C/C++ Compiler v4.60](https://www.microchip.com/mplab/compilers)
