/****************************************************************************************************************************
  multiFileProject.h
  For STM32 with built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc)

  AsyncUDP_STM32 is a Async UDP library for the STM32 using built-in LAN8742A Ethernet

  Based on and modified from ESPAsyncUDP Library (https://github.com/me-no-dev/ESPAsyncUDP)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncUDP_STM32
  Licensed under MIT license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#pragma once

#define _ASYNC_UDP_STM32_LOGLEVEL_       1

#define USING_LAN8720                   true

#include <LwIP.h>
#include <STM32Ethernet.h>

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "AsyncUDP_STM32.hpp"
