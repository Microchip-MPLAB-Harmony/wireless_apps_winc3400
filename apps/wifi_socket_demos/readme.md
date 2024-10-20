# WINC3400 Socket Mode Demo Applications

This example project demonstrates the WINC3400 applications of WiFi and BLE in Socket mode

-   **[Wi-Fi BLE Connectionless Gateway Demo](docs/GUID-9529805E-7FC7-420D-8DC2-49600780BC69.md)**  

-   **[WiFi Provisioning via microchip android application](docs/GUID-27AD4A89-B663-48BD-ADA8-F36812640DB7.md)**  

-   **[WiFi Provisioning via BLE](docs/GUID-A24A649B-14FE-4938-8BF3-AFDD3F36E2D2.md)**  

-   **[Transparent Service Application Demo](docs/GUID-E3159AC0-44A2-4304-9ED7-75C30606A4F3.md)**  

-   **[WiFi Station Mode / Access Point Mode Demo](docs/GUID-CF0832B7-23E1-4E35-A1DE-7FC82194FDD6.md)**  

-   **[SSL Demo](docs/GUID-62FC0E1E-3C98-45A0-A7D8-A40A1F58A004.md)**  

-   **[SNTP Demo](docs/GUID-617E4AF5-AFBF-4AD8-A694-D17E347A103E.md)**  

-   **[Proximity Reporter Application Demo](docs/GUID-423A02F6-C40D-47FD-A330-B86AD684E2F1.md)**  

-   **[Ping Demo](docs/GUID-E623850D-7676-4ACC-A8BE-634D53B4BF5C.md)**  

-   **[OTA Demo](docs/GUID-C3E09031-D714-4F59-8C0D-5AD6C31F7129.md)**  

-   **[MQTT Demo](docs/GUID-B5D94855-68C3-41B9-8499-44E0ED492759.md)**  

-   **[Iperf Demo](docs/GUID-11B187F2-A2D5-4004-8085-4E1960FF2510.md)**  

-   **[Heart Rate Profile Application Demo](docs/GUID-29322041-5FEE-440A-86ED-FF758E26DF94.md)**  

-   **[Custom Serial Chat Application Demo](docs/GUID-4179DE5D-7260-49E4-B8A3-D7954299ADCB.md)**  

-   **[Certificate Download OTA Demo](docs/GUID-75D92290-831A-4383-BDF2-FBDB8F6E651B.md)**  

-   **[Battery Service Application Demo](docs/GUID-F6C1AEC3-D21B-440A-9AF7-40CE3A8C6251.md)**  


**Parent topic:**[Harmony 3 Wireless application examples for WINC3400](GUID-B02CCF0F-B40C-487D-8D4D-570EFA78D2BF.md)

## Description

This project has both WiFi and BLE example applications. The user can configure the WiFi parameters and select the required example application through command. The user would need to use "Microchip Bluetooth Data" mobile application to run the BLE example applications.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400)

Path of the application within the repository is ,**wireless\_apps\_winc3400/apps/wifi\_socket\_demos/firmware**.

To build the application, refer to the following table and open the project using its IDE.

|Project Name|Description|
|------------|-----------|
|sam\_e54\_xpro\_winc3400.X|MPLABX project for SAME54 Xplained Pro Evaluation Kit and WINC3400 Xplained pro|
|sam\_d21\_xpro\_winc3400.X|MPLABX project for SAMD21 Xplained Pro Evaluation Kit and WINC3400 Xplained pro|
|sam\_e54\_xpro\_winc3400\_freertos.X|MPLABX project for SAME54 Xplained Pro Evaluation Kit and WINC3400 Xplained pro using FreeRTOS|
|sam\_a5d27\_som1\_winc3400.X|MPLABX project for SAMA5D27 SAMA5D27-SOM1-EK1 Evaluation Kit and WINC1500 WiFi 7 Click board|
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

