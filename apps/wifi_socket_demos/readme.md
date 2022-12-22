
# WINC3400 Socket Mode Demo Applications

This example project demonstrates the WINC3400 applications of WiFi and BLE in Socket mode

## Description

This project has both WiFi and BLE example applications. The user can configure the WiFi parameters and select the required example application through command. The user would need to use "Microchip Bluetooth Data" mobile application to run the BLE example applications.

## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400)


Path of the application within the repository is ,**wireless_apps_winc3400/apps/wifi_socket_demos/firmware**.

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------| -----------------------------------------------------  |
| sam_e54_xpro_winc3400.X | MPLABX project for SAME54 and WINC3400 Xplained pro|
| sam_d21_xpro_winc3400.X | MPLABX project for SAMD21 and WINC3400 Xplained pro|
| sam_e54_xpro_winc3400_freertos.X | MPLABX project for SAME54 and WINC3400 Xplained pro using FreeRTOS|
| sam_a5d27_som1_winc3400.X | MPLABX project for SAMA5D27 and WINC1500 WiFi 7 Click board|
|||


## Setting up SAMXXX Xplained Pro board

- Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable

## Setting up SAMA5D27 SOM1-Ek1 board

- Connect the WINC3400 WiFi 8 Click board to the MBus1 connector.

- Connect the USB port (J10) on SOM1-Ek1 board to the computer using micro USB cable.

### Setting up the SD card

- Copy the boot loader binary( boot.bin) from "firmware\at91bootstrap_sam_a5d27_som1_ek.X\binaries" onto the SD card

- Copy the application (harmony.bin) from "firmware/sam_a5d27_som1_winc3400.X/dist/sam_a5d27_som1_winc3400/production" onto the SD card, available after a successful build of the application

## Running the Application

1. Build and program the application project using its respective IDE

2. Open the Terminal application (Ex.:Tera term) on the computer

3. Connect to the "USB to UART" COM port and configure the serial settings as follows:

    * Baud : 115200
    * Data : 8 Bits
    * Parity : None
    * Stop : 1 Bit
    * Flow Control : None

4. Use WiFi commands to configure WiFi parameters and use application commands to select the example application.

WiFi Commands Details

| Command         | Details        |               Example                |
| ----------------| ---------------|-------------------------------       |
| wifi help    	  | Wi-Fi Service help command| wifi help                 |
| wifi set \<bootmode\> \<ssid_name\> \<auth_type\> \<pwd\> \<username/index\>     | Set Wi-Fi Configuration for Station(STA) mode or Access Point (AP) mode | wifi set 2 DEMO_AP 2 12345678 |
| wifi get        | Get Wi-Fi Configuration   | wifi get   |
|||

Wi-Fi command parameters information

| Parameter       | Sub Parameter                                          |
| ----------------| -----------------------------------------------------  |
| bootmode        | 1- Access point(AP) mode.<br>2- Station(STA) mode.     |
| ssid_name       | SSID name                                			   |
|authtype(Security type) | 1 - OPEN Mode.<br> 2 - WPAPSK mode.<br> 3 - WEP mode.<br>  5 -  802.1x authentication MSCHAPV2 mode.  |
|pwd(password)| Password/passphrase  |
|username/index| Username if authtype is 802.1x authentication MSCHAPV2  or Key Index if the authtype is WEP.  |
|||

Application command parameters information

| Command         | Details        |               Example                |
| ----------------| ---------------|-------------------------------       |
| appdemo help    | Application Service help command| appdemo help        |
| appdemo start \<demo_id\>  | Select and start an application demo | appdemo start 1 |
| appdemo get     | Get the ID of currently running application demo  | appdemo get   |
| appdemo stop     | Stop the currently running application demo  | appdemo stop   |
|||

Application command parameters information

