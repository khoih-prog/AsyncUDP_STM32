/****************************************************************************************************************************
  AsyncUdp_STM32.h
  
  For STM32 with built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc)
  
  AsyncUDP_STM32 is a Async UDP library for the STM32 using built-in LAN8742A Ethernet
  
  Based on and modified from ESPAsyncUDP Library (https://github.com/me-no-dev/ESPAsyncUDP)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncUDP_STM32
  Licensed under MIT license
  
  Version: 1.3.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.1.0   K Hoang      03/09/2020 Initial coding for STM32 for built-in Ethernet (Nucleo-144, DISCOVERY, etc).
                                  Bump up version to v1.1.0 to sync with ESPAsyncUDP v1.1.0
  1.2.0   K Hoang      11/04/2021 Add support to LAN8720 using STM32F4 or STM32F7
  1.2.1   K Hoang      09/10/2021 Update `platform.ini` and `library.json`
  1.3.0   K Hoang      21/06/2022 Fix multiple-definitions linker error. Update for STM32 core v2.3.0 
 *****************************************************************************************************************************/

#pragma once

#ifndef ASYNCUDP_STM32_H
#define ASYNCUDP_STM32_H

///////////////////////////////////////////////////

#define ASYNC_UDP_STM32_VERSION         "AsyncUdp_STM32 v1.3.0"

///////////////////////////////////////////////////

#include "AsyncUDP_Debug_STM32.h"

#include "AsyncUDP_STM32.hpp"
#include "AsyncUDP_Impl_STM32.h"

///////////////////////////////////////////////////

#endif    //ASYNCUDP_STM32_H
