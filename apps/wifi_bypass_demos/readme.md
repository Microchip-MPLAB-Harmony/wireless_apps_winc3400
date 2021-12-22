---
parent: Harmony 3 Wireless application examples for WINC3400
title: Wi-Fi Bypass Mode Demos
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAME54
family: SAMD21
function: Wi-Fi Bypass Mode Demos
---

# WINC3400 Example Applications

This example project demonstrates the WINC3400 WiFi applicationsin Bypass mode.

## Description

This project has WiFi example applications. The user can configure the WiFi parameters and select the required example application through command. 
## Downloading and building the application

To download or clone this application from Github, go to the [top level of the repository](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400)


Path of the application within the repository is ,**wireless_apps_winc3400/apps/wifi_bypass_demos/firmware**.

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------| -----------------------------------------------------  |
| sam_e54_xpro_winc3400.X | MPLABX project for SAME54 and WINC3400 Xplained pro|
| sam_e54_xpro_winc3400_freertos.X | MPLABX project for SAME54 and WINC3400 Xplained pro usinf FreeRTOS|
|||


## Setting up SAMXXX Xplained Pro board

- Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable



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
| demo_ID         | 1 - WiFi station mode/Access point mode demo.<br> 8 - SSL Demo. <br> 9 - Ping Demo. <br> 10 - Iperf demo. <br> 11 - SNTP demo. <br> 18 - MQTT Demo.|
|||


## List of Applications

| Application      | Description                                    |
| ----------------| -----------------------------------------------------  |
| [WiFi station mode/Access point mode demo](docs/readme_sta_ap_mode_application.md)   | Demonstartes the Station Mode or Access Point(AP) mode of WINC3400   | 	    
| [SSL Demo](docs/readme_ssl_application.md) |  Demonstrates TCP SSL Client application |       
| [Ping Demo](docs/readme_ping_application.md) | Demonstrates the Ping test |       
| [Iperf Demo](docs/readme_iperf_application.md) | Demonstrates the iperf application|       
| [SNTP Demo](docs/readme_sntp_application.md)  |Demonstrates how to retrieve time information from the time server|     
| [MQTT Demo](docs/readme_mqtt_application.md)  | Demonstrates  MQTT Application  |     
| [WiFi Provisioning Demo](docs/readme_wifi_provision_application.md)  | Demonstartes the WiFi provisioning application|     
|||

### Steps to isolate/copy individual application(s) from the demo
 If the user wants to isolate an application, follow the below mentioned steps <br>

 For example, the user wants to isolate the SNTP demo in Bypass mode.
1. The SNTP demo uses the WiFi functionalities to get connected with the network. So copy the files "<em> app_wifi.c</em>" and "<em> app_wifi.h </em>" from the path "<em>wireless_apps_winc3400/apps/wifi_bypass_demos/firmware/src </em>" or "<em>wireless_apps_winc3400/apps/wifi_socket_demos/firmware/src</em>" to "src" folder of the new demo project. Then add these files to the project.<br>

2. Now user should copy and add the SNTP application files "<em>app_sntp.c</em>" and "<em>app_sntp.h</em>" from the path "<em>wireless_apps_winc3400/apps/wifi_bypass_demos/firmware/src </em>" or "<em>wireless_apps_winc3400/apps/wifi_socket_demos/firmware/src</em>" to the "<em>src</em> folder of the new demo project. <br>

3. The "<em>app.c</em>" and "<em>app.h</em>"  files need to be copied by the user. These files integrate the SNTP application and WiFi functionalities. Copy and add these two files from the same "src" path to the "src" folder of the new demo project. <br>

4. In "app.c", within "<em>APP_Initialize()</em>" function, initialize the sntp application by calling "<em> APP_SntpInitialize(APPWiFiCallback)</em>".

5. In "app.c" file, make sure that, "<em> APP_WiFiTasks(wdrvHandle)</em>" is getting called from the "<em> APP_STATE_WDRV_OPEN </em>" state of "<em> APP_Tasks() </em>" state machine.

6. In the same state machine "<em> APP_Tasks() </em>", within the state "<em> APP_STATE_WDRV_APP_LOOP </em>" , call the sntp application state machine "<em>APP_SntpTasks(handle)</em>".

7. Now follow the steps mentioned in the SNTP demo document to run the SNTP demo using "wifi", "sntp" and "appdemo" commands.

Similarly, for any application demo, take the required application files along with WiFi files and "app" files to create the demo.


**Note:** <br> 
1. User has to make sure the project path does not exceed windows path limit.

2. User should reset the device before switching the application and unpair the device from the android phone in case of switching BLE application demos. <br>


<a href="#top">Back to top</a>