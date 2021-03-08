---
parent: Harmony 3 Wireless application examples for WINC3400
title: Power Save Mode
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAMD21
family: SAME54
function: Power Save Mode
---

# Power Save Mode

This example compiles the Power Save Mode application which is used to demonstrate WINC's low power mode.

## Description

In this demonstration, the WINC’s power save feature is demonstrated. The Power save mode is demonstrated depending on the value configured in example_conf.h - WDRV_WINC_PS_MODE_OFF, WDRV_WINC_PS_MODE_AUTO_LOW_POWER and WDRV_WINC_PS_MODE_MANUAL.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/wireless)


Path of the application within the repository is **apps/power_save_mode_example/firmware** .

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
3. Refer "firmware update guide" for information.
4. Please note this example will not output any console messages.
