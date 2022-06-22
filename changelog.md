# AsyncUDP_STM32


[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncUDP_STM32.svg?)](https://www.ardu-badge.com/AsyncUDP_STM32)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncUDP_STM32.svg)](https://github.com/khoih-prog/AsyncUDP_STM32/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/AsyncUDP_STM32/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncUDP_STM32.svg)](http://github.com/khoih-prog/AsyncUDP_STM32/issues)

---
---

## Table of Contents


* [Changelog](#changelog)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.1](#releases-v121)
  * [Releases v1.2.0](#releases-v120)
  * [Initial Releases v1.1.0](#initial-releases-v110)

---
---

## Changelog

### Releases v1.3.0

1. Fix multiple-definitions linker error. 
2. Update examples for new STM32 core v2.3.0 
3. Add example [multiFileProject](examples/multiFileProject) and [multiFileProject_LAN8720](examples/multiFileProject_LAN8720) to demo for multiple-file project to avoid `multiple-definitions` linker error
4. Update `Packages' Patches`

### Releases v1.2.1

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`

### Releases v1.2.0

1. Add support to **LAN8720** Ethernet for many **STM32F4** (F407xx, NUCLEO_F429ZI) and **STM32F7** (DISCO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG) boards.
2. Add LAN8720 examples
3. Add Packages' Patches for STM32 to use LAN8720 with STM32Ethernet and LwIP libraries
4. Add Table-of-Contents

### Initial Releases v1.1.0

1. Initial coding to port [ESPAsyncUDP](https://github.com/me-no-dev/ESPAsyncUDP) to STM32 boards using builtin LAN8742A Ethernet. More supports will be added gradually later, such as other Ethernet / WiFi shields.
2. Add more examples.
3. Add debugging features.
4. Bump up to v1.1.0 to sync with [ESPAsyncUDP v1.1.0](https://github.com/me-no-dev/ESPAsyncUDP).