| Parameter       | Sub Parameter                                          |
| ----------------| -----------------------------------------------------  |
| demo_ID         | 1 - WiFi station mode/Access point mode demo.<br>6 - WiFi Provisioning via BLE. <br> 7 - OTA Demo. <br> 8 - SSL Demo. <br> 9 - Ping Demo. <br> 10 - Iperf demo. <br> 11 - SNTP demo. <br> 12 - Serial Chat. <br> 13 - Heart rate profile. <br> 14 - Battery Service. <br> 15 - Proximity Reporter. <br> 16 - Transparent Service. <br> 18 - MQTT Demo. <br> 19 - Certificate Download OTA Demo.|
|||


## List of Applications

| Application      | Description                                    |
| ----------------| -----------------------------------------------------  |
| [WiFi station mode/Access point mode demo](GUID-CF0832B7-23E1-4E35-A1DE-7FC82194FDD6.md)  | Demonstartes the Station Mode or Access Point(AP) mode of WINC3400   |  	  
| [WiFi Provisioning via BLE](GUID-A24A649B-14FE-4938-8BF3-AFDD3F36E2D2.md)  |Demonstartes the WiFi provisioning using BLE |    
| [OTA Demo](GUID-C3E09031-D714-4F59-8C0D-5AD6C31F7129.md) |Demonstartes the OTA firmware upgrade of WINC3400 |        
| [SSL Demo](GUID-62FC0E1E-3C98-45A0-A7D8-A40A1F58A004.md)  |Demonstrates TCP SSL Client application |      
| [Ping Demo](GUID-E623850D-7676-4ACC-A8BE-634D53B4BF5C.md) | Demonstrates the Ping test |       
| [Iperf Demo](GUID-11B187F2-A2D5-4004-8085-4E1960FF2510.md) | Demonstrates the iperf application|      
| [SNTP Demo](GUID-617E4AF5-AFBF-4AD8-A694-D17E347A103E.md)  |Demonstrates how to retrieve time information from the time server|     
| [Custom serial Chat Demo](GUID-4179DE5D-7260-49E4-B8A3-D7954299ADCB.md)   |Demonstrates the Custom Serial Chat application using BLE|    
| [Heart Rate Profile Demo](GUID-29322041-5FEE-440A-86ED-FF758E26DF94.md)   | Demonstrates the Heart Rate Profile application using BLE|    
| [Battery Service Demo](GUID-F6C1AEC3-D21B-440A-9AF7-40CE3A8C6251.md)   | Demonstrates the Battery Service application using BLE|     
| [Proximity Reporter Demo](GUID-423A02F6-C40D-47FD-A330-B86AD684E2F1.md)   | Demonstrates the Proximity Reporter application using BLE|    
| [Transparent Service Demo](GUID-E3159AC0-44A2-4304-9ED7-75C30606A4F3.md) |Demonstrates the Transparent Service application using BLE     |
| [MQTT Demo](GUID-B5D94855-68C3-41B9-8499-44E0ED492759.md) | Demonstrates  MQTT Application  |      
| [WiFi Provisioning Demo](GUID-27AD4A89-B663-48BD-ADA8-F36812640DB7.md) | Demonstartes the WiFi provisioning application|
| [Certificate Download OTA Demo](GUID-75D92290-831A-4383-BDF2-FBDB8F6E651B.md) | Demonstartes the Certificate Download OTA Demo|
| [WiFi BLE Connectionless Gateway Demo](GUID-9529805E-7FC7-420D-8DC2-49600780BC69.md) | Demonstrates the WiFi BLE connectionless Gateway|      
|||


### Steps to isolate/copy individual application(s) from the demo

 If the user wants to isolate an application, follow the below mentioned steps <br>

 For example, the user wants to create an SNTP demo in Socket mode.

1. The SNTP demo uses the WiFi functionalities to get connected with the network. So copy the files "<em> app_wifi.c</em>" and "<em> app_wifi.h </em>" from the path "<em>wireless_apps_winc3400/apps/wifi_bypass_demos/firmware/src </em>" or "<em>wireless_apps_winc3400/apps/wifi_socket_demos/firmware/src</em>" to "src" folder of the new demo project. Then add these files to the project.<br>

