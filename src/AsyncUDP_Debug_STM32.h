/****************************************************************************************************************************
  AsyncUDP_Debug_STM32.h - Dead simple AsyncWebServer for STM32 built-in LAN8742A Ethernet
  
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

#ifndef AsyncUDP_Debug_STM32_H
#define AsyncUDP_Debug_STM32_H

#ifdef ASYNC_UDP_STM32_DEBUG_PORT
  #define DBG_PORT      ASYNC_UDP_STM32_DEBUG_PORT
#else
  #define DBG_PORT      Serial
#endif

///////////////////////////////////////////////////

// Change _ASYNC_UDP_STM32_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _ASYNC_UDP_STM32_LOGLEVEL_
  #define _ASYNC_UDP_STM32_LOGLEVEL_       0
#endif

///////////////////////////////////////////////////

#define UDP_LOGERROR(x)         if(_ASYNC_UDP_STM32_LOGLEVEL_>0) { DBG_PORT.print("[UDP] "); DBG_PORT.println(x); }
#define UDP_LOGERROR0(x)        if(_ASYNC_UDP_STM32_LOGLEVEL_>0) { DBG_PORT.print(x); }
#define UDP_LOGERROR1(x,y)      if(_ASYNC_UDP_STM32_LOGLEVEL_>0) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.println(y); }
#define UDP_LOGERROR2(x,y,z)    if(_ASYNC_UDP_STM32_LOGLEVEL_>0) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.println(z); }
#define UDP_LOGERROR3(x,y,z,w)  if(_ASYNC_UDP_STM32_LOGLEVEL_>0) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.print(z); DBG_PORT.print(" "); DBG_PORT.println(w); }

///////////////////////////////////////////////////

#define UDP_LOGWARN(x)          if(_ASYNC_UDP_STM32_LOGLEVEL_>1) { DBG_PORT.print("[UDP] "); DBG_PORT.println(x); }
#define UDP_LOGWARN0(x)         if(_ASYNC_UDP_STM32_LOGLEVEL_>1) { DBG_PORT.print(x); }
#define UDP_LOGWARN1(x,y)       if(_ASYNC_UDP_STM32_LOGLEVEL_>1) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.println(y); }
#define UDP_LOGWARN2(x,y,z)     if(_ASYNC_UDP_STM32_LOGLEVEL_>1) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.println(z); }
#define UDP_LOGWARN3(x,y,z,w)   if(_ASYNC_UDP_STM32_LOGLEVEL_>1) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.print(z); DBG_PORT.print(" "); DBG_PORT.println(w); }

///////////////////////////////////////////////////

#define UDP_LOGINFO(x)          if(_ASYNC_UDP_STM32_LOGLEVEL_>2) { DBG_PORT.print("[UDP] "); DBG_PORT.println(x); }
#define UDP_LOGINFO0(x)         if(_ASYNC_UDP_STM32_LOGLEVEL_>2) { DBG_PORT.print(x); }
#define UDP_LOGINFO1(x,y)       if(_ASYNC_UDP_STM32_LOGLEVEL_>2) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.println(y); }
#define UDP_LOGINFO2(x,y,z)     if(_ASYNC_UDP_STM32_LOGLEVEL_>2) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.println(z); }
#define UDP_LOGINFO3(x,y,z,w)   if(_ASYNC_UDP_STM32_LOGLEVEL_>2) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.print(z); DBG_PORT.print(" "); DBG_PORT.println(w); }

///////////////////////////////////////////////////

#define UDP_LOGDEBUG(x)         if(_ASYNC_UDP_STM32_LOGLEVEL_>3) { DBG_PORT.print("[UDP] "); DBG_PORT.println(x); }
#define UDP_LOGDEBUG0(x)        if(_ASYNC_UDP_STM32_LOGLEVEL_>3) { DBG_PORT.print(x); }
#define UDP_LOGDEBUG1(x,y)      if(_ASYNC_UDP_STM32_LOGLEVEL_>3) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.println(y); }
#define UDP_LOGDEBUG2(x,y,z)    if(_ASYNC_UDP_STM32_LOGLEVEL_>3) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.println(z); }
#define UDP_LOGDEBUG3(x,y,z,w)  if(_ASYNC_UDP_STM32_LOGLEVEL_>3) { DBG_PORT.print("[UDP] "); DBG_PORT.print(x); DBG_PORT.print(" "); DBG_PORT.print(y); DBG_PORT.print(" "); DBG_PORT.print(z); DBG_PORT.print(" "); DBG_PORT.println(w); }

///////////////////////////////////////////////////

#endif    //AsyncUDP_Debug_STM32_H
