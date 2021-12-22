---
grand_parent: Harmony 3 Wireless application examples for WINC3400
parent: Wi-Fi Bypass Mode Demos
title: WiFi Station Mode / Access Point Mode Demo
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAME54
family: SAMD21
function: WiFi Station Mode / Access Point Mode Demo
---

## WiFi Station Mode / Access Point Mode Demo<a name="stademo"></a>
This example demonstrates the use of the WINC3400 to behave as a Station or Access Point(AP).

### Station Mode
1. Configure the WiFi parameters using the "wifi set " command.

	![](images/wifi_config.png)
	
2. Select and run the application using the command "appdemo start 1"

	![](images/ap_scan_start.png)
	
3. The application starts and perform scanning and connects to the 
WiFi.

	![](images/ap_scan_console.png)
	
### Access Point Mode
1. If the user wants to configure the device as Access Point,configure the wifi using "wifi set" command. In the configuration set the bootmode as Access point mode, keep the authentication type as "OPEN" and give an SSID name for the Access point.

	![](images/ap_mode_config_cmd.png)

2. Enter the command "appdemo start 1" to run the application.

	![](images/ap_mode_config.png)

3. Connect a device to this Access point. The IP address of connected device will be displayed on the console.

	![](images/ap_mode_connected.png)


