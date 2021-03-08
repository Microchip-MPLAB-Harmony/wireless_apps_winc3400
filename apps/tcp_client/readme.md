---
parent: Harmony 3 Wireless application examples for WINC3400
title: TCP Client
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: WINC
family: SAMD21
family: SAME54
function: TCP Client
---

# TCP Client

The WINC example application demonstrates as a conventional, open tcp client-server communication.

## Description

In this demonstration, the WINC Driver will connect to a BSS and begin a TCP client socket connection to a remote server service.
This demonstration can be configured in the following ways in the source code.
• The BSS to connect to.
• The TCP server address and port to connect to.
• The receive buffer size.
• The message which should be sent as the first data once connected to the server.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/wireless)


Path of the application within the repository is **apps/tcp_client/firmware** .

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
