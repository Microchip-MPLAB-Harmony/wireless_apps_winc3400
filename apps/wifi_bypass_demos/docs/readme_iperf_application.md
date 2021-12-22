---
grand_parent: Harmony 3 Wireless application examples for WINC3400
parent: Wi-Fi Bypass Mode Demos
title: Iperf Demo
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAME54
family: SAMD21
function: Iperf Demo
---

## Iperf Demo<a name="iperfdemo"></a>

This application demonstrates how a user can run iperf application on WINC3400 device in Bypass Mode.

1. Configure the wifi parameters using "wifi set" command.

	![](images/wifi_config.png)

2. Enter the command "appdemo start 1" to set the DUT(Device Under Test) in station mode. It will connect to the wifi network and the IP address will be displayed on the terminal.


3. The user should enter the iperf commands in the terminal window (for DUT) and in the iperf application which is available in the PC.

	| Protocol         | PC         | DUT         | Command on PC        | Command on DUT      | 
	| ---------------- | ----------------| ----------------| ---------------|-------------------------------       |
	| UDP   | Client | Server        |iperf -u -c \<Server_IP_Address\> -t \<time_peroid\> -i \<time_interval\> -u -b \<bandwidth\><br> e.g.: iperf -u -c 192.168.43.27 -b 20M -i 1 -t 10 |iperf -s -u -i \<time_interval\> <br> e.g.: iperf -s -u -i 1|
	| UDP | Server | Client |iperf -s -u -i \<time_interval\> <br> e.g.: iperf -s -u -i 1| iperf -u -c \<Server_IP_Address\> -t \<time_peroid\> -i \<time_interval\> -u -b \<bandwidth\><br> e.g.: iperf -u -c 192.168.43.87 -b 20M -i 1 -t 10 |
	| TCP  | Client | Server | iperf -c \<Server_IP_Address\> -t \<time_peroid\> -i \<time_interval\> <br> e.g: iperf -c 192.168.43.27 -i 1 -t 10 | iperf -s -i \<time_interval\> <br> e.g: iperf -s -i 1|
	| TCP| Server| Client| iperf -s -i \<time_interval\> <br> e.g: iperf -s -i 1| iperf -c \<Server_IP_Address\> -t \<time_peroid\> -x \<bandwidth\> <br> e.g: iperf -c 192.168.43.87 -x 10M -t 10 
	|||
