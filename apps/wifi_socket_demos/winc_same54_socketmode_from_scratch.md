---
parent: Harmony 3 Wireless application examples for WINC3400
title: Example project creation - WINC3400+SAME54 Socket mode
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAME54
family: SAMD21
function: Example project creation - WINC Socket mode project with SAME54
---

# Example project creation - WINC Socket mode project with SAME54
This document explains a step by step approach to create a WINC Socket mode project with SAME54 host.


## Hardware Setup

The document demonstrates the creation of a demo on the SAM E54 Xplained Pro board with the ATWINC1500 XPRO board.

The SAME54 Xplained PRO contains a built-in programmer-debugger tool called Embedded Debugger (EDBG) which is used in this tutorial.

Following image shows the hardware setup.

![](images/same54_57.png)



## Steps to create the new example project

Follow the below mwntioned steps to create the new WINC project in socket mode with SAME54 from scratch.

## Project Creation

* Open MP Lab
* Go to File Menu and select New Project…

    ![](images/same54_1.png)



### Project Selection

* Under the Projects section, select 32bit MPLAB Harmony3 Project and click on Next.

    ![](images/same54_2.png)

### Framework Selection

* Enter the local system path where the packages are downloaded click Next.

    ![](images/same54_3.png)


### Project Settings

* Under {local system H3 path}\wireless_apps_winc1500\apps, create a folder name for the project (Ex: sample_project).
* Enter the full path including the newly created project folder.
* Enter the Folder name and Project name and click on Next (To know about “Folder” and “Name” please click “Show visual Help” button).

    ![](images/same54_4.png)

### Configuration Settings

* Enter a **Name** for the config setting folder
* select the **Target device** name
* Click **Finish**.

    ![](images/same54_5.png)

* Click **Launch** once **Configuration Database Setup** windows pops up.

    ![](images/same54_6.png)

MHC window and has three panes.
1. Available components: <br>
It lists all the components from downloaded packages.
2. Project Graph.<br>
It is where the user adds components from Available components
3. Configuration options. <br>
Each component in project graph can be configured using Configuration options.

    ![](images/same54_7.png)

### Adding components in MH3

User should select required components for creating WINC project.

### Core

The first component to enable is Core because core is the base component for many drivers and system components.

 * Go to Harmony in the Available components
 * Select core.

    ![](images/same54_8.png)

 * Drag and drop it in the **Project Graph**.
 * This will ask permission to activate Free RTOS. Since this project does not require free RTOS, click **No**.

    ![](images/samd21_9.png)

 * Core component appears in the Project Graph as shown below.

    ![](images/same54_10.png)

### SAME54 Xplained pro component

This example uses SAME54 xplained pro board for host development board.
Enable component SAM E54 Xplained Pro BSP.
* Go to Board Support Packages
* select SAM E54 Xplained Pro BSP

    ![](images/same54_11.png)

* Drag and drop it in the Project Graph.

    ![](images/same54_12.png)

### Timer component

WINC driver needs driver for its delay functionality and user can select the any timer for this.
To enable Timer
* Go to **Harmony -> System Services**
* Select **TIME**

    ![](images/same54_13.png)

* Drag and drop it in the Project Graph.

    ![](images/same54_14.png)

* Right click on **TMR** in the **TIME component**
* Go to Satisfiers and select **TC3** (user can select any timer)

    ![](images/same54_15.png)

* This adds **TC3** connected with **TIME**

    ![](images/same54_16.png)

### EIC component
WINC device uses interrupt pin PB07. To configure PB07, EIC component must be enabled.
* Go to **Peripherals**
* Select **EIC**

    ![](images/same54_17.png)

* Drag and drop it in the Project Graph.

    ![](images/same54_18.png)

Pin PB07 belongs to external interrupt channel 7 so EIC channel 7 has to be enabled and configured.
* Select EIC in the Project Graph
* Please do the following changes in the Configuration Options:
    * Check Enable **EIC channel4** box and expand **EIC channel7 Configuration**
    * Check **Enable Interrupt** box
    * Change **Enable Interrupt7 Edge detection** to **Falling Edge detection**

    ![](images/same54_19.png)

