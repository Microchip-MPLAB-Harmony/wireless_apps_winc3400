# **Create your first WINC3400 Bypass mode example using Harmony TCP/IP stack**

## **Overview**

This tutorial is a getting-started guide to demonstrate how to create a WINC3400 Bypass \(Ethernet\) mode example using MPLAB® Harmony v3 TCP/IP stack.

This tutorial implements a simple STA Client application on a microcontroller development board. This will guide you through the steps required to create a new TCP/IP application using MPLAB® Harmony 3 modules.

## **Software Details**

This tutorial is tested with following tool versions.

-   [MPLAB® X IDE v5.40](https://www.microchip.com/mplab/mplab-x-ide)

-   [MPLAB® XC32/32++ C Compiler v2.40](https://www.microchip.com/mplab/compilers)

-   [MPLAB® Harmony Configurator Plugin \(MHC\) v3.6.0](https://www.microchip.com/mplab/mplab-harmony)

-   [MPLAB® Harmony v3 Software Framework](https://www.microchip.com/mplab/mplab-harmony)


**Note** : Harmony 3 comes in modular format where user can choose which modules to work with. In order to create WINC1500 bypass mode example, following modules are essential.

Harmony Content Manager tool can be used to download/clone the repositories from Github.

-   bsp v3.9.0

-   core v3.9.2

-   csp v3.9.1

-   dev\_packs v3.9.0

-   mhc v3.8.0

-   net v3.7.2

-   wireless\_wifi v3.5.1

-   wireless\_apps\_winc3400 v3.4.1


## **Hardware Setup**

The getting-started guide demonstrates the creation of a TCP/IP demo on the **SAM E54 Xplained Pro** board with the **ATWINC1500 XPRO board**. These steps can be applied for other supported development boards applying the device/board specific configuration changes. The microcontroller should be supported by NET and Wireless modules within H3. At this point, SAM E54 is the only device supported by both modules. New device support is constantly added to modules. Check the individual module release notes for more details about device support.

-   [SAME54 Xplained PRO](https://www.microchip.com/developmenttools/ProductDetails/ATSAME54-XPRO)

-   [ATWINC3400 XPRO](https://www.microchip.com/DevelopmentTools/ProductDetails/ATWINC3400-XPRO)


The SAME54 Xplained PRO contains a built-in programmer-debugger tool called Embedded Debugger \(EDBG\) which is used in this tutorial.

-   Embedded Debugger \([EDBG](http://ww1.microchip.com/downloads/en/devicedoc/atmel-42096-microcontrollers-embedded-debugger_user-guide.pdf)\).


Following image shows the hardware setup.

![samd21_57](GUID-E5C92C39-942A-4E54-8B09-AC0DBED18E23-low.png)

## **Creating a new Harmony project**

Follow the steps to create a basic Harmony project. The assumption is that H3 modules are cloned at **"C:\\microchip\\harmony\\v3"**

1.  Open the **MPLAB® X IDE**.

2.  Create a New Project by selecting **File \> New Project**.

3.  In the New Project window select **32-Bit MPLAB® Harmony 3 Project** and click **Next**.

    ![new_project_choose_project](GUID-7A44FF9E-2597-436F-B68B-06FDF3C172CF-low.png)

    **Note:** The MPLAB® Harmony 3 Project will not be displayed if the MPLAB® Harmony 3 Configurator plug-in is not installed. It has to be installed before continuing with the next steps.

4.  In the **Framework Path**, enter the path of the folder to which the MPLAB® Harmony 3 packages are downloaded.

    ![new_project_manage_framework](GUID-8ABAEC99-FCDC-42A4-B16A-8430AEC168F6-low.png)

5.  In the Project Setting dialog window, fill in or select the information needed as follows:

    -   **Location**: First, create a "winc\_bypass\_getting\_started" folder in the location of your choice \(for example, create the application project inside the 'C:\\microchip\\harmony\\v3\\wireless\_apps\_winc3400\\apps' folder\). Then enter the path in this field.

    -   **Folder**: Project Folder name. For example, **sam\_e54\_xpro\_winc3400**.

    -   **Name**: Project Name i.e. **winc\_bypass\_getting\_started\_sam\_e54\_xpro\_winc3400**.

    -   **Path**: Selecting the above fields auto populates the **Path**.

        ![winc3400_project_location](GUID-427AD757-7357-45E0-A904-0161617A6840-low.png)

    -   Click **Next**.

6.  In the Configuration Settings dialog window, fill in or select the information needed as follows:

    -   **Name**: Configuration Name. For example, **sam\_e54\_xpro\_winc3400**.

    -   **Target Device**: Use the below table to chose the target device part number based on the demo board that you are using. For this example: SAM E54 Xplained Pro uses **ATSAME54P20A**.

    -   The **Device Filter** textbox helps narrow down list of available devices as shown.

        ![winc3400_project_config](GUID-21999A51-8AFF-4945-8DDB-C69FB3DCC4F8-low.png)

    -   Click **Finish**.

7.  First time when you create a Harmony 3 project, "Window Manager Selection Dialog" appears. The user can select "Standalone" or "Native" depending upon the preference. "Standalone" opens the MHC in a separate window. "Native" opens MHC as a window within MPLAB® X IDE.

    ![mhc3_window_manager_selection](GUID-413A3028-F97D-429B-B079-245902CDA434-low.png)

8.  If the above dialog window doesn't appear then MHC can be launched by selecting MPLAB® Harmony 3 Configurator under **Tools -\> Embedded -\> MPLAB® Harmony 3 Configurator**.

    ![project_start_mhc](GUID-36D8EEEE-DD9C-4EFF-B7FF-55E12161A2E1-low.png)

9.  In the MPLAB® Harmony Launcher window, leave the launch path as default option i.e. **MPLAB® Harmony Project Path** but make sure it is correctly pointed to desired H3 cloned directory and click **Launch**.

    ![winc3400_mhc_launch_1](GUID-20848E32-6A91-4297-A970-D5895B68DB1A-low.png)

10. In the **Configuration Database Setup** window, leave the DFP and CMSIS paths as default and click **Launch**

    ![winc3400_mhc_launch_2](GUID-18AA1D0C-BC11-420D-B0B4-416583D438A6-low.png)

11. MHC window will open now. The default standalone Harmony configurator will be as shown below.

    Different parts of configurator are:

    -   **Available Components**

    -   **Active Components**

    -   **Project Graph**

    -   **Configuration Options**

    -   **Console Window**

    ![winc3400_project_graph](GUID-B24ACEF2-A41D-4682-B7CE-AC4DF4022F12-low.png)

12. Depending upon the application needs, the necessary components can be added from the **Available Components**.

    Go to **Available Components -\> Board Support Packages \(BSPs\)** and double click on the Board support package for the target board. Below example shows the BSP for SAME54 Xplained Ultra board.

    ![winc3400_bsp](GUID-B16DFF59-4D53-4021-9CE3-3DF60C8F7FDA-low.png)

    After adding BSP, the Project Graph will look as below:

    ![winc3400_bsp_active](GUID-C25FE373-2641-49F1-9F1D-FFF4FE581C30-low.png)

    Basic components needed for creating a project will be available in project graph by default. The next step would be to configure the components based on the application needs.


## **Add TCP/IP Components**

The **TCP/IP** components can be added from the **Available Components**. Go to **Available Components -\> Libraries -\> TCPIP**

The TCP/IP components are categorized into 5 different groups and a configurator is available for each group.

These configurators are:

-   **TCP/IP Application Layer Configurator**

-   **TCP/IP Transport Layer Configurator**

-   **TCP/IP Network Layer Configurator**

-   **TCP/IP Driver Layer Configurator**

-   **TCP/IP Basic Configurator**


![mhc_steps_tcpip_avlbl_comp](GUID-CDC66CE9-6A75-470B-902A-FC83DEB3ACD2-low.png)

**Note:** It is recommended to add the TCP/IP components using these configurators.

When the components are added using configurators, the dependent modules will be auto-activated.

## **Application Layer Configurator**

1.  Under **Available Components**, Select the **TCP/IP Application Layer Configurator** and double click. This step will add the **TCP/IP Application Layer Configurator** inside the **APPLICATION LAYER** group.

    ![winc3400_tcp_ip_application](GUID-E2548C05-0BA4-43A0-8AD0-112B9882AAF3-low.png)

2.  This step also creates a hierarchy of groups as **Root-\>TCP/IP STACK-\>APPLICATION LAYER**. Verify the hierarchy by going **View:** dropdown and check out different layers.

    ![mhc_steps_tcpip_view_dropdown](GUID-0E09A60B-8544-452D-850F-ECE0928448E3-low.png)

3.  If you changed the view, come back to **APPLICATION LAYER** view by using **View:** dropdown.

4.  Select the **TCP/IP Application Layer Configurator**. See the configurations options on right hand side.

    ![mhc_steps_tcpip_app_configurator_show](GUID-ACA52A33-F98F-48E8-B8BD-706DB300241C-low.png)

    The different application protocols supported in the Harmony TCP/IP stack are listed.

    Start selecting the required TCP/IP application layer protocols from the **Configuration Options** on right hand side.

5.  For the Getting Started demo, select the **DHCP CLIENT**. This step will auto-activate all the dependent components.

6.  Click **Yes** to add the **Harmony Core** component.

    ![mhc_steps_tcpip_app_configurator_dhcpc_core](GUID-7E42C6DA-26A5-401F-8176-A8A2048DE32B-low.png)

7.  Click **No** to for the FreeRTOS auto-activation as this demo does not need the FreeRTOS.

    ![mhc_steps_tcpip_app_configurator_rtos](GUID-03DA3D35-1914-48CD-A1BE-48336F2AFC8B-low.png)

8.  Click **Yes** to add the **TIME** \(sys\_time\) component.

    ![mhc_steps_tcpip_app_configurator_time](GUID-BE923548-9C16-4696-8DCC-73EE5559BADC-low.png)

9.  Click **Yes** to add the **CONSOLE** \(sys\_console\) component.

    ![mhc_steps_tcpip_app_configurator_console](GUID-6D1FC7F2-FE5F-493B-9449-FD4508D7709B-low.png)

10. Click **Yes** to connect the **CONSOLE** component with **TCP/IP CORE**.

    ![mhc_steps_tcpip_app_configurator_console_autoconn](GUID-F0E87CD4-895F-404A-9349-462718D7D8E1-low.png)

11. Click **Yes** to add the **DEBUG** \(sys\_debug\) component.

    ![mhc_steps_tcpip_app_configurator_debug](GUID-A97EDA1E-A8E9-430D-AED8-CE2D2BD851B2-low.png)

12. Click **Yes** to connect the **CONSOLE** component with **TCP/IP CORE**.

    ![mhc_steps_tcpip_app_configurator_debug_autoconn](GUID-87088E1F-6C6C-42C2-8B14-0D974B3B40B3-low.png)

13. Click **Yes** to add the **IPv4** component in TCP/IP Network Layer.

    ![mhc_steps_tcpip_app_configurator_ipv4](GUID-443BBCC2-5D4F-4D2B-82DC-B00E9F0D3864-low.png)

14. Click **Yes** to add the **ARP** component in TCP/IP Network Layer.

    ![mhc_steps_tcpip_app_configurator_arp](GUID-C9F29696-8DAA-447B-A020-B08B022A920B-low.png)

15. Click **Yes** to add the **UDP** component in TCP/IP Transport Layer.

    ![mhc_steps_tcpip_app_configurator_udp](GUID-84769EEC-66B4-4C3B-87DA-4944410B25A8-low.png)

    After the auto-activation of dependent components, the **DHCP CLIENT** component is added to Project Graph

    ![mhc_steps_tcpip_app_configurator_dhcpc_done](GUID-CB93AE49-5D04-4BAC-8CD5-A7C842E097BC-low.png)

16. Add the **DNS CLIENT** to **APPLICATION LAYER**

    ![mhc_steps_tcpip_app_configurator_dnsc](GUID-AD8DF68E-2825-4BCC-B00D-F32641D1223A-low.png)


## **Transport Layer Configurator**

1.  Click on **View:** dropdown and go to the **TRANSPORT LAYER**.

    ![mhc_steps_tcpip_view_dropdown_app_to_trans](GUID-6360A0EB-535A-49D8-87AD-3171DEA516FA-low.png)

2.  Select the **TCP/IP Transport Layer Configurator**.

    ![mhc_steps_tcpip_trans_configurator](GUID-3B5B05A3-AFCC-4B57-9A4B-46642CB505DF-low.png)

    UDP has been auto-activated while adding the Application Layer components.

3.  Add the **TCP** protocol support for this demo.

    ![mhc_steps_tcpip_trans_configurator_tcp](GUID-45B5F46C-84F4-4C81-8185-CDFE90247EC3-low.png)

4.  Click **Yes** to add the **TCP** component in the TCP/IP Transport Layer

    ![mhc_steps_tcpip_trans_configurator_tcp_done](GUID-5B391773-8500-45E3-9171-5335B37E7F6D-low.png)


## **Network Layer Configurator**

1.  Click on **View:** dropdown and go to the **NETWORK LAYER**.

    ![mhc_steps_tcpip_view_dropdown_trans_to_netw](GUID-A574E3B0-808A-4EDB-B666-A7685657A0D2-low.png)

2.  Select the **TCP/IP Network Layer Configurator**.

    ![mhc_steps_tcpip_network_configurator](GUID-44C54065-983E-4145-A758-03EA8EBC2A08-low.png)

3.  Add the **ICMPv4** protocol support for this demo.

    ![mhc_steps_tcpip_network_icmp](GUID-4E1FCAA2-5478-4214-9CD3-D537113B45D2-low.png)

4.  Click **Yes** to add the **ICMPv4** component in the TCP/IP Network Layer

    ![mhc_steps_tcpip_network_icmp_done](GUID-02C893A1-1E03-41D1-BBDA-D93AE720798A-low.png)

5.  Select **ICMPv4** component in project graph to show its configuration settings in Configuration Options window. Enable checkbox for **Use ICMPv4 Client**. We need this to be able to ping other devices.

    ![mhc_steps_tcpip_network_icmpc_enable](GUID-9E343ED4-9B32-430F-A09E-DCFFEA8BA188-low.png)


## **Driver Layer Configurator**

1.  Click on **View:** dropdown and go to the **DRIVER LAYER**.

    ![mhc_steps_tcpip_view_dropdown_netw_to_drv](GUID-C282A014-0351-4669-99EB-9FF5056D8156-low.png)

2.  Select the **TCP/IP Driver Layer Configurator** and enable **WINC** module checkbox. Click **Yes** to add the **WINC** component in the TCP/IP Driver Layer

    ![mhc_steps_tcpip_drv_layer_winc](GUID-B6E1D863-3A87-43B4-A248-0D674E3D509D-low.png)

3.  Click **Yes** to connect the **WINC** component with the **NETCONFIG**.

    ![mhc_steps_tcpip_drv_winc_mac_depndnc](GUID-71570CD9-11E7-45B8-A38D-44AD7E68FC04-low.png)

4.  **WINC** component is added in the TCP/IP Driver Layer.

    ![mhc_steps_tcpip_drv_winc_added](GUID-CA91FC1C-38AC-422F-BBDB-8EE9E851FEA4-low.png)


## **Basic Configuration**

1.  Click on **View:** dropdown and go to the **Basic Configuration** layer.

    ![mhc_steps_tcpip_view_dropdown_drv_to_basic](GUID-273C7BF9-B59F-43B5-B620-E7243FC5C8FD-low.png)

2.  This layer contains TCP/IP stack's core configuration,interface selection, heap management, MAC configuration, etc. **Basic STACK Configuration** and **Network Configuration** are already auto-activated, during previous steps.

    ![mhc_steps_tcpip_basic_configurator](GUID-C9CEA5F6-FD24-4102-BF74-BB9BF59D93A4-low.png)

3.  Select the **TCP/IP Basic Configurator** and enable **TCPIP CMD**

    ![mhc_steps_tcpip_basic_cmd](GUID-E6B2C206-1670-43F0-9096-143B27C1CBC6-low.png)

4.  Click **Yes** to connect the **CMD** component with the **SYS Console**.

    ![mhc_steps_tcpip_basic_cmd_depndncy](GUID-64ADC654-48EF-4F69-B7D9-30902E757F43-low.png)

5.  Command module is added to the **Basic Configuration** layer.

    ![mhc_steps_tcpip_basic_cmd_added](GUID-44344C2E-D5D4-4AED-A025-4314ADFAB66F-low.png)


## **Satisfying Module Dependencies**

The project needs few more Harmony components. In this section, we will add and configure the required components.

1.  Click on **View:** dropdown and go to the **Root** layer.

    ![mhc_steps_tcpip_view_dropdown_basic_to_root](GUID-58B27832-A10C-4C34-9C0C-624396756832-low.png)

    The **Root** layer will be as shown below. The **red diamond-shaped** buttons are unsatisfied mandatory dependencies. the connections might look messy at first. Feel free to move around some boxes so that project graph looks pretty.

    ![mhc_steps_tcpip_root_1](GUID-7006D35D-B4F8-41AB-84BB-3B6FDE89C156-low.png)


-   **Note:** There are two ways to satisfy dependencies. You can either **right-click** on red diamonds and select available satisfiers **OR** you can manually add components from Avilable Components window and **manually** connect diamonds. Both ways are shown here.


### **Satisfy Timer dependency:**

1.  Right click on red diamond for **TIME** module. From the list of Satisfiers, select **TC3**.

    ![mhc_steps_project_tcpip_root_tc](GUID-EA9AF278-82AA-479D-ADCC-2803A8835FA7-low.png)

2.  Timer peripheral instance **TC3** will be added to **Root** layer and connected to the **TIMER** module.

    ![mhc_steps_tcpip_root_tc_done](GUID-E27E4F89-0C67-4830-8C12-1AC21B119010-low.png)


### **Satisfy Console dependency:**

1.  From **Available Components \> Peripherals \> SERCOM \>**, double-click on **SERCOM2** to add it to current layer.

    ![mhc_steps_avilable_plib_sercom](GUID-F4E110E4-C58C-41EF-97A3-36E04AEAE32C-low.png)

2.  **SERCOM2** is added to the **Root** layer.

    ![mhc_steps_tcpip_root_sercom_added](GUID-7455B416-3164-4F2C-A89C-D249A229C8DB-low.png)

3.  To satisy Console UART dependency, **manually connect UART diamond from SERCOM2 with the UART diamond of CONSOLE module**.

    ![mhc_steps_tcpip_root_console_uart_connection](GUID-AFC095DD-840B-401D-BC74-91B38D3CB964-low.png)

4.  Select **SERCOM2** in the Project Graph. In the Configuration Options of **SERCOM2**,

    -   Set the **TX Ring Buffer Size** to **1024**

    -   Set the **Receive Pinout** to **PAD**.

    ![mhc_steps_tcpip_root_sercom_recv_pad](GUID-7FF93B56-5921-4957-BD5A-ABAC03DE978F-low.png)


### **Satisfy TCP/IP Stack's \(i.e. WINC's\) SPI dependency:**

1.  Right click on **DRV\_SPI** red diamond of **TCP/IP STACK** module and select **SPI** as satisfier.

    ![mhc_steps_tcpip_root_spi_drv](GUID-E7DF1B2A-5726-4269-ADF8-66A0213C4DB2-low.png)

2.  Right click on red diamond of SPI driver module and select **SERCOM4**.

    ![mhc_steps_tcpip_root_drv_spi_plib](GUID-9FE217C1-88DC-4E56-9B67-45A2E88176C2-low.png)

3.  Select **SERCOM4** in the Project Graph. In the Configuration Options of **SERCOM4**,

    -   Set the **Data IN pad** to **PAD**

    -   Select **Enable SPI Master Hardware Select** checkbox.

    ![mhc_steps_tcpip_root_sercom_spi_settings](GUID-B283698F-F20C-456E-82E8-E63FDA8E7DE8-low.png)


### **Satisfy Transport Layer LIB\_CRYPTO Dependency:**

1.  Click on **View**: dropdown and go to the **Tranport layer**.

    ![winc3400_transport_layer](GUID-5D7FAE8B-7646-4F4E-8021-46C69F5BD03C-low.png)

2.  Right click on **LIB\_CRYPTO** of **TCP** and select **Cryptographic Library** from **Available Satisfiers**

    ![winc3400_transport_layer_1](GUID-E69B7943-9C45-4F12-8BCB-C310001372DB-low.png)

3.  Right click on **LIB\_WOLFCRYPT** of **Cryptographic Library** and select **wolfCrypt Library** from the list of Satisfiers.

    ![winc3400_transport_layer_2](GUID-C04DC531-D6C6-4563-BD99-82BDC58047D4-low.png)

4.  The project graph will become:

    ![winc3400_transport_layer_3](GUID-AD1E81D9-154E-48C5-AFB4-61FB6A26FAF2-low.png)


### **Satisfy WINC's External Interrupt dependency:**

1.  From **Available Components \> Peripherals \> EIC \>**, double-click on **EIC** to add it to current Root layer.

    ![mhc_steps_avilable_plib_eic](GUID-0EBA306B-31AA-4607-B553-8037732CE9FE-low.png)

2.  Select **EIC** in the Project Graph. In the Configuration Options of **EIC**,

    -   Select **Enable EIC channel 7**.

    -   Select **Enable Interrupt**

    -   Set the Edge selection to **Falling edge detection**.

    ![mhc_steps_tcpip_root_eic_conf](GUID-08A32197-3002-4CE3-BB28-39E5AC550ABD-low.png)


All necessary dependencies are care of.

## **Project Heap Configuration**

1.  Select the **System** in the Project Graph. In Configuration Options, set the **Heap Size \(bytes\)** to **96960**.

    ![mhc_steps_system_heap](GUID-9EFA3C64-06C6-4A06-9448-3CFEE11A0A99-low.png)


## **WINC Driver Configuration**

1.  Click on **View:** dropdown and go to the **DRIVER LAYER**.

    ![mhc_steps_tcpip_view_dropdown_root_to_drv](GUID-E2219A32-41DD-49D9-A5ED-2B77BFAA591A-low.png)

2.  Select **WINC** module in project graph. In the Configuration Options window, select the Interrupt Source for WINC as recently enabled **EIC Channel 7**.

    ![mhc_steps_tcpip_drv_winc_conf_eic](GUID-D57B39E1-51D9-4AD2-8430-0F0C7BADCD33-low.png)


## **Pin Configuration**

The I/O pins on the device can have alternate functions other than the general purpose I/O function. Here, we will configure the functionality of the I/O pins required for this demo.

1.  Open **MHC -\> Tools -\> Pin Configuration**.

    ![mhc_steps_tcpip_pin_config](GUID-6E310B41-E2A1-4F4C-A2B1-24745B5E2591-low.png)

2.  Configure the pins for **EXT\_INT7, SERCOM2, SERCOM4 and 2 GPIO** as shown below. Notice the GPIO pins must have **Custom Name** as shown in the figure.

    ![winc3400_reset_pin](GUID-84AD5C6E-5692-4789-B19D-8EFF1E1EC048-low.png)

    ![mhc_steps_tcpip_pin_config_2](GUID-9F5FE955-DFC7-48CA-9279-3861609ACAD7-low.png)


## **Code Generation**

Once Harmony components are added using MHC to the Project Graph, it's time to generate the source files based on the configurations.

1.  Click Save button and Generate the code by clicking the **Generate Code** button \(marked in red\).

    ![mhc_steps_tcpip_generate_code](GUID-7028DF3B-4028-4F95-9293-4A72A2E33FB5-low.png)

2.  Select the **Merge Strategy** as **USER ALL**. Refer to the MHC documentation for different merge strategy options.

    ![mhc_steps_tcpip_generate_code_merg_strat](GUID-1C4B94EE-8AB8-4267-8B8B-0D9971E0E964-low.png)

3.  Click the **Generate** button to start the code generation.

    ![mhc_steps_tcpip_generate_code_progress](GUID-C5031A80-AE29-4849-B233-D8FE515898C6-low.png)


## **Application Coding**

Now, you have the MPLAB® Harmony components configured for a TCP/IP application. The Getting-Started demo implements a simple Wi-Fi STA application. This application is written using the APIs provided by the MPLAB® Harmony TCP/IP Stack.

There is already a STA demo implemented at **D:\\MH3\\wireless\_apps\_winc3400\\apps\\wifi\_winc\_sta\_bypass**. Let's make use of those source files for the **winc\_bypass\_getting\_started** demo.

1.  Copy the application files \(i.e. **app.c**, **app.h**\) from **D:\\MH3\\wireless\_apps\_winc3400\\apps\\wifi\_winc\_sta\_bypass\\firmware\\src**.

2.  Paste the application files at our current project's location. **D:\\MH3\\wireless\_apps\_winc3400\\apps\\winc\_bypass\_getting\_started\\firmware\\src**.

    ![winc3400_copy_files](GUID-86977541-0C3E-4C48-A180-35C5E6BD2E44-low.png)

3.  In MPLAB® X IDE project, open the **app.c** file that has been added to project and change the access point parameters as shown in the picture below.

    ![winc3400_homeap](GUID-63D4BFAB-D745-4A12-ABB9-490A99D59FE1-low.png)


## **Build the Application**

1.  Open the project **Properties** by Right Clicking on the project name \(winc\_bypass\_getting\_started\). Ensure that the **XC32** Compiler Tool-chain and **SAME54 EDBG** hardware tool is selected. Press **OK**.

    ![winc3400_project_properties](GUID-7AE08418-6B5B-458D-BCA0-F5959F1514AC-low.png)

2.  Build the application by clicking on the **Build Main Project**.

    ![project_build](GUID-5B0CAE06-45B6-4099-8C41-2F63ED340A15-low.png)

3.  Verify the build results. Make sure that the build is successful.

    ![project_build_result](GUID-192B5C8B-91CC-46B1-AE0E-3A70AC6695B2-low.png)


## **Program the Application**

Now, the project is ready to be programmed on the hardware board. Refer to the hardware user-guide to see the different programming options supported.

The SAME54 Xplained board can be programmed using the on-board debugger **EDBG**.

1.  Connect a micro-USB cable from computer to the **DEBUG USB** port on the SAM E54 Xplained Ultra board.

2.  Program the application by clicking on the **Make and Program Device Main Project**.

    ![project_program](GUID-6CB42059-40BA-494F-B8E4-FCB0F7A5B711-low.png)

3.  Make sure that the programming is successful.


## **Test the Application**

The testing of the application is done using different console commands.

There will be a virtual COM port enumerated when a micro-USB cable from the computer is connected to the **DEBUG USB** port on SAM E54 Xplained Ultra board.

1.  Open a terminal application \(eg: TeraTerm\) and configure the baud rate for **115200**.

    ![open_teraterm](GUID-83C37950-2B0E-4C96-B805-66905A489E15-low.png)

2.  Press the **Reset** button on the SAM E54 Xplained Ultra board.

3.  The following messages will be visible on the terminal window.

    ![run_teraterm_outout_1](GUID-7FE4A27D-8D03-461F-AF04-520459AF4DD2-low.png)

4.  Type **ping <PC's IP address\>** in the terminal window and press **Enter** to see responses.

    ![run_teraterm_ping](GUID-D17929EB-4EB4-4B76-8495-CE5CC01A819A-low.png)

5.  You can also ping this board from your PC using cmd prompt as shown below.

    ![run_pc_cmd_pingy](GUID-B1B9E430-B2BA-4A62-A232-7CE5AF7A90CB-low.png)

6.  Currently, WINC driver is configured not to display any logs. You can change this setting in MHC by going to **DRIVER LAYER** and modifying the WINC configuration as shown below.

    ![run_mhc_winc_change_log_conf](GUID-80EB8047-3FFC-4F7A-925F-F036854DE6C9-low.png)

7.  After re-generating and re-programming with logging turned on, you will see following output in tera term console.

    ![run_teraterm_winc_log](GUID-0940D5B1-9189-4D3C-91ED-F0E76E766F3C-low.png)


You have successfully created and tested your first WINC3400 Bypass mode Application.

## **References**

1.  [TCP/IP Stack Library Help](https://microchip-mplab-harmony.github.io/net/frames.html)