2. Now user should copy and add the SNTP application files "<em>app_sntp.c</em>" and "<em>app_sntp.h</em>" from the path "<em>wireless_apps_winc3400/apps/wifi_bypass_demos/firmware/src </em>" or "<em>wireless_apps_winc3400/apps/wifi_socket_demos/firmware/src</em>" to the "<em>src</em> folder of the new demo project. <br>

3. The "<em>app.c</em>" and "<em>app.h</em>"  files need to be copied by the user. These files integrate the SNTP application and WiFi functionalities. Copy and add these two files from the same "src" path to the "src" folder of the new demo project. <br>

4. In "app.c", within "<em>APP_Initialize()</em>" function, initialize the sntp application by calling "<em> APP_SntpInitialize(APPWiFiCallback)</em>".

5. In "app.c" file, make sure that, "<em> APP_WiFiTasks(wdrvHandle)</em>" is getting called from the "<em> APP_STATE_WDRV_OPEN </em>" state of "<em> APP_Tasks() </em>" state machine.

6. In the same state machine "<em> APP_Tasks() </em>", within the state "<em> APP_STATE_WDRV_APP_LOOP </em>" , call the sntp application state machine "<em>APP_SntpTasks(handle)</em>".

7. Now follow the steps mentioned in the SNTP demo document to run the SNTP demo using "wifi", "sntp" and "appdemo" commands.

Similarly, for any application demo, take the required application files along with WiFi files and "app" files to create the demo.


### Steps to isolate/copy individual BLE application(s) from the demo

For BLE applications, no need to copy the WiFi files. But the user should copy the Ble_Service and Ble_Profile files from the path "<em>wireless_apps_winc3400\apps\wifi_socket_demos\firmware\src\ble </em>".

For example, the user wants to create a new project, say "Heart_rate_demo", then

1. Copy and add the ble_manager files from the path "<em>wireless_apps_winc3400\apps\wifi_socket_demos\firmware\src\ble\ble_services\ble_mgr</em>" to the "<em> Heart_rate_demo\firmware\src\ble\ble_services\ble_mgr</em>" of the new project.

2. Copy and add the Heart rate profile files from the path "<em>wireless_apps_winc3400\apps\wifi_socket_demos\firmware\src\ble\ble_profiles\hr_sensor</em>" to the "<em> Heart_rate_demo\firmware\src\ble\ble_profiles\hr_sensor</em>" of the new project.

3. Copy and add the Heart rate service files from the path "<em>wireless_apps_winc3400\apps\wifi_socket_demos\firmware\src\ble\ble_services\heart_rate</em>" to the "<em> Heart_rate_demo\firmware\src\ble\ble_services\heart_rate</em>" of the new project.

4. Now copy and add the application files "app_heart_rate.c" and "app_heart_rate.h" from "<em>wireless_apps_winc3400\apps\wifi_socket_demos\firmware\src</em>" to the "<em> Heart_rate_demo\firmware\src</em>" of the new project.

5. Copy and add the main application files "app.c" and "app.h" files from "<em>wireless_apps_winc3400\apps\wifi_socket_demos\firmware\src</em>" to the "<em> Heart_rate_demo\firmware\src</em>" of the new project.

6. In "app.c", within "<em>APP_Initialize()</em>" function, initialize the Heart Rate application by calling "<em> APP_BleHeartrateInitialize(APPWiFiCallback)</em>".

7. In "app.c" file, make sure that, "<em> APP_BleHeartrateTasks(wdrvHandle)</em>" is getting called from the "<em> APP_STATE_WDRV_OPEN </em>" state of "<em> APP_Tasks() </em>" state machine.

8. Add the macro "BLE_DEVICE_ROLE=BLE_PERIPHERAL" in the project properties.

    ![project_properties](GUID-C989929B-2974-4594-B484-F17D0E9F1688-low.png)

9. Now follow the steps mentioned in the "Heart rate demo document" to run the application using "appdemo" command.

Similarly, for any ble application demo, take the required application files, ble_profile files, ble_service files and "app" files to create the demo.

**Note:**

1. User has to make sure the project path does not exceed windows path limit.

2. User should reset the device before switching the application and unpair the device from the android phone in case of switching BLE application demos.


<a href="#top">Back to top</a>