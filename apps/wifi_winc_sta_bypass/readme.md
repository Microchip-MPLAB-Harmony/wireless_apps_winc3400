# WINC STA Bypass Demo Application

This example compiles the WINC STA Bypass application.

## Description

This example implements a simple STA Client application on the SAM E54 Xplained Pro board with the ATWINC1500/3400 XPRO board where the WINC controller is in Bypass/Ethernet mode.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400)

Path of the application within the repository is **apps/wifi\_winc\_sta\_bypass/firmware** .

To build the application, refer to the following table and open the project using its IDE.

|Project Name|Description|
|------------|-----------|
|sam\_e54\_xpro\_winc3400.X|MPLABX project for SAME54 and WINC3400 Xplained pro|
| | |

## Setting up SAME54 Xplained Pro board

-   Connect the ATWINCxx00 Xpro Wi-Fi board to **EXT1** XPRO Header of SAME54 Xplained baord.

-   Connect the Debug USB port on the SAME54 Xplained Pro board to the computer using a micro USB cable


## Running the Application

1.  Open the project in MPLAB® X IDE and open the **app.c** file to change the access point parameters as shown in the picture below.

    ![app_ap_parameters_2](images/GUID-A0E976C6-0493-4C47-8899-5A88402351B1-low.png)

2.  Build and program the generated code into the hardware using its IDE by using on-board EDBG programmer.

3.  Open a terminal application \(eg: TeraTerm\) and configure the baud rate for **115200**.

    ![open_teraterm](images/GUID-14DE9A16-CCBD-4E37-8CD5-127DA5E7DF14-low.png)

4.  Press the **Reset** button on the SAM E54 Xplained Ultra board.

5.  The following messages will be visible on the terminal window.

    ![run_teraterm_outout_1](images/GUID-07A2E0DD-B68F-4660-9F03-E6EB1246DAD9-low.png)

6.  Type **ping <PC's IP address\>** in the terminal window and press **Enter** to see responses.

    ![run_teraterm_ping](images/GUID-A9E21FE0-303A-4CEB-BF16-2E5FF3CE74A8-low.png)

7.  You can also ping this board from your PC using cmd prompt as shown below.

    ![run_pc_cmd_ping](images/GUID-EAD97CBD-E9E7-4D94-ADEB-AF5C8E3B7D2A-low.png)


## How to create this project from scratch

Following Wireless Wiki tutorial shows step-by-step process to create this project from scratch

[Create WINC1500 bypass mode demo from scratch](https://github.com/Microchip-MPLAB-Harmony/wireless/wiki/Create-your-first-winc-bypass-application)