### Virtual Console

Virtual Console is used to send debug messages and to receive commands from user. Virtual console uses UART interface for communication.<br>
Host SAME54 uses pins PB24 and PB25 for UART interface to perform receive and transmit operation, respectively. These two pins belong to SERCOM2 of the host SAME54 device.<br>
For more information please refer section 5.4.2 (Virtual COM Port) of **[SAM E54 Xplained Pro User's Guide](http://ww1.microchip.com/downloads/en/DeviceDoc/70005321A.pdf)**<br>

To enable and configure Virtual COM port:
* Go to **System Services**
* Select **CONSOLE**

    ![](images/same54_20.png)

* Drag and drop it in the Project Graph.

    ![](images/same54_21.png)

UART interface of **SERCOM2** is used by **CONSOLE**.
* Right click on the **UART** port of **Instance 0** of the **CONSOLE** component.
* Go to Satisfiers and select **SERCOM2**.

    ![](images/same54_22.png)

**SERCOM2** appears in **Project Graph** connected with **CONSOLE**. 

![](images/same54_23.png)

**SERCOM2** uses **PAD[1]** for data reception.
* Change the **Receive pinout** property to **SERCOM PAD[1]** in the Configuration Options

    ![](images/same54_24.png)   

**CONSOLE** has a dependency on **DEBUG** and **COMMAND** component.
To add DEBUG component
* Right click on the SYS_CONSOLE interface of Instance 0 of the **CONSOLE** component.
* Go to **Consumers** and select **DEBUG**

    ![](images/same54_25.png)

* **DEBUG** component connected with **CONSOLE** appears in the Project Graph

    ![](images/same54_26.png)

### To add COMMAND component

* Right click on the SYS_CONSOLE interface of Instance 0 of the CONSOLE component.
* Go to Consumers and select COMMAND

    ![](images/same54_27.png)

* COMMAND component connected with CONSOLE appears in the Project Graph

    ![](images/same54_28.png)

### SPI component

WINC communicates with host using SPI interface. So, to establish a SPI connection between WINC and host, three components are required.<br>
They are:
* SPI Driver
* SERCOM4 (Peripheral library)
* WINC Driver

To enable SPI driver,
* In the Available Components, go to Harmony -> Drivers.
* Select SPI

    ![](images/same54_29.png)

* Drag and drop it in the Project Graph

    ![](images/same54_30.png)

Connect SERCOM4 with SPI driver.
* Right click on the SPI interface of Instance 0 of the SPI component.
* Go to Satisfiers and select SERCOM4

    ![](images/same54_31.png)

SERCOM4 appears in Project Graph connected with SPI driver.

    ![](images/same54_32.png)

Enable DMA for SPI driver
* Select instance 0 on SPI driver
* Go to Configurations Options and enable Use DMA for Transmit and Receive

    ![](images/same54_33.png)

* **SERCOM4** uses PAD[3] for data reception. change the SPI Data In Pad selection property to SERCOM PAD[3] in the Configuration Options
* Enable the property SPI Master Hardware Slave Select.

    ![](images/same54_34.png)

### WINC Component

Enable WINC Driver in the project:
* In the Available Components, go to Wireless
* Select **Driver -> WINC**

    ![](images/same54_35.png)

* Drag and drop it in the Project Graph.

    ![](images/same54_36.png)

* Connect DRV_SPI interface of SPI interface 0 and WINC component

    ![](images/same54_37.png)

User has the option to select between WINC1500 and WINC3400 using the WINC Device configuration option.<br>

Enable Interrupt for WINC:
* In the configuration options for WINC, expand Interrupt Source
* Select EIC channel 7

    ![](images/same54_38.png)

**WINC3400 BLE:**<br>

User can enable BLE option in WINC3400 as shown below.

![](images/winc3400_1.png)


### MHC PIN Configuration

This section summarizes the pin configuration requirement for MHC pin configuration component.

In MHC, user can do pin configuration with the help of below steps
* Go to Tools in menu bar
* Select Pin Configuration

    ![](images/same54_39.png)

The following window appears

![](images/samd21_40.png)

The pin can be configured as shown below.

* RESETN pin configuration:<br>
    For WINC1500,
    * Go to PA06 pin column
    * Change the function to GPIO
    * Name should be changed as “WDRV_WINC_RESETN”

        ![](images/samd21_41.png)
    
    For WINC3400,<br>
    * Go to PB05 pin column
    * Change the function to GPIO
    * Name should be changed as “WDRV_WINC_RESETN”

        ![](images/winc3400_2.png)

* Interrupt pin configuration:<br>
    For both WINC1500 and WINC3400,
    * Go to PB07 pin column
    * Select the function as EIC_EXTINT7

        ![](images/same54_42.png)

* Chip enable pin configuration:<br>
For both WINC1500 and WINC3400,<br>
    * Go to PA27 of pin column
    * Change the function to GPIO
    * Name should be changed as “WDRV_WINC_CHIP_EN”

        ![](images/same54_43.png)

* BLE pin configuration:<br>
This configuration only applicable for WINC3400,
* Go to PA04 pin column
* Change the function to SERCOM0_PAD0
* Go to PA05 pin column
* Change the function to SERCOM0_PAD1
* Go to PA06 pin column
* Change the function to SERCOM0_PAD2
* Go to PA07 pin column
* Change the function to SERCOM0_PAD3

    ![](images/winc3400_3.png)

* SERCOM2 (COM Port) and SERCOM4 (SPI) pin configuration:<br>
    For both WINC1500 and WINC3400,
    * Go to PB24 pin column
    * Change the function to SERCOM2_PAD1
    * Go to PB25 pin column
    * Change the function to SERCOM2_PAD0
    * Go to PB26 pin column
    * Change the function to SERCOM4_PAD1
    * Go to PB27 pin column
    * Change the function to SERCOM4_PAD0
    * Go to PB28 pin column
    * Change the function to SERCOM4_PAD2
    * Go to PB29 pin column
    * Change the function to SERCOM4_PAD3

        ![](images/same54_44.png)


### Save and generate code

To save the modifications
* Click Save Click Generate Code

    ![](images/same54_46.png)

* In the next window, click Generate

    ![](images/same54_47.png)


### Application Code

With above component and pin configuration in MHC, user has required peripheral libraries and drivers for application development. User can follow the API guidelines to develop the application or follow the below step to create simple application for getting started.
* Go to the path {local system path}\wireless_apps_winc1500\apps\{User project name}\firmware\src.
    1. app.c
    2. app.h
    3. example.c
* Replace the following files with the files available in the AP scan example project
{local system path}\wireless_apps_winc1500\apps\ap_scan\firmware\src
* As example.c file does not come with default project, create a new file called example.c under Source Files
* Right click on Source Files
* Select Add Existing Item
* Go to {local system path}\wireless_apps_winc1500\apps\{User project name}\firmware\src
* Select example.c
* In the file example.c, user can change the Home AP credentials.

    ![](images/samd21_50.png)



### Build and program the device

To compile the project
* Right click on the project
* Select Clean and Build

    ![](images/same54_51.png)

After successful build make sure SAME54 XPRO is connected with local system.
* Right click again on the project
* Select Make and Program Device.

    ![](images/same54_52.png)


### Output

Expected output

![](images/samd21_53.png)

**Note:**<br>
If the user wants to create the project using the FrreRTOS, then follow the below mentioned steps.

To add FreeRTOS component
* Select FreeRTOS from Thrid party Libraries -> RTOS -> FreeRTOS

    ![](images/samd21_54.png)

* Drag and drop it in the Project Graph

    ![](images/samd21_55.png)

* In the configuration options of FreeRTOS, change the **Total heap size** to 10000.

    ![](images/samd21_56.png)

