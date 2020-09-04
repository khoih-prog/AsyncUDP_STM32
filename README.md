# AsyncUDP_STM32


[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncUDP_STM32.svg?)](https://www.ardu-badge.com/AsyncUDP_STM32)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncUDP_STM32.svg)](https://github.com/khoih-prog/AsyncUDP_STM32/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/AsyncUDP_STM32/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncUDP_STM32.svg)](http://github.com/khoih-prog/AsyncUDP_STM32/issues)

---
---

### Why do we need this Async [AsyncUDP_STM32 library](https://github.com/khoih-prog/AsyncUDP_STM32)

- Using asynchronous network means that you can handle **more than one connection at the same time**
- You are called once the packet is ready
- After connecting to a UDP server as an Async Client, you are **immediately ready** to handle other connections while the Client is taking care of receiving the UDP responding packets in the background.
- You are not required to check in a tight loop() the arrival of the UDP responding packets to process them.
- **Speed is OMG**

---

### Initial Releases v1.1.0

1. Initial coding to port [ESPAsyncUDP](https://github.com/me-no-dev/ESPAsyncUDP) to STM32 boards using builtin LAN8742A Ethernet. More supports will be added gradually later, such as other Ethernet / WiFi shields.
2. Add more examples.
3. Add debugging features.
4. Bump up to v1.1.0 to sync with [ESPAsyncUDP v1.1.0](https://github.com/me-no-dev/ESPAsyncUDP).

#### Currently Supported Boards

1. Nucleo-144 (F429ZI, F746ZG, F756ZG, F767ZI)
2. Discovery STM32F746G-DISCOVERY
3. Any STM32 boards with enough flash/memory and already configured to run LAN8742A Ethernet.

---

### Async UDP [AsyncUDP_STM32 library](https://github.com/khoih-prog/AsyncUDP_STM32) for STM32 boards using builtin LAN8742A Ethernet

This [AsyncUDP_STM32 library](https://github.com/khoih-prog/AsyncUDP_STM32) is a fully asynchronous UDP library, designed for a trouble-free, multi-connection network environment, for STM32 boards using builtin LAN8742A Ethernet. The library is easy to use and includes support for Unicast, Broadcast and Multicast environments.

This library is based on, modified from:

1. [Hristo Gochkov's ESPAsyncUDP](https://github.com/me-no-dev/ESPAsyncUDP)

to apply the better and faster **asynchronous** feature of the **powerful** [ESPAsyncUDP Library](https://github.com/me-no-dev/ESPAsyncUDP) into STM32 boards using builtin LAN8742A Ethernet.


---
---

## Prerequisite

 1. [`Arduino IDE 1.8.12+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino Core for STM32 1.9.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32 (Use Arduino Board Manager)
 3. [`STM32Ethernet library v1.2.0+`](https://github.com/stm32duino/STM32Ethernet) for built-in Ethernet on (Nucleo-144, Discovery)
 4. [`LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP) for built-in Ethernet on (Nucleo-144, Discovery)
 
---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `AsyncUDP_STM32`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncUDP_STM32.svg?)](https://www.ardu-badge.com/AsyncUDP_STM32) for more detailed instructions.

### Manual Install

1. Navigate to [AsyncUDP_STM32](https://github.com/khoih-prog/AsyncUDP_STM32) page.
2. Download the latest release `AsyncUDP_STM32-master.zip`.
3. Extract the zip file to `AsyncUDP_STM32-master` directory 
4. Copy the whole `AsyncUDP_STM32-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:
1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install **AsyncUDP_STM32** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/). Search for ***AsyncUDP_STM32*** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](examples/platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically.

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

### Examples

 1. [AsyncUDPClient](examples/AsyncUDPClient)
 2. [AsyncUdpNTPClient](examples/AsyncUdpNTPClient)
 3. [AsyncUdpSendReceive](examples/AsyncUdpSendReceive) 
 4. [AsyncUDPServer](examples/AsyncUDPServer)
 5. [AsyncUDPMulticastServer](examples/AsyncUDPMulticastServer)

---

### Example [AsyncUdpNTPClient](examples/AsyncUdpNTPClient)

#### 1. File [AsyncUdpNTPClient.ino](examples/AsyncUdpNTPClient/AsyncUdpNTPClient.ino)


```cpp
#include "defines.h"
#include <time.h>

IPAddress timeWindowsCom = IPAddress(13, 86, 101, 172);

#define NTP_REQUEST_PORT      123

char timeServer[]         = "time.nist.gov";  // NTP server

const int NTP_PACKET_SIZE = 48;       // NTP timestamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE];   // buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
AsyncUDP Udp;

// send an NTP request to the time server at the given address
void createNTPpacket(void)
{
  Serial.println("============= createNTPpacket =============");

  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)

  packetBuffer[0]   = 0b11100011;   // LI, Version, Mode
  packetBuffer[1]   = 0;     // Stratum, or type of clock
  packetBuffer[2]   = 6;     // Polling Interval
  packetBuffer[3]   = 0xEC;  // Peer Clock Precision
  
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
}

void parsePacket(AsyncUDPPacket packet)
{
  struct tm  ts;
  char       buf[80];
  
  memcpy(packetBuffer, packet.data(), sizeof(packetBuffer));

  Serial.print("Received UDP Packet Type: ");
  Serial.println(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
  Serial.print("From: ");
  Serial.print(packet.remoteIP());
  Serial.print(":");
  Serial.print(packet.remotePort());
  Serial.print(", To: ");
  Serial.print(packet.localIP());
  Serial.print(":");
  Serial.print(packet.localPort());
  Serial.print(", Length: ");
  Serial.print(packet.length());
  Serial.println();

  unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
  unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

  // combine the four bytes (two words) into a long integer
  // this is NTP time (seconds since Jan 1 1900):
  unsigned long secsSince1900 = highWord << 16 | lowWord;
  
  Serial.print(F("Seconds since Jan 1 1900 = "));
  Serial.println(secsSince1900);

  // now convert NTP time into )everyday time:
  Serial.print(F("Epoch/Unix time = "));
  
  // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
  const unsigned long seventyYears = 2208988800UL;
  
  // subtract seventy years:
  unsigned long epoch = secsSince1900 - seventyYears;
  time_t epoch_t = epoch;   //secsSince1900 - seventyYears;
 
  // print Unix time:
  Serial.println(epoch);

  // print the hour, minute and second:
  Serial.print(F("The UTC/GMT time is "));       // UTC is the time at Greenwich Meridian (GMT)

  ts = *localtime(&epoch_t);
  strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
  Serial.println(buf);
}

void sendNTPPacket(void)
{
  createNTPpacket();
  //Send unicast
  Udp.write(packetBuffer, sizeof(packetBuffer));
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStart AsyncUdpNTPClient on " + String(BOARD_NAME));

  // start the ethernet connection and the server
  // Use random mac
  uint16_t index = millis() % NUMBER_OF_MAC;

  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  // Use DHCP dynamic IP and random mac
  Ethernet.begin(mac[index]);

  // you're connected now, so print out the data
  Serial.print(F("You're connected to the network, IP = "));
  Serial.println(Ethernet.localIP());

  //NTP requests are to port NTP_REQUEST_PORT = 123
  if (Udp.connect(timeWindowsCom, NTP_REQUEST_PORT))
  {
    Serial.println("UDP connected");

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

#### 2. File [defines.h](examples/AsyncUdpNTPClient/defines.h)

```cpp
/*
   Currently support
   1) STM32 boards with built-in Ethernet (to use USE_BUILTIN_ETHERNET = true) such as :
      - Nucleo-144 (F429ZI, F767ZI)
      - Discovery (STM32F746G-DISCOVERY)
      - STM32 boards (STM32F/L/H/G/WB/MP1) with 32K+ Flash, with Built-in Ethernet, 
      - See How To Use Built-in Ethernet at (https://github.com/khoih-prog/EthernetWebServer_STM32/issues/1)
   2) STM32F/L/H/G/WB/MP1 boards (with 32+K Flash) running ENC28J60 shields (to use USE_BUILTIN_ETHERNET = false)
   3) STM32F/L/H/G/WB/MP1 boards (with 32+K Flash) running W5x00 shields
*/

#ifndef defines_h
#define defines_h

#if !( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) )
  #error This code is designed to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
#endif

#define ASYNC_UDP_STM32_DEBUG_PORT      Serial
#define _ASYNC_UDP_STM32_LOGLEVEL_      1


#if defined(STM32F0)
  #warning STM32F0 board selected
  #define BOARD_TYPE  "STM32F0"
#elif defined(STM32F1)
  #warning STM32F1 board selected
  #define BOARD_TYPE  "STM32F1"
#elif defined(STM32F2)
  #warning STM32F2 board selected
  #define BOARD_TYPE  "STM32F2"
#elif defined(STM32F3)
  #warning STM32F3 board selected
  #define BOARD_TYPE  "STM32F3"
#elif defined(STM32F4)
  #warning STM32F4 board selected
  #define BOARD_TYPE  "STM32F4"
#elif defined(STM32F7)
  #warning STM32F7 board selected
  #define BOARD_TYPE  "STM32F7"
#elif defined(STM32L0)
  #warning STM32L0 board selected
  #define BOARD_TYPE  "STM32L0"
#elif defined(STM32L1)
  #warning STM32L1 board selected
  #define BOARD_TYPE  "STM32L1"
#elif defined(STM32L4)
  #warning STM32L4 board selected
  #define BOARD_TYPE  "STM32L4"
#elif defined(STM32H7)
  #warning STM32H7 board selected
  #define BOARD_TYPE  "STM32H7"
#elif defined(STM32G0)
  #warning STM32G0 board selected
  #define BOARD_TYPE  "STM32G0"
#elif defined(STM32G4)
  #warning STM32G4 board selected
  #define BOARD_TYPE  "STM32G4"
#elif defined(STM32WB)
  #warning STM32WB board selected
  #define BOARD_TYPE  "STM32WB"
#elif defined(STM32MP1)
  #warning STM32MP1 board selected
  #define BOARD_TYPE  "STM32MP1"
#else
  #warning STM32 unknown board selected
  #define BOARD_TYPE  "STM32 Unknown"
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#include <LwIP.h>
#include <STM32Ethernet.h>

#include <AsyncUDP_STM32.h>

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x14 },
};

// Select the static IP address according to your local network
IPAddress ip(192, 168, 2, 232);

#endif    //defines_h
```

---

### Debug Termimal Output Samples

1. This is terminal debug output when running [AsyncUdpNTPClient](examples/AsyncUdpNTPClient) on  ***STM32F7 Nucleo-144 NUCLEO_F767ZI.***. It connects to NTP Server time.windows.com(IP=13.86.101.172) using AsyncUDP_STM32 library, and requests NTP time every 60s. The packet is then **received and processed asynchronously** to print current UTC/GMT time.

```
Start AsyncUdpNTPClient on NUCLEO_F767ZI
You're connected to the network, IP = 192.168.2.187
UDP connected
============= createNTPpacket =============
[UDP] _recv: Call packetHandler with packet from remoteIP = 13.86.101.172 , remotePort = 123
[UDP] To destIP = 192.168.2.187 , destPort = 62510
[UDP] Packet len = 48
Received UDP Packet Type: Unicast
From: 13.86.101.172:123, To: 192.168.2.187:62510, Length: 48
Seconds since Jan 1 1900 = 3808150993
Epoch/Unix time = 1599162193
The UTC/GMT time is Thu 2020-09-03 19:43:13 GMT
...
============= createNTPpacket =============
[UDP] _recv: Call packetHandler with packet from remoteIP = 13.86.101.172 , remotePort = 123
[UDP] To destIP = 192.168.2.187 , destPort = 62510
[UDP] Packet len = 48
Received UDP Packet Type: Unicast
From: 13.86.101.172:123, To: 192.168.2.187:62510, Length: 48
Seconds since Jan 1 1900 = 3808151290
Epoch/Unix time = 1599162490
The UTC/GMT time is Thu 2020-09-03 19:48:10 GMT
============= createNTPpacket =============
[UDP] _recv: Call packetHandler with packet from remoteIP = 13.86.101.172 , remotePort = 123
[UDP] To destIP = 192.168.2.187 , destPort = 62510
[UDP] Packet len = 48
Received UDP Packet Type: Unicast
From: 13.86.101.172:123, To: 192.168.2.187:62510, Length: 48
Seconds since Jan 1 1900 = 3808151349
Epoch/Unix time = 1599162549
The UTC/GMT time is Thu 2020-09-03 19:49:09 GMT
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
---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of Arduino IDE, the Arduino `STM32` core or depending libraries.

Sometimes, the library will only work if you update the `STM32` core to the latest version because I am always using the latest cores /libraries.


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
 
---
---

### Initial Releases v1.1.0

1. Initial coding to port [ESPAsyncUDP](https://github.com/me-no-dev/ESPAsyncUDP) to STM32 boards using builtin LAN8742A Ethernet. More supports will be added gradually later, such as other Ethernet / WiFi shields.
2. Add more examples.
3. Add debugging features.
4. Bump up to v1.1.0 to sync with [ESPAsyncUDP v1.1.0](https://github.com/me-no-dev/ESPAsyncUDP).

#### Currently Supported Boards

1. Nucleo-144 (F429ZI, F746ZG, F756ZG, F767ZI)
2. Discovery STM32F746G-DISCOVERY
3. Any STM32 boards with enough flash/memory and already configured to run LAN8742A Ethernet.

---

This library is based on, modified from:

1. [Hristo Gochkov's ESPAsyncUDP](https://github.com/me-no-dev/ESPAsyncUDP)

to apply the better and faster **asynchronous** feature of the **great** [ESPAsyncUDP Library](https://github.com/me-no-dev/ESPAsyncUDP) into STM32 boards using builtin LAN8742A Ethernet.

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

### License and credits ###

- The library is licensed under [MIT](https://github.com/khoih-prog/WebSockets2_Generic/blob/master/LICENSE)

---

## Copyright

Copyright 2020- Khoi Hoang


