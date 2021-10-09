/*

Copyright 2021 Marc Ketel
SPDX-License-Identifier: Apache-2.0

*/

#include <Arduino.h>

#ifndef config_h
#define config_h

extern const char *ssid;
extern const char *password;

extern const char *otapassword;
extern const char *otahostname;

#define PIN_SHIFT_NOT_OUTPUT_ENABLE D4
#define PIN_SHIFT_DATA D7
#define PIN_SHIFT_CLOCK D5
#define PIN_SHIFT_LATCH D8

#define PIN_BUFFER_NOT_ENABLE D0

#define PIN_IO_INT D3
#define PIN_RTC_INT D6

#define PIN_IO_ROT_A 0
#define PIN_IO_ROT_B 1
#define PIN_IO_ROT_SW 2

#endif