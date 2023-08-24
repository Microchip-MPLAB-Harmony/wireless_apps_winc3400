# WINC3400 Bypass Mode Demo Applications

This example project demonstrates the WINC3400 WiFi applicationsin Bypass mode.

-   **[WiFi Provisioning](docs/GUID-4E41A963-CE42-4337-A4F7-7B6F4F6C4298.md)**  

-   **[WiFi Station Mode / Access Point Mode Demo](docs/GUID-68E8D0A3-9E94-4C43-BE0E-646C0FF1ED5D.md)**  

-   **[SSL Demo](docs/GUID-541D141F-C0A2-4E43-98EA-602C80C05F58.md)**  

-   **[SNTP Demo](docs/GUID-658CA5E0-6127-4E31-8626-3E88161483DC.md)**  

-   **[Ping Demo](docs/GUID-7AD2548F-606B-4F25-A71F-5B555FF3D4A7.md)**  

-   **[MQTT Demo](docs/GUID-49316BE3-AC2F-4E11-AE94-1E35E949F3B2.md)**  

-   **[Iperf Demo](GUID-955C3E8C-7967-49D9-A353-AE0486131D1C.md)**  


**Parent topic:**[Harmony 3 Wireless application examples for WINC3400](GUID-B02CCF0F-B40C-487D-8D4D-570EFA78D2BF.md)

## Description

This project has WiFi example applications. The user can configure the WiFi parameters and select the required example application through command.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400)

Path of the application within the repository is ,**wireless\_apps\_winc3400/apps/wifi\_bypass\_demos/firmware**.

To build the application, refer to the following table and open the project using its IDE.

|Project Name|Description|
|------------|-----------|
|sam\_e54\_xpro\_winc3400.X|MPLABX project for SAME54 Xplained Pro Evaluation Kit and WINC3400 Xplained pro|
|sam\_e54\_xpro\_winc3400\_freertos.X|MPLABX project for SAME54 Xplained Pro Evaluation Kit and WINC3400 Xplained pro usinf FreeRTOS|
|sam\_a5d27\_som1\_winc3400.X|MPLABX project for SAMA5D27-SOM1-EK1 Evaluation Kit and WINC3400 WiFi 8 Click board|
|pic32mz\_ef\_curiosity\_v2\_winc3400.X|MPLABX project for PIC32MZ EF 2.0 curiosity board and WINC3400 Xplained pro|
| |

## Setting up SAMXXX Xplained Pro board

-   Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable

-   Connect the WINC3400 Xplained pro on the EXT1 header of SAMXXX Xplained Pro board


## Setting up PIC32MZ EF 2.0 Curiosity board

-   Connect the Debug USB port on the PIC32MZ EF 2.0 Curiosity board to the computer using a micro USB cable

-   Connect the WINC3400 Xplained pro on the EXT1 header of PIC32MZ EF 2.0 Curiosity board


## Setting up SAMA5D27-SOM1-EK1 Evaluation Kit

-   Connect the WINC3400 WiFi 8 Click board to the MBus1 connector.

-   Connect the USB port \(J10\) on SOM1-Ek1 board to the computer using micro USB cable.


### Addtional hardware required

-   SD Card with FAT32 file system


### Setting up the SD card

-   Copy the boot loader binary\( boot.bin\) from "firmware\\at91bootstrap\_sam\_a5d27\_som1\_ek.X\\binaries" onto the SD card

-   Copy the application \(harmony.bin\) from "firmware/sam\_a5d27\_som1\_winc3400.X/dist/sam\_a5d27\_som1\_winc3400/production" onto the SD card, available after a successful build of the application


### Setting up the board

-   Insert the SD card into SDMMC slot \(J12\).

-   Connect the Debug USB port on the board to the computer using a micro USB cable.


## Running the Application

1.  Build and program the application project using its respective IDE

2.  Open the Terminal application \(Ex.:Tera term\) on the computer

3.  Connect to the "USB to UART" COM port and configure the serial settings as follows:

    -   Baud : 115200

    -   Data : 8 Bits

    -   Parity : None

    -   Stop : 1 Bit

    -   Flow Control : None

4.  Use WiFi commands to configure WiFi parameters and use application commands to select the example application.


WiFi Commands Details

|Command|Details|Example|
|-------|-------|-------|
|wifi help|Wi-Fi Service help command|wifi help|
|wifi set <bootmode\> <ssid\_name\> <auth\_type\> <pwd\> <username/index\>|Set Wi-Fi Configuration for Station\(STA\) mode or Access Point \(AP\) mode|wifi set 2 DEMO\_AP 2 12345678|
|wifi get|Get Wi-Fi Configuration|wifi get|
| |

