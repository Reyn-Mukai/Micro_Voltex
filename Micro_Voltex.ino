#include "Setup.h"
#include "Faders.h"
#include "pt.h"

Faders FadersSDVX = Faders();

void setup() {
  msInterruptSetup(); // Timer3 Setup 1ms Interrupt (16MHz Ext. Clk)
  
  // Start Serial Debug Output
  Serial.begin(115200);
}

void loop() {
  FadersSDVX.updateLeft();
  FadersSDVX.updateRight();
}
