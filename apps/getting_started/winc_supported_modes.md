---
parent: Harmony 3 Wireless application examples for WINC3400
title: Supported Network Modes in WINC
has_toc: true
has_children: false
has_toc: false
nav_order: 1

family: SAME54
family: SAMD21
function: Supported Network Modes in WINC
---

# Supported Network Modes in WINC

WINC devices can work in two modes.
* Socket mode
* Bypass mode.
 
### Socket Mode

By default, WINC firmware includes TCP/ IP Stack, and Wifi/ BT MAC.<br>
Socket Mode exports driver level APIs for the User to write his Application and configure / communicate the TCP/ IP Stack and the Wi-Fi Stack using these APIs.

![](images/socket_mode.png)

### Bypass Mode

 In Bypass mode, instead of using TCP/IP stack of WINC firmware, user can use Harmony 3 TCP/IP stack on host side and directly access mac layer of WINC firmware via the WINC Driver APIs. In this case TCP/IP stack of WINC firmware is bypassed.

   ![](images/bypass_mode.png)
 
 
  

