#include <Arduino.h>

#include "Setup.h"

// Millisecond Counter
ISR(TIMER3_COMPA_vect) {}

// Timer3 Setup 1ms Interrupt (16MHz Ext. Clk)
void msInterruptSetup(){
  noInterrupts();
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3 = 0;

  // COM3A Compare Match Register
  OCR3A = 250;
  // CTC Enable
  TCCR3B |= (1 << WGM32);
  // Prescaler 64
  TCCR3B |= (0 << CS32);
  TCCR3B |= (1 << CS31);
  TCCR3B |= (1 << CS30);
  // Enable COMP3A match register
  TIMSK3 |= (1 << OCIE3A);
  interrupts();
}
