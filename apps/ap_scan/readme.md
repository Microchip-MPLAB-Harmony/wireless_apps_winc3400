---
parent: Harmony 3 Wireless application examples for WINC3400
title: AP Scan
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAMD21
family: SAME54
function: AP Scan
---

# AP Scan

This example compiles the AP Scan application which is used to scan for available BSSs and display the list.

## Description

AP Scan application is used to scan for available BSSs and display the list. It sends out a scan requests and lists responses of all Access points along with their signal strength.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400)


Path of the application within the repository is **apps/ap_scan/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| sam_d21_xpro_winc3400.X | MPLABX project for SAMD21 and WINC3400 Xplained pro |
| sam_e54_xpro_winc3400.X | MPLABX project for SAME54 and WINC3400 Xplained pro |
|||

## Setting up SAMXXX Xplained Pro board

- Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable

## Running the Application

1. Open the project.
2. Build and program the generated code into the hardware using its IDE.
3. Refer "firmware update guide" and "WINC Driver Demonstrations" for information.
