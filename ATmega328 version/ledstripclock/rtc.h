/*

Copyright 2012 Marc Ketel
SPDX-License-Identifier: Apache-2.0

*/

#ifndef RTC_H_
#define RTC_H_

// DS3231 defines
#define DS3231_SLA 0x68  // Slave Address

// Note: in the following structure declaration, bitfields are assigned starting
// from the low-order bit.  Some compilers assign bitfields starting from the
// high-order bit.

#define DS3231RegDateTimeOffset 0x00
typedef struct {

  //0x00
  uint8_t seconds1  : 4;
  uint8_t seconds10 : 3;
  uint8_t           : 1;

  //0x01
  uint8_t minutes1  : 4;
  uint8_t minutes10 : 3;
  uint8_t           : 1;

  //0x02
  uint8_t hours1    : 4;
  uint8_t hours10   : 2;
  uint8_t mode12    : 1;  // 12-hour mode (1) or 24-hour mode (0)
  uint8_t           : 1;

  //0x03
  uint8_t day       : 3;
  uint8_t           : 5;

  //0x04
  uint8_t date1     : 4;
  uint8_t date10    : 2;
  uint8_t           : 2;

  //0x05
  uint8_t month1    : 4;
  uint8_t month10   : 1;
  uint8_t           : 2;
  uint8_t century   : 1;

  //0x06
  uint8_t year1     : 4;
  uint8_t year10    : 4;

} DS3231RegDateTime_t;

#define DS3231RegAlarmOffset 0x07
typedef struct {

  //Niet helemaal de inhoud van 0x07 - 0x0D, word nu misbruikt als RAM.
  uint8_t hour;
  uint8_t minutes;
  uint8_t active;

  /*
  //0x07
  uint8_t           : 8;

  //0x08
  uint8_t           : 8;

  //0x09
  uint8_t           : 8;

  //0x0A
  uint8_t           : 8;

  //0x0B
  uint8_t           : 8;

  //0x0B
  uint8_t           : 8;

  //0x0D
  uint8_t           : 8;
  */


} DS3231RegAlarm_t;

#define DS3231RegControlOffset 0x0E
typedef struct {
  //0x0E
  uint8_t a1ie      : 1;  //Alarm 1 Interrupt Enable
  uint8_t a2ie      : 1;  //Alarm 2 Interrupt Enable
  uint8_t intcn     : 1;  //Interrupt Control
  uint8_t rs        : 2;  //Rate select
  uint8_t conv      : 1;  //Convert Temperature
  uint8_t bbsqw     : 1;  //Battery-Backed Square-Wave Enable
  uint8_t eosc      : 1;  //!(Enable Oscillator): 0 is enable osc

  //0x0F
  uint8_t a1f       : 1;  //Alarm 1 Flag
  uint8_t a2f       : 1;  //Alarm 2 Flag
  uint8_t busy      : 1;  //Busy
  uint8_t en32khz   : 1;  //Enable 32kHz Output
  uint8_t           : 3;
  uint8_t osf       : 1;  //Oscillator Stop Flag

  //0x10
  int8_t agingOffset: 8;

} DS3231RegControl_t;

#define DS3231RegTemperatureOffset 0x11
typedef struct {
  //0x11
  uint8_t msb     : 7;
  uint8_t sign    : 1;

  //0x12
  uint8_t         : 6;
  uint8_t lsb     : 2;

} DS3231RegTemperatureOffset_t;

void initRTC(void);

void getRTC(DS3231RegDateTime_t *);
void setRTC(DS3231RegDateTime_t *);

typedef struct {
  uint16_t ocr;
} DS3231Ram_t;

void getRTCRAM(DS3231Ram_t *);
void setRTCRAM(DS3231Ram_t *);

#endif /* RTC_H_ */