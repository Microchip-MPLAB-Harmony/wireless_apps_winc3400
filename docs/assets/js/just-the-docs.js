var myVariable = `
{"0": {
    "doc": "Create WINC Project - Getting Started",
    "title": "Create WINC Project - Getting Started",
    "content": " ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/create_winc_project_from_scratch.html",
    "relUrl": "/apps/getting_started/create_winc_project_from_scratch.html"
  },"1": {
    "doc": "Create WINC Project - Getting Started",
    "title": "Download wireless repository from Github",
    "content": "After the installation, open the MPLAB IDE and launch H3 content manager from the IDE . Please provide the framework path with the local system path. This displays a new window as shown below. Using this window, user can download either all the packages or only the wireless packages with its required dependencies. To download the wireless packages and its dependencies: . | Scroll down and select wireless_wifi, wireless_apps_winc1500 and wireless_apps_winc3400. | Click Download Selected | . It requests permission to download its dependencies. Click OK . In the License Window . | Select Accept All License | Click Close | . Go to the local system path and check if the following packages are downloaded correctly . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/create_winc_project_from_scratch.html#download-wireless-repository-from-github",
    "relUrl": "/apps/getting_started/create_winc_project_from_scratch.html#download-wireless-repository-from-github"
  },"2": {
    "doc": "Create WINC Project - Getting Started",
    "title": "Pin mapping between host and WINC",
    "content": "This section explains how to map pins between WINC1500/WINC3400 device and host to establish connection and exchange data. Totally 7/11 pins are involved in pin mapping (except VCC and GND) and they are. | SPI (SS, CLOCK, MOSI and MISO) | Reset | Chip Enable | Interrupt | UART only applicable for WINC3400 BLE (Tx, Rx, CTS and RTS) | . SAME54 and SAMD21 is used as example host throughout this document for both WINC1500 and WINC3400. SAME54 / SAMD21 XPRO board is used as the host development board and WINC1500 XPRO / WINC3400 XPRO is used as development board. Host and the WINC device are connected through extension headers. In this document, Extension 1 of SAME54 / SAMD21 host is used to connect with WINC device. The one to one pin mapping can be performed between SAME54 / SAMD21 XPRO extension header and WINC XPRO extension header by referring the following sections of the document. Table 4-1 section under 4.1.1 of WINC1500 Xplained Pro User’s Guide. Table 4-1 section under 4.1.1 of WINC3400 Xplained Pro User’s Guide Table 5-1 section under 5.2.1 of SAM E54 Xplained Pro User’s Guide Table 4-1 section under 4.1.1 of SAM D21 Xplained Pro User’s Guide In the same way if the user is using a different host, then he can perform one to one pin mapping by referring that host’s user guide. SPI interface . Communication between SAME54 / SAMD21 and WINC happens through SPI interface. Here, WINC acts as a slave and SAME54 / SAMD21 acts as master. The below table lists the SPI pins of WINC extension and its corresponding pins of SAME54 and SAMD21. Power up pins . Reset and Chip Enable pins are used to perform power up sequence in WINC from host. The below table lists the power up pins of WINC extension and its corresponding pins of SAME54 / SAMD21. WINC1500 Power up pins . WINC3400 Power up pins . Interrupt pin . Interrupt pin is used to send signal to host from WINC device. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/create_winc_project_from_scratch.html#pin-mapping-between-host-and-winc",
    "relUrl": "/apps/getting_started/create_winc_project_from_scratch.html#pin-mapping-between-host-and-winc"
  },"3": {
    "doc": "License",
    "title": "License",
    "content": "IMPORTANT: READ CAREFULLY . MICROCHIP IS WILLING TO LICENSE THIS INTEGRATED SOFTWARE FRAMEWORK SOFTWARE AND ACCOMPANYING DOCUMENTATION OFFERED TO YOU ONLY ON THE CONDITION THAT YOU ACCEPT ALL OF THE FOLLOWING TERMS. TO ACCEPT THE TERMS OF THIS LICENSE, CLICK “I ACCEPT” AND PROCEED WITH THE DOWNLOAD OR INSTALL. IF YOU DO NOT ACCEPT THESE LICENSE TERMS, CLICK “I DO NOT ACCEPT,” AND DO NOT DOWNLOAD OR INSTALL THIS SOFTWARE. NON-EXCLUSIVE SOFTWARE LICENSE AGREEMENT FOR MICROCHIP MPLAB HARMONY INTEGRATED SOFTWARE FRAMEWORK . This Nonexclusive Software License Agreement (“Agreement”) is between you, your heirs, agents, successors and assigns (“Licensee”) and Microchip Technology Incorporated, a Delaware corporation, with a principal place of business at 2355 W. Chandler Blvd., Chandler, AZ 85224-6199, and its subsidiary, Microchip Technology (Barbados) II Incorporated (collectively, “Microchip”) for Microchip’s MPLAB Harmony Integrated Software Framework (“Software”) and accompanying documentation (“Documentation”). The Software and Documentation are licensed under this Agreement and not sold. U.S. copyright laws and international copyright treaties, and other intellectual property laws and treaties protect the Software and Documentation. Microchip reserves all rights not expressly granted to Licensee in this Agreement. | License and Sublicense Grant. (a) Definitions. As used this Agreement, the following terms shall have the meanings defined below: . (i) \\\"Licensee Products\\\" means Licensee products that use or incorporate Microchip Products. (ii) \\\"Microchip Product\\\" means Microchip 16-bit and 32-bit microcontrollers, digital signal controllers or other Microchip semiconductor products with PIC16 and PIC18 prefix and specifically excepting the CX870 and CY920, which are not covered under this Agreement, that use or implement the Software. (iii) \\\"Object Code\\\" means the Software computer programming code provided by Microchip that is in binary form (including related documentation, if any) and error corrections, improvements and updates to such code provided by Microchip in its sole discretion, if any. (iv) \\\"Source Code\\\" means the Software computer programming code provided by Microchip that may be printed out or displayed in human readable form (including related programmer comments and documentation, if any), and error corrections, improvements, updates, modifications and derivatives of such code developed by Microchip, Licensee or Third Party. (v) \\\"Third Party\\\" means Licensee's agents, representatives, consultants, clients, customers, or contract manufacturers. (vi) \\\"Third Party Products\\\" means Third Party products that use or incorporate Microchip Products. (b) Software License Grant. Subject to the terms of this Agreement, Microchip grants strictly to Licensee a personal, worldwide, non-exclusive, non-transferable limited license to use, modify (except as limited by Section 1(f) below), copy and distribute the Software only when the Software is embedded on a Microchip Product that is integrated into Licensee Product or Third Party Product pursuant to Section 2(d) below. Any portion of the Software (including derivatives or modifications thereof) may not be: . (i) embedded on a non-Microchip microcontroller or digital signal controller; (ii) distributed (in Source Code or Object Code), except as described in Section 2(d) below. (c) Documentation License Grant. Subject to all of the terms and conditions of this Agreement, Microchip grants strictly to Licensee a perpetual, worldwide, non-exclusive license to use the Documentation in support of Licensee’s use of the Software. (d) Sublicense Grants. Subject to terms of this Agreement, Licensee may grant a limited sublicense to a Third Party to use the Software as described below only if such Third Party expressly agrees to be bound by terms of confidentiality and limited use that are no broader in scope and duration than the confidentiality and limited use terms of this Agreement: . (i) Third Party may modify Source Code for Licensee, except as limited by Section 1(f) below. (ii) Third Party may program Software into Microchip Products for Licensee. (iii) Third Party may use Software to develop and/or manufacture Licensee Product. (iv) Third Party may use Software to develop and/or manufacture Third Party Products where either: (x) the sublicensed Software contains Source Code modified or otherwise optimized by Licensee for Third Party use; or (y) the sublicensed Software is programmed into Microchip Products by Licensee on behalf of such Third Party. (v) Third Party may use the Documentation in support of Third Party's authorized use of the Software in conformance with this Section 2(d). (e) Audit. Authorized representatives of Microchip shall have the right to reasonably inspect Licensee’s premises and to audit Licensee’s records and inventory of Licensee Products, whether located on Licensee’s premises or elsewhere at any time, announced or unannounced, and in its sole and absolute discretion, in order to ensure Licensee’s adherence to the terms of this Agreement. (f) License and Sublicense Limitation. This Section 1 does not grant Licensee or any Third Party the right to modify any dotstack™ Bluetooth® stack, profile, or iAP protocol included in the Software. | Third Party Requirements. Licensee acknowledges that it is Licensee’s responsibility to comply with any third party license terms or requirements applicable to the use of such third party software, specifications, systems, or tools, including but not limited to SEGGER Microcontroller GmbH &amp; Co. KG’s rights in the emWin software and certain libraries included herein. Microchip is not responsible and will not be held responsible in any manner for Licensee’s failure to comply with such applicable terms or requirements. | Open Source Components. Notwithstanding the license grants contained herein, Licensee acknowledges that certain components of the Software may be covered by so-called “open source” software licenses (“Open Source Components”). Open Source Components means any software licenses approved as open source licenses by the Open Source Initiative or any substantially similar licenses, including any license that, as a condition of distribution, requires Microchip to provide Licensee with certain notices and/or information related to such Open Source Components, or requires that the distributor make the software available in source code format. Microchip will use commercially reasonable efforts to identify such Open Source Components in a text file or “About Box” or in a file or files referenced thereby (and will include any associated license agreement, notices, and other related information therein), or the Open Source Components will contain or be accompanied by its own license agreement. To the extent required by the licenses covering Open Source Components, the terms of such licenses will apply in lieu of the terms of this Agreement, and Microchip hereby represents and warrants that the licenses granted to such Open Source Components will be no less broad than the license granted in Section 1(b). To the extent the terms of the licenses applicable to Open Source Components prohibit any of the restrictions in this Agreement with respect to such Open Source Components, such restrictions will not apply to such Open Source Components. | Licensee’s Obligations. (a) Licensee will ensure Third Party compliance with the terms of this Agreement. (b) Licensee will not: (i) engage in unauthorized use, modification, disclosure or distribution of Software or Documentation, or its derivatives; (ii) use all or any portion of the Software, Documentation, or its derivatives except in conjunction with Microchip Products; or (iii) reverse engineer (by disassembly, decompilation or otherwise) Software or any portion thereof; or (iv) copy or reproduce all or any portion of Software, except as specifically allowed by this Agreement or expressly permitted by applicable law notwithstanding the foregoing limitations. (c) Licensee must include Microchip’s copyright, trademark and other proprietary notices in all copies of the Software, Documentation, and its derivatives. Licensee may not remove or alter any Microchip copyright or other proprietary rights notice posted in any portion of the Software or Documentation. (d) Licensee will defend, indemnify and hold Microchip and its subsidiaries harmless from and against any and all claims, costs, damages, expenses (including reasonable attorney’s fees), liabilities, and losses, including without limitation product liability claims, directly or indirectly arising from or related to: (i) the use, modification, disclosure or distribution of the Software, Documentation or any intellectual property rights related thereto; (ii) the use, sale, and distribution of Licensee Products or Third Party Products, and (iii) breach of this Agreement. THE FOREGOING STATES THE SOLE AND EXCLUSIVE LIABILITY OF THE PARTIES FOR INTELLECTUAL PROPERTY RIGHTS INFRINGEMENT. | Confidentiality. (a) Licensee agrees that the Software (including but not limited to the Source Code, Object Code and library files) and its derivatives, Documentation and underlying inventions, algorithms, know-how and ideas relating to the Software and the Documentation are proprietary information belonging to Microchip and its licensors (“Proprietary Information”). Except as expressly and unambiguously allowed herein, Licensee will hold in confidence and not use or disclose any Proprietary Information and shall similarly bind its employees and Third Party(ies) in writing. Proprietary Information shall not include information that: (i) is in or enters the public domain without breach of this Agreement and through no fault of the receiving party; (ii) the receiving party was legally in possession of prior to receiving it; (iii) the receiving party can demonstrate was developed by it independently and without use of or reference to the disclosing party’s Proprietary Information; or (iv) the receiving party receives from a third party without restriction on disclosure. If Licensee is required to disclose Proprietary Information by law, court order, or government agency, such disclosure shall not be deemed a breach of this Agreement provided that Licensee gives Microchip prompt notice of such requirement in order to allow Microchip to object or limit such disclosure, Licensee cooperates with Microchip to protect Proprietary Information, and Licensee complies with any protective order in place and discloses only the information required by process of law. (b) Licensee agrees that the provisions of this Agreement regarding unauthorized use and nondisclosure of the Software, Documentation and related Proprietary Rights are necessary to protect the legitimate business interests of Microchip and its licensors and that monetary damages alone cannot adequately compensate Microchip or its licensors if such provisions are violated. Licensee, therefore, agrees that if Microchip alleges that Licensee or Third Party has breached or violated such provision then Microchip will have the right to petition for injunctive relief, without the requirement for the posting of a bond, in addition to all other remedies at law or in equity. | Ownership of Proprietary Rights. (a) Microchip and its licensors retain all right, title and interest in and to the Software and Documentation (“Proprietary Rights”) including, but not limited to: (i) patent, copyright, trade secret and other intellectual property rights in the Software, Documentation, and underlying technology; (ii) the Software as implemented in any device or system, all hardware and software implementations of the Software technology (expressly excluding Licensee and Third Party code developed and used in conformance with this Agreement solely to interface with the Software and Licensee Products and/or Third Party Products); and (iii) all modifications and derivative works thereof (by whomever produced). Further, modifications and derivative works shall be considered works made for hire with ownership vesting in Microchip on creation. To the extent such modifications and derivatives do not qualify as a “work for hire,” Licensee hereby irrevocably transfers, assigns and conveys the exclusive copyright thereof to Microchip, free and clear of any and all liens, claims or other encumbrances, to the fullest extent permitted by law. Licensee and Third Party use of such modifications and derivatives is limited to the license rights described in Section 1 above. (b) Licensee shall have no right to sell, assign or otherwise transfer all or any portion of the Software, Documentation or any related intellectual property rights except as expressly set forth in this Agreement. | Termination of Agreement. Without prejudice to any other rights, this Agreement terminates immediately, without notice by Microchip, upon a failure by License or Third Party to comply with any provision of this Agreement. Further, Microchip may also terminate this Agreement upon reasonable belief that Licensee or Third Party have failed to comply with this Agreement. Upon termination, Licensee and Third Party will immediately stop using the Software, Documentation, and derivatives thereof, and immediately destroy all such copies, remove Software from any of Licensee’s tangible media and from systems on which the Software exists, and stop using, disclosing, copying, or reproducing Software (even as may be permitted by this Agreement). Termination of this Agreement will not affect the right of any end user or consumer to use Licensee Products or Third Party Products provided that such products were purchased prior to the termination of this Agreement. | Dangerous Applications. The Software is not fault-tolerant and is not designed, manufactured, or intended for use in hazardous environments requiring failsafe performance (“Dangerous Applications”). Dangerous Applications include the operation of nuclear facilities, aircraft navigation, aircraft communication systems, air traffic control, direct life support machines, weapons systems, or any environment or system in which the failure of the Software could lead directly or indirectly to death, personal injury, or severe physical or environmental damage. Microchip specifically disclaims (a) any express or implied warranty of fitness for use of the Software in Dangerous Applications; and (b) any and all liability for loss, damages and claims resulting from the use of the Software in Dangerous Applications. | Warranties and Disclaimers. THE SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. MICROCHIP AND ITS LICENSORS ASSUME NO RESPONSIBILITY FOR THE ACCURACY, RELIABILITY OR APPLICATION OF THE SOFTWARE OR DOCUMENTATION. MICROCHIP AND ITS LICENSORS DO NOT WARRANT THAT THE SOFTWARE WILL MEET REQUIREMENTS OF LICENSEE OR THIRD PARTY, BE UNINTERRUPTED OR ERROR-FREE. MICROCHIP AND ITS LICENSORS HAVE NO OBLIGATION TO CORRECT ANY DEFECTS IN THE SOFTWARE. LICENSEE AND THIRD PARTY ASSUME THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE AND DOCUMENTATION PROVIDED UNDER THIS AGREEMENT. | Limited Liability. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL OR EQUITABLE THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS. The aggregate and cumulative liability of Microchip and its licensors for damages hereunder will in no event exceed $1000 or the amount Licensee paid Microchip for the Software and Documentation, whichever is greater. Licensee acknowledges that the foregoing limitations are reasonable and an essential part of this Agreement. | General. (a) Governing Law, Venue and Waiver of Trial by Jury. THIS AGREEMENT SHALL BE GOVERNED BY AND CONSTRUED UNDER THE LAWS OF THE STATE OF ARIZONA AND THE UNITED STATES WITHOUT REGARD TO CONFLICTS OF LAWS PROVISIONS. Licensee agrees that any disputes arising out of or related to this Agreement, Software or Documentation shall be brought in the courts of State of Arizona. The parties agree to waive their rights to a jury trial in actions relating to this Agreement. (b) Attorneys’ Fees. If either Microchip or Licensee employs attorneys to enforce any rights arising out of or relating to this Agreement, the prevailing party shall be entitled to recover its reasonable attorneys’ fees, costs and other expenses. (c) Entire Agreement. This Agreement shall constitute the entire agreement between the parties with respect to the subject matter hereof. It shall not be modified except by a written agreement signed by an authorized representative of Microchip. (d) Severability. If any provision of this Agreement shall be held by a court of competent jurisdiction to be illegal, invalid or unenforceable, that provision shall be limited or eliminated to the minimum extent necessary so that this Agreement shall otherwise remain in full force and effect and enforceable. (e) Waiver. No waiver of any breach of any provision of this Agreement shall constitute a waiver of any prior, concurrent or subsequent breach of the same or any other provisions hereof, and no waiver shall be effective unless made in writing and signed by an authorized representative of the waiving party. (f) Export Regulation. Licensee agrees to comply with all export laws and restrictions and regulations of the Department of Commerce or other United States or foreign agency or authority. (g) Survival. The indemnities, obligations of confidentiality, and limitations on liability described herein, and any right of action for breach of this Agreement prior to termination shall survive any termination of this Agreement. (h) Assignment. Neither this Agreement nor any rights, licenses or obligations hereunder, may be assigned by Licensee without the prior written approval of Microchip except pursuant to a merger, sale of all assets of Licensee or other corporate reorganization, provided that assignee agrees in writing to be bound by the Agreement. (i) Restricted Rights. Use, duplication or disclosure by the United States Government is subject to restrictions set forth in subparagraphs (a) through (d) of the Commercial Computer-Restricted Rights clause of FAR 52.227-19 when applicable, or in subparagraph (c)(1)(ii) of the Rights in Technical Data and Computer Software clause at DFARS 252.227-7013, and in similar clauses in the NASA FAR Supplement. Contractor/manufacturer is Microchip Technology Inc., 2355 W. Chandler Blvd., Chandler, AZ 85225-6199. | . If Licensee has any questions about this Agreement, please write to Microchip Technology Inc., 2355 W. Chandler Blvd., Chandler, AZ 85224-6199 USA, ATTN: Marketing. Microchip MPLAB Harmony Integrated Software Framework. Copyright © 2015 Microchip Technology Inc. All rights reserved. License Rev. 11/2015 . Copyright © 2015 Qualcomm Atheros, Inc. All Rights Reserved. Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies. THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/mplab_harmony_license.html",
    "relUrl": "/mplab_harmony_license.html"
  },"4": {
    "doc": "AP Scan",
    "title": "AP Scan",
    "content": "This example compiles the AP Scan application which is used to scan for available BSSs and display the list. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/ap_scan/readme.html",
    "relUrl": "/apps/ap_scan/readme.html"
  },"5": {
    "doc": "AP Scan",
    "title": "Description",
    "content": "AP Scan application is used to scan for available BSSs and display the list. It sends out a scan requests and lists responses of all Access points along with their signal strength. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/ap_scan/readme.html#description",
    "relUrl": "/apps/ap_scan/readme.html#description"
  },"6": {
    "doc": "AP Scan",
    "title": "Downloading and building the application",
    "content": "To download or clone this application from Github, go to the top level of the repository . Path of the application within the repository is apps/ap_scan/firmware . To build the application, refer to the following table and open the project using its IDE. | Project Name | Description | . | sam_d21_xpro_winc3400.X | MPLABX project for SAMD21 and WINC3400 Xplained pro | . | sam_e54_xpro_winc3400.X | MPLABX project for SAME54 and WINC3400 Xplained pro | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/ap_scan/readme.html#downloading-and-building-the-application",
    "relUrl": "/apps/ap_scan/readme.html#downloading-and-building-the-application"
  },"7": {
    "doc": "AP Scan",
    "title": "Setting up SAMXXX Xplained Pro board",
    "content": ". | Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/ap_scan/readme.html#setting-up-samxxx-xplained-pro-board",
    "relUrl": "/apps/ap_scan/readme.html#setting-up-samxxx-xplained-pro-board"
  },"8": {
    "doc": "AP Scan",
    "title": "Running the Application",
    "content": ". | Open the project. | Build and program the generated code into the hardware using its IDE. | Refer “firmware update guide” and “WINC Driver Demonstrations” for information. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/ap_scan/readme.html#running-the-application",
    "relUrl": "/apps/ap_scan/readme.html#running-the-application"
  },"9": {
    "doc": "STA Bypass mode",
    "title": "WINC STA Bypass",
    "content": "This example compiles the WINC STA Bypass application. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_winc_sta_bypass/readme.html#winc-sta-bypass",
    "relUrl": "/apps/wifi_winc_sta_bypass/readme.html#winc-sta-bypass"
  },"10": {
    "doc": "STA Bypass mode",
    "title": "Description",
    "content": "This example implements a simple STA Client application on the SAM E54 Xplained Pro board with the ATWINC1500/3400 XPRO board where the WINC controller is in Bypass/Ethernet mode. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_winc_sta_bypass/readme.html#description",
    "relUrl": "/apps/wifi_winc_sta_bypass/readme.html#description"
  },"11": {
    "doc": "STA Bypass mode",
    "title": "Downloading and building the application",
    "content": "To download or clone this application from Github, go to the top level of the repository . Path of the application within the repository is apps/wifi_winc_sta_bypass/firmware . To build the application, refer to the following table and open the project using its IDE. | Project Name | Description | . | sam_e54_xpro_winc3400.X | MPLABX project for SAME54 and WINC3400 Xplained pro | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_winc_sta_bypass/readme.html#downloading-and-building-the-application",
    "relUrl": "/apps/wifi_winc_sta_bypass/readme.html#downloading-and-building-the-application"
  },"12": {
    "doc": "STA Bypass mode",
    "title": "Setting up SAME54 Xplained Pro board",
    "content": ". | Connect the ATWINCxx00 Xpro Wi-Fi board to EXT1 XPRO Header of SAME54 Xplained baord. | Connect the Debug USB port on the SAME54 Xplained Pro board to the computer using a micro USB cable | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_winc_sta_bypass/readme.html#setting-up-same54-xplained-pro-board",
    "relUrl": "/apps/wifi_winc_sta_bypass/readme.html#setting-up-same54-xplained-pro-board"
  },"13": {
    "doc": "STA Bypass mode",
    "title": "Running the Application",
    "content": ". | Open the project in MPLAB® X IDE and open the app.c file to change the access point parameters as shown in the picture below. | Build and program the generated code into the hardware using its IDE by using on-board EDBG programmer. | Open a terminal application (eg: TeraTerm) and configure the baud rate for 115200. | Press the Reset button on the SAM E54 Xplained Ultra board. | The following messages will be visible on the terminal window. | Type ping &lt;PC’s IP address&gt; in the terminal window and press Enter to see responses. | You can also ping this board from your PC using cmd prompt as shown below. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_winc_sta_bypass/readme.html#running-the-application",
    "relUrl": "/apps/wifi_winc_sta_bypass/readme.html#running-the-application"
  },"14": {
    "doc": "STA Bypass mode",
    "title": "How to create this project from scratch",
    "content": "Following Wireless Wiki tutorial shows step-by-step process to create this project from scratch . Create WINC1500 bypass mode demo from scratch . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_winc_sta_bypass/readme.html#how-to-create-this-project-from-scratch",
    "relUrl": "/apps/wifi_winc_sta_bypass/readme.html#how-to-create-this-project-from-scratch"
  },"15": {
    "doc": "STA Bypass mode",
    "title": "STA Bypass mode",
    "content": " ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_winc_sta_bypass/readme.html",
    "relUrl": "/apps/wifi_winc_sta_bypass/readme.html"
  },"16": {
    "doc": "Power Save Mode",
    "title": "Power Save Mode",
    "content": "This example compiles the Power Save Mode application which is used to demonstrate WINC’s low power mode. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/power_save_mode_example/readme.html",
    "relUrl": "/apps/power_save_mode_example/readme.html"
  },"17": {
    "doc": "Power Save Mode",
    "title": "Description",
    "content": "In this demonstration, the WINC’s power save feature is demonstrated. The Power save mode is demonstrated depending on the value configured in example_conf.h - WDRV_WINC_PS_MODE_OFF, WDRV_WINC_PS_MODE_AUTO_LOW_POWER and WDRV_WINC_PS_MODE_MANUAL. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/power_save_mode_example/readme.html#description",
    "relUrl": "/apps/power_save_mode_example/readme.html#description"
  },"18": {
    "doc": "Power Save Mode",
    "title": "Downloading and building the application",
    "content": "To download or clone this application from Github, go to the top level of the repository . Path of the application within the repository is apps/power_save_mode_example/firmware . To build the application, refer to the following table and open the project using its IDE. | Project Name | Description | . | sam_d21_xpro_winc3400.X | MPLABX project for SAMD21 and WINC3400 Xplained pro | . | sam_e54_xpro_winc3400.X | MPLABX project for SAME54 and WINC3400 Xplained pro | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/power_save_mode_example/readme.html#downloading-and-building-the-application",
    "relUrl": "/apps/power_save_mode_example/readme.html#downloading-and-building-the-application"
  },"19": {
    "doc": "Power Save Mode",
    "title": "Setting up SAMXXX Xplained Pro board",
    "content": ". | Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/power_save_mode_example/readme.html#setting-up-samxxx-xplained-pro-board",
    "relUrl": "/apps/power_save_mode_example/readme.html#setting-up-samxxx-xplained-pro-board"
  },"20": {
    "doc": "Power Save Mode",
    "title": "Running the Application",
    "content": ". | Open the project. | Build and program the generated code into the hardware using its IDE. | Refer “firmware update guide” for information. | Please note this example will not output any console messages. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/power_save_mode_example/readme.html#running-the-application",
    "relUrl": "/apps/power_save_mode_example/readme.html#running-the-application"
  },"21": {
    "doc": "TCP Client",
    "title": "TCP Client",
    "content": "The WINC example application demonstrates as a conventional, open tcp client-server communication. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/tcp_client/readme.html",
    "relUrl": "/apps/tcp_client/readme.html"
  },"22": {
    "doc": "TCP Client",
    "title": "Description",
    "content": "In this demonstration, the WINC Driver will connect to a BSS and begin a TCP client socket connection to a remote server service. This demonstration can be configured in the following ways in the source code. • The BSS to connect to. • The TCP server address and port to connect to. • The receive buffer size. • The message which should be sent as the first data once connected to the server. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/tcp_client/readme.html#description",
    "relUrl": "/apps/tcp_client/readme.html#description"
  },"23": {
    "doc": "TCP Client",
    "title": "Downloading and building the application",
    "content": "To download or clone this application from Github, go to the top level of the repository . Path of the application within the repository is apps/tcp_client/firmware . To build the application, refer to the following table and open the project using its IDE. | Project Name | Description | . | sam_d21_xpro_winc3400.X | MPLABX project for SAMD21 and WINC3400 Xplained pro | . | sam_e54_xpro_winc3400.X | MPLABX project for SAME54 and WINC3400 Xplained pro | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/tcp_client/readme.html#downloading-and-building-the-application",
    "relUrl": "/apps/tcp_client/readme.html#downloading-and-building-the-application"
  },"24": {
    "doc": "TCP Client",
    "title": "Setting up SAMXXX Xplained Pro board",
    "content": ". | Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/tcp_client/readme.html#setting-up-samxxx-xplained-pro-board",
    "relUrl": "/apps/tcp_client/readme.html#setting-up-samxxx-xplained-pro-board"
  },"25": {
    "doc": "TCP Client",
    "title": "Running the Application",
    "content": ". | Open the project. | Build and program the generated code into the hardware using its IDE. | Refer “firmware update guide” and “WINC Driver Demonstrations” for information. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/tcp_client/readme.html#running-the-application",
    "relUrl": "/apps/tcp_client/readme.html#running-the-application"
  },"26": {
    "doc": "TCP Server in SoftAP",
    "title": "TCP Server in SoftAP",
    "content": "This example compiles the TCP Server in SoftAP application which is used to demonstrate a TCP Client-Server connection. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_tcp_server_in_softap/readme.html",
    "relUrl": "/apps/wifi_tcp_server_in_softap/readme.html"
  },"27": {
    "doc": "TCP Server in SoftAP",
    "title": "Description",
    "content": "In this demonstration, the WINC Driver will advertise a SoftAP. The SoftAP connection is used to demonstrate a TCP client-server operation. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_tcp_server_in_softap/readme.html#description",
    "relUrl": "/apps/wifi_tcp_server_in_softap/readme.html#description"
  },"28": {
    "doc": "TCP Server in SoftAP",
    "title": "Downloading and building the application",
    "content": "To download or clone this application from Github, go to the top level of the repository . Path of the application within the repository is apps/wifi_tcp_server_in_softap/firmware . To build the application, refer to the following table and open the project using its IDE. | Project Name | Description | . | sam_d21_xpro_winc3400.X | MPLABX project for SAMD21 and WINC3400 Xplained pro | . | sam_e54_xpro_winc3400.X | MPLABX project for SAME54 and WINC3400 Xplained pro | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_tcp_server_in_softap/readme.html#downloading-and-building-the-application",
    "relUrl": "/apps/wifi_tcp_server_in_softap/readme.html#downloading-and-building-the-application"
  },"29": {
    "doc": "TCP Server in SoftAP",
    "title": "Setting up SAMXXX Xplained Pro board",
    "content": ". | Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_tcp_server_in_softap/readme.html#setting-up-samxxx-xplained-pro-board",
    "relUrl": "/apps/wifi_tcp_server_in_softap/readme.html#setting-up-samxxx-xplained-pro-board"
  },"30": {
    "doc": "TCP Server in SoftAP",
    "title": "Running the Application",
    "content": ". | Open the project. | Build and program the generated code into the hardware using its IDE. | Refer “firmware update guide” and “WINC Driver Demonstrations” for information. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_tcp_server_in_softap/readme.html#running-the-application",
    "relUrl": "/apps/wifi_tcp_server_in_softap/readme.html#running-the-application"
  },"31": {
    "doc": "Wi-Fi Socket Mode Demos",
    "title": "WINC3400 Example Applications",
    "content": "This example project demonstrates the WINC3400 applications of WiFi and BLE in Socket mode . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/readme.html#winc3400-example-applications",
    "relUrl": "/apps/wifi_socket_demos/readme.html#winc3400-example-applications"
  },"32": {
    "doc": "Wi-Fi Socket Mode Demos",
    "title": "Description",
    "content": "This project has both WiFi and BLE example applications. The user can configure the WiFi parameters and select the required example application through command. The user would need to use “Microchip Bluetooth Data” mobile application to run the BLE example applications. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/readme.html#description",
    "relUrl": "/apps/wifi_socket_demos/readme.html#description"
  },"33": {
    "doc": "Wi-Fi Socket Mode Demos",
    "title": "Downloading and building the application",
    "content": "To download or clone this application from Github, go to the top level of the repository . Path of the application within the repository is ,wireless_apps_winc3400/apps/wifi_socket_demos/firmware. To build the application, refer to the following table and open the project using its IDE. | Project Name | Description | . | sam_e54_xpro_winc3400.X | MPLABX project for SAME54 and WINC3400 Xplained pro | . | sam_d21_xpro_winc3400.X | MPLABX project for SAMD21 and WINC3400 Xplained pro | . | sam_e54_xpro_winc3400_freertos.X | MPLABX project for SAME54 and WINC3400 Xplained pro using FreeRTOS | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/readme.html#downloading-and-building-the-application",
    "relUrl": "/apps/wifi_socket_demos/readme.html#downloading-and-building-the-application"
  },"34": {
    "doc": "Wi-Fi Socket Mode Demos",
    "title": "Setting up SAMXXX Xplained Pro board",
    "content": ". | Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/readme.html#setting-up-samxxx-xplained-pro-board",
    "relUrl": "/apps/wifi_socket_demos/readme.html#setting-up-samxxx-xplained-pro-board"
  },"35": {
    "doc": "Wi-Fi Socket Mode Demos",
    "title": "Running the Application",
    "content": ". | Build and program the application project using its respective IDE . | Open the Terminal application (Ex.:Tera term) on the computer . | Connect to the “USB to UART” COM port and configure the serial settings as follows: . | Baud : 115200 | Data : 8 Bits | Parity : None | Stop : 1 Bit | Flow Control : None | . | Use WiFi commands to configure WiFi parameters and use application commands to select the example application. | . WiFi Commands Details . | Command | Details | Example | . | wifi help | Wi-Fi Service help command | wifi help | . | wifi set &lt;bootmode&gt; &lt;ssid_name&gt; &lt;auth_type&gt; &lt;pwd&gt; &lt;username/index&gt; | Set Wi-Fi Configuration for Station(STA) mode or Access Point (AP) mode | wifi set 2 DEMO_AP 2 12345678 | . | wifi get | Get Wi-Fi Configuration | wifi get | . |   |   |   | . Wi-Fi command parameters information . | Parameter | Sub Parameter | . | bootmode | 1- Access point(AP) mode.2- Station(STA) mode. | . | ssid_name | SSID name | . | authtype(Security type) | 1 - OPEN Mode. 2 - WPAPSK mode. 3 - WEP mode. 5 - 802.1x authentication MSCHAPV2 mode. | . | pwd(password) | Password/passphrase | . | username/index | Username if authtype is 802.1x authentication MSCHAPV2 or Key Index if the authtype is WEP. | . |   |   | . Application command parameters information . | Command | Details | Example | . | appdemo help | Application Service help command | appdemo help | . | appdemo start &lt;demo_id&gt; | Select and start an application demo | appdemo start 1 | . | appdemo get | Get the ID of currently running application demo | appdemo get | . | appdemo stop | Stop the currently running application demo | appdemo stop | . |   |   |   | . Application command parameters information . | Parameter | Sub Parameter | . | demo_ID | 1 - WiFi station mode/Access point mode demo.6 - WiFi Provisioning via BLE. 7 - OTA Demo. 8 - SSL Demo. 9 - Ping Demo. 10 - Iperf demo. 11 - SNTP demo. 12 - Serial Chat. 13 - Heart rate profile. 14 - Battery Service. 15 - Proximity Reporter. 16 - Transparent Service. 18 - MQTT Demo. 19 - Certificate Download OTA Demo. | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/readme.html#running-the-application",
    "relUrl": "/apps/wifi_socket_demos/readme.html#running-the-application"
  },"36": {
    "doc": "Wi-Fi Socket Mode Demos",
    "title": "List of Applications",
    "content": "| Application | Description | . | WiFi station mode/Access point mode demo | Demonstartes the Station Mode or Access Point(AP) mode of WINC3400 | . | WiFi Provisioning via BLE | Demonstartes the WiFi provisioning using BLE | . | OTA Demo | Demonstartes the OTA firmware upgrade of WINC3400 | . | SSL Demo | Demonstrates TCP SSL Client application | . | Ping Demo | Demonstrates the Ping test | . | Iperf Demo | Demonstrates the iperf application | . | SNTP Demo | Demonstrates how to retrieve time information from the time server | . | Custom serial Chat Demo | Demonstrates the Custom Serial Chat application using BLE | . | Heart Rate Profile Demo | Demonstrates the Heart Rate Profile application using BLE | . | Battery Service Demo | Demonstrates the Battery Service application using BLE | . | Proximity Reporter Demo | Demonstrates the Proximity Reporter application using BLE | . | Transparent Service Demo | Demonstrates the Transparent Service application using BLE | . | MQTT Demo | Demonstrates MQTT Application | . | WiFi Provisioning Demo | Demonstartes the WiFi provisioning application | . | Certificate Download OTA Demo | Demonstartes the Certificate Download OTA Demo | . |   |   | . Steps to isolate/copy individual application(s) from the demo . If the user wants to isolate an application, follow the below mentioned steps . For example, the user wants to create an SNTP demo in Socket mode. | The SNTP demo uses the WiFi functionalities to get connected with the network. So copy the files “ app_wifi.c” and “ app_wifi.h ” from the path “wireless_apps_winc3400/apps/wifi_bypass_demos/firmware/src ” or “wireless_apps_winc3400/apps/wifi_socket_demos/firmware/src” to “src” folder of the new demo project. Then add these files to the project. | Now user should copy and add the SNTP application files “app_sntp.c” and “app_sntp.h” from the path “wireless_apps_winc3400/apps/wifi_bypass_demos/firmware/src ” or “wireless_apps_winc3400/apps/wifi_socket_demos/firmware/src” to the “src folder of the new demo project. | The “app.c” and “app.h” files need to be copied by the user. These files integrate the SNTP application and WiFi functionalities. Copy and add these two files from the same “src” path to the “src” folder of the new demo project. | In “app.c”, within “APP_Initialize()” function, initialize the sntp application by calling “ APP_SntpInitialize(APPWiFiCallback)”. | In “app.c” file, make sure that, “ APP_WiFiTasks(wdrvHandle)” is getting called from the “ APP_STATE_WDRV_OPEN ” state of “ APP_Tasks() ” state machine. | In the same state machine “ APP_Tasks() ”, within the state “ APP_STATE_WDRV_APP_LOOP ” , call the sntp application state machine “APP_SntpTasks(handle)”. | Now follow the steps mentioned in the SNTP demo document to run the SNTP demo using “wifi”, “sntp” and “appdemo” commands. | . Similarly, for any application demo, take the required application files along with WiFi files and “app” files to create the demo. Steps to isolate/copy individual BLE application(s) from the demo . For BLE applications, no need to copy the WiFi files. But the user should copy the Ble_Service and Ble_Profile files from the path “wireless_apps_winc3400\\\\apps\\wifi_socket_demos\\firmware\\\\src\\ble ”. For example, the user wants to create a new project, say “Heart_rate_demo”, then . | Copy and add the ble_manager files from the path “wireless_apps_winc3400\\\\apps\\wifi_socket_demos\\firmware\\\\src\\ble\\ble_services\\ble_mgr” to the “ Heart_rate_demo\\firmware\\\\src\\ble\\ble_services\\ble_mgr” of the new project. | Copy and add the Heart rate profile files from the path “wireless_apps_winc3400\\\\apps\\wifi_socket_demos\\firmware\\\\src\\ble\\ble_profiles\\\\hr_sensor” to the “ Heart_rate_demo\\firmware\\\\src\\ble\\ble_profiles\\\\hr_sensor” of the new project. | Copy and add the Heart rate service files from the path “wireless_apps_winc3400\\\\apps\\wifi_socket_demos\\firmware\\\\src\\ble\\ble_services\\\\heart_rate” to the “ Heart_rate_demo\\firmware\\\\src\\ble\\ble_services\\\\heart_rate” of the new project. | Now copy and add the application files “app_heart_rate.c” and “app_heart_rate.h” from “wireless_apps_winc3400\\\\apps\\wifi_socket_demos\\firmware\\\\src” to the “ Heart_rate_demo\\firmware\\\\src” of the new project. | Copy and add the main application files “app.c” and “app.h” files from “wireless_apps_winc3400\\\\apps\\wifi_socket_demos\\firmware\\\\src” to the “ Heart_rate_demo\\firmware\\\\src” of the new project. | In “app.c”, within “APP_Initialize()” function, initialize the Heart Rate application by calling “ APP_BleHeartrateInitialize(APPWiFiCallback)”. | In “app.c” file, make sure that, “ APP_BleHeartrateTasks(wdrvHandle)” is getting called from the “ APP_STATE_WDRV_OPEN ” state of “ APP_Tasks() ” state machine. | Add the macro “BLE_DEVICE_ROLE=BLE_PERIPHERAL” in the project properties. | Now follow the steps mentioned in the “Heart rate demo document” to run the application using “appdemo” command. | . Similarly, for any ble application demo, take the required application files, ble_profile files, ble_service files and “app” files to create the demo. Note: . | User has to make sure the project path does not exceed windows path limit. | User should reset the device before switching the application and unpair the device from the android phone in case of switching BLE application demos. | . Back to top . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/readme.html#list-of-applications",
    "relUrl": "/apps/wifi_socket_demos/readme.html#list-of-applications"
  },"37": {
    "doc": "Wi-Fi Socket Mode Demos",
    "title": "Wi-Fi Socket Mode Demos",
    "content": " ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/readme.html",
    "relUrl": "/apps/wifi_socket_demos/readme.html"
  },"38": {
    "doc": "Wi-Fi Bypass Mode Demos",
    "title": "WINC3400 Example Applications",
    "content": "This example project demonstrates the WINC3400 WiFi applicationsin Bypass mode. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/readme.html#winc3400-example-applications",
    "relUrl": "/apps/wifi_bypass_demos/readme.html#winc3400-example-applications"
  },"39": {
    "doc": "Wi-Fi Bypass Mode Demos",
    "title": "Description",
    "content": "This project has WiFi example applications. The user can configure the WiFi parameters and select the required example application through command. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/readme.html#description",
    "relUrl": "/apps/wifi_bypass_demos/readme.html#description"
  },"40": {
    "doc": "Wi-Fi Bypass Mode Demos",
    "title": "Downloading and building the application",
    "content": "To download or clone this application from Github, go to the top level of the repository . Path of the application within the repository is ,wireless_apps_winc3400/apps/wifi_bypass_demos/firmware. To build the application, refer to the following table and open the project using its IDE. | Project Name | Description | . | sam_e54_xpro_winc3400.X | MPLABX project for SAME54 and WINC3400 Xplained pro | . | sam_e54_xpro_winc3400_freertos.X | MPLABX project for SAME54 and WINC3400 Xplained pro usinf FreeRTOS | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/readme.html#downloading-and-building-the-application",
    "relUrl": "/apps/wifi_bypass_demos/readme.html#downloading-and-building-the-application"
  },"41": {
    "doc": "Wi-Fi Bypass Mode Demos",
    "title": "Setting up SAMXXX Xplained Pro board",
    "content": ". | Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/readme.html#setting-up-samxxx-xplained-pro-board",
    "relUrl": "/apps/wifi_bypass_demos/readme.html#setting-up-samxxx-xplained-pro-board"
  },"42": {
    "doc": "Wi-Fi Bypass Mode Demos",
    "title": "Running the Application",
    "content": ". | Build and program the application project using its respective IDE . | Open the Terminal application (Ex.:Tera term) on the computer . | Connect to the “USB to UART” COM port and configure the serial settings as follows: . | Baud : 115200 | Data : 8 Bits | Parity : None | Stop : 1 Bit | Flow Control : None | . | Use WiFi commands to configure WiFi parameters and use application commands to select the example application. | . WiFi Commands Details . | Command | Details | Example | . | wifi help | Wi-Fi Service help command | wifi help | . | wifi set &lt;bootmode&gt; &lt;ssid_name&gt; &lt;auth_type&gt; &lt;pwd&gt; &lt;username/index&gt; | Set Wi-Fi Configuration for Station(STA) mode or Access Point (AP) mode | wifi set 2 DEMO_AP 2 12345678 | . | wifi get | Get Wi-Fi Configuration | wifi get | . |   |   |   | . Wi-Fi command parameters information . | Parameter | Sub Parameter | . | bootmode | 1- Access point(AP) mode.2- Station(STA) mode. | . | ssid_name | SSID name | . | authtype(Security type) | 1 - OPEN Mode. 2 - WPAPSK mode. 3 - WEP mode. 5 - 802.1x authentication MSCHAPV2 mode. | . | pwd(password) | Password/passphrase | . | username/index | Username if authtype is 802.1x authentication MSCHAPV2 or Key Index if the authtype is WEP. | . |   |   | . Application command parameters information . | Command | Details | Example | . | appdemo help | Application Service help command | appdemo help | . | appdemo start &lt;demo_id&gt; | Select and start an application demo | appdemo start 1 | . | appdemo get | Get the ID of currently running application demo | appdemo get | . | appdemo stop | Stop the currently running application demo | appdemo stop | . |   |   |   | . Application command parameters information . | Parameter | Sub Parameter | . | demo_ID | 1 - WiFi station mode/Access point mode demo. 8 - SSL Demo. 9 - Ping Demo. 10 - Iperf demo. 11 - SNTP demo. 18 - MQTT Demo. | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/readme.html#running-the-application",
    "relUrl": "/apps/wifi_bypass_demos/readme.html#running-the-application"
  },"43": {
    "doc": "Wi-Fi Bypass Mode Demos",
    "title": "List of Applications",
    "content": "| Application | Description | . | WiFi station mode/Access point mode demo | Demonstartes the Station Mode or Access Point(AP) mode of WINC3400 | . | SSL Demo | Demonstrates TCP SSL Client application | . | Ping Demo | Demonstrates the Ping test | . | Iperf Demo | Demonstrates the iperf application | . | SNTP Demo | Demonstrates how to retrieve time information from the time server | . | MQTT Demo | Demonstrates MQTT Application | . | WiFi Provisioning Demo | Demonstartes the WiFi provisioning application | . |   |   | . Steps to isolate/copy individual application(s) from the demo . If the user wants to isolate an application, follow the below mentioned steps . For example, the user wants to isolate the SNTP demo in Bypass mode. | The SNTP demo uses the WiFi functionalities to get connected with the network. So copy the files “ app_wifi.c” and “ app_wifi.h ” from the path “wireless_apps_winc3400/apps/wifi_bypass_demos/firmware/src ” or “wireless_apps_winc3400/apps/wifi_socket_demos/firmware/src” to “src” folder of the new demo project. Then add these files to the project. | Now user should copy and add the SNTP application files “app_sntp.c” and “app_sntp.h” from the path “wireless_apps_winc3400/apps/wifi_bypass_demos/firmware/src ” or “wireless_apps_winc3400/apps/wifi_socket_demos/firmware/src” to the “src folder of the new demo project. | The “app.c” and “app.h” files need to be copied by the user. These files integrate the SNTP application and WiFi functionalities. Copy and add these two files from the same “src” path to the “src” folder of the new demo project. | In “app.c”, within “APP_Initialize()” function, initialize the sntp application by calling “ APP_SntpInitialize(APPWiFiCallback)”. | In “app.c” file, make sure that, “ APP_WiFiTasks(wdrvHandle)” is getting called from the “ APP_STATE_WDRV_OPEN ” state of “ APP_Tasks() ” state machine. | In the same state machine “ APP_Tasks() ”, within the state “ APP_STATE_WDRV_APP_LOOP ” , call the sntp application state machine “APP_SntpTasks(handle)”. | Now follow the steps mentioned in the SNTP demo document to run the SNTP demo using “wifi”, “sntp” and “appdemo” commands. | . Similarly, for any application demo, take the required application files along with WiFi files and “app” files to create the demo. Note: . | User has to make sure the project path does not exceed windows path limit. | User should reset the device before switching the application and unpair the device from the android phone in case of switching BLE application demos. | . Back to top . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/readme.html#list-of-applications",
    "relUrl": "/apps/wifi_bypass_demos/readme.html#list-of-applications"
  },"44": {
    "doc": "Wi-Fi Bypass Mode Demos",
    "title": "Wi-Fi Bypass Mode Demos",
    "content": " ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/readme.html",
    "relUrl": "/apps/wifi_bypass_demos/readme.html"
  },"45": {
    "doc": "Wifi Provisioning via WPS",
    "title": "Wifi Provisioning via WPS",
    "content": "This example compiles the Wifi Provisioning via WPS application which is used to provision a WiFi connection. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provisioning_via_wps/readme.html",
    "relUrl": "/apps/wifi_provisioning_via_wps/readme.html"
  },"46": {
    "doc": "Wifi Provisioning via WPS",
    "title": "Description",
    "content": "In this demonstration, the WINC Driver will move into WPS mode – PIN or PBC. By activating the WPS mode in the AP concurrently, a WiFi connection is established. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provisioning_via_wps/readme.html#description",
    "relUrl": "/apps/wifi_provisioning_via_wps/readme.html#description"
  },"47": {
    "doc": "Wifi Provisioning via WPS",
    "title": "Downloading and building the application",
    "content": "To download or clone this application from Github, go to the top level of the repository . Path of the application within the repository is apps/wifi_provisioning_via_wps/firmware . To build the application, refer to the following table and open the project using its IDE. | Project Name | Description | . | sam_d21_xpro_winc3400.X | MPLABX project for SAMD21 and WINC3400 Xplained pro | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provisioning_via_wps/readme.html#downloading-and-building-the-application",
    "relUrl": "/apps/wifi_provisioning_via_wps/readme.html#downloading-and-building-the-application"
  },"48": {
    "doc": "Wifi Provisioning via WPS",
    "title": "Setting up SAMXXX Xplained Pro board",
    "content": ". | Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provisioning_via_wps/readme.html#setting-up-samxxx-xplained-pro-board",
    "relUrl": "/apps/wifi_provisioning_via_wps/readme.html#setting-up-samxxx-xplained-pro-board"
  },"49": {
    "doc": "Wifi Provisioning via WPS",
    "title": "Running the Application",
    "content": ". | Open the project. | Build and program the generated code into the hardware using its IDE. | Please refer “WINC Firmware Update Guide” and “WINC Driver Demonstrations” for more information. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provisioning_via_wps/readme.html#running-the-application",
    "relUrl": "/apps/wifi_provisioning_via_wps/readme.html#running-the-application"
  },"50": {
    "doc": "Wi-Fi provisioning using BLE",
    "title": "Wi-Fi provisioning using BLE",
    "content": "This example demonstrates how to pass the AP credentials to WINC3400 device via BLE. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provision_via_ble/readme.html",
    "relUrl": "/apps/wifi_provision_via_ble/readme.html"
  },"51": {
    "doc": "Wi-Fi provisioning using BLE",
    "title": "Description",
    "content": "This application demonstrates how a user can pass the target AP credentials to WINC3400 device via BLE. The user would need to use “Microchip Bluetooth Data” mobile application to pass the AP credentials to WINC3400 after pairing with the mobile. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provision_via_ble/readme.html#description",
    "relUrl": "/apps/wifi_provision_via_ble/readme.html#description"
  },"52": {
    "doc": "Wi-Fi provisioning using BLE",
    "title": "Downloading and building the application",
    "content": "To download or clone this application from Github, go to the top level of the repository . Path of the application within the repository is apps/wifi_provision_via_ble/firmware . To build the application, refer to the following table and open the project using its IDE. | Project Name | Description | . | sam_e54_xpro_winc3400.X | MPLABX project for SAME54 and WINC3400 Xplained pro | . | sam_d21_xpro_winc3400.X | MPLABX project for SAMD21 and WINC3400 Xplained pro | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provision_via_ble/readme.html#downloading-and-building-the-application",
    "relUrl": "/apps/wifi_provision_via_ble/readme.html#downloading-and-building-the-application"
  },"53": {
    "doc": "Wi-Fi provisioning using BLE",
    "title": "Setting up SAMXXX Xplained Pro board",
    "content": ". | Connect the Debug USB port on the SAMEXXX Xplained Pro board to the computer using a micro USB cable | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provision_via_ble/readme.html#setting-up-samxxx-xplained-pro-board",
    "relUrl": "/apps/wifi_provision_via_ble/readme.html#setting-up-samxxx-xplained-pro-board"
  },"54": {
    "doc": "Wi-Fi provisioning using BLE",
    "title": "Running the Application",
    "content": ". | Build and program the application project using its respective IDE . | Open the Terminal application (Ex.:Tera term) on the computer . | Connect to the “USB to UART” COM port and configure the serial settings as follows: . | Baud : 115200 | Data : 8 Bits | Parity : None | Stop : 1 Bit | Flow Control : None | . | Download the Microchip Bluetooth Data application from App Store and open it. | The WINC3400 device will scan the APs and ready to get paired with Mobile application. | . | In the Mobile Application, Open the “Ble provisioner” widget. | . | In the “Ble provisioner” widget, press the “scan” button. It will list the surrounding BLE devices. | . | The default name given for WINC3400 in the “Wi-Fi provisioning using BLE” application is “Wifi Prov”. Click on “Wifi Prov” device. | . | The next screen will display the scanned AP list. | . | Select the desired AP from the scan list and provide the required credentials to make Wi-Fi connection. | Press “Provision” button . | The mobile application will ask for the password to pair. | The password is stored in the “pincode” variable in the “wifi_prov.c” file. | Enter the password to pair the WINC3400 device with mobile. | . | The device will connect to the AP and print the IP address obtained. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provision_via_ble/readme.html#running-the-application",
    "relUrl": "/apps/wifi_provision_via_ble/readme.html#running-the-application"
  },"55": {
    "doc": "Wifi Provisioning via SoftAP",
    "title": "Wifi Provisioning via SoftAP",
    "content": "This example compiles the Wifi Provisioning via SoftAP application which is used to provision a WiFi connection. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provisioning_via_softap/readme.html",
    "relUrl": "/apps/wifi_provisioning_via_softap/readme.html"
  },"56": {
    "doc": "Wifi Provisioning via SoftAP",
    "title": "Description",
    "content": "In this demonstration, the WINC Driver will advertise a SoftAP. The SoftAP connection is leveraged to provision a WiFi connection. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provisioning_via_softap/readme.html#description",
    "relUrl": "/apps/wifi_provisioning_via_softap/readme.html#description"
  },"57": {
    "doc": "Wifi Provisioning via SoftAP",
    "title": "Downloading and building the application",
    "content": "To download or clone this application from Github, go to the top level of the repository . Path of the application within the repository is apps/wifi_provisioning_via_softap/firmware . To build the application, refer to the following table and open the project using its IDE. | Project Name | Description | . | sam_d21_xpro_winc3400.X | MPLABX project for SAMD21 and WINC3400 Xplained pro | . |   |   | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provisioning_via_softap/readme.html#downloading-and-building-the-application",
    "relUrl": "/apps/wifi_provisioning_via_softap/readme.html#downloading-and-building-the-application"
  },"58": {
    "doc": "Wifi Provisioning via SoftAP",
    "title": "Setting up SAMXXX Xplained Pro board",
    "content": ". | Connect the Debug USB port on the SAMXXX Xplained Pro board to the computer using a micro USB cable | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provisioning_via_softap/readme.html#setting-up-samxxx-xplained-pro-board",
    "relUrl": "/apps/wifi_provisioning_via_softap/readme.html#setting-up-samxxx-xplained-pro-board"
  },"59": {
    "doc": "Wifi Provisioning via SoftAP",
    "title": "Running the Application",
    "content": ". | Open the project. | Build and program the generated code into the hardware using its IDE. | Please refer “firmware update guide” and “WINC Driver Demonstrations” for more information. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_provisioning_via_softap/readme.html#running-the-application",
    "relUrl": "/apps/wifi_provisioning_via_softap/readme.html#running-the-application"
  },"60": {
    "doc": "Battery Service",
    "title": "Battery Service",
    "content": "The]is application demonstartes the reporting of battery level of the device using the battery characteristics. This example application simulates the device battery level from 0% to 100%, with the step of 1% every second. Note: Currently, this demo is disabled in the project sam_d21_xpro_winc3400.X due to memory limitation.The user can enable this demo by enabling the macro APP_BLE_BATTERY in app.h file. | This is an BLE application example. So the user need to download the Microchip Bluetooth Data application from App Store. | Enter the command “appdemo start 14” to select and run the application. | Open the Microchip Bluetooth Data application. Select Bluetooth Smart Widget. In the Bluetooth Smart Widget, press “START SCAN”. From the list of available devices select the device name MCHP-BAS. | Enter the pass-key “123456” on Bluetooth Pairing Request window and click Pair. | When paired, the application displays the Battery Service and the Generic Information service. | Select “Battery Service” to receive notifications for the battery level characteristic. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_battery_service_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_battery_service_application.html"
  },"61": {
    "doc": "Certificate Download OTA Demo",
    "title": "Certificate Download OTA Demo",
    "content": "This example demonstrates how to download the TLS certificates into WINC3400 via OTA. It downloads the certificates from an OTA download server, which is a web server. Note: This example will be only available with SAME54 Host. | Use any HTTP server or hfs.exe from http://www.rejetto.com/hfs/ . | Run the hfs.exe . | Add the certificates from the “\\\\utilities\\\\cert_store” to the root folder in the hfs.exe tool. | Configure the wifi parameters using “wifi set” command. | Copy the URL from server. | Enter the command “cert &lt;url&gt;”. | Enter the application command “appdemo start 1 19” to run the Certificate download via OTA demo. First the device will connect to the network. | After the IP address has displayed on the terminal window, application will execute the CERT command and starts the certificate download. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_certificate_download_ota_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_certificate_download_ota_application.html"
  },"62": {
    "doc": "Custom Serial Chat",
    "title": "Custom Serial Chat",
    "content": "This application demonstrates the Custom Serial Chat application used for sending and receiving data between WINC3400 and the Microchip Bluetooth Data mobile application using BLE. The user can send the information to the mobile phone using the console terminal that is configured with the board and vice versa. | Download the Microchip Bluetooth Data application from App Store. | Enter the command “appdemo start 12” to select and run the application. | Open the Mobile Application and select the “Bluetooth Smart” widget. | In the Bluetooth Smart Widget, press “START SCAN”. From the list of available devices select the device name AT-CSC. | Enter the pass-key “123456” on Bluetooth Pairing Request window and click Pair. | After pairing completed, the Custom Serial Chat service appears on the service list page. | Click the Custom Serial Chat icon. The chat icon appears, and the user can type the text that is to be sent to the remote device. Press “Send” button. | The text received from the Mobile application will be displayed on the terminal. | The user can write the text on the terminal using the command format “csc send \\\" and press ENTER key to send the text. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_csc_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_csc_application.html"
  },"63": {
    "doc": "Heart Rate Profile",
    "title": "Heart Rate Profile",
    "content": "This application demonstrates the exchange of heart rate parameters of heart rate profile between the sensor and monitor. The heart rate profile is provided by Bluetooth SIG. | This is an BLE application example. So the user need to download the Microchip Bluetooth Data application from App Store. | Enter the command “appdemo start 13” to select and run the application. | Open the Microchip Bluetooth Data application. Select Bluetooth Smart Widget. In the Bluetooth Smart Widget, press “START SCAN”. From the list of available devices select the device name MCHP-HRT. | Enter the pass-key “123456” on Bluetooth Pairing Request window and click Pair. | After the device is connected, the application displays the Heart Rate and the Device Information Service. Select Heart Rate Service. | When notifications are enabled, the HRM values, Sensor Location and Energy Expended are displayed in the console and the corresponding mobile app. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_heartrate_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_heartrate_application.html"
  },"64": {
    "doc": "Iperf Demo",
    "title": "Iperf Demo",
    "content": "This application demonstrates how a user can run iperf application on WINC3400 device in Socket Mode. | Configure the wifi parameters using “wifi set” command. | Enter “siperf &lt;tcp/udp&gt;” on the terminal window to select and start the iperf application demo in the DUT. | Command on DUT | Details | . | siperf tcp | Starts the TCP server at the DUT | . | siperf udp | Starts the UDP server at the DUT | . |   |   | . | Enter the application command “appdemo start 1 10 “ to run the iperf demo. First the device will connect to the network. The IP address will be displayed on the terminal window. Then the TCP/UDP server will get started. | After the “TCP/UDP” server has started, the user wants to run the iperf commands on the PC to start the iperf application as TCP/UDP Client . iperf command details. | Command on PC | Details | Example | . | iperf -c &lt;Server_IP_Address&gt; -t &lt;time_peroid&gt; -i &lt;time_interval&gt; -r | Setup the TCP Client in the PC | iperf -c 192.168.43.27 -i 1 -t 10 -r | . | iperf -u -c &lt;Server_IP_Address&gt; -t &lt;time_peroid&gt; -i &lt;time_interval&gt; -u -b &lt;bandwidth&gt; -r | Setup the UDP Client in the PC | iperf -u -c 192.168.43.27 -b 20M -i 1 -t 10 -r | . |   |   |   | . | After receiving the “Server Report” on the terminal, enter the iperf commands on the PC to set the iperf application as TCP/UDP server. | Command on PC | Details | Example | . | iperf -s -i &lt;time_interval&gt; | Setup the TCP Server in the PC | iperf -s -i 1 | . | iperf -s -u -i &lt;time_interval&gt; | Setup the UDP Server in the PC | iperf -s -u -i 1 | . |   |   |   | . | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_iperf_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_iperf_application.html"
  },"65": {
    "doc": "Iperf Demo",
    "title": "Iperf Demo",
    "content": "This application demonstrates how a user can run iperf application on WINC3400 device in Bypass Mode. | Configure the wifi parameters using “wifi set” command. | Enter the command “appdemo start 1” to set the DUT(Device Under Test) in station mode. It will connect to the wifi network and the IP address will be displayed on the terminal. | The user should enter the iperf commands in the terminal window (for DUT) and in the iperf application which is available in the PC. | Protocol | PC | DUT | Command on PC | Command on DUT | . | UDP | Client | Server | iperf -u -c &lt;Server_IP_Address&gt; -t &lt;time_peroid&gt; -i &lt;time_interval&gt; -u -b &lt;bandwidth&gt; e.g.: iperf -u -c 192.168.43.27 -b 20M -i 1 -t 10 | iperf -s -u -i &lt;time_interval&gt; e.g.: iperf -s -u -i 1 | . | UDP | Server | Client | iperf -s -u -i &lt;time_interval&gt; e.g.: iperf -s -u -i 1 | iperf -u -c &lt;Server_IP_Address&gt; -t &lt;time_peroid&gt; -i &lt;time_interval&gt; -u -b &lt;bandwidth&gt; e.g.: iperf -u -c 192.168.43.87 -b 20M -i 1 -t 10 | . | TCP | Client | Server | iperf -c &lt;Server_IP_Address&gt; -t &lt;time_peroid&gt; -i &lt;time_interval&gt; e.g: iperf -c 192.168.43.27 -i 1 -t 10 | iperf -s -i &lt;time_interval&gt; e.g: iperf -s -i 1 | . | TCP | Server | Client | iperf -s -i &lt;time_interval&gt; e.g: iperf -s -i 1 | iperf -c &lt;Server_IP_Address&gt; -t &lt;time_peroid&gt; -x &lt;bandwidth&gt; e.g: iperf -c 192.168.43.87 -x 10M -t 10 | . |   |   |   |   |   | . | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/docs/readme_iperf_application.html",
    "relUrl": "/apps/wifi_bypass_demos/docs/readme_iperf_application.html"
  },"66": {
    "doc": "MQTT Demo",
    "title": "MQTT Demo",
    "content": "This application demonstrates how a user run a MQTT Client using third party Paho software on WINC3400 device. The user would need to use “MQTT.fx” third party Mqtt Client application to receive message posted by MQTT Client running on WINC3400 device once it connects to the MQTT server. | Download the MQTT.fx Third Party Mqtt Client Application and open it on Laptop. | Connect the MQTT.fx Application to the MQTT Server - broker.hivemq.com with port 1883. | Make the MQTT.fx Application susbcribe to Topic MCHP/Sample/a. | Configure the wifi parameters using “wifi set” command. | Enter the command “mqtt start”. | Enter the command “appdemo start 1 18”. The device will connect to the network and IP address will be displayed on the terminal window. Then the MQTT Client on the WINC3400 device shall connect to the MQTT Server - broker.hivemq.com. | After connecting to MQTT Server, the MQTT Client on the WINC3400 device shall subscribe to Topic MCHP/Sample/b. | The MQTT Client on the WINC3400 device shall publish the message “Hello” to Topic MCHP/Sample/a. | MQTT.fx Application receives the message “Hello” on the Topic MCHP/Sample/a sent by the MQTT Client running on the WINC3400. | Publish message from MQTT.fx Application on the Topic MCHP/Sample/b. | The MQTT Client on the WINC3400 device receives the message on the Topic MCHP/Sample/b sent by the MQTT.fx Application running on the laptop. | . Note: If the user wants to create a MQTT application project in Socket Mode, and wants to use the Paho for MQTT Protocol, One needs to follow the below mentioned steps 1. From the “paho.mqtt.embedded-c” repo, copy the folder “paho.mqtt.embedded-c\\\\MQTTPacket” to “app_demos\\firmware\\\\src\\third_party\\\\paho.mqtt.embedded-c\\\\MQTTPacket” of the new project directory. 2. From the “paho.mqtt.embedded-c” repo, copy the folder “paho.mqtt.embedded-c\\\\MQTTClient-C” to “app_demos\\firmware\\\\src\\third_party\\\\paho.mqtt.embedded-c\\\\MQTTClient-C” of the new project directory. 3. It is important to have the porting files “MCHP_winc.c” and “MCHP_winc.h” in the project. These porting files are available only in “wifi_socket_demo” project. Copy the folder from “wifi_socket_demos\\firmware\\\\src\\third_party\\\\paho.mqtt.embedded-c\\\\MQTTClient-C\\\\Platforms” to “app_demos\\firmware\\\\src\\third_party\\\\paho.mqtt.embedded-c\\\\MQTTClient-C\\\\Platforms” of the new project directory. Please make sure that the folder structure of the new project is same as mentioned above. | Enable MQTT User should enable the macro “WINC_MQTT” to enable the MQTT application. For this follow the steps: . | Open project properties . | Select xc32-gcc . | Select “preprocessing and messages” from the “Option Categories”. | Select the “add” button of “Preprocessor Macros” . | Add the macro “WINC_MQTT” and press OK. | . | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_mqtt_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_mqtt_application.html"
  },"67": {
    "doc": "MQTT Demo",
    "title": "MQTT Demo",
    "content": "This application demonstrates how a user run a MQTT Client using third party Paho software on WINC3400 device. The user would need to use “MQTT.fx” third party Mqtt Client application to receive message posted by MQTT Client running on WINC3400 device once it connects to the MQTT server. | Download the MQTT.fx Third Party Mqtt Client Application and open it on Laptop. | Connect the MQTT.fx Application to the MQTT Server - mqtt.eclipseprojects.io with port 1883. | Make the MQTT.fx Application susbcribe to Topic “MQTT_NET_Client topic”. | Configure the wifi parameters using “wifi set” command. | Enter the command “mqtt start”. | Enter the command “appdemo start 1 18”. The device will connect to the network and IP address will be displayed on the terminal window. | The MQTT Client on the WINC3400 device shall connect to the MQTT Server - mqtt.eclipseprojects.io. | After connecting to MQTT Server, the MQTT Client on the WINC3400 device shall subscribe to Topic “MQTT_NET_Client topic”. | The MQTT Client on the WINC3400 device shall publish the message “MQTT NET Demo Test Message” to Topic “MQTT_NET_Client topic”. | MQTT.fx Application receives the message “MQTT NET Demo Test Message” on the Topic “MQTT_NET_Client topic” sent by the MQTT Client running on the WINC3400. | The message “MQTT NET Demo Test Message” will be published from MQTT.fx Application. Since it is subcribing to the same topic “MQTT_NET_Client topic”. The MQTT demo will exit after publishing the message. | . NOTE: Sometimes the MQTT demo will give connection error, if the default broker mqtt.eclipseprojects.io is down. If so try the demo with this broker : broker.hivemq.com . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/docs/readme_mqtt_application.html",
    "relUrl": "/apps/wifi_bypass_demos/docs/readme_mqtt_application.html"
  },"68": {
    "doc": "OTA Demo",
    "title": "OTA Demo",
    "content": "This example demonstrates how to upgrade the WINC3400 firmware via OTA. It downloads the WINC3400 firmware from an OTA download server, which is a web server. | Use any HTTP server or hfs.exe from http://www.rejetto.com/hfs/ . | Run the hfs.exe . | Set the port number to 8000 in the hfs tool. | Add the OTA firmware from the “\\\\utilities\\\\m2m_ota_3400.bin” to the root folder in the hfs.exe tool. Note: Current OTA application ( \\\\utilities\\\\m2m_ota_3400.bin ) image is of latest firmware 1.4.2 release, user can select required firmware version of the OTA image as per their choice. To create the required OTA firmware, follow the steps mentioned in the document Firmware Upgrade of WINC Devices. | Configure the wifi parameters using “wifi set” command. | Enter the command “ota &lt;image_url&gt;”. | Enter the application command “appdemo start 1 7” to run the OTA demo. First the device will connect to the network. After the IP address has displayed on the terminal window, application will execute the OTA command and starts the OTA firmware upgrade. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_ota_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_ota_application.html"
  },"69": {
    "doc": "Ping Demo",
    "title": "Ping Demo",
    "content": "This application demonstrates how a user can run a ping test on WINC3400 device in Bypass Mode. | Configure the wifi parameters using “wifi set” command. | Enter the command “appdemo start 1”. Then the device will connected to the AP and the IP address will be displayed on the terminal. | Enter the command “ping &lt;ip_address&gt;”. It will start pinging the corresponding IP address. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/docs/readme_ping_application.html",
    "relUrl": "/apps/wifi_bypass_demos/docs/readme_ping_application.html"
  },"70": {
    "doc": "Ping Demo",
    "title": "Ping Demo",
    "content": "This application demonstrates how a user can run a ping test on WINC3400 device in Socket Mode. | Configure the wifi parameters using “wifi set” command. | Enter the command “sping &lt;ip_address&gt; &lt;no_of_ping&gt;”. | Then enter the command “appdemo start 1 9” to run the Ping demo. First the device will connect to the network. After the IP address has displayed on the terminal window, the ping command will start. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_ping_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_ping_application.html"
  },"71": {
    "doc": "Proximity Reporter",
    "title": "Proximity Reporter",
    "content": "This application demonstrates the proximity monitoring between the WINC3400 and Android Mobile phone with Microchip Bluetooth Data application. Note: Currently, this demo is disabled in the project sam_d21_xpro_winc3400.X due to memory limitation.The user can enable this demo by enabling the macro APP_BLE_PROXIMITY in app.h file. | This is an BLE application example. So the user need to download the Microchip Bluetooth Data application from App Store. | Enter the command “appdemo start 15” to select and run the application. | Open the Microchip Bluetooth Data application. Select Bluetooth Smart Widget. In the Bluetooth Smart Widget, press “START SCAN”. From the list of available devices select the device name ATMEL-PXP. | Enter the pass-key “123456” on Bluetooth Pairing Request window and click Pair. | After pairing completed, the supported services are displayed on the application. | Select the desired service (Link Loss or Immediate Alert) for alert level characteristics configuration. Choose a value from the following: HIGH ALERT/MILD ALERT/NO ALERT . | After configuration of the desired alert levels, click Immediate Alert service and then move the mobile phone away from the Proximity Reporter. Based on the distance of separation, Path Loss is plotted on the zone radar (using RSSI values received from the Proximity Reporter). | Based on the zone, the Proximity Monitor sends the corresponding alert level. The console log on the Proximity Reporter displays the corresponding alerts and on-board status LED behavior. | After configuration of the desired alert levels, click on the Link Loss service and then move the mobile phone away from the reporter. Keep moving until the “Link Loss”pop-up appears. The console log on the Proximity Reporter displays the corresponding alerts and when Link Loss occurs, it reports the disconnection and the on-board status LED behavior. ; . | After Link Loss, the mobile application attempts to reconnect to the Proximity Reporter. The connection is re-established by moving the mobile phone closer to the reporter. | Click the Tx Power Service icon in the services screen. The Proximity Monitor reads the Tx Power value from the Proximity Reporter and displays the TX POWER LEVEL. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_pxp_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_pxp_application.html"
  },"72": {
    "doc": "SNTP Demo",
    "title": "SNTP Demo",
    "content": "This example demonstrates the use of the WINC3400 to retrieve time information from the time server. Follow the below mentioned steps to run the demo. | Configure the wifi parameters using “wifi set” command. | Enter the command “sntp get”. | Enter the command “appdemo start 1 11” to run the SNTP demo. First the device will connect to the network. After the IP address has displayed on the terminal window, application will execute the SNTP command and the response will be displayed on the terminal wimdow. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_sntp_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_sntp_application.html"
  },"73": {
    "doc": "SNTP Demo",
    "title": "SNTP Demo",
    "content": "This example demonstrates the use of the WINC3400 to retrieve time information from the time server. Follow the below mentioned steps to run the demo. | Configure the wifi parameters using “wifi set” command. | Enter the command “sntp get”. | Enter the command “appdemo start 1 11” to run the SNTP demo. First the device will connect to the network. After the IP address has displayed on the terminal window, application will execute the SNTP command and the response will be displayed on the terminal wimdow. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/docs/readme_sntp_application.html",
    "relUrl": "/apps/wifi_bypass_demos/docs/readme_sntp_application.html"
  },"74": {
    "doc": "SSL Demo",
    "title": "SSL Demo",
    "content": "This application demonstrates how a user can run a secured TCP Client on WINC3400 device. In this application, we open a secured html page ‘https://www.google.com’. Here the TCP SSL Client running on the WINC3400 device shall connect to server google.com over a secured html port 443, and make a reuqtest for getting the html page. | Configure the wifi parameters using “wifi set” command. | Enter the command “ssl https://www.google.com/” . | Enter the command “appdemo start 1 8”. The device will connect to the network and IP address will be displayed on the terminal window. After connecting to the AP, the TCP SSL Client on the WINC3400 device shall connect to the Server - google.com over the secured html port 443. Note: The user needs to ensure that the server certificate is a part of the WINC FW Image in case a secured connection is needed with the server. | After connecting to google Server, the TCP SSL Client on the WINC3400 device shall send a GET HTML request, and the google server shall send in the html page. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_ssl_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_ssl_application.html"
  },"75": {
    "doc": "SSL Demo",
    "title": "SSL Demo",
    "content": "This application demonstrates how a user can run a secured TCP Client on WINC3400 device. In this application, we open a secured html page ‘https://www.google.com’. Here the TCP SSL Client running on the WINC3400 device shall connect to server google.com over a secured html port 443, and make a reuqtest for getting the html page. | Configure the wifi parameters using “wifi set” command. | Enter the command “ssl https://www.google.com/” . | Enter the command “appdemo start 1 8”. The device will connect to the network and IP address will be displayed on the terminal window. After connecting to the AP, the TCP SSL Client on the WINC3400 device shall connect to the Server - google.com over the secured html port 443. Note: The user needs to ensure that the server certificate is a part of the WINC FW Image in case a secured connection is needed with the server. | After connecting to google Server, the TCP SSL Client on the WINC3400 device shall send a GET HTML request, and the google server shall send in the html page. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/docs/readme_ssl_application.html",
    "relUrl": "/apps/wifi_bypass_demos/docs/readme_ssl_application.html"
  },"76": {
    "doc": "WiFi Station Mode / Access Point Mode Demo",
    "title": "WiFi Station Mode / Access Point Mode Demo",
    "content": "This example demonstrates the use of the WINC3400 to behave as a Station or Access Point(AP). Station Mode . | Configure the WiFi parameters using the “wifi set “ command. | Select and run the application using the command “appdemo start 1” . | The application starts and perform scanning and connects to the WiFi. | . Access Point Mode . | If the user wants to configure the device as Access Point,configure the wifi using “wifi set” command. In the configuration set the bootmode as Access point mode, keep the authentication type as “OPEN” and give an SSID name for the Access point. | Enter the command “appdemo start 1” to run the application. | Connect a device to this Access point. The IP address of connected device will be displayed on the console. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_sta_ap_mode_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_sta_ap_mode_application.html"
  },"77": {
    "doc": "WiFi Station Mode / Access Point Mode Demo",
    "title": "WiFi Station Mode / Access Point Mode Demo",
    "content": "This example demonstrates the use of the WINC3400 to behave as a Station or Access Point(AP). Station Mode . | Configure the WiFi parameters using the “wifi set “ command. | Select and run the application using the command “appdemo start 1” . | The application starts and perform scanning and connects to the WiFi. | . Access Point Mode . | If the user wants to configure the device as Access Point,configure the wifi using “wifi set” command. In the configuration set the bootmode as Access point mode, keep the authentication type as “OPEN” and give an SSID name for the Access point. | Enter the command “appdemo start 1” to run the application. | Connect a device to this Access point. The IP address of connected device will be displayed on the console. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/docs/readme_sta_ap_mode_application.html",
    "relUrl": "/apps/wifi_bypass_demos/docs/readme_sta_ap_mode_application.html"
  },"78": {
    "doc": "Transparent Service",
    "title": "Transparent Service",
    "content": "The Transparent Service is used as a data exchange method between the client and the server. This application demonstrates the data exchange using Transparent service. | This is an BLE application example. Download and install the Microchip SmartConnect mobile application from “\\\\utilities\\\\apk\\BLEDK3_V1.0.apk” . | Enter the command “appdemo start 16” to select and run the application. | Open the Open the Microchip SmartConnect mobile application. In application click Scan to start scanning for the BLE devices. | Select uC-TRANS from the list of scanned devices. | Enter the pass-key “123456” on Bluetooth Pairing Request window and click Pair. | When paired, the application displays the “Transfer data to device” on the service page. Click Transfer data to device. The chat screen appears where the user can type the text that is to be sent to the remote device, and also see the text coming from the remote device. | Chat text “Hello” to the remote device. The data/text sent is displayed on the console/terminal for the device connected. | The user can write the text on the terminal using the command format “trans send \\\" and press ENTER key to send the text. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_transparent_service_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_transparent_service_application.html"
  },"79": {
    "doc": "WiFi Provisioning",
    "title": "WiFi Provisioning",
    "content": "The WiFi Provisioning application demonstartes the WiFi provisioning using BLE. | This is an BLE application example. So the user need to download the Microchip Bluetooth Data application from App Store. | Enter “wifiprov start” command to start the provisioning. | Enter the command “appdemo start 6” to select and run the application. | Open the android application and select the “Ble Provisioner” widget. Then press Scan button. | Select “WiFi Prov” from the list for the ATWINC3400. | Select the AP and enter the security details and click Provision to start provisioning process. | The mobile application will ask for the password to pair. | Enter the pass-key “123456” on Bluetooth Pairing Request window and click Pair. | The device will connect to the AP and the IP address will be displayed on the terminal. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_wifi_prov_via_ble_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_wifi_prov_via_ble_application.html"
  },"80": {
    "doc": "WiFi Provisioning",
    "title": "WiFi Provisioning",
    "content": "The WiFi Provisioning application is used for receiving Wi-Fi provisioning data via the microchip android application “WiFi-Provisioning” and then triggering a Wi-Fi connection. | Download the android application “WiFi Provisioning” of Microchip Technologies from App store. | Start the DUT as Access Point. Use “wifi set” command to configure Access Point. In the configuration, set the bootmode as Access point mode, keep the authentication type as “OPEN” and give an SSID name for the Access point. | Enter the command “appdemo start 1” to run the application. | Connect the mobile phone to this Access point. The IP address of connected device will be displayed on the console. | Open the WiFi Provisioning application in mobile phone. Set the Server IP Address as “192.168.1.1” and Server Port Number as “6666”. Then press connect. | The list of available networks will be displayed in the next window. | Select the network and enter the password. Then press, “SEND”. | The DUT will connect to the selected network and the IP address will be displayed on the terminal. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/docs/readme_wifi_provision_application.html",
    "relUrl": "/apps/wifi_bypass_demos/docs/readme_wifi_provision_application.html"
  },"81": {
    "doc": "WiFi Provisioning",
    "title": "WiFi Provisioning",
    "content": "The WiFi Provisioning application is used for receiving Wi-Fi provisioning data via the microchip android application “WiFi-Provisioning” and then triggering a Wi-Fi connection. | Download the android application “WiFi Provisioning” of Microchip Technologies from App store. | Start the DUT as Access Point. Use “wifi set” command to configure Access Point. In the configuration, set the bootmode as Access point mode, keep the authentication type as “OPEN” and give an SSID name for the Access point. | Enter the command “appdemo start 1” to run the application. | Connect the mobile phone to this Access point. The IP address of connected device will be displayed on the console. | Open the WiFi Provisioning application in mobile phone. Set the Server IP Address as “192.168.1.1” and Server Port Number as “80” . Then press connect. | The list of available networks will be displayed in the next window. | Select the network and enter the password. Then press, “SEND”. | The DUT will connect to the selected network and the IP address will be displayed on the terminal. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/docs/readme_wifi_provision_application.html",
    "relUrl": "/apps/wifi_socket_demos/docs/readme_wifi_provision_application.html"
  },"82": {
    "doc": "Release notes",
    "title": "Microchip MPLAB® Harmony 3 Release Notes",
    "content": " ",
    "url": "http://localhost:4000/wireless_apps_winc3400/release_notes.html#microchip-mplab-harmony-3-release-notes",
    "relUrl": "/release_notes.html#microchip-mplab-harmony-3-release-notes"
  },"83": {
    "doc": "Release notes",
    "title": "Harmony 3 Wireless application examples for WINC3400 v3.4.2",
    "content": "Development kit and demo application support . Following table provides number of Wireless examples available for different development kits. | Development Kits | MPLABx applications | . | SAMD21 with WINC3400 Xpro | 8 | . | SAME54 with WINC3400 Xpro | 10 | . New Features . | New MQTT, SSL, SNTP and OTA demos added for Bypass mode. | New MQTT, SSL, SNTP, OTA Certificate download and OTA demos added for Socket mode. | . Bug fixes . | “wireless_wifi_apps_winc3400” applications are upgraded with Countermeasures for ‘Fragattack’ vulnerabilities. | . Known Issues . | Due to an issue in the underlying net repo, you need to turn off -Werror for the icmp.c file in your projects. | User may face connectivity issue with the SSL demo of bypass mode with FreeRTOS. Please use SSL demo of bypass mode without FreeRTOS. | “wireless_wifi” Serial bridge application needs to be regenerated before using it for firmware update. Additional known issues can be found at WINC3400-known-issues | . Development Tools . | MPLAB® X IDE v5.50 | MPLAB® X IDE plug-ins: . | MPLAB® Harmony Configurator (MHC) v3.8.2 | . | MPLAB® XC32 C/C++ Compiler v3.01 | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/release_notes.html#harmony-3-wireless-application-examples-for-winc3400-v342",
    "relUrl": "/release_notes.html#harmony-3-wireless-application-examples-for-winc3400-v342"
  },"84": {
    "doc": "Release notes",
    "title": "Release notes",
    "content": ". ",
    "url": "http://localhost:4000/wireless_apps_winc3400/release_notes.html",
    "relUrl": "/release_notes.html"
  },"85": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Create your first WIN3400 Bypass mode example using Harmony TCP/IP stack",
    "content": " ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#create-your-first-win3400-bypass-mode-example-using-harmony-tcpip-stack",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#create-your-first-win3400-bypass-mode-example-using-harmony-tcpip-stack"
  },"86": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Overview",
    "content": "This tutorial is a getting-started guide to demonstrate how to create a WINC3400 Bypass (Ethernet) mode example using MPLAB® Harmony v3 TCP/IP stack. This tutorial implements a simple STA Client application on a microcontroller development board. This will guide you through the steps required to create a new TCP/IP application using MPLAB® Harmony 3 modules. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#overview",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#overview"
  },"87": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Software Details",
    "content": "This tutorial is tested with following tool versions. | MPLAB® X IDE v5.40 | MPLAB® XC32/32++ C Compiler v2.40 | MPLAB® Harmony Configurator Plugin (MHC) v3.6.0 | MPLAB® Harmony v3 Software Framework | . Note : Harmony 3 comes in modular format where user can choose which modules to work with. In order to create WINC1500 bypass mode example, following modules are essential. Harmony Content Manager tool can be used to download/clone the repositories from Github. | bsp v3.9.0 | core v3.9.2 | csp v3.9.1 | dev_packs v3.9.0 | mhc v3.8.0 | net v3.7.2 | wireless_wifi v3.5.1 | wireless_apps_winc3400 v3.4.1 | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#software-details",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#software-details"
  },"88": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Hardware Setup",
    "content": "The getting-started guide demonstrates the creation of a TCP/IP demo on the SAM E54 Xplained Pro board with the ATWINC1500 XPRO board. These steps can be applied for other supported development boards applying the device/board specific configuration changes. The microcontroller should be supported by NET and Wireless modules within H3. At this point, SAM E54 is the only device supported by both modules. New device support is constantly added to modules. Check the individual module release notes for more details about device support. | SAME54 Xplained PRO | ATWINC3400 XPRO | . The SAME54 Xplained PRO contains a built-in programmer-debugger tool called Embedded Debugger (EDBG) which is used in this tutorial. | Embedded Debugger (EDBG). | . Following image shows the hardware setup. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#hardware-setup",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#hardware-setup"
  },"89": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Creating a new Harmony project",
    "content": "Follow the steps to create a basic Harmony project. The assumption is that H3 modules are cloned at “C:\\\\microchip\\\\harmony\\v3\\\" . | Open the MPLAB® X IDE. | Create a New Project by selecting File &gt; New Project. | In the New Project window select 32-Bit MPLAB® Harmony 3 Project and click Next. Note: The MPLAB® Harmony 3 Project will not be displayed if the MPLAB® Harmony 3 Configurator plug-in is not installed. It has to be installed before continuing with the next steps. | In the Framework Path, enter the path of the folder to which the MPLAB® Harmony 3 packages are downloaded. | In the Project Setting dialog window, fill in or select the information needed as follows: . | Location: First, create a “winc_bypass_getting_started” folder in the location of your choice (for example, create the application project inside the ‘C:\\\\microchip\\\\harmony\\v3\\wireless_apps_winc3400\\\\apps' folder). Then enter the path in this field. | Folder: Project Folder name. For example, sam_e54_xpro_winc3400. | Name: Project Name i.e. winc_bypass_getting_started_sam_e54_xpro_winc3400. | Path: Selecting the above fields auto populates the Path. | Click Next. | . | In the Configuration Settings dialog window, fill in or select the information needed as follows: . | Name: Configuration Name. For example, sam_e54_xpro_winc3400. | Target Device: Use the below table to chose the target device part number based on the demo board that you are using. For this example: SAM E54 Xplained Pro uses ATSAME54P20A. | The Device Filter textbox helps narrow down list of available devices as shown. | Click Finish. | . | First time when you create a Harmony 3 project, “Window Manager Selection Dialog” appears. The user can select “Standalone” or “Native” depending upon the preference. “Standalone” opens the MHC in a separate window. “Native” opens MHC as a window within MPLAB® X IDE. | If the above dialog window doesn’t appear then MHC can be launched by selecting MPLAB® Harmony 3 Configurator under Tools -&gt; Embedded -&gt; MPLAB® Harmony 3 Configurator. | In the MPLAB® Harmony Launcher window, leave the launch path as default option i.e. MPLAB® Harmony Project Path but make sure it is correctly pointed to desired H3 cloned directory and click Launch. | In the Configuration Database Setup window, leave the DFP and CMSIS paths as default and click Launch . | MHC window will open now. The default standalone Harmony configurator will be as shown below. Different parts of configurator are: . | Available Components | Active Components | Project Graph | Configuration Options | Console Window . | . | Depending upon the application needs, the necessary components can be added from the Available Components. Go to Available Components -&gt; Board Support Packages (BSPs) and double click on the Board support package for the target board. Below example shows the BSP for SAME54 Xplained Ultra board. After adding BSP, the Project Graph will look as below: . Basic components needed for creating a project will be available in project graph by default. The next step would be to configure the components based on the application needs. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#creating-a-new-harmony-project",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#creating-a-new-harmony-project"
  },"90": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Add TCP/IP Components",
    "content": "The TCP/IP components can be added from the Available Components. Go to Available Components -&gt; Libraries -&gt; TCPIP . The TCP/IP components are categorized into 5 different groups and a configurator is available for each group. These configurators are: . | TCP/IP Application Layer Configurator | TCP/IP Transport Layer Configurator | TCP/IP Network Layer Configurator | TCP/IP Driver Layer Configurator | TCP/IP Basic Configurator | . Note: It is recommended to add the TCP/IP components using these configurators. When the components are added using configurators, the dependent modules will be auto-activated. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#add-tcpip-components",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#add-tcpip-components"
  },"91": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Application Layer Configurator",
    "content": ". | Under Available Components, Select the TCP/IP Application Layer Configurator and double click. This step will add the TCP/IP Application Layer Configurator inside the APPLICATION LAYER group. | This step also creates a hierarchy of groups as Root-&gt;TCP/IP STACK-&gt;APPLICATION LAYER. Verify the hierarchy by going View: dropdown and check out different layers. | If you changed the view, come back to APPLICATION LAYER view by using View: dropdown. | Select the TCP/IP Application Layer Configurator. See the configurations options on right hand side. The different application protocols supported in the Harmony TCP/IP stack are listed. Start selecting the required TCP/IP application layer protocols from the Configuration Options on right hand side. | For the Getting Started demo, select the DHCP CLIENT. This step will auto-activate all the dependent components. | Click Yes to add the Harmony Core component. | Click No to for the FreeRTOS auto-activation as this demo does not need the FreeRTOS. | Click Yes to add the TIME (sys_time) component. | Click Yes to add the CONSOLE (sys_console) component. | Click Yes to connect the CONSOLE component with TCP/IP CORE. | Click Yes to add the DEBUG (sys_debug) component. | Click Yes to connect the CONSOLE component with TCP/IP CORE. | Click Yes to add the IPv4 component in TCP/IP Network Layer. | Click Yes to add the ARP component in TCP/IP Network Layer. | Click Yes to add the UDP component in TCP/IP Transport Layer. After the auto-activation of dependent components, the DHCP CLIENT component is added to Project Graph . | Add the DNS CLIENT to APPLICATION LAYER . | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#application-layer-configurator",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#application-layer-configurator"
  },"92": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Transport Layer Configurator",
    "content": ". | Click on View: dropdown and go to the TRANSPORT LAYER. | Select the TCP/IP Transport Layer Configurator. UDP has been auto-activated while adding the Application Layer components. | Add the TCP protocol support for this demo. | Click Yes to add the TCP component in the TCP/IP Transport Layer . | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#transport-layer-configurator",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#transport-layer-configurator"
  },"93": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Network Layer Configurator",
    "content": ". | Click on View: dropdown and go to the NETWORK LAYER. | Select the TCP/IP Network Layer Configurator. | Add the ICMPv4 protocol support for this demo. | Click Yes to add the ICMPv4 component in the TCP/IP Network Layer . | Select ICMPv4 component in project graph to show its configuration settings in Configuration Options window. Enable checkbox for Use ICMPv4 Client. We need this to be able to ping other devices. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#network-layer-configurator",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#network-layer-configurator"
  },"94": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Driver Layer Configurator",
    "content": ". | Click on View: dropdown and go to the DRIVER LAYER. | Select the TCP/IP Driver Layer Configurator and enable WINC module checkbox. Click Yes to add the WINC component in the TCP/IP Driver Layer . | Click Yes to connect the WINC component with the NETCONFIG. | WINC component is added in the TCP/IP Driver Layer. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#driver-layer-configurator",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#driver-layer-configurator"
  },"95": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Basic Configuration",
    "content": ". | Click on View: dropdown and go to the Basic Configuration layer. | This layer contains TCP/IP stack’s core configuration,interface selection, heap management, MAC configuration, etc. Basic STACK Configuration and Network Configuration are already auto-activated, during previous steps. | Select the TCP/IP Basic Configurator and enable TCPIP CMD . | Click Yes to connect the CMD component with the SYS Console. | Command module is added to the Basic Configuration layer. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#basic-configuration",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#basic-configuration"
  },"96": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Satisfying Module Dependencies",
    "content": "The project needs few more Harmony components. In this section, we will add and configure the required components. | Click on View: dropdown and go to the Root layer. The Root layer will be as shown below. The red diamond-shaped buttons are unsatisfied mandatory dependencies. the connections might look messy at first. Feel free to move around some boxes so that project graph looks pretty. | . | Note: There are two ways to satisfy dependencies. You can either right-click on red diamonds and select available satisfiers OR you can manually add components from Avilable Components window and manually connect diamonds. Both ways are shown here. | . Satisfy Timer dependency: . | Right click on red diamond for TIME module. From the list of Satisfiers, select TC3. | Timer peripheral instance TC3 will be added to Root layer and connected to the TIMER module. | . Satisfy Console dependency: . | From Available Components &gt; Peripherals &gt; SERCOM &gt;, double-click on SERCOM2 to add it to current layer. | SERCOM2 is added to the Root layer. | To satisy Console UART dependency, manually connect UART diamond from SERCOM2 with the UART diamond of CONSOLE module. | Select SERCOM2 in the Project Graph. In the Configuration Options of SERCOM2, . | Set the TX Ring Buffer Size to 1024 | Set the Receive Pinout to PAD[1]. | . | . Satisfy TCP/IP Stack’s (i.e. WINC’s) SPI dependency: . | Right click on DRV_SPI red diamond of TCP/IP STACK module and select SPI as satisfier. | Right click on red diamond of SPI driver module and select SERCOM4. | Select SERCOM4 in the Project Graph. In the Configuration Options of SERCOM4, . | Set the Data IN pad to PAD[3] | Select Enable SPI Master Hardware Select checkbox. | . | . Satisfy Transport Layer LIB_CRYPTO Dependency: . | Click on View: dropdown and go to the Tranport layer. | Right click on LIB_CRYPTO of TCP and select Cryptographic Library from Available Satisfiers . | Right click on LIB_WOLFCRYPT of Cryptographic Library and select wolfCrypt Library from the list of Satisfiers. | The project graph will become: . | . Satisfy WINC’s External Interrupt dependency: . | From Available Components &gt; Peripherals &gt; EIC &gt;, double-click on EIC to add it to current Root layer. | Select EIC in the Project Graph. In the Configuration Options of EIC, . | Select Enable EIC channel 7. | Select Enable Interrupt | Set the Edge selection to Falling edge detection. | . | . All necessary dependencies are care of. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#satisfying-module-dependencies",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#satisfying-module-dependencies"
  },"97": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Project Heap Configuration",
    "content": ". | Select the System in the Project Graph. In Configuration Options, set the Heap Size (bytes) to 96960. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#project-heap-configuration",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#project-heap-configuration"
  },"98": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "WINC Driver Configuration",
    "content": ". | Click on View: dropdown and go to the DRIVER LAYER. | Select WINC module in project graph. In the Configuration Options window, select the Interrupt Source for WINC as recently enabled EIC Channel 7. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#winc-driver-configuration",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#winc-driver-configuration"
  },"99": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Pin Configuration",
    "content": "The I/O pins on the device can have alternate functions other than the general purpose I/O function. Here, we will configure the functionality of the I/O pins required for this demo. | Open MHC -&gt; Tools -&gt; Pin Configuration. | Configure the pins for EXT_INT7, SERCOM2, SERCOM4 and 2 GPIO as shown below. Notice the GPIO pins must have Custom Name as shown in the figure. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#pin-configuration",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#pin-configuration"
  },"100": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Code Generation",
    "content": "Once Harmony components are added using MHC to the Project Graph, it’s time to generate the source files based on the configurations. | Click Save button and Generate the code by clicking the Generate Code button (marked in red). | Select the Merge Strategy as USER ALL. Refer to the MHC documentation for different merge strategy options. | Click the Generate button to start the code generation. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#code-generation",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#code-generation"
  },"101": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Application Coding",
    "content": "Now, you have the MPLAB® Harmony components configured for a TCP/IP application. The Getting-Started demo implements a simple Wi-Fi STA application. This application is written using the APIs provided by the MPLAB® Harmony TCP/IP Stack. There is already a STA demo implemented at D:\\\\MH3\\wireless_apps_winc3400\\\\apps\\wifi_winc_sta_bypass. Let’s make use of those source files for the winc_bypass_getting_started demo. | Copy the application files (i.e. app.c, app.h) from D:\\\\MH3\\wireless_apps_winc3400\\\\apps\\wifi_winc_sta_bypass\\firmware\\\\src. | Paste the application files at our current project’s location. D:\\\\MH3\\wireless_apps_winc3400\\\\apps\\winc_bypass_getting_started\\firmware\\\\src. | In MPLAB® X IDE project, open the app.c file that has been added to project and change the access point parameters as shown in the picture below. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#application-coding",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#application-coding"
  },"102": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Build the Application",
    "content": ". | Open the project Properties by Right Clicking on the project name (winc_bypass_getting_started). Ensure that the XC32 Compiler Tool-chain and SAME54 EDBG hardware tool is selected. Press OK. | Build the application by clicking on the Build Main Project. | Verify the build results. Make sure that the build is successful. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#build-the-application",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#build-the-application"
  },"103": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Program the Application",
    "content": "Now, the project is ready to be programmed on the hardware board. Refer to the hardware user-guide to see the different programming options supported. The SAME54 Xplained board can be programmed using the on-board debugger EDBG. | Connect a micro-USB cable from computer to the DEBUG USB port on the SAM E54 Xplained Ultra board. | Program the application by clicking on the Make and Program Device Main Project. | Make sure that the programming is successful. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#program-the-application",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#program-the-application"
  },"104": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Test the Application",
    "content": "The testing of the application is done using different console commands. There will be a virtual COM port enumerated when a micro-USB cable from the computer is connected to the DEBUG USB port on SAM E54 Xplained Ultra board. | Open a terminal application (eg: TeraTerm) and configure the baud rate for 115200. | Press the Reset button on the SAM E54 Xplained Ultra board. | The following messages will be visible on the terminal window. | Type ping &lt;PC’s IP address&gt; in the terminal window and press Enter to see responses. | You can also ping this board from your PC using cmd prompt as shown below. | Currently, WINC driver is configured not to display any logs. You can change this setting in MHC by going to DRIVER LAYER and modifying the WINC configuration as shown below. | After re-generating and re-programming with logging turned on, you will see following output in tera term console. | . You have successfully created and tested your first WINC3400 Bypass mode Application. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#test-the-application",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#test-the-application"
  },"105": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "References",
    "content": ". | TCP/IP Stack Library Help | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#references",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html#references"
  },"106": {
    "doc": "Example project creation - WINC3400+SAME54 Bypass mode",
    "title": "Example project creation - WINC3400+SAME54 Bypass mode",
    "content": " ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html",
    "relUrl": "/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html"
  },"107": {
    "doc": "Firmware Upgrade of WINC Devices",
    "title": "WINC Devices – Integrated Serial Flash Memory Download Procedure",
    "content": "ATWINC1500/ATWINC3400 features an on-chip microcontroller and integrated SPI Flash memory for system firmware. The serial flash memory also stores the root certificate required for TLS/SSL connection and the gain table values used by transceiver. This application note explains in detail downloading procedure of firmware, certificate, and gain values into WINC serial flash through different supported serial interfaces like UART/I2C. This document also covers some useful troubleshooting tips for downloading failures. Features: . | Firmware download procedure | Root certificate download procedure | Gain table values download procedure | Troubleshooting tips | Common download procedure for WINC1500 and WINC3400 | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/winc_firmware_upgrade.html#winc-devices--integrated-serial-flash-memory-download-procedure",
    "relUrl": "/apps/getting_started/winc_firmware_upgrade.html#winc-devices--integrated-serial-flash-memory-download-procedure"
  },"108": {
    "doc": "Firmware Upgrade of WINC Devices",
    "title": "Introduction",
    "content": "The WINC1500 or WINC3400 firmware update project will be available in the path {local system path}\\wireless_wifi\\\\utilities\\wifi\\winc. The latest firmware update project contains the new firmware images as well as the batch script and Shell script files used to download the firmware into Wi-Fi Network Controller (WINC) through SPI/UART. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/winc_firmware_upgrade.html#introduction",
    "relUrl": "/apps/getting_started/winc_firmware_upgrade.html#introduction"
  },"109": {
    "doc": "Firmware Upgrade of WINC Devices",
    "title": "Firmware update project",
    "content": "The ATWINC1500 and ATWINC3400 WiFi devices require firmware to be loaded into flash memory. The ATWINC1500 and ATWINC3400 devices are preloaded with the firmware, however it would be useful to update the latest firmware to take advantage of fixes and new features. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/winc_firmware_upgrade.html#firmware-update-project",
    "relUrl": "/apps/getting_started/winc_firmware_upgrade.html#firmware-update-project"
  },"110": {
    "doc": "Firmware Upgrade of WINC Devices",
    "title": "Download wireless repository from Github",
    "content": "Install MPLAB® X Integrated Development Environment (IDE). After the installation, open the MPLAB IDE and launch H3 content manager from the IDE . Please provide the framework path with the local system path. This displays a new window as shown below. Using this window, user can download either all the packages or only the wireless packages with its required dependencies. To download the wireless packages and its dependencies: . | Scroll down and select wireless_wifi, wireless_apps_winc1500 and wireless_apps_winc3400. | Click Download Selected | . It requests permission to download its dependencies. Click OK . In the License Window . | Select Accept All License | Click Close | . Go to the local system path and check if the following packages are downloaded correctly . The firmware upgrade tool for WINC devices will be available in : {local system path}\\wireless_wifi\\\\utilities\\wifi\\winc . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/winc_firmware_upgrade.html#download-wireless-repository-from-github",
    "relUrl": "/apps/getting_started/winc_firmware_upgrade.html#download-wireless-repository-from-github"
  },"111": {
    "doc": "Firmware Upgrade of WINC Devices",
    "title": "Hardware Setup",
    "content": ". | SAM D21 Xplained Pro Evaluation Kit (ATSAMD21-XPRO) - SAMD21 is used as a HostMCU | ATWINC1500 / WINC3400 Xplained PRO Evaluation Kit (ATWINC1500-XPRO / ATWINC3400-XPRO) - Wi-Fi SPI slave device connected to SAMD21 HostMCU device | The ATWINC1500 / ATWINC3400 device is attached to EXT1 of the SAMD21 Xplained Pro kit. | Plug a micro-USB cable from Windows computer to the debug USB port of the SAM D21 Xplained Pro Evaluation kit . | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/winc_firmware_upgrade.html#hardware-setup",
    "relUrl": "/apps/getting_started/winc_firmware_upgrade.html#hardware-setup"
  },"112": {
    "doc": "Firmware Upgrade of WINC Devices",
    "title": "Serial Bridge Application",
    "content": "As the WINC device is connected to host MCU through SPI interface, upgrading the WINC serial flash via the host MCU would be an easier solution. Since, WINC provides transparent access to host MCU, the WINC serial flash can be read/written from host MCU. The host MCU can program the serial (SPI) flash without the need for operational firmware in the WINC. The host MCU running the serial bridge firmware is connected between computer and WINC SPI to download the firmware to WINC serial flash. winc_programmer_UART (PC) &lt;—-&gt; samd21_xplained_pro_serial_bridge.elf(Host) &lt;—-&gt; WINC SPI device . Serial Bridge Application for Harmony 3 . | Open MPLAB | Go to File Menu and select Open Project | In the next window, select the Serial bridge project from {local system path}\\wireless_wifi\\\\apps\\\\serial_bridge\\firmware and click Open Project . | Build the project | The click Make and Program Device button. | . Hardware Setup . | Power On Sequence . | • To perform a serial flash download using the ATWINC1500 built-in UART, it is mandatory that the ATWINC1500 chip is in the right bootloader state. | To do so, the HostMCU must power up the ATWINC1500 chip and then perform the reset sequence as defined in the ATWINC1500 datasheet | . | UART Pin Assignment . | Pin assignment of WINC1500 module UART are described in the following table. | On ATWINC1500 Xplained Pro, TX and RX are available on through holes labeled “DEBUG_UART” for easy identification. | . | ATWINC1500 module pin name | ATWINC1500 Xplained Pro pin name | Function | . | J14 | UART_TX | TXD | . | J19 | UART_RXD | RXD | . |   |   |   | . Ensure that the HostMCU is powered up and ATWINC1500 built-in UART is connected to PC via a serial to USB converter. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/winc_firmware_upgrade.html#serial-bridge-application",
    "relUrl": "/apps/getting_started/winc_firmware_upgrade.html#serial-bridge-application"
  },"113": {
    "doc": "Firmware Upgrade of WINC Devices",
    "title": "General Information on Firmware Update",
    "content": "The firmware upgrade tool for the WINC devices contains, . | Scripts | Binary Tools | . Scripts . The “winc” folder in {local system path}\\wireless_wifi\\\\utilities\\wifi path contains the following two scripts. | winc_flash_tool.cmd This script is for the firmware upgrade in Windows and it uses the “image_tool” and “winc_programmer_uart/i2c” to build and program the firmware binary image to the WINC devices. | winc_flash_tool.cmd Usage . | Usage | Command Example | . | To erase the entire flash | winc_flash_tool.cmd /p COM3 /d WINC3400 /v 1.4.2 /e | . | To create and program the Firmware Image | winc_flash_tool.cmd /p COM3 /d WINC3400 /v 1.4.2 /e /x /i prog /w | . | To create and program the All-in-one(AIO) Image | winc_flash_tool.cmd /p COM3 /d WINC3400 /v 1.4.2 /e /x /i aio /w | . | To create OTA Image | winc_flash_tool.cmd /p COM3 /d WINC3400 /v 1.4.2 /i ota | . | Writing to “Root certificate” region | winc_flash_tool.cmd /p COM3 /d WINC3400 /v 1.4.2 /e /x /i root /w | . | Writing to “HTTP files” region | winc_flash_tool.cmd /p COM3 /d WINC3400 /v 1.4.2 /e /x /i http /w | . | To read the entire flash | winc_flash_tool.cmd /p COM3 /d WINC3400 /v 1.4.2 /r | . |   |   | . | Arguments | Details | . | /p | Serial port for UART mode | . | /d | WINC device type | . | /s | Aardvark serial number | . | /v | Firmware version number | . | /e | Erase entire device before programming | . | /x | Read XO offset before creating programming image | . | /i | Image type:prog - Programmer formataio - All in one image, raw binary ota - OTAroot - Root certificates in programmer format http - HTTP files in programmer formatn | . | /w | Write to device | . | /f | Filename of image file to create | . | /r | Read entire flash from device | . |   |   | . | . | winc_flash_tool.sh This script is for the firmware upgrade in Linux and it uses the “image_tool” and “winc_programmer_uart/i2c” to build and program the firmware binary image to the WINC devices. | winc_flash_tool.sh Usage . | Usage | Command Example | . | To erase the entire flash | winc_flash_tool.cmd -p TTYS0 -d WINC3400 -v 1.4.2 -e | . | To create and program the Firmware Image | winc_flash_tool.cmd -p TTYS0 -d WINC3400 -v 1.4.2 -e -x -i prog -w | . | To create and program the All-in-one(AIO) Image | winc_flash_tool.cmd -p TTYS0 -d WINC3400 -v 1.4.2 -e -x i aio -w | . | To create OTA Image | winc_flash_tool.cmd -p TTYS0 -d WINC3400 -v 1.4.2 -i ota | . | Writing to “Root certificate” region | winc_flash_tool.cmd -p TTYS0 -d WINC3400 -v 1.4.2 -e -x -i root -w | . | Writing to “HTTP files” region | winc_flash_tool.cmd -p TTYS0 -d WINC3400 -v 1.4.2 -e -x -i http -w | . | To read the entire flash | winc_flash_tool.cmd -p TTYS0 -d WINC3400 -v 1.4.2 -r | . |   |   | . | Arguments | Details | . | -p | Serial port for UART mode | . | -d | WINC device type | . | -s | Aardvark serial number | . | -v | Firmware version number | . | -e | Erase entire device before programming | . | -x | Read XO offset before creating programming image | . | -i | Image type:prog - Programmer formataio - All in one image, raw binary ota - OTAroot - Root certificates in programmer format http - HTTP files in programmer formatn | . | -w | Write to device | . | -f | Filename of image file to create | . | -r | Read entire flash from device | . |   |   | . | . | . ATWINC1500/ATWINC3400 Binary Tools . The script files internally use the following tools to build and program the image. | image_tool - Builds firmware binary image | winc_programmer_uart/i2c – Program the built firmware binary image to the WINC device using UART or I2C interface. | . Building Firmware Image . | image_tool located in {local system path}\\wireless_wifi\\\\utilities\\wifi\\winc\\tools is used to build binary images for ATWINC devices. | It collects all the binaries for each section and combine it in to one firmware called wincXXXX_X.X.X.bin. | The image_tool arrange the section according to the flash memory orgianization of ATWINC1500/ATWINC3400 | The image_tool collects the information from the flash_image XML file. | Refer flash_image.config XML for how the flash memory is divided. | User needs to update the flash_image.config for updating the root certificate or adding custom provisioning pages | The configuration XML file(flash_image.config) can be found under {local system path}wireless_wifi\\\\utilities\\wifi\\winc\\files\\wincXXXX\\X.X.X directory | . image_tool Usage . | Usage | Command Example | . | To create firmware image | image_tool.exe -c 1.4.2\\flash_image.config -c gain_tables\\\\gain.config -o winc3400_1.4.2.bin -of prog | . | Writing to a specific region(eg: Root certificate) | image_tool.exe -c 1.4.2\\flash_image.config -c gain_tables\\\\gain.config winc3400_1.4.2.bin -of prog -r “root certificates” | . | To create OTA firmware image | image_tool.exe -c 1.4.2\\flash_image.config -o winc3400_1.4.2.bin -of winc_ota -s ota | . | To create OTA Image | winc_flash_tool.cmd -p TTYS0 -d WINC3400 -v 1.4.2 -i ota | . |   |   | . | Arguments | Details | . | -c | Configuration files Microchip recommends to use the default configuration files which is flash_image.config | . | -o | Output name of the binary image files ATWINC1500: winc1500_X.X.X.bin &lt;/br&gt; ATWINC3400: winc3400_X.X.X.bin | . | -of | The image_tool supports 4 output formats raw - Raw binary image. winc_ota - WINC OTA format.prog - Format suitable for programming.log - Textual log information | . | -r | Firmware version number | . | -e | Erase entire device before programming | . | -x | Read XO offset before creating programming image | . | -i | Image type:prog - Programmer formataio - All in one image, raw binary ota - OTAroot - Root certificates in programmer format http - HTTP files in programmer formatn | . | -w | Specifies a region to process.More than one region can be specified with repeated use of this option. If used only the regions specified will be processed. | . |   |   | . For more information, enter image_tool help command:image_tool -h . Commands Logs . | Creating Firmware Image | . Expected output log for the command: image_tool.exe -c 1.4.2\\flash_image.config -c gain_tables\\\\gain.config -o winc3400_1.4.2.bin -of prog . | Writing to a Specific Region | . Expected output log for the command: . image_tool.exe -c 1.4.2\\flash_image.config -c gain_tables\\\\gain.config winc3400_1.4.2.bin -of prog -r “root certificates” . | Creating OTA Firmware Image | . Expected output log for the command: . image_tool.exe -c 1.4.2\\flash_image.config -o winc3400_1.4.2.bin -of winc_ota -s ota . Programming Firmware Image . winc_programmer_uart/i2c tool located in src/firmware/firmware is used to program the binary images for ATWINC1500/ATWINC3400 devices using UART or I2C interface. it does the following primary jobs: . | Erase the ATWINC1500/ATWINC3400 memory | Read the firmware from ATWINC1500/ATWINC3400 | Write the firmware to ATWINC1500/ATWINC3400 | Verify the written firmware. | . winc_programmer_uart Tool Usage . | Usage | Command Example | . | Erase ATWINC1500/ATWINC3400 flash memory | winc_programmer_uart.exe -p COM16 -d winc3400 -e -pfw 1.4.2\\firmware\\\\programmer_firmware.bin | . | Write the created binary image to ATWINC1500/ATWINC3400 flash memory | winc_programmer_uart.exe -p COM16 -d winc3400 -i winc3400_1.4.2.bin -if prog -w -pfw 1.4.2\\firmware\\\\programmer_firmware.bin | . | Verify the written image in ATWINC1500/ATWINC3400 device | winc_programmer_uart.exe -p COM16 -d winc3400 -i winc3400_1.4.2.bin -if prog -r -pfw 1.4.2\\firmware\\\\programmer_firmware.bin | . | Single command (including all the above operations) | winc_programmer_UART.exe -p COM16 -d winc3400 -e -i winc3400_1.4.2.bin -if prog -w -r -pfw 1.4.2\\firmware\\\\programmer_firmware.bin | . |   |   | . | Arguments | Details | . | -p | Port number of the connected HostMCU COM Port Command to find the Port number: test_edbg | . | -d | ATWINC device: winc1500 or winc3400 | . | -e | To erase the ATWINC1500/ATWINC3400 device flash memory before writing the firmware image | . | -w | To write the firmware image | . | -r | To read the firmware image | . | -if | Input format. winc_ota - WINC OTA format.raw - A raw binary image.prog - Format suitable for programming. | . | -pfw | programming firmware : WINC firmware used to program the device. | . |   |   | . For more information enter winc_programmer_uart help command: winc_programmer_uart.exe -h . Commands logs . | Erase WINC memory . Expected output log for the command: winc_programmer_uart.exe -p COM16 -d winc3400 -e -pfw 1.4.2\\firmware\\\\programmer_firmware.bin . | Write Firmware Image to WINC Expected output log for the command: . winc_programmer_uart.exe -p COM16 -d winc3400 -i winc3400_1.4.2.bin -if prog -w -pfw 1.4.2\\firmware\\\\programmer_firmware.bin . | Read Firmware Image from WINC memory Expected output log for the Command: . winc_programmer_uart.exe -p COM16 -d winc3400 -r -pfw 1.4.2\\firmware\\\\programmer_firmware.bin . | Verify the Written Image Expected output log for the command: . winc_programmer_uart.exe -p COM16 -d winc3400 -i winc3400_1.4.2.bin -if prog -r -pfw 1.4.2\\firmware\\\\programmer_firmware.bin . | Consolidated Single Command This command does all the all the above operations in a single command. Expected output log for the command: . winc_programmer_UART.exe -p COM16 -d winc3400 -e -i winc3400_1.4.2.bin -if prog -w -r -pfw 1.4.2\\firmware\\\\programmer_firmware.bin . | . Download Failure Troubleshooting . Here are the troubleshooting tips for a specific error while downloading using batch script. | The script Failed To Find Any COM Port The winc_programmer_uart.exe expects a COM port as an argument. If the expected COM port is not found, then it will provide the below error. How to fix it: . | Make sure ATWINC1500/ATWINC3400 COM port is listed in the device manager. | Make sure ATWINC1500/ATWINC3400 COM port is not opened by any other application. For verification, try to open and close the COM port with a terminal application. | low quality USB cable or low quality serial to USB converter (built-in UART) can introduce garbage on the UART line thus failing the detection of the ATWINC1500/ATWINC3400 COM port. Try a different cable. | When performing a “built-in UART download”, it is expected that the ATWINC1500/ATWINC3400 bootloader is in a particular state that can only be achieved after doing a clean power up and reset sequence. Hence, before doing a download always ensure that a clean power up and reset sequence has been made. | Make sure that no other extension board (ex: IO1…) is connected to the Xplained Pro board while performing the download. | Make sure the project path is not exceeding Windows maximum 260 characters path length. | . | Failed To Initialize Programmer: Invalid Chip ID . The Failed to initialize programmer with Invalid chip ID error typically happens when there is garbage or noise on the UART line preventing from reading the correct chip ID value. How to fix it: . | Try connecting the PC and the ATWINC1500/ATWINC3400 with a different cable. A clean power up and reset sequence of the ATWINC1500/ATWINC3400 is necessary to start over with the ATWINC1500/ATWINC3400 bootloader in the appropriate state. | . | Failed To Initialize Programmer: Waiting For Chip Permission . After printing the correct chip ID of the ATWINC1500/ATWINC3400, the winc_programmer_UART tool programs a small binary (programmer firmware) to assist with ATWINC1500/ATWINC3400 flash programming. At this stage the winc_programmer_UART will change the UART baud rate from 115200 to 500000 to speed up the actual transfer of the firmware image. Once the baud rate change is made, the chip permission is verified to ensure the UART connection is reliable. Failing at this stage means that the current setup does not support such a high baud rate. How to fix it: . | It is recommended to try connecting the PC and the ATWINC1500/ATWINC3400 with a different cable. Also a clean power up and reset sequence of the ATWINC1500/ATWINC3400 is necessary to start over with the ATWINC1500/ATWINC3400 bootloader in the appropriate state. | . | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/winc_firmware_upgrade.html#general-information-on-firmware-update",
    "relUrl": "/apps/getting_started/winc_firmware_upgrade.html#general-information-on-firmware-update"
  },"114": {
    "doc": "Firmware Upgrade of WINC Devices",
    "title": "Firmware Upgrade of WINC Devices",
    "content": " ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/winc_firmware_upgrade.html",
    "relUrl": "/apps/getting_started/winc_firmware_upgrade.html"
  },"115": {
    "doc": "Example project creation - WINC3400+SAMD21 Socket mode",
    "title": "Example project creation - WINC Socket mode project with SAMD21",
    "content": "This document explains a step by step approach to create a WINC Socket mode project with SAMD21 host. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.html#example-project-creation---winc-socket-mode-project-with-samd21",
    "relUrl": "/apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.html#example-project-creation---winc-socket-mode-project-with-samd21"
  },"116": {
    "doc": "Example project creation - WINC3400+SAMD21 Socket mode",
    "title": "Hardware Setup",
    "content": "The document demonstrates the creation of a demo on the SAM D21 Xplained Pro board with the ATWINC1500 XPRO board. The SAMD21 Xplained PRO contains a built-in programmer-debugger tool called Embedded Debugger (EDBG) which is used in this tutorial. Following image shows the hardware setup. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.html#hardware-setup",
    "relUrl": "/apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.html#hardware-setup"
  },"117": {
    "doc": "Example project creation - WINC3400+SAMD21 Socket mode",
    "title": "Steps to create the new example project",
    "content": "Follow the below mwntioned steps to create the new WINC project in socket mode with SAMD21 from scratch. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.html#steps-to-create-the-new-example-project",
    "relUrl": "/apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.html#steps-to-create-the-new-example-project"
  },"118": {
    "doc": "Example project creation - WINC3400+SAMD21 Socket mode",
    "title": "Project Creation",
    "content": ". | Open MP Lab | Go to File Menu and select New Project… . | . Project Selection . | Under the Projects section, select 32bit MPLAB Harmony3 Project and click on Next. | . Framework Selection . | Enter the local system path where the packages are downloaded click Next. | . Project Settings . | Under {local system H3 path}\\wireless_apps_winc1500\\\\apps, create a folder name for the project (Ex: sample_project). | Enter the full path including the newly created project folder. | Enter the Folder name and Project name and click on Next (To know about “Folder” and “Name” please click “Show visual Help” button). | . Configuration Settings . | Enter a Name for the config setting folder | select the Target device name | Click Finish. | Click Launch once Configuration Database Setup windows pops up. | . MHC window and has three panes. | Available components: It lists all the components from downloaded packages. | Project Graph. It is where the user adds components from Available components | Configuration options. Each component in project graph can be configured using Configuration options. | . Adding components in MH3 . User should select required components for creating WINC project. Core . The first component to enable is Core because core is the base component for many drivers and system components. | Go to Harmony in the Available components | Select core. | Drag and drop it in the Project Graph. | This will ask permission to activate Free RTOS. Since this project does not require free RTOS, click No. | Core component appears in the Project Graph as shown below. | . SAMD21 Xplained pro component . This example uses SAMD21 xplained pro board for host development board. Enable component SAM D21 Xplained Pro BSP. | Go to Board Support Packages | select SAM D21 Xplained Pro BSP . | Drag and drop it in the Project Graph. | . Timer component . WINC driver needs driver for its delay functionality and user can select the any timer for this. To enable Timer . | Go to Harmony -&gt; System Services | Select TIME . | Drag and drop it in the Project Graph. | Right click on TMR in the TIME component | Go to Satisfiers and select TC3 (user can select any timer) . | This adds TC3 connected with TIME . | . EIC component . WINC device uses interrupt pin PB07. To configure PB07, EIC component must be enabled. | Go to Peripherals | Select EIC . | Drag and drop it in the Project Graph. | . Pin PB04 belongs to external interrupt channel 4 so EIC channel 4 has to be enabled and configured. | Select EIC in the Project Graph | Please do the following changes in the Configuration Options: . | Check Enable EIC channel4 box and expand EIC channel4 Configuration | Check Enable Interrupt box | Change Enable Interrupt4 Edge detection to Falling Edge detection | . | . Virtual Console . Virtual Console is used to send debug messages and to receive commands from user. Virtual console uses UART interface for communication. Host SAMD21 uses pins PA22 and PA23 for UART interface to perform receive and transmit operation, respectively. These two pins belong to SERCOM3 of the host SAMD21 device. For more information please refer section 5.4.2 (Virtual COM Port) of SAM D21 Xplained Pro User’s Guide . To enable and configure Virtual COM port: . | Go to System Services | Select CONSOLE . | Drag and drop it in the Project Graph. | . UART interface of SERCOM3 is used by CONSOLE. | Right click on the UART port of Instance 0 of the CONSOLE component. | Go to Satisfiers and select SERCOM3. | . SERCOM3 appears in Project Graph connected with CONSOLE. SERCOM3 uses PAD[1] for data reception. | Change the Receive pinout property to SERCOM PAD[1] in the Configuration Options | Change the TX ring buffer size of SERCOM3 configuration to “2048” . | . CONSOLE has a dependency on DEBUG and COMMAND component. To add DEBUG component . | Right click on the SYS_CONSOLE interface of Instance 0 of the CONSOLE component. | Go to Consumers and select DEBUG . | DEBUG component connected with CONSOLE appears in the Project Graph . | . To add COMMAND component . | Right click on the SYS_CONSOLE interface of Instance 0 of the CONSOLE component. | Go to Consumers and select COMMAND . | COMMAND component connected with CONSOLE appears in the Project Graph . | . SPI component . WINC communicates with host using SPI interface. So, to establish a SPI connection between WINC and host, three components are required. They are: . | SPI Driver | SERCOM0 (Peripheral library) | WINC Driver | . To enable SPI driver, . | In the Available Components, go to Harmony -&gt; Drivers. | Select SPI . | Drag and drop it in the Project Graph . | . Connect SERCOM0 with SPI driver. | Right click on the SPI interface of Instance 0 of the SPI component. | Go to Satisfiers and select SERCOM0 . | . SERCOM0 appears in Project Graph connected with SPI driver. Enable DMA for SPI driver . | Select instance 0 on SPI driver | Go to Configurations Options and enable Use DMA for Transmit and Receive . | SERCOM0 uses PAD[2] for Data out, PAD[3] for Clock and PAD[1] for Slave select. Change the SPI Data out Pad to the required Pad selection in the configuration options of SERCOM0 | Enable the property SPI Master Hardware Slave Select. | . WINC Component . Enable WINC Driver in the project: . | In the Available Components, go to Wireless | Select Driver -&gt; WINC . | Drag and drop it in the Project Graph. | Connect DRV_SPI interface of SPI interface 0 and WINC component . | . User has the option to select between WINC1500 and WINC3400 using the WINC Device configuration option. Enable Interrupt for WINC: . | In the configuration options for WINC, expand Interrupt Source | Select EIC channel 4 . | . WINC3400 BLE: . User can enable BLE option in WINC3400 as shown below. MHC PIN Configuration . This section summarizes the pin configuration requirement for MHC pin configuration component. In MHC, user can do pin configuration with the help of below steps . | Go to Tools in menu bar | Select Pin Configuration . | . The following window appears . The pin can be configured as shown below. | RESETN pin configuration: For WINC1500, . | Go to PB06 pin column | Change the function to GPIO | Name should be changed as “WDRV_WINC_RESETN” . | . For WINC3400, . | Go to PB01 pin column | Change the function to GPIO | Name should be changed as “WDRV_WINC_RESETN” . | . | Interrupt pin configuration: For both WINC1500 and WINC3400, . | Go to PB04 pin column | Select the function as EIC_EXTINT4 . | . | Chip enable pin configuration: For both WINC1500 and WINC3400, . | Go to PB05 of pin column | Change the function to GPIO | Name should be changed as “WDRV_WINC_CHIP_EN” . | . | SERCOM0 Pin configuration . | Go to PA04 pin column | Select the function as SERCOM0_PAD0 | Go to PA05 pin column | Select the function as SERCOM0_PAD1 | Go to PA06 pin column | Select the function as SERCOM0_PAD2 | Go to PA07 pin column | Select the function as SERCOM0_PAD3 . | . | SERCOM3 Pin configuration . | Go to PA22 pin column | Select the function as SERCOM3_PAD0 | Go to PA23 pin column | Select the function as SERCOM3_PAD1 . | . | . Save and generate code . To save the modifications . | Click Save Click Generate Code . | In the next window, click Generate . | . Application Code . With above component and pin configuration in MHC, user has required peripheral libraries and drivers for application development. User can follow the API guidelines to develop the application or follow the below step to create simple application for getting started. | Go to the path {local system path}\\wireless_apps_winc1500\\\\apps{User project name}\\firmware\\\\src. | app.c | app.h | example.c | . | Replace the following files with the files available in the AP scan example project {local system path}\\wireless_apps_winc1500\\\\apps\\\\ap_scan\\firmware\\\\src | As example.c file does not come with default project, create a new file called example.c under Source Files | Right click on Source Files | Select Add Existing Item . | Go to {local system path}\\wireless_apps_winc1500\\\\apps{User project name}\\firmware\\\\src | Select example.c . | In the file example.c, user can change the Home AP credentials. | . Build and program the device . To compile the project . | Right click on the project | Select Clean and Build . | . After successful build make sure SAME54 XPRO is connected with local system. | Right click again on the project | Select Make and Program Device. | . Output . Expected output . Note: If the user wants to create the project using the FrreRTOS, then follow the below mentioned steps. To add FreeRTOS component . | Select FreeRTOS from Thrid party Libraries -&gt; RTOS -&gt; FreeRTOS . | Drag and drop it in the Project Graph . | In the configuration options of FreeRTOS, change the Total heap size to 10000. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.html#project-creation",
    "relUrl": "/apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.html#project-creation"
  },"119": {
    "doc": "Example project creation - WINC3400+SAMD21 Socket mode",
    "title": "Example project creation - WINC3400+SAMD21 Socket mode",
    "content": " ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.html",
    "relUrl": "/apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.html"
  },"120": {
    "doc": "Example project creation - WINC3400+SAME54 Socket mode",
    "title": "Example project creation - WINC Socket mode project with SAME54",
    "content": "This document explains a step by step approach to create a WINC Socket mode project with SAME54 host. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.html#example-project-creation---winc-socket-mode-project-with-same54",
    "relUrl": "/apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.html#example-project-creation---winc-socket-mode-project-with-same54"
  },"121": {
    "doc": "Example project creation - WINC3400+SAME54 Socket mode",
    "title": "Hardware Setup",
    "content": "The document demonstrates the creation of a demo on the SAM E54 Xplained Pro board with the ATWINC1500 XPRO board. The SAME54 Xplained PRO contains a built-in programmer-debugger tool called Embedded Debugger (EDBG) which is used in this tutorial. Following image shows the hardware setup. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.html#hardware-setup",
    "relUrl": "/apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.html#hardware-setup"
  },"122": {
    "doc": "Example project creation - WINC3400+SAME54 Socket mode",
    "title": "Steps to create the new example project",
    "content": "Follow the below mwntioned steps to create the new WINC project in socket mode with SAME54 from scratch. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.html#steps-to-create-the-new-example-project",
    "relUrl": "/apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.html#steps-to-create-the-new-example-project"
  },"123": {
    "doc": "Example project creation - WINC3400+SAME54 Socket mode",
    "title": "Project Creation",
    "content": ". | Open MP Lab | Go to File Menu and select New Project… . | . Project Selection . | Under the Projects section, select 32bit MPLAB Harmony3 Project and click on Next. | . Framework Selection . | Enter the local system path where the packages are downloaded click Next. | . Project Settings . | Under {local system H3 path}\\wireless_apps_winc1500\\\\apps, create a folder name for the project (Ex: sample_project). | Enter the full path including the newly created project folder. | Enter the Folder name and Project name and click on Next (To know about “Folder” and “Name” please click “Show visual Help” button). | . Configuration Settings . | Enter a Name for the config setting folder | select the Target device name | Click Finish. | Click Launch once Configuration Database Setup windows pops up. | . MHC window and has three panes. | Available components: It lists all the components from downloaded packages. | Project Graph. It is where the user adds components from Available components | Configuration options. Each component in project graph can be configured using Configuration options. | . Adding components in MH3 . User should select required components for creating WINC project. Core . The first component to enable is Core because core is the base component for many drivers and system components. | Go to Harmony in the Available components | Select core. | Drag and drop it in the Project Graph. | This will ask permission to activate Free RTOS. Since this project does not require free RTOS, click No. | Core component appears in the Project Graph as shown below. | . SAME54 Xplained pro component . This example uses SAME54 xplained pro board for host development board. Enable component SAM E54 Xplained Pro BSP. | Go to Board Support Packages | select SAM E54 Xplained Pro BSP . | Drag and drop it in the Project Graph. | . Timer component . WINC driver needs driver for its delay functionality and user can select the any timer for this. To enable Timer . | Go to Harmony -&gt; System Services | Select TIME . | Drag and drop it in the Project Graph. | Right click on TMR in the TIME component | Go to Satisfiers and select TC3 (user can select any timer) . | This adds TC3 connected with TIME . | . EIC component . WINC device uses interrupt pin PB07. To configure PB07, EIC component must be enabled. | Go to Peripherals | Select EIC . | Drag and drop it in the Project Graph. | . Pin PB07 belongs to external interrupt channel 7 so EIC channel 7 has to be enabled and configured. | Select EIC in the Project Graph | Please do the following changes in the Configuration Options: . | Check Enable EIC channel4 box and expand EIC channel7 Configuration | Check Enable Interrupt box | Change Enable Interrupt7 Edge detection to Falling Edge detection | . | . Virtual Console . Virtual Console is used to send debug messages and to receive commands from user. Virtual console uses UART interface for communication. Host SAME54 uses pins PB24 and PB25 for UART interface to perform receive and transmit operation, respectively. These two pins belong to SERCOM2 of the host SAME54 device. For more information please refer section 5.4.2 (Virtual COM Port) of SAM E54 Xplained Pro User’s Guide . To enable and configure Virtual COM port: . | Go to System Services | Select CONSOLE . | Drag and drop it in the Project Graph. | . UART interface of SERCOM2 is used by CONSOLE. | Right click on the UART port of Instance 0 of the CONSOLE component. | Go to Satisfiers and select SERCOM2. | . SERCOM2 appears in Project Graph connected with CONSOLE. SERCOM2 uses PAD[1] for data reception. | Change the Receive pinout property to SERCOM PAD[1] in the Configuration Options . | . CONSOLE has a dependency on DEBUG and COMMAND component. To add DEBUG component . | Right click on the SYS_CONSOLE interface of Instance 0 of the CONSOLE component. | Go to Consumers and select DEBUG . | DEBUG component connected with CONSOLE appears in the Project Graph . | . To add COMMAND component . | Right click on the SYS_CONSOLE interface of Instance 0 of the CONSOLE component. | Go to Consumers and select COMMAND . | COMMAND component connected with CONSOLE appears in the Project Graph . | . SPI component . WINC communicates with host using SPI interface. So, to establish a SPI connection between WINC and host, three components are required. They are: . | SPI Driver | SERCOM4 (Peripheral library) | WINC Driver | . To enable SPI driver, . | In the Available Components, go to Harmony -&gt; Drivers. | Select SPI . | Drag and drop it in the Project Graph . | . Connect SERCOM4 with SPI driver. | Right click on the SPI interface of Instance 0 of the SPI component. | Go to Satisfiers and select SERCOM4 . | . SERCOM4 appears in Project Graph connected with SPI driver. ![](/wireless_apps_winc3400/apps/wifi_socket_demos/images/same54_32.png) . Enable DMA for SPI driver . | Select instance 0 on SPI driver | Go to Configurations Options and enable Use DMA for Transmit and Receive . | SERCOM4 uses PAD[3] for data reception. change the SPI Data In Pad selection property to SERCOM PAD[3] in the Configuration Options | Enable the property SPI Master Hardware Slave Select. | . WINC Component . Enable WINC Driver in the project: . | In the Available Components, go to Wireless | Select Driver -&gt; WINC . | Drag and drop it in the Project Graph. | Connect DRV_SPI interface of SPI interface 0 and WINC component . | . User has the option to select between WINC1500 and WINC3400 using the WINC Device configuration option. Enable Interrupt for WINC: . | In the configuration options for WINC, expand Interrupt Source | Select EIC channel 7 . | . WINC3400 BLE: . User can enable BLE option in WINC3400 as shown below. MHC PIN Configuration . This section summarizes the pin configuration requirement for MHC pin configuration component. In MHC, user can do pin configuration with the help of below steps . | Go to Tools in menu bar | Select Pin Configuration . | . The following window appears . The pin can be configured as shown below. | RESETN pin configuration: For WINC1500, . | Go to PA06 pin column | Change the function to GPIO | Name should be changed as “WDRV_WINC_RESETN” . | . For WINC3400, . | Go to PB05 pin column | Change the function to GPIO | Name should be changed as “WDRV_WINC_RESETN” . | . | Interrupt pin configuration: For both WINC1500 and WINC3400, . | Go to PB07 pin column | Select the function as EIC_EXTINT7 . | . | Chip enable pin configuration: For both WINC1500 and WINC3400, . | Go to PA27 of pin column | Change the function to GPIO | Name should be changed as “WDRV_WINC_CHIP_EN” . | . | BLE pin configuration: This configuration only applicable for WINC3400, | Go to PA04 pin column | Change the function to SERCOM0_PAD0 | Go to PA05 pin column | Change the function to SERCOM0_PAD1 | Go to PA06 pin column | Change the function to SERCOM0_PAD2 | Go to PA07 pin column | Change the function to SERCOM0_PAD3 . | SERCOM2 (COM Port) and SERCOM4 (SPI) pin configuration: For both WINC1500 and WINC3400, . | Go to PB24 pin column | Change the function to SERCOM2_PAD1 | Go to PB25 pin column | Change the function to SERCOM2_PAD0 | Go to PB26 pin column | Change the function to SERCOM4_PAD1 | Go to PB27 pin column | Change the function to SERCOM4_PAD0 | Go to PB28 pin column | Change the function to SERCOM4_PAD2 | Go to PB29 pin column | Change the function to SERCOM4_PAD3 . | . | . Save and generate code . To save the modifications . | Click Save Click Generate Code . | In the next window, click Generate . | . Application Code . With above component and pin configuration in MHC, user has required peripheral libraries and drivers for application development. User can follow the API guidelines to develop the application or follow the below step to create simple application for getting started. | Go to the path {local system path}\\wireless_apps_winc1500\\\\apps{User project name}\\firmware\\\\src. | app.c | app.h | example.c | . | Replace the following files with the files available in the AP scan example project {local system path}\\wireless_apps_winc1500\\\\apps\\\\ap_scan\\firmware\\\\src | As example.c file does not come with default project, create a new file called example.c under Source Files | Right click on Source Files | Select Add Existing Item | Go to {local system path}\\wireless_apps_winc1500\\\\apps{User project name}\\firmware\\\\src | Select example.c | In the file example.c, user can change the Home AP credentials. | . Build and program the device . To compile the project . | Right click on the project | Select Clean and Build . | . After successful build make sure SAME54 XPRO is connected with local system. | Right click again on the project | Select Make and Program Device. | . Output . Expected output . Note: If the user wants to create the project using the FrreRTOS, then follow the below mentioned steps. To add FreeRTOS component . | Select FreeRTOS from Thrid party Libraries -&gt; RTOS -&gt; FreeRTOS . | Drag and drop it in the Project Graph . | In the configuration options of FreeRTOS, change the Total heap size to 10000. | . ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.html#project-creation",
    "relUrl": "/apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.html#project-creation"
  },"124": {
    "doc": "Example project creation - WINC3400+SAME54 Socket mode",
    "title": "Example project creation - WINC3400+SAME54 Socket mode",
    "content": " ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.html",
    "relUrl": "/apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.html"
  },"125": {
    "doc": "Supported Network Modes in WINC",
    "title": "Supported Network Modes in WINC",
    "content": "WINC devices can work in two modes. | Socket mode | Bypass mode. | . Socket Mode . By default, WINC firmware includes TCP/ IP Stack, and Wifi/ BT MAC. Socket Mode exports driver level APIs for the User to write his Application and configure / communicate the TCP/ IP Stack and the Wi-Fi Stack using these APIs. Bypass Mode . In Bypass mode, instead of using TCP/IP stack of WINC firmware, user can use Harmony 3 TCP/IP stack on host side and directly access mac layer of WINC firmware via the WINC Driver APIs. In this case TCP/IP stack of WINC firmware is bypassed. ",
    "url": "http://localhost:4000/wireless_apps_winc3400/apps/getting_started/winc_supported_modes.html",
    "relUrl": "/apps/getting_started/winc_supported_modes.html"
  },"126": {
    "doc": "Harmony 3 Wireless application examples for WINC3400",
    "title": "Harmony 3 Wireless application examples for WINC3400",
    "content": "[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com) # Harmony 3 Wireless application examples for WINC3400 MPLAB® Harmony 3 is an extension of the MPLAB® ecosystem for creating embedded firmware solutions for Microchip 32-bit SAM and PIC® microcontroller and microprocessor devices. Refer to the following links for more information. - [Microchip 32-bit MCUs](https://www.microchip.com/design-centers/32-bit) - [Microchip 32-bit MPUs](https://www.microchip.com/design-centers/32-bit-mpus) - [Microchip MPLAB X IDE](https://www.microchip.com/mplab/mplab-x-ide) - [Microchip MPLAB® Harmony](https://www.microchip.com/mplab/mplab-harmony) - [Microchip MPLAB® Harmony Pages](https://microchip-mplab-harmony.github.io/) This repository contains the MPLAB® Harmony 3 Wireless application examples for WINC3400 - [Release Notes](/wireless_apps_winc3400/release_notes.html) - [MPLAB® Harmony License](/wireless_apps_winc3400/mplab_harmony_license.html) To clone or download these applications from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400) and then click **Clone** button to clone this repository or download as zip file. This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki). ## Contents Summary | Folder | Description | --- | --- | apps | Contains Wireless service example applications. | docs | Contains documentation in html format for offline viewing (to be used only after cloning this repository onto a local machine). Use [github pages](https://microchip-mplab-harmony.github.io/wireless_apps_winc3400/) of this repository for viewing it online. | ## Code Examples The following applications are provided to demonstrate the typical or interesting usage models of one or more wireless usecases. | Name | Description | ---- | ----------- |[AP Scan (Socket mode)](/wireless_apps_winc3400/apps/ap_scan/readme.html)|Demonstrates scan of near by HomeAP’s and connects to configured HomeAP|[TCP Client (Socket mode)](/wireless_apps_winc3400/apps/tcp_client/readme.html)|Demonstrates WINC3400 TCP Client example application|[TCP Server (Socket mode) ](/wireless_apps_winc3400/apps/wifi_tcp_server_in_softap/readme.html)|Demonstrates WINC3400 TCP Server example application|[Wi-Fi Provisioning using SoftAP (Socket mode)](/wireless_apps_winc3400/apps/wifi_provisioning_via_softap/readme.html)|Demonstrates WINC3400 HomeAP Provisioning using SoftAP |[Wi-Fi Provisioning using WPS (Socket mode)](/wireless_apps_winc3400/apps/wifi_provisioning_via_wps/readme.html)|Demonstrates WINC3400 HomeAP Provisioning using WPS|[Wi-Fi Provisioning using BLE (Socket mode)](/wireless_apps_winc3400/apps/wifi_provision_via_ble/readme.html)|Demonstrates WINC3400 HomeAP Provisioning using BLE|[Wi-Fi STA (Bypass/Ethernet mode)](/wireless_apps_winc3400/apps/wifi_winc_sta_bypass/readme.html)|Demonstrates WINC3400 STA Bypass\\Ethenet mode application|[Power Save Mode](/wireless_apps_winc3400/apps/power_save_mode_example/readme.html)|Demonstrates WINC3400 low power modes|[Wi-Fi Bypass Mode Demos](/wireless_apps_winc3400/apps/wifi_bypass_demos/readme.html)|Demonstrates the below WINC3400 applications in Bypass Mode. WiFi station mode/Access point mode demo SSL Demo Ping Demo Iperf Demo SNTP Demo MQTT Demo WiFi Provisioning Demo|[Wi-Fi Socket Mode Demos](/wireless_apps_winc3400/apps/wifi_socket_demos/readme.html)|Demonstrates the below WINC3400 applications in Socket Mode. WiFi station mode/Access point mode demo SSL Demo Ping Demo Iperf Demo SNTP Demo MQTT Demo OTA Demo WiFi Provisioning Demo WiFi Provisioning via BLE Custom serial Chat Demo Heart Rate Profile Demo Battery Service Demo Proximity Reporter Demo Transparent Service Demo Certificate Download OTA Demo | ## Documentation | Mode | Document| Description | ---- | ---- |--- | | [Create WINC Project - Getting Started](/wireless_apps_winc3400/apps/getting_started/create_winc_project_from_scratch.html) | This is a getting-started guide for MPLABX IDE | | [Firmware Upgrade of WINC Devices ](/wireless_apps_winc3400/apps/getting_started/winc_firmware_upgrade.html) | This document explains in detail downloading procedure of firmware, certificate, and gain values into WINC serial flash through different supported serial interfaces like UART/I2C. | | [Supported Modes In WINC devices](/wireless_apps_winc3400/apps/getting_started/winc_supported_modes.html) | Describes the supported modes in WINC devices |Socket Mode| [WINC3400+SAMD21](/wireless_apps_winc3400/apps/wifi_socket_demos/winc_samd21_socketmode_from_scratch.html)| This document explains a step by step approach to create a WINC3400 Socket mode project with SAMD21 host.|Socket Mode|[WINC3400+SAME54](/wireless_apps_winc3400/apps/wifi_socket_demos/winc_same54_socketmode_from_scratch.html)|This document explains a step by step approach to create a WINC3400 Socket mode project with SAME54 host.|Bypass Mode|[WINC3400+SAME54](/wireless_apps_winc3400/apps/wifi_bypass_demos/winc3400_same54_bypassmode_from_scratch.html)|This document explains a step by step approach to create a WINC3400 Bypass mode project with SAME54 host. | ____ [![License](https://img.shields.io/badge/license-Harmony%20license-orange.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/blob/master/mplab_harmony_license.md) [![Latest release](https://img.shields.io/github/release/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/releases/latest) [![Latest release date](https://img.shields.io/github/release-date/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/releases/latest) [![Commit activity](https://img.shields.io/github/commit-activity/y/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_winc3400/graphs/commit-activity) [![Contributors](https://img.shields.io/github/contributors-anon/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg)]() ____ [![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/user/MicrochipTechnology) [![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/microchip-technology) [![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/microchiptechnology/) [![Follow us on Twitter](https://img.shields.io/twitter/follow/MicrochipTech.svg?style=social)](https://twitter.com/MicrochipTech) [![](https://img.shields.io/github/stars/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg?style=social)]() [![](https://img.shields.io/github/watchers/Microchip-MPLAB-Harmony/wireless_apps_winc3400.svg?style=social)]() ",
    "url": "http://localhost:4000/wireless_apps_winc3400/",
    "relUrl": "/"
  }
}
`;
var data_for_search

