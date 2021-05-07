/*

Copyright 2012 Marc Ketel
SPDX-License-Identifier: Apache-2.0

*/

#ifndef FUNCTIONS_H_
#define LIB_H_

#include <stdio.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "rtc.h"

//volatile uint8_t EVENTS;
#define event GPIOR0
#define EV_10Hz    _BV(0)
#define EV_1s      _BV(1)
#define EVrotCW    _BV(2)
#define EVrotCCW   _BV(3)
#define EVrotClick _BV(4)

#define SHIFTSIZE 4

uint8_t shiftbuffer[SHIFTSIZE];

void init(void);

void shiftOut(uint8_t * buffer, uint8_t len);

void addMinute(DS3231RegDateTime_t *dateTime);
void substractMinute(DS3231RegDateTime_t *dateTime);

#endif /* LIB_H_ */