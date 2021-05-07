#include <avr/interrupt.h>
#include <util/delay.h>

#include "../lib.h"

//Rotary encoder algorithm, Copyright 2011 Ben Buxton. Licenced under the GNU GPL Version 3.
//http://www.buxtronix.net/2011/10/rotary-encoders-done-properly.html

uint8_t rot_state = 0;

#define DIR_NONE 0x0
#define DIR_CW 0x10
#define DIR_CCW 0x20

#define R_START 0x0
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char ttable[7][4] = {
  // R_START
{R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
{R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
{R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
{R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
{R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
{R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
{R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};

//PCINT16..23
ISR(PCINT2_vect)
{
  //Rotary encoder, PC4, PC5.
  uint8_t pinstate = (PIND & _BV(PD7)) >> 6 | (PIND & _BV(PD6)) >> 6; //PD7 op bit1, PD6 op bit0
  rot_state = ttable[rot_state & 0x0F][pinstate];

  if ((rot_state & 0x30) == DIR_CW)
  event |= EVrotCW;

  if ((rot_state & 0x30) == DIR_CCW)
  event |= EVrotCCW;
  
  //Rotary encoder click, PD0.
  if ((PIND & _BV(PD5)) == 0)
  {
    _delay_ms(1);
    if ((PIND & _BV(PD5)) == 0)
      event |= EVrotClick;    
  }
}

void initRotaryEncoder(void)
{
  //Enable PCINT21, 22, 23
  PORTD |= _BV(PD5) | _BV(PD6) | _BV(PD7);
  PCMSK2 |= _BV(PCINT21) | _BV(PCINT22) | _BV(PCINT23);
  PCICR |= _BV(PCIE2);
}