1.  Build and program the application project using its respective IDE. \(This step is not applicable for the host SAMA5D27.The application will load from SD card\)

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
|demo\_ID|1 - WiFi station mode/Access point mode demo.6 - WiFi Provisioning via BLE. 7 - OTA Demo. 8 - SSL Demo. 9 - Ping Demo. 10 - Iperf demo. 11 - SNTP demo. 12 - Serial Chat. 13 - Heart rate profile. 14 - Battery Service. 15 - Proximity Reporter. 16 - Transparent Service. 18 - MQTT Demo. 19 - Certificate Download OTA Demo.|
| |

## List of Applications

|Application|Description|
|-----------|-----------|
|[WiFi station mode/Access point mode demo](docs/GUID-CF0832B7-23E1-4E35-A1DE-7FC82194FDD6.md)|Demonstartes the Station Mode or Access Point\(AP\) mode of WINC3400|
|[WiFi Provisioning via BLE](docs/GUID-A24A649B-14FE-4938-8BF3-AFDD3F36E2D2.md)|Demonstartes the WiFi provisioning using BLE|
|[OTA Demo](docs/GUID-C3E09031-D714-4F59-8C0D-5AD6C31F7129.md)|Demonstartes the OTA firmware upgrade of WINC3400|
|[SSL Demo](docs/GUID-62FC0E1E-3C98-45A0-A7D8-A40A1F58A004.md)|Demonstrates TCP SSL Client application|
|[Ping Demo](docs/GUID-E623850D-7676-4ACC-A8BE-634D53B4BF5C.md)|Demonstrates the Ping test|
|[Iperf Demo](docs/GUID-11B187F2-A2D5-4004-8085-4E1960FF2510.md)|Demonstrates the iperf application|
|[SNTP Demo](docs/GUID-617E4AF5-AFBF-4AD8-A694-D17E347A103E.md)|Demonstrates how to retrieve time information from the time server|
|[Custom serial Chat Demo](docs/GUID-4179DE5D-7260-49E4-B8A3-D7954299ADCB.md)|Demonstrates the Custom Serial Chat application using BLE|
|[Heart Rate Profile Demo](docs/GUID-29322041-5FEE-440A-86ED-FF758E26DF94.md)|Demonstrates the Heart Rate Profile application using BLE|
|[Battery Service Demo](docs/GUID-F6C1AEC3-D21B-440A-9AF7-40CE3A8C6251.md)|Demonstrates the Battery Service application using BLE|
|[Proximity Reporter Demo](docs/GUID-423A02F6-C40D-47FD-A330-B86AD684E2F1.md)|Demonstrates the Proximity Reporter application using BLE|
|[Transparent Service Demo](docs/GUID-E3159AC0-44A2-4304-9ED7-75C30606A4F3.md)|Demonstrates the Transparent Service application using BLE|
|[MQTT Demo](docs/GUID-B5D94855-68C3-41B9-8499-44E0ED492759.md)|Demonstrates MQTT Application|
|[WiFi Provisioning Demo](docs/GUID-27AD4A89-B663-48BD-ADA8-F36812640DB7.md)|Demonstartes the WiFi provisioning application|
|[Certificate Download OTA Demo](docs/GUID-75D92290-831A-4383-BDF2-FBDB8F6E651B.md)|Demonstartes the Certificate Download OTA Demo|
|[WiFi BLE Connectionless Gateway Demo](docs/GUID-9529805E-7FC7-420D-8DC2-49600780BC69.md)|Demonstrates the WiFi BLE connectionless Gateway|
| |

### Steps to isolate/copy individual application\(s\) from the demo

If the user wants to isolate an application, follow the below mentioned steps

For example, the user wants to create an SNTP demo in Socket mode.

1.  The SNTP demo uses the WiFi functionalities to get connected with the network. So copy the files "*app\_wifi.c*" and "*app\_wifi.h*" from the path "*wireless\_apps\_winc3400/apps/wifi\_bypass\_demos/firmware/src*" or "*wireless\_apps\_winc3400/apps/wifi\_socket\_demos/firmware/src*" to "src" folder of the new demo project. Then add these files to the project.

2.  Now user should copy and add the SNTP application files "*app\_sntp.c*" and "*app\_sntp.h*" from the path "*wireless\_apps\_winc3400/apps/wifi\_bypass\_demos/firmware/src*" or "*wireless\_apps\_winc3400/apps/wifi\_socket\_demos/firmware/src*" to the "*src* folder of the new demo project.

