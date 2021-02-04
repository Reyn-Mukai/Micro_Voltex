#include "Setup.h"
#include "Faders.h"
#include "Keypad.h"
#include "KeypadProfile.h"

#include "pt.h"

// === Profiles =====================
KeypadProfile kpp = KeypadProfile();
// ==================================

// === Devices ======================
Faders faders = Faders();
Keypad keypad = Keypad();
// ==================================

void setup() {

  // Arduino Setup
  msInterruptSetup();   // Timer3 Setup 1ms Interrupt (16MHz Ext. Clk)
  Serial.begin(115200); // Start Serial Debug Output

  // Profile callbacks
  kpp.START    = [](){ return '1'; };
  kpp.BUTTON_A = [](){ return 'D'; };
  kpp.BUTTON_B = [](){ return 'F'; };
  kpp.BUTTON_C = [](){ return 'J'; };
  kpp.BUTTON_D = [](){ return 'K'; };
  kpp.FX_L     = [](){ return 'M'; };
  kpp.FX_R     = [](){ return 'C'; };
  
}

// Main execution (ONLY FAST EXECUTING CODE!!!)
// Slower code should be encased in a protothread so that the function is chunked into small sections of code so other functions can update.
void loop() {
  faders.updateLeft();  // [ ]us
  faders.updateRight(); // [ ]us
  // foreach protothread function, run next chunk.
}
