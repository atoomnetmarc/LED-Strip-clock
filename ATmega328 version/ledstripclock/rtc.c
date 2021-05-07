/*

Copyright 2012 Marc Ketel
SPDX-License-Identifier: Apache-2.0

*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/power.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>

#include "lib.h"
#include "twi.h"
#include "rtc.h"

ISR(INT0_vect)
{
  //INT0 is connected to SQW/OUT of the RTC chip
  event |= EV_1s;
}

void initRTC()
{
  uint8_t regAddress;
  power_twi_enable();

  EIMSK |= _BV(INT0);
  EICRA |= _BV(ISC01); //The falling edge between two samples of INTn generates an interrupt request

  twiInit(10);

  DS3231RegControl_t DS3231Control;
  regAddress = DS3231RegControlOffset;
  twiWrite(DS3231_SLA, &regAddress, 1);
  twiRead(DS3231_SLA, (uint8_t*)&DS3231Control, sizeof(DS3231RegControl_t));

  //Disable build-in alarms
  DS3231Control.a1ie = 0;
  DS3231Control.a2ie = 0;

  //1Hz SQWE on
  DS3231Control.rs = 0;
  DS3231Control.intcn = 0;

  //Disable Battery-Backed Square-Wave
  DS3231Control.bbsqw = 0;

  //Enable oscilator
  DS3231Control.eosc = 0; //Yup, zero enables it.

  //Disable 32kHz output
  DS3231Control.en32khz = 0;

  //clear flags
  DS3231Control.osf = 0;
  DS3231Control.a1f = 0;
  DS3231Control.a2f = 0;

  uint8_t iobuffer[sizeof(DS3231RegControl_t)+1];

  memcpy(&iobuffer[1], &DS3231Control, sizeof(DS3231RegControl_t));
  iobuffer[0] = regAddress;
  twiWrite(DS3231_SLA, (uint8_t*)&iobuffer, sizeof(iobuffer));


  //Set 24-hour mode.
  DS3231RegDateTime_t dateTime;
  getRTC(&dateTime);
  if (dateTime.mode12 != 0)
  {
    dateTime.mode12 = 0;
    setRTC(&dateTime);
  }
}

void getRTC(DS3231RegDateTime_t *dateTime)
{
  uint8_t regAddress;

  regAddress = DS3231RegDateTimeOffset;
  twiWrite(DS3231_SLA, &regAddress, 1);
  twiRead(DS3231_SLA, (uint8_t*)dateTime, 8);
}

void setRTC(DS3231RegDateTime_t *dateTime)
{
  uint8_t iobuffer[sizeof(DS3231RegDateTime_t)+1];

  memcpy(&iobuffer[1], dateTime, sizeof(DS3231RegDateTime_t));

  iobuffer[0] = DS3231RegDateTimeOffset;
  twiWrite(DS3231_SLA, (uint8_t*)&iobuffer, 8);
}

void getRTCRAM(DS3231Ram_t *ram)
{
  uint8_t regAddress;

  regAddress = DS3231RegAlarmOffset;
  twiWrite(DS3231_SLA, &regAddress, 1);
  twiRead(DS3231_SLA, (uint8_t*)ram, sizeof(DS3231Ram_t));
}

void setRTCRAM(DS3231Ram_t *ram)
{
  uint8_t iobuffer[sizeof(DS3231Ram_t)+1];

  memcpy(&iobuffer[1], ram, sizeof(DS3231Ram_t));

  iobuffer[0] = DS3231RegAlarmOffset;
  twiWrite(DS3231_SLA, (uint8_t*)&iobuffer, sizeof(DS3231Ram_t)+1);
}