var repo_name = "wireless_apps_winc3400";
var doc_folder_name = "docs";
var localhost_path = "http://localhost:4000/";
var home_index_string = "Wireless WINC3400 Applications";

(function (jtd, undefined) {

// Event handling

jtd.addEvent = function(el, type, handler) {
  if (el.attachEvent) el.attachEvent('on'+type, handler); else el.addEventListener(type, handler);
}
jtd.removeEvent = function(el, type, handler) {
  if (el.detachEvent) el.detachEvent('on'+type, handler); else el.removeEventListener(type, handler);
}
jtd.onReady = function(ready) {
  // in case the document is already rendered
  if (document.readyState!='loading') ready();
  // modern browsers
  else if (document.addEventListener) document.addEventListener('DOMContentLoaded', ready);
  // IE <= 8
  else document.attachEvent('onreadystatechange', function(){
      if (document.readyState=='complete') ready();
  });
}

// Show/hide mobile menu

function initNav() {
  jtd.addEvent(document, 'click', function(e){
    var target = e.target;
    while (target && !(target.classList && target.classList.contains('nav-list-expander'))) {
      target = target.parentNode;
    }
    if (target) {
      e.preventDefault();
      target.parentNode.classList.toggle('active');
    }
  });

  const siteNav = document.getElementById('site-nav');
  const mainHeader = document.getElementById('main-header');
  const menuButton = document.getElementById('menu-button');

  jtd.addEvent(menuButton, 'click', function(e){
    e.preventDefault();

    if (menuButton.classList.toggle('nav-open')) {
      siteNav.classList.add('nav-open');
      mainHeader.classList.add('nav-open');
    } else {
      siteNav.classList.remove('nav-open');
      mainHeader.classList.remove('nav-open');
    }
  });
}
// Site search

function initSearch() {

    data_for_search = JSON.parse(myVariable);
    lunr.tokenizer.separator = /[\s/]+/

    var index = lunr(function () {
        this.ref('id');
        this.field('title', { boost: 200 });
        this.field('content', { boost: 2 });
        this.field('url');
        this.metadataWhitelist = ['position']

        var location = document.location.pathname;
        var path = location.substring(0, location.lastIndexOf("/"));
        var directoryName = path.substring(path.lastIndexOf("/")+1);

        var cur_path_from_repo = path.substring(path.lastIndexOf(repo_name));

        // Decrement depth by 2 as HTML files are placed in repo_name/doc_folder_name
        var cur_depth_from_doc_folder = (cur_path_from_repo.split("/").length - 2);

        var rel_path_to_doc_folder = "";

        if (cur_depth_from_doc_folder == 0) {
            rel_path_to_doc_folder = "./"
        }
        else {
            for (var i = 0; i < cur_depth_from_doc_folder; i++)
            {
                rel_path_to_doc_folder = rel_path_to_doc_folder + "../"
            }
        }

        for (var i in data_for_search) {

            data_for_search[i].url = data_for_search[i].url.replace(localhost_path + repo_name, rel_path_to_doc_folder);

            if (data_for_search[i].title == home_index_string)
            {
                data_for_search[i].url = data_for_search[i].url + "index.html"
            }

            this.add({
                id: i,
                title: data_for_search[i].title,
                content: data_for_search[i].content,
                url: data_for_search[i].url
            });
        }
    });

    searchLoaded(index, data_for_search);
}function searchLoaded(index, docs) {
  var index = index;
  var docs = docs;
  var searchInput = document.getElementById('search-input');
  var searchResults = document.getElementById('search-results');
  var mainHeader = document.getElementById('main-header');
  var currentInput;
  var currentSearchIndex = 0;

  function showSearch() {
    document.documentElement.classList.add('search-active');
  }

  function hideSearch() {
    document.documentElement.classList.remove('search-active');
  }

  function update() {
    currentSearchIndex++;

    var input = searchInput.value;
    if (input === '') {
      hideSearch();
    } else {
      showSearch();
      // scroll search input into view, workaround for iOS Safari
      window.scroll(0, -1);
      setTimeout(function(){ window.scroll(0, 0); }, 0);
    }
    if (input === currentInput) {
      return;
    }
    currentInput = input;
    searchResults.innerHTML = '';
    if (input === '') {
      return;
    }

    var results = index.query(function (query) {
      var tokens = lunr.tokenizer(input)
      query.term(tokens, {
        boost: 10
      });
      query.term(tokens, {
        wildcard: lunr.Query.wildcard.TRAILING
      });
    });

    if ((results.length == 0) && (input.length > 2)) {
      var tokens = lunr.tokenizer(input).filter(function(token, i) {
        return token.str.length < 20;
      })
      if (tokens.length > 0) {
        results = index.query(function (query) {
          query.term(tokens, {
            editDistance: Math.round(Math.sqrt(input.length / 2 - 1))
          });
        });
      }
    }

    if (results.length == 0) {
      var noResultsDiv = document.createElement('div');
      noResultsDiv.classList.add('search-no-result');
      noResultsDiv.innerText = 'No results found';
      searchResults.appendChild(noResultsDiv);

    } else {
      var resultsList = document.createElement('ul');
      resultsList.classList.add('search-results-list');
      searchResults.appendChild(resultsList);

      addResults(resultsList, results, 0, 10, 100, currentSearchIndex);
    }

    function addResults(resultsList, results, start, batchSize, batchMillis, searchIndex) {
      if (searchIndex != currentSearchIndex) {
        return;
      }
      for (var i = start; i < (start + batchSize); i++) {
        if (i == results.length) {
          return;
        }
        addResult(resultsList, results[i]);
      }
      setTimeout(function() {
        addResults(resultsList, results, start + batchSize, batchSize, batchMillis, searchIndex);
      }, batchMillis);
    }

    function addResult(resultsList, result) {
      var doc = docs[result.ref];

      var resultsListItem = document.createElement('li');
      resultsListItem.classList.add('search-results-list-item');
      resultsList.appendChild(resultsListItem);

      var resultLink = document.createElement('a');
      resultLink.classList.add('search-result');
      resultLink.setAttribute('href', doc.url);
      resultsListItem.appendChild(resultLink);

      var resultTitle = document.createElement('div');
      resultTitle.classList.add('search-result-title');
      resultLink.appendChild(resultTitle);

      var resultDoc = document.createElement('div');
      resultDoc.classList.add('search-result-doc');
      resultDoc.innerHTML = '<svg viewBox="0 0 24 24" class="search-result-icon"><use xlink:href="#svg-doc"></use></svg>';
      resultTitle.appendChild(resultDoc);

      var resultDocTitle = document.createElement('div');
      resultDocTitle.classList.add('search-result-doc-title');
      resultDocTitle.innerHTML = doc.doc;
      resultDoc.appendChild(resultDocTitle);
      var resultDocOrSection = resultDocTitle;

      if (doc.doc != doc.title) {
        resultDoc.classList.add('search-result-doc-parent');
        var resultSection = document.createElement('div');
        resultSection.classList.add('search-result-section');
        resultSection.innerHTML = doc.title;
        resultTitle.appendChild(resultSection);
        resultDocOrSection = resultSection;
      }

      var metadata = result.matchData.metadata;
      var titlePositions = [];
      var contentPositions = [];
      for (var j in metadata) {
        var meta = metadata[j];
        if (meta.title) {
          var positions = meta.title.position;
          for (var k in positions) {
            titlePositions.push(positions[k]);
          }
        }
        if (meta.content) {
          var positions = meta.content.position;
          for (var k in positions) {
            var position = positions[k];
            var previewStart = position[0];
            var previewEnd = position[0] + position[1];
            var ellipsesBefore = true;
            var ellipsesAfter = true;
            for (var k = 0; k < 5; k++) {
              var nextSpace = doc.content.lastIndexOf(' ', previewStart - 2);
              var nextDot = doc.content.lastIndexOf('. ', previewStart - 2);
              if ((nextDot >= 0) && (nextDot > nextSpace)) {
                previewStart = nextDot + 1;
                ellipsesBefore = false;
                break;
              }
              if (nextSpace < 0) {
                previewStart = 0;
                ellipsesBefore = false;
                break;
              }
              previewStart = nextSpace + 1;
            }
            for (var k = 0; k < 10; k++) {
              var nextSpace = doc.content.indexOf(' ', previewEnd + 1);
              var nextDot = doc.content.indexOf('. ', previewEnd + 1);
              if ((nextDot >= 0) && (nextDot < nextSpace)) {
                previewEnd = nextDot;
                ellipsesAfter = false;
                break;
              }
              if (nextSpace < 0) {
                previewEnd = doc.content.length;
                ellipsesAfter = false;
                break;
              }
              previewEnd = nextSpace;
            }
            contentPositions.push({
              highlight: position,
              previewStart: previewStart, previewEnd: previewEnd,
              ellipsesBefore: ellipsesBefore, ellipsesAfter: ellipsesAfter
            });
          }
        }
      }

      if (titlePositions.length > 0) {
        titlePositions.sort(function(p1, p2){ return p1[0] - p2[0] });
        resultDocOrSection.innerHTML = '';
        addHighlightedText(resultDocOrSection, doc.title, 0, doc.title.length, titlePositions);
      }

      if (contentPositions.length > 0) {
        contentPositions.sort(function(p1, p2){ return p1.highlight[0] - p2.highlight[0] });
        var contentPosition = contentPositions[0];
        var previewPosition = {
          highlight: [contentPosition.highlight],
          previewStart: contentPosition.previewStart, previewEnd: contentPosition.previewEnd,
          ellipsesBefore: contentPosition.ellipsesBefore, ellipsesAfter: contentPosition.ellipsesAfter
        };
        var previewPositions = [previewPosition];
        for (var j = 1; j < contentPositions.length; j++) {
          contentPosition = contentPositions[j];
          if (previewPosition.previewEnd < contentPosition.previewStart) {
            previewPosition = {
              highlight: [contentPosition.highlight],
              previewStart: contentPosition.previewStart, previewEnd: contentPosition.previewEnd,
              ellipsesBefore: contentPosition.ellipsesBefore, ellipsesAfter: contentPosition.ellipsesAfter
            }
            previewPositions.push(previewPosition);
          } else {
            previewPosition.highlight.push(contentPosition.highlight);
            previewPosition.previewEnd = contentPosition.previewEnd;
            previewPosition.ellipsesAfter = contentPosition.ellipsesAfter;
          }
        }

        var resultPreviews = document.createElement('div');
        resultPreviews.classList.add('search-result-previews');
        resultLink.appendChild(resultPreviews);

        var content = doc.content;
        for (var j = 0; j < Math.min(previewPositions.length, 3); j++) {
          var position = previewPositions[j];

          var resultPreview = document.createElement('div');
          resultPreview.classList.add('search-result-preview');
          resultPreviews.appendChild(resultPreview);

          if (position.ellipsesBefore) {
            resultPreview.appendChild(document.createTextNode('... '));
          }
          addHighlightedText(resultPreview, content, position.previewStart, position.previewEnd, position.highlight);
          if (position.ellipsesAfter) {
            resultPreview.appendChild(document.createTextNode(' ...'));
          }
        }
      }
      var resultRelUrl = document.createElement('span');
      resultRelUrl.classList.add('search-result-rel-url');
      resultRelUrl.innerText = doc.relUrl;
      resultTitle.appendChild(resultRelUrl);
    }

    function addHighlightedText(parent, text, start, end, positions) {
      var index = start;
      for (var i in positions) {
        var position = positions[i];
        var span = document.createElement('span');
        span.innerHTML = text.substring(index, position[0]);
        parent.appendChild(span);
        index = position[0] + position[1];
        var highlight = document.createElement('span');
        highlight.classList.add('search-result-highlight');
        highlight.innerHTML = text.substring(position[0], index);
        parent.appendChild(highlight);
      }
      var span = document.createElement('span');
      span.innerHTML = text.substring(index, end);
      parent.appendChild(span);
    }
  }

  jtd.addEvent(searchInput, 'focus', function(){
    setTimeout(update, 0);
  });

  jtd.addEvent(searchInput, 'keyup', function(e){
    switch (e.keyCode) {
      case 27: // When esc key is pressed, hide the results and clear the field
        searchInput.value = '';
        break;
      case 38: // arrow up
      case 40: // arrow down
      case 13: // enter
        e.preventDefault();
        return;
    }
    update();
  });

  jtd.addEvent(searchInput, 'keydown', function(e){
    switch (e.keyCode) {
      case 38: // arrow up
        e.preventDefault();
        var active = document.querySelector('.search-result.active');
        if (active) {
          active.classList.remove('active');
          if (active.parentElement.previousSibling) {
            var previous = active.parentElement.previousSibling.querySelector('.search-result');
            previous.classList.add('active');
          }
        }
        return;
      case 40: // arrow down
        e.preventDefault();
        var active = document.querySelector('.search-result.active');
        if (active) {
          if (active.parentElement.nextSibling) {
            var next = active.parentElement.nextSibling.querySelector('.search-result');
            active.classList.remove('active');
            next.classList.add('active');
          }
        } else {
          var next = document.querySelector('.search-result');
          if (next) {
            next.classList.add('active');
          }
        }
        return;
      case 13: // enter
        e.preventDefault();
        var active = document.querySelector('.search-result.active');
        if (active) {
          active.click();
        } else {
          var first = document.querySelector('.search-result');
          if (first) {
            first.click();
          }
        }
        return;
    }
  });

  jtd.addEvent(document, 'click', function(e){
    if (e.target != searchInput) {
      hideSearch();
    }
  });
}

// Switch theme

jtd.getTheme = function() {
  var cssFileHref = document.querySelector('[rel="stylesheet"]').getAttribute('href');
  return cssFileHref.substring(cssFileHref.lastIndexOf('-') + 1, cssFileHref.length - 4);
}

jtd.setTheme = function(theme) {
  var cssFile = document.querySelector('[rel="stylesheet"]');
  cssFile.setAttribute('href', 'http://localhost:4000/wireless_apps_winc3400/assets/css/just-the-docs-' + theme + '.css');
}

// Document ready

jtd.onReady(function(){
  initNav();
  initSearch();
});

})(window.jtd = window.jtd || {});


