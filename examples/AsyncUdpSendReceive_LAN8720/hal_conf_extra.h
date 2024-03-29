/****************************************************************************************************************************
  hal_conf_extra.h

  For STM32 with LAN8720 (STM32F4/F7) or built-in LAN8742A Ethernet (Nucleo-144, DISCOVERY, etc)

  AsyncWebServer_STM32 is a library for the STM32 run LAN8720 or built-in LAN8742A Ethernet WebServer

  Based on and modified from ESPAsyncWebServer (https://github.com/me-no-dev/ESPAsyncWebServer)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncWebServer_STM32
  Licensed under MIT license
 *****************************************************************************************************************************/

// Note: Must replace
// .arduino15/packages/STM32/hardware/stm32/x.y.z/system/STM32F4xx/stm32f4xx_hal_conf_default.h
// as described in README.md

#pragma once

#ifndef HAL_CONF_EXTRA_STM32_H
#define HAL_CONF_EXTRA_STM32_H

#include <stm32_def.h>

// Don't need from core v2.3.0

#if (STM32_CORE_VERSION < 0x2030000)
  #warning Using STM32 core < v2.3.0
  #define HAL_ETH_MODULE_ENABLED
#endif

#define LAN8742A_PHY_ADDRESS            0x01U

#endif      // HAL_CONF_EXTRA_STM32_H
