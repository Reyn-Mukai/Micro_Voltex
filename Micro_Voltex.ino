#include "Setup.h"
#include "Controller.h"
#include "pt.h"

Controller miniSDVX = Controller();

void setup() {
  msInterruptSetup(); // Timer3 Setup 1ms Interrupt (16MHz Ext. Clk)
  
  // Start Serial Debug Output
  Serial.begin(115200);
}

void loop() {
  miniSDVX.updateLeftEncoder();
  miniSDVX.updateRightEncoder();
}
