/**
 * @file Arduboy2Beep.cpp
 * \brief
 * Classes to generate simple square wave tones on the Arduboy speaker pins.
 */

#include <Arduino.h>
#include "Arduboy2Beep.h"

//Mega Speaker pin 1, Timer 3A, Port E bit 3, Arduino pin 5

uint8_t BeepPin1::duration = 0;

void BeepPin1::begin()
{
  TCCR3A = 0;
  TCCR3B = (bit(WGM32) | bit(CS31)); // CTC mode. Divide by 8 clock prescale
}

void BeepPin1::tone(uint16_t count)
{
  tone(count, 0);
}

void BeepPin1::tone(uint16_t count, uint8_t dur)
{
  duration = dur;
  TCCR3A = bit(COM3A0); // set toggle on compare mode (which connects the pin)
  OCR3A = count; // load the count (16 bits), which determines the frequency
}

void BeepPin1::timer()
{
  if (duration && (--duration == 0)) {
    TCCR3A = 0; // set normal mode (which disconnects the pin)
  }
}

void BeepPin1::noTone()
{
  duration = 0;
  TCCR3A = 0; // set normal mode (which disconnects the pin)
}


//No second pin defined. Beep 2 will run nothing
uint8_t BeepPin2::duration = 0;

void BeepPin2::begin()
{
}

void BeepPin2::tone(uint16_t count)
{
  tone(count, 0);
}

void BeepPin2::tone(uint16_t count, uint8_t dur)
{
  (void) count; // parameter not used

  duration = dur;
}

void BeepPin2::timer()
{
  if (duration) {
    --duration;
  }
}

void BeepPin2::noTone()
{
  duration = 0;
}
