#include "Setup.h"
#include "Faders.h"
#include "Keypad.h"
#include "KeypadProfile.h"
#include "Key.h"

#include "pt.h"

// === Profiles =====================
KeypadProfile kpp = KeypadProfile();
// ==================================

// === Devices ======================
Faders faders = Faders();
Keypad keypad = Keypad(&kpp);
// ==================================

void setup() {

  // Arduino Setup
  msInterruptSetup();   // Timer3 Setup 1ms Interrupt (16MHz Ext. Clk)
  Serial.begin(115200); // Start Serial Debug Output

  // Profile callbacks
  kpp.START = SimpleKeypress<'1'>;
  kpp.BTA  = SimpleKeypress<'d'>;
  kpp.BTB  = SimpleKeypress<'f'>;
  kpp.BTC  = SimpleKeypress<'j'>;
  kpp.BTD  = SimpleKeypress<'k'>;
  kpp.FXL  = SimpleKeypress<'m'>;
  kpp.FXR  = SimpleKeypress<'c'>;
  
}

// Main execution (ONLY FAST EXECUTING CODE!!!)
// Slower code should be encased in a protothread so that the function is chunked into small sections of code so other functions can update.
void loop() {
  faders.updateLeft();  // [ ]us
  faders.updateRight(); // [ ]us
  keypad.process();
  // foreach protothread function, run next chunk.
}
