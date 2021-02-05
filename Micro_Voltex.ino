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
Keypad keypad = Keypad(kpp);
// ==================================

void setup() {

  // Arduino Setup
  msInterruptSetup();   // Timer3 Setup 1ms Interrupt (16MHz Ext. Clk)
  Serial.begin(115200); // Start Serial Debug Output

  // Profile callbacks
  kpp.START = SimpleKeypress<'1'>;
  kpp.BTA  = SimpleKeypress<'D'>;
  kpp.BTB  = SimpleKeypress<'F'>;
  kpp.BTC  = SimpleKeypress<'J'>;
  kpp.BTD  = SimpleKeypress<'K'>;
  kpp.FXL  = SimpleKeypress<'M'>;
  kpp.FXR  = SimpleKeypress<'C'>;
  
}

// Main execution (ONLY FAST EXECUTING CODE!!!)
// Slower code should be encased in a protothread so that the function is chunked into small sections of code so other functions can update.
void loop() {
  faders.updateLeft();  // [ ]us
  faders.updateRight(); // [ ]us
  Serial.println( keypad.buttons[0].key.getValue() );
  Serial.println( keypad.buttons[0].pin );
  // foreach protothread function, run next chunk.
}
