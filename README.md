# AsyncUDP_STM32


[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncUDP_STM32.svg?)](https://www.ardu-badge.com/AsyncUDP_STM32)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncUDP_STM32.svg)](https://github.com/khoih-prog/AsyncUDP_STM32/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/AsyncUDP_STM32/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncUDP_STM32.svg)](http://github.com/khoih-prog/AsyncUDP_STM32/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents

* [Important Change from v1.3.0](#Important-Change-from-v130)
* [Why do we need this AsyncUDP_STM32 library](#why-do-we-need-this-asyncudp_stm32-library)
  * [Features](#features)
  * [Why Async is better](#why-async-is-better)
  * [Currently supported Boards](#currently-supported-boards)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For STM32 boards to use LAN8720](#1-for-stm32-boards-to-use-lan8720)
  * [2. For STM32 boards to use Serial1](#2-for-stm32-boards-to-use-serial1)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [HOWTO Setting up the Async UDP Client](#howto-setting-up-the-async-udp-client)
* [HOWTO use STM32F4 with LAN8720](#howto-use-stm32f4-with-lan8720)
  * [1. Wiring](#1-wiring)
  * [2. HOWTO program using STLink V-2 or V-3](#2-howto-program-using-stlink-v-2-or-v-3)
  * [3. HOWTO use Serial Port for Debugging](#3-howto-use-serial-port-for-debugging)
* [Examples](#examples)
  * [ 1. AsyncUDPClient](examples/AsyncUDPClient)
  * [ 2. AsyncUdpNTPClient](examples/AsyncUdpNTPClient)
  * [ 3. AsyncUdpSendReceive](examples/AsyncUdpSendReceive)
  * [ 4. AsyncUDPServer](examples/AsyncUDPServer)
  * [ 5. AsyncUDPMulticastServer](examples/AsyncUDPMulticastServer)
  * [ 6. AsyncUDPClient_LAN8720](examples/AsyncUDPClient_LAN8720)
  * [ 7. AsyncUdpNTPClient_LAN8720](examples/AsyncUdpNTPClient_LAN8720)
  * [ 8. AsyncUdpSendReceive_LAN8720](examples/AsyncUdpSendReceive_LAN8720)
  * [ 9. AsyncUDPServer_LAN8720](examples/AsyncUDPServer_LAN8720)
  * [10. AsyncUDPMulticastServer_LAN8720](examples/AsyncUDPMulticastServer_LAN8720)
  * [11. **multiFileProject**](examples/multiFileProject) **New**
  * [12. **multiFileProject_LAN8720**](examples/multiFileProject_LAN8720) **New**
* [Example AsyncUdpNTPClient](#example-asyncudpntpclient)
  * [1. File AsyncUdpNTPClient.ino](#1-file-asyncudpntpclientino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. AsyncUdpNTPClient on STM32F7 NUCLEO_F767ZI with LAN8742A Ethernet using STM32Ethernet Library](#1-asyncudpntpclient-on-stm32f7-nucleo_f767zi-with-lan8742a-ethernet-using-stm32ethernet-library)
  * [2. AsyncUdpNTPClient_LAN8720 on STM32F4 BLACK_F407VE with LAN8720 Ethernet using STM32Ethernet Library](#2-asyncudpntpclient_lan8720-on-stm32f4-black_f407ve-with-lan8720-ethernet-using-stm32ethernet-library)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Change from v1.3.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)

For `Generic STM32F4 series` boards, such as STM32F407VE, using LAN8720, please use STM32 core v2.2.0 as breaking core v2.3.0 creates the compile error. Will fix in the near future.

---
---

### Why do we need this [AsyncUDP_STM32 library](https://github.com/khoih-prog/AsyncUDP_STM32)

#### Features

This [AsyncUDP_STM32 library](https://github.com/khoih-prog/AsyncUDP_STM32) is a fully asynchronous UDP library, designed for a trouble-free, multi-connection network environment, for STM32 boards using LAN8720 or builtin LAN8742A Ethernet. The library is easy to use and includes support for Unicast, Broadcast and Multicast environments.

This library is based on, modified from:

1. [Hristo Gochkov's ESPAsyncUDP](https://github.com/me-no-dev/ESPAsyncUDP)

to apply the better and faster **asynchronous** feature of the **powerful** [ESPAsyncUDP Library](https://github.com/me-no-dev/ESPAsyncUDP) into STM32 boards using LAN8720 or builtin LAN8742A Ethernet.


#### Why Async is better

- Using asynchronous network means that you can handle **more than one connection at the same time**
- You are called once the request is ready and parsed
- When you send the response, you are **immediately ready** to handle other connections while the server is taking care of sending the response in the background
- **Speed is OMG**
- After connecting to a UDP server as an Async Client, you are **immediately ready** to handle other connections while the Client is taking care of receiving the UDP responding packets in the background.
- You are not required to check in a tight loop() the arrival of the UDP responding packets to process them.


#### Currently supported Boards

1. **STM32 boards with built-in Ethernet LAN8742A** such as :

  - **Nucleo-144 (F429ZI, F767ZI)**
  - **Discovery (STM32F746G-DISCOVERY)**
  - **All STM32 boards (STM32F/L/H/G/WB/MP1) with 32K+ Flash, with Built-in Ethernet**
  - See [EthernetWebServer_STM32 Support and Test Results](https://github.com/khoih-prog/EthernetWebServer_STM32/issues/1)
  
2. **STM32 boards using Ethernet LAN8720** such as :

  - **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
  - **Discovery (DISCO_F746NG)**
  - **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino Core for STM32 v2.3.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
 3. [`STM32Ethernet library v1.3.0+`](https://github.com/stm32duino/STM32Ethernet) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/STM32Ethernet.svg)](https://github.com/stm32duino/STM32Ethernet/releases/latest)
 4. [`LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/LwIP.svg)](https://github.com/stm32duino/LwIP/releases/latest)
 
---

### Installation

The suggested way to install is to:

#### Use Arduino Library Manager

The best way is to use `Arduino Library Manager`. Search for `AsyncUDP_STM32`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncUDP_STM32.svg?)](https://www.ardu-badge.com/AsyncUDP_STM32) for more detailed instructions.

### Manual Install

1. Navigate to [AsyncUDP_STM32](https://github.com/khoih-prog/AsyncUDP_STM32) page.
2. Download the latest release `AsyncUDP_STM32-master.zip`.
3. Extract the zip file to `AsyncUDP_STM32-master` directory 
4. Copy the whole `AsyncUDP_STM32-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**AsyncUDP_STM32** library](https://registry.platformio.org/libraries/khoih-prog/AsyncUDP_STM32) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/AsyncUDP_STM32/installation). Search for AsyncUDP_STM32 in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 2. For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.3.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`


---
---


### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include this `.hpp` file

```
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "AsyncUDP_STM32.hpp"     //https://github.com/khoih-prog/AsyncUDP_STM32
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "AsyncUDP_STM32.h"       //https://github.com/khoih-prog/AsyncUDP_STM32
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.



---
---

## HOWTO Setting up the Async UDP Client

```cpp
#include <LwIP.h>
#include <STM32Ethernet.h>
#include <AsyncUDP_STM32.h>

byte mac[] =  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x01 };

IPAddress timeWindowsCom = IPAddress(13, 86, 101, 172);

#define NTP_REQUEST_PORT      123

const int NTP_PACKET_SIZE = 48;       // NTP timestamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE];   // buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
AsyncUDP Udp;

// send an NTP request to the time server at the given address
void createNTPpacket(void)
{
  ...
}

void sendNTPPacket(void)
{
  createNTPpacket();
  //Send unicast
  Udp.write(packetBuffer, sizeof(packetBuffer));
}

void parsePacket(AsyncUDPPacket packet)
{
  ...
}

void setup()
{
  ...
  
  //NTP requests are to port NTP_REQUEST_PORT = 123
  if (Udp.connect(timeWindowsCom, NTP_REQUEST_PORT))
  {
    // Setting up Async packet Handler
    Udp.onPacket([](AsyncUDPPacket packet)
    {
      parsePacket(packet);
    });
  }
}

void loop()
{
  sendNTPPacket();

  // wait 60 seconds before asking for the time again
  delay(60000);
}
```

---
---

### HOWTO use STM32F4 with LAN8720

#### 1. Wiring

This is the Wiring for STM32F4 (BLACK_F407VE, etc.) using LAN8720


|LAN8720 PHY|<--->|STM32F4|
|:-:|:-:|:-:|
|TX1|<--->|PB_13|
|TX_EN|<--->|PB_11|
|TX0|<--->|PB_12|
|RX0|<--->|PC_4|
|RX1|<--->|PC_5|
|nINT/RETCLK|<--->|PA_1|
|CRS|<--->|PA_7|
|MDIO|<--->|PA_2|
|MDC|<--->|PC_1|
|GND|<--->|GND|
|VCC|<--->|+3.3V|

---

#### 2. HOWTO program using STLink V-2 or V-3

Connect as follows. To program, use **STM32CubeProgrammer** or Arduino IDE with 

- **U(S)ART Support: "Enabled (generic Serial)"**
- **Upload Method : "STM32CubeProgrammer (SWD)"**


|STLink|<--->|STM32F4|
|:-:|:-:|:-:|
|SWCLK|<--->|SWCLK|
|SWDIO|<--->|SWDIO|
|RST|<--->|NRST|
|GND|<--->|GND|
|5v|<--->|5V|


<p align="center">
    <img src="https://github.com/khoih-prog/AsyncUDP_STM32/blob/master/pics/STM32F407VET6.png">
</p>

---

#### 3. HOWTO use Serial Port for Debugging

Connect FDTI (USB to Serial) as follows:

|FDTI|<--->|STM32F4|
|:-:|:-:|:-:|
|RX|<--->|TX=PA_9|
|TX|<--->|RX=PA_10|
|GND|<--->|GND|


---
---

### Examples

 1. [AsyncUDPClient](examples/AsyncUDPClient)
 2. [AsyncUdpNTPClient](examples/AsyncUdpNTPClient)
 3. [AsyncUdpSendReceive](examples/AsyncUdpSendReceive) 
 4. [AsyncUDPServer](examples/AsyncUDPServer)
 5. [AsyncUDPMulticastServer](examples/AsyncUDPMulticastServer)
 6. [AsyncUDPClient_LAN8720](examples/AsyncUDPClient_LAN8720)
 7. [AsyncUdpNTPClient_LAN8720](examples/AsyncUdpNTPClient_LAN8720)
 8. [AsyncUdpSendReceive_LAN8720](examples/AsyncUdpSendReceive_LAN8720)
 9. [AsyncUDPServer_LAN8720](examples/AsyncUDPServer_LAN8720)
10. [AsyncUDPMulticastServer_LAN8720](examples/AsyncUDPMulticastServer_LAN8720)
11. [**multiFileProject**](examples/multiFileProject) **New**
12. [**multiFileProject_LAN8720**](examples/multiFileProject_LAN8720) **New**

---

### Example [AsyncUdpNTPClient](examples/AsyncUdpNTPClient)

#### 1. File [AsyncUdpNTPClient.ino](examples/AsyncUdpNTPClient/AsyncUdpNTPClient.ino)

https://github.com/khoih-prog/AsyncUDP_STM32/blob/5adf5c9fad72c9118590b5f07abd0dfee499786f/examples/AsyncUdpNTPClient/AsyncUdpNTPClient.ino#L13-L160


#### 2. File [defines.h](examples/AsyncUdpNTPClient/defines.h)

https://github.com/khoih-prog/AsyncUDP_STM32/blob/5adf5c9fad72c9118590b5f07abd0dfee499786f/examples/AsyncUdpNTPClient/defines.h#L12-L124


---

### Debug Terminal Output Samples

#### 1. AsyncUdpNTPClient on STM32F7 NUCLEO_F767ZI with LAN8742A Ethernet using STM32Ethernet Library

This is terminal debug output when running [AsyncUdpNTPClient](examples/AsyncUdpNTPClient) on  ***STM32F7 Nucleo-144 NUCLEO_F767ZI.***. It connects to NTP Server time.windows.com (IP=13.86.101.172) using AsyncUDP_STM32 library, and requests NTP time every 60s. The packet is then **received and processed asynchronously** to print current UTC/GMT time.

```
Start AsyncUdpNTPClient on NUCLEO_F767ZI
AsyncUdp_STM32 v1.3.0
STM32 Core version v2.3.0
You're connected to the network, IP = 192.168.2.157
UDP connected
============= createNTPpacket =============
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.157:62510, Length: 48
Seconds since Jan 1 1900 = 3864858437
Epoch/Unix time = 1655869637
The UTC/GMT time is Wed 2022-06-22 03:47:17 GMT
============= createNTPpacket =============
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.157:62510, Length: 48
Seconds since Jan 1 1900 = 3864858497
Epoch/Unix time = 1655869697
The UTC/GMT time is Wed 2022-06-22 03:48:17 GMT
============= createNTPpacket =============
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.157:62510, Length: 48
Seconds since Jan 1 1900 = 3864858557
Epoch/Unix time = 1655869757
The UTC/GMT time is Wed 2022-06-22 03:49:17 GMT
```

---

#### 2. AsyncUdpNTPClient_LAN8720 on STM32F4 BLACK_F407VE with LAN8720 Ethernet using STM32Ethernet Library

This is terminal debug output when running [AsyncUdpNTPClient_LAN8720](examples/AsyncUdpNTPClient_LAN8720) on **STM32F4 BLACK_F407VE with LAN8720 Ethernet using STM32Ethernet Library**. It connects to NTP Server time.windows.com (IP=13.86.101.172) using AsyncUDP_STM32 library, and requests NTP time every 60s. The packet is then **received and processed asynchronously** to print current UTC/GMT time.

```
Start AsyncUdpNTPClient_LAN8720 on BLACK_F407VE
AsyncUdp_STM32 v1.3.0
STM32 Core version v2.3.0
You're connected to the network, IP = 192.168.2.151
UDP connected
============= createNTPpacket =============
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.157:62510, Length: 48
Seconds since Jan 1 1900 = 3864858616
Epoch/Unix time = 1655869816
The UTC/GMT time is Wed 2022-06-22 03:50:16 GMT
============= createNTPpacket =============
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.157:62510, Length: 48
Seconds since Jan 1 1900 = 3864858676
Epoch/Unix time = 1655869876
The UTC/GMT time is Wed 2022-06-22 03:51:16 GMT
============= createNTPpacket =============
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.157:62510, Length: 48
Seconds since Jan 1 1900 = 3864858735
Epoch/Unix time = 1655869935
The UTC/GMT time is Wed 2022-06-22 03:52:15 GMT
```

---
---

### Debug

Debug is enabled by default on Serial. To disable, use level 0

```cpp
#define ASYNC_UDP_STM32_DEBUG_PORT      Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_UDP_STM32_LOGLEVEL_      0
```

You can also change the debugging level from 0 to 4

```cpp
#define ASYNC_UDP_STM32_DEBUG_PORT      Serial


// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_UDP_STM32_LOGLEVEL_    4
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of Arduino IDE, the Arduino `STM32` core or depending libraries.

Sometimes, the library will only work if you update the `STM32` core to the latest version because I am always using the latest cores /libraries.

---
---


### Issues ###

Submit issues to: [AsyncUDP_STM32 issues](https://github.com/khoih-prog/AsyncUDP_STM32/issues)

---

## TO DO

 1. Fix bug. Add enhancement
 2. Add support to more Ethernet / WiFi shield
 3. Add support to more STM32 boards.


## DONE

 1. Initial port to STM32 using builtin LAN8742A Etnernet. Tested on **STM32F7 Nucleo-144 F767ZI**.
 2. Add more examples.
 3. Add debugging features.
 4. Add support to **Ethernet LAN8720** using [STM32Ethernet library](https://github.com/stm32duino/STM32Ethernet), for boards such as **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG), Discovery (DISCO_F746NG)** and **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**
 5. Fix multiple-definitions linker error
 6. Update examples for new **STM32 core v2.3.0**
 7. Add example [multiFileProject](examples/multiFileProject) and [multiFileProject_LAN8720](examples/multiFileProject_LAN8720) to demo for multiple-file project to avoid `multiple-definitions` linker error


---
---

### Contributions and Thanks

1. Based on and modified from [Hristo Gochkov's ESPAsyncUDP](https://github.com/me-no-dev/ESPAsyncUDP). Many thanks to [Hristo Gochkov](https://github.com/me-no-dev) for great [ESPAsyncUDP Library](https://github.com/me-no-dev/ESPAsyncUDP)
2. Relied on [Frederic Pillon's STM32duino LwIP Library](https://github.com/stm32duino/LwIP).
3. Thanks to good work of [Miguel Wisintainer](https://github.com/tcpipchip) for working with, developing, debugging and testing.


<table>
  <tr>
    <td align="center"><a href="https://github.com/me-no-dev"><img src="https://github.com/me-no-dev.png" width="100px;" alt="me-no-dev"/><br /><sub><b>⭐️⭐️ Hristo Gochkov</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/fpistm"><img src="https://github.com/fpistm.png" width="100px;" alt="fpistm"/><br /><sub><b>⭐️ Frederic Pillon</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>tcpipchip</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/WebSockets2_Generic/blob/master/LICENSE)

---

## Copyright

Copyright 2020- Khoi Hoang


