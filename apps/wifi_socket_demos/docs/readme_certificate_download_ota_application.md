---
grand_parent: Harmony 3 Wireless application examples for WINC3400
parent: Wi-Fi Socket Mode Demos
title:  Certificate Download OTA Demo
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAME54
family: SAMD21
function:  Certificate Download OTA Demo
---	

## Certificate Download OTA Demo<a name="Certificate Download OTA Demo"></a>
This example demonstrates how to download the TLS certificates into WINC3400 via OTA. It downloads the certificates from an OTA download server, which is a web server.  

**Note:**<br>
This example will be only available with SAME54 Host.

1. Use any HTTP server or hfs.exe from http://www.rejetto.com/hfs/

2. Run the hfs.exe

3. Add the certificates from the “\utilities\cert_store” to the root folder in the hfs.exe tool.

	![](images/cert_down_ota_1.png)	

4. Configure the wifi parameters using "wifi set" command.

	![](images/ping_demo_config.png)

5. Copy the URL from server.

	![](images/cert_down_ota_7.png)

6. Enter the command "cert \<url\>". 

	![](images/cert_down_ota_3.png)

7. Enter the application command "appdemo start 1 19" to run the Certificate download via OTA demo. First the device will connect to the network. 

	![](images/cert_down_ota_4.png)

8. After the IP address has displayed on the terminal window, application will execute the CERT command and starts the certificate download.

	![](images/cert_down_ota_5.png)

