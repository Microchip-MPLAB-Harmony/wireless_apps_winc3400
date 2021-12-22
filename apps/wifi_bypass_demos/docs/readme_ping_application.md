---
grand_parent: Harmony 3 Wireless application examples for WINC3400
parent: Wi-Fi Bypass Mode Demos
title: Ping Demo
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAME54
family: SAMD21
function: Ping Demo
---

## Ping Demo<a name="pingdemo"></a>
This application demonstrates how a user can run a ping test on WINC3400 device in Bypass Mode.

1. Configure the wifi parameters using "wifi set" command.

	![](images/wifi_config.png)

2. Enter the command "appdemo start 1". Then the device will connected to the AP and the IP address will be displayed on the terminal.

	![](images/ping_bypass_ip.png)

3. Enter the command "ping \<ip_address\>". It will start pinging the corresponding IP address.
	
	![](images/ping_bypass_response.png)