3.  The "*app.c*" and "*app.h*" files need to be copied by the user. These files integrate the SNTP application and WiFi functionalities. Copy and add these two files from the same "src" path to the "src" folder of the new demo project.

4.  In "app.c", within "*APP\_Initialize\(\)*" function, initialize the sntp application by calling "*APP\_SntpInitialize\(APPWiFiCallback\)*".

5.  In "app.c" file, make sure that, "*APP\_WiFiTasks\(wdrvHandle\)*" is getting called from the "*APP\_STATE\_WDRV\_OPEN*" state of "*APP\_Tasks\(\)*" state machine.

6.  In the same state machine "*APP\_Tasks\(\)*", within the state "*APP\_STATE\_WDRV\_APP\_LOOP*" , call the sntp application state machine "*APP\_SntpTasks\(handle\)*".

7.  Now follow the steps mentioned in the SNTP demo document to run the SNTP demo using "wifi", "sntp" and "appdemo" commands.


Similarly, for any application demo, take the required application files along with WiFi files and "app" files to create the demo.

### Steps to isolate/copy individual BLE application\(s\) from the demo

For BLE applications, no need to copy the WiFi files. But the user should copy the Ble\_Service and Ble\_Profile files from the path "*wireless\_apps\_winc3400\\apps\\wifi\_socket\_demos\\firmware\\src\\ble*".

For example, the user wants to create a new project, say "Heart\_rate\_demo", then

1.  Copy and add the ble\_manager files from the path "*wireless\_apps\_winc3400\\apps\\wifi\_socket\_demos\\firmware\\src\\ble\\ble\_services\\ble\_mgr*" to the "*Heart\_rate\_demo\\firmware\\src\\ble\\ble\_services\\ble\_mgr*" of the new project.

2.  Copy and add the Heart rate profile files from the path "*wireless\_apps\_winc3400\\apps\\wifi\_socket\_demos\\firmware\\src\\ble\\ble\_profiles\\hr\_sensor*" to the "*Heart\_rate\_demo\\firmware\\src\\ble\\ble\_profiles\\hr\_sensor*" of the new project.

3.  Copy and add the Heart rate service files from the path "*wireless\_apps\_winc3400\\apps\\wifi\_socket\_demos\\firmware\\src\\ble\\ble\_services\\heart\_rate*" to the "*Heart\_rate\_demo\\firmware\\src\\ble\\ble\_services\\heart\_rate*" of the new project.

4.  Now copy and add the application files "app\_heart\_rate.c" and "app\_heart\_rate.h" from "*wireless\_apps\_winc3400\\apps\\wifi\_socket\_demos\\firmware\\src*" to the "*Heart\_rate\_demo\\firmware\\src*" of the new project.

5.  Copy and add the main application files "app.c" and "app.h" files from "*wireless\_apps\_winc3400\\apps\\wifi\_socket\_demos\\firmware\\src*" to the "*Heart\_rate\_demo\\firmware\\src*" of the new project.

6.  In "app.c", within "*APP\_Initialize\(\)*" function, initialize the Heart Rate application by calling "*APP\_BleHeartrateInitialize\(APPWiFiCallback\)*".

7.  In "app.c" file, make sure that, "*APP\_BleHeartrateTasks\(wdrvHandle\)*" is getting called from the "*APP\_STATE\_WDRV\_OPEN*" state of "*APP\_Tasks\(\)*" state machine.

8.  Add the macro "BLE\_DEVICE\_ROLE=BLE\_PERIPHERAL" in the project properties.

    ![project_properties](docs/GUID-C989929B-2974-4594-B484-F17D0E9F1688-low.png)

9.  Now follow the steps mentioned in the "Heart rate demo document" to run the application using "appdemo" command.


Similarly, for any ble application demo, take the required application files, ble\_profile files, ble\_service files and "app" files to create the demo.

**Note:**

1.  User has to make sure the project path does not exceed windows path limit.

2.  User should reset the device before switching the application and unpair the device from the android phone in case of switching BLE application demos.


[Back to top](#top)