Wi-Fi command parameters information

|Parameter|Sub Parameter|
|---------|-------------|
|bootmode|1- Access point\(AP\) mode.2- Station\(STA\) mode.|
|ssid\_name|SSID name|
|authtype\(Security type\)|1 - OPEN Mode. 2 - WPAPSK mode. 3 - WEP mode. 5 - 802.1x authentication MSCHAPV2 mode.|
|pwd\(password\)|Password/passphrase|
|username/index|Username if authtype is 802.1x authentication MSCHAPV2 or Key Index if the authtype is WEP.|
| |

Application command parameters information

|Command|Details|Example|
|-------|-------|-------|
|appdemo help|Application Service help command|appdemo help|
|appdemo start <demo\_id\>|Select and start an application demo|appdemo start 1|
|appdemo get|Get the ID of currently running application demo|appdemo get|
|appdemo stop|Stop the currently running application demo|appdemo stop|
| |

Application command parameters information

|Parameter|Sub Parameter|
|---------|-------------|
|demo\_ID|1 - WiFi station mode/Access point mode demo. 8 - SSL Demo. 9 - Ping Demo. 10 - Iperf demo. 11 - SNTP demo. 18 - MQTT Demo.|
| |

## List of Applications

|Application|Description|
|-----------|-----------|
|[WiFi station mode/Access point mode demo](docs/GUID-68E8D0A3-9E94-4C43-BE0E-646C0FF1ED5D.md)|Demonstartes the Station Mode or Access Point\(AP\) mode of WINC3400|
|[SSL Demo](docs/GUID-541D141F-C0A2-4E43-98EA-602C80C05F58.md)|Demonstrates TCP SSL Client application|
|[Ping Demo](docs/GUID-7AD2548F-606B-4F25-A71F-5B555FF3D4A7.md)|Demonstrates the Ping test|
|[Iperf Demo](docs/GUID-955C3E8C-7967-49D9-A353-AE0486131D1C.md)|Demonstrates the iperf application|
|[SNTP Demo](docs/GUID-658CA5E0-6127-4E31-8626-3E88161483DC.md)|Demonstrates how to retrieve time information from the time server|
|[MQTT Demo](docs/GUID-49316BE3-AC2F-4E11-AE94-1E35E949F3B2.md)|Demonstrates MQTT Application|
|[WiFi Provisioning Demo](docs/GUID-4E41A963-CE42-4337-A4F7-7B6F4F6C4298.md)|Demonstartes the WiFi provisioning application|
| | |

### Steps to isolate/copy individual application\(s\) from the demo

If the user wants to isolate an application, follow the below mentioned steps

For example, the user wants to isolate the SNTP demo in Bypass mode.

1.  The SNTP demo uses the WiFi functionalities to get connected with the network. So copy the files "*app\_wifi.c*" and "*app\_wifi.h*" from the path "*wireless\_apps\_winc3400/apps/wifi\_bypass\_demos/firmware/src*" or "*wireless\_apps\_winc3400/apps/wifi\_socket\_demos/firmware/src*" to "src" folder of the new demo project. Then add these files to the project.

2.  Now user should copy and add the SNTP application files "*app\_sntp.c*" and "*app\_sntp.h*" from the path "*wireless\_apps\_winc3400/apps/wifi\_bypass\_demos/firmware/src*" or "*wireless\_apps\_winc3400/apps/wifi\_socket\_demos/firmware/src*" to the "*src* folder of the new demo project.

3.  The "*app.c*" and "*app.h*" files need to be copied by the user. These files integrate the SNTP application and WiFi functionalities. Copy and add these two files from the same "src" path to the "src" folder of the new demo project.

4.  In "app.c", within "*APP\_Initialize\(\)*" function, initialize the sntp application by calling "*APP\_SntpInitialize\(APPWiFiCallback\)*".

5.  In "app.c" file, make sure that, "*APP\_WiFiTasks\(wdrvHandle\)*" is getting called from the "*APP\_STATE\_WDRV\_OPEN*" state of "*APP\_Tasks\(\)*" state machine.

6.  In the same state machine "*APP\_Tasks\(\)*", within the state "*APP\_STATE\_WDRV\_APP\_LOOP*" , call the sntp application state machine "*APP\_SntpTasks\(handle\)*".

7.  Now follow the steps mentioned in the SNTP demo document to run the SNTP demo using "wifi", "sntp" and "appdemo" commands.


Similarly, for any application demo, take the required application files along with WiFi files and "app" files to create the demo.

**Note:**

1.  User has to make sure the project path does not exceed windows path limit.

2.  User should reset the device before switching the application and unpair the device from the android phone in case of switching BLE application demos.


[Back to top](#top)

