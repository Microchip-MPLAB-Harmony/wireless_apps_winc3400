---
grand_parent: Harmony 3 Wireless application examples for WINC3400
parent: Wi-Fi Bypass Mode Demos
title: SNTP Demo
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAME54
family: SAMD21
function: SNTP Demo
---

## SNTP Demo<a name="sntpdemo"></a>
This example demonstrates the use of the WINC3400 to retrieve time information from the time server. Follow the below mentioned steps to run the demo.
1. Configure the wifi parameters using "wifi set" command.

	![](images/wifi_config.png)

2.  Enter the command "sntp get".

	![](images/sntp_get_cmd.png)

3. Enter the command "appdemo start 1 11" to run the SNTP demo. First the device will connect to the network. After the IP address has displayed on the terminal window, application will execute the SNTP command and the response will be displayed on the terminal wimdow.

	![](images/sntp_response.png)

