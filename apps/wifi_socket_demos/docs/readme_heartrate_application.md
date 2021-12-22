---
grand_parent: Harmony 3 Wireless application examples for WINC3400
parent: Wi-Fi Socket Mode Demos
title:  Heart Rate Profile
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAME54
family: SAMD21
function:  Heart Rate Profile
---		

## Heart Rate Profile<a name="hrtdemo"></a>
This application demonstrates the exchange of heart rate parameters of heart rate profile between the sensor and monitor.  The heart rate profile is provided by Bluetooth SIG. 
1. This is an BLE application example. So the user need to download the Microchip Bluetooth Data application from App Store. 

2. Enter the command "appdemo start 13" to select and run the application.

	![](images/heart_rate_start.png)

3. Open the Microchip Bluetooth Data application. Select Bluetooth Smart Widget. In the Bluetooth Smart Widget, press "START SCAN". From the list of available devices select the device name MCHP-HRT.

	![](images/HRT_device_list.png)

4. Enter the pass-key “123456” on Bluetooth Pairing Request window and click Pair.

	![](images/HRT_pairing.png)

5. After the device is connected, the application displays the Heart Rate and the Device Information Service. Select Heart Rate Service.

	![](images/Heart_rate.png)

6. When notifications are enabled, the HRM values, Sensor Location and Energy Expended are displayed in the console and the corresponding mobile app.

	![](images/Heart_rate_console.png)
	

