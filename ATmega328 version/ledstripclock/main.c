/*

Copyright 2012 Marc Ketel
SPDX-License-Identifier: Apache-2.0

*/

#include "lib.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>

#include <util/delay.h>

#include "rtc.h"

char command[16];
unsigned int position;
unsigned int data;

uint8_t brightness = 31;
uint8_t const intensity[] PROGMEM = {0,1,2,3,6,8,12,15,20,24,30,35,42,48,56,63,72,80,90,99,110,120,132,143,156,168,182,195,210,224,240,255};
uint8_t const number[] PROGMEM = {0x00, 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
uint8_t maxBrightness = 0;

uint8_t i, j;
char line[5];

#define STATE_BRIGHTNESS 1
#define STATE_CLOCKSET 2

uint8_t state = STATE_BRIGHTNESS;
uint8_t stateTimeout = 0;

int main(void)
{
  wdt_enable(WDTO_120MS);
	init();

/*
  ds1307Reg_t dateTime;
  getRTC(&dateTime);
  dateTime.ch = 0;
  dateTime.rs = 0;
  dateTime.out = 0;
  dateTime.sqwe = 1;
  dateTime.mode12 = 0;
  setRTC(&dateTime);
*/

  DS3231Ram_t ram;
  getRTCRAM(&ram);
  OCR1A = ram.ocr;

  if (OCR1A > ICR1)
    OCR1A = ICR1;

  for(;;)
  {
	  while(event == 0) {} //Wait for events

		if (event & EV_10Hz)
		{
			event &= ~EV_10Hz;
		}

    if (event & EV_1s)
    {
      event &= ~EV_1s;

      DS3231RegDateTime_t DS3231Reg;
      getRTC(&DS3231Reg);

      memset(line, '0', sizeof(line));
      sprintf_P(line, PSTR("%02d%02d"), DS3231Reg.hours10*10+DS3231Reg.hours1, DS3231Reg.minutes10*10+DS3231Reg.minutes1);

      for(i=0;i<4;i++)
      {
        shiftbuffer[3-i] = pgm_read_byte(&(number[line[i] - 0x2F]));
      }

      shiftOut(shiftbuffer, SHIFTSIZE);

      if (stateTimeout > 1)
      {
        stateTimeout--;
      }
      else
      if (stateTimeout==1)
      {
        state = STATE_BRIGHTNESS;
        stateTimeout = 0;
      }

      /*
      OCR1A += 200;
      _delay_ms(50);
      OCR1A -= 200;
      */

    }


    if (event & EVrotCW)
    {
      event &= ~EVrotCW;

      if (state == STATE_BRIGHTNESS)
      {
        if (OCR1A < ICR1 && OCR1A < 30)
          OCR1A+=1;
        else if (OCR1A < ICR1)
          OCR1A+=100;
        else
          OCR1A = ICR1;

        ram.ocr = OCR1A;
        setRTCRAM(&ram);
      }

      if (state == STATE_CLOCKSET)
      {
        DS3231RegDateTime_t DS3231Reg;
        getRTC(&DS3231Reg);
        addMinute(&DS3231Reg);
        setRTC(&DS3231Reg);

        event |= EV_1s;

        stateTimeout = 60;
      }
    }

    if (event & EVrotCCW)
    {
      event &= ~EVrotCCW;

      if (state == STATE_BRIGHTNESS)
      {
        if (OCR1A <= 30 && OCR1A > 1)
          OCR1A-=1;
        else if (OCR1A > 100)
          OCR1A-=100;
        else
          OCR1A=1;

        ram.ocr = OCR1A;
        setRTCRAM(&ram);
      }

      if (state == STATE_CLOCKSET)
      {
        DS3231RegDateTime_t DS3231Reg;
        getRTC(&DS3231Reg);
        substractMinute(&DS3231Reg);
        setRTC(&DS3231Reg);

        event |= EV_1s;

        stateTimeout = 60;
      }
    }

    if (event & EVrotClick)
    {
      event &= ~EVrotClick;

      if (state == STATE_BRIGHTNESS)
        state = STATE_CLOCKSET;
      else
        state = STATE_BRIGHTNESS;
    }


     wdt_reset();
  }
}
