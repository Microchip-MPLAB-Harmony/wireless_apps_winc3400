---
grand_parent: Harmony 3 Wireless application examples for WINC3400
parent: Wi-Fi Socket Mode Demos
title: Battery Service
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAME54
family: SAMD21
function: Battery Service
---

## Battery Service<a name="batdemo"></a>
The]is application demonstartes the reporting of battery level of the device using the battery characteristics. This example application simulates the device battery level from 0% to 100%, with the step of 1% every second.

**Note:**<br>
Currently, this demo is disabled in the project **sam_d21_xpro_winc3400.X** due to memory limitation.<br>The user can enable this demo by enabling the macro **APP_BLE_BATTERY** in **app.h** file.

1. This is an BLE application example. So the user need to download the Microchip Bluetooth Data application from App Store. 

2. Enter the command "appdemo start 14" to select and run the application.

	![](images/battery_start.png)

3. Open the Microchip Bluetooth Data application. Select Bluetooth Smart Widget. In the Bluetooth Smart Widget, press "START SCAN". From the list of available devices select the device name MCHP-BAS.

	![](images/BAS_device_list.png)

4. Enter the pass-key “123456” on Bluetooth Pairing Request window and click Pair.

	![](images/bas_pairing.png)

5. When paired, the application displays the Battery Service and the Generic Information service. 

6. Select “Battery Service” to receive notifications for the battery level characteristic.
	
	![](images/Bat_notification_options.png)
	

