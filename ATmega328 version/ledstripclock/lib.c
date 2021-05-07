/*

Copyright 2012 Marc Ketel
SPDX-License-Identifier: Apache-2.0

*/

#include "lib.h"
#include "Ben Buxton/rotary.h"

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

//1000Hz
uint16_t timer0counter = 0;
ISR(TIMER0_COMPA_vect)
{
	if (timer0counter==0)
	{
		timer0counter = 100;
	  event |= EV_10Hz;
  }

  timer0counter--;
}

void shiftOut(uint8_t * buffer, uint8_t len)
{
  uint8_t i;

  SPDR = buffer[0];

  for (i=1;i<len;i++)
  {
	  loop_until_bit_is_set(SPSR, SPIF);
    SPDR = buffer[i];
  }

  loop_until_bit_is_set(SPSR, SPIF);
  PORTB |= _BV(PB0);
  _delay_loop_1(20);
  PORTB &= ~_BV(PB0);
}

void init(void)
{
  clock_prescale_set(clock_div_1); //sysclk = 16MHz
	power_all_disable();

	//SPI
	power_spi_enable();
	DDRB |= _BV(PB0) | _BV(PB2) | _BV(PB3) | _BV(PB5);
  SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPI2X);

  //ADC
	power_adc_enable();
  DIDR0 |= _BV(ADC0D);
  ADMUX |= _BV(REFS0); //AVCC with external capacitor at AREF pin
  //Division Factor 64: 250KHz
  ADCSRA |= _BV(ADPS1) | _BV(ADPS2) | _BV(ADEN);
  PORTC |= _BV(PC0);

  //Timer0
  power_timer0_enable();
  TCCR0A |= _BV(WGM01); //CTC mode
  TCCR0B |= _BV(CS00) | _BV(CS01); //clk/64
  TIMSK0 |= _BV(OCIE0A); //Timer/Counter0 Output Compare Match A Interrupt Enable
  OCR0A = 0xF9; //1KHz

  //Timer1
  power_timer1_enable();
	DDRB |= _BV(PB1);

  //10-bit PWM
	//TCCR1A |= _BV(WGM10) | _BV(WGM11);
  //TCCR1B |= _BV(WGM12);

  TCCR1B |= _BV(WGM13);


	TCCR1A |= _BV(COM1A0) | _BV(COM1A1); //Set OC1A on Compare Match when upcounting. Clear OC1A on Compare Match when downcounting.
  TCCR1B |= _BV(CS10); //clk/0
  //OCR1A = 0x03FF; //max on
  OCR1A = 0x0001; //min on
  ICR1 = 0x1F3F; //1KHz

  //PIR sensor
  PORTC |= _BV(PC5);

  //Rotary encoder
  initRotaryEncoder();

  //Enable pull-up on unused ports.
  PORTB |= _BV(PB4) | _BV(PB6) | _BV(PB7);
  PORTC |= _BV(PC1) | _BV(PC2) | _BV(PC3) | _BV(PC4);
  PORTD |= _BV(PD2) | _BV(PD3) | _BV(PD4);

  event = 0;

  //Setup RTC
  initRTC();

  // Activate interrupts
  sei();

	memset(shiftbuffer, 0x00, SHIFTSIZE);
  shiftOut(shiftbuffer, SHIFTSIZE);
}

void addMinute(DS3231RegDateTime_t *dateTime)
{
  int8_t minutes = dateTime->minutes1 + dateTime->minutes10*10;
  int8_t hours = dateTime->hours1 + dateTime->hours10*10;

  minutes++;

  if (minutes >= 60)
  {
    minutes=0;
    hours++;
  }

  if (hours>=24)
  {
    hours=0;
  }

  dateTime->minutes10 = minutes/10;
  dateTime->minutes1 = minutes%10;

  dateTime->hours10 = hours/10;
  dateTime->hours1 = hours%10;

  dateTime->seconds1 = 0;
  dateTime->seconds10 = 0;
}

void substractMinute(DS3231RegDateTime_t *dateTime)
{
  int8_t minutes = dateTime->minutes1 + dateTime->minutes10*10;
  int8_t hours = dateTime->hours1 + dateTime->hours10*10;

  minutes--;

  if (minutes <= -1)
  {
    minutes=59;
    hours--;
  }

  if (hours<=-1)
  {
    hours=23;
  }

  dateTime->minutes10 = minutes/10;
  dateTime->minutes1 = minutes%10;

  dateTime->hours10 = hours/10;
  dateTime->hours1 = hours%10;

  dateTime->seconds1 = 0;
  dateTime->seconds10 = 0;
}
