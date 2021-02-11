#include <Arduino.h>
#include <math.h>

#include "Setup.h"
#include "Faders.h"
#include "Keypad.h"
#include "KeypadProfile.h"
#include "Key.h"
//#include "Overglow.h"

#include "Utility.h"

#include "pt.h"

// !!! Dont send capital letters !!!!!!!!!!!!!!!!!!!!

// Theres a hardware limitation where the shift key has to be emulated, therefore 
// making it so a held capital 'A' will cause the next input to also be capital 
// regardless of if it should be capital or not.

// You can send a separate shift input as a keypress with no problems though.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

extern KeypadProfile kpp, kpp2;
extern Keypad keypad;

class ProfileSwitch : public Key{
    public:
        using Key::Key;
    private:
        void onKeyPress() override{
        }
        void onKeyHold() override{
        }
        void onKeyRelease() override{
            keypad.setProfile( ( keypad.getProfile() == &kpp ) ? &kpp2 : &kpp );
        }
};

// === Profiles =====================
KeypadProfile kpp = KeypadProfile(
    new ProfileSwitch(Key::START_PIN),
    new SimpleKeypress<'a'>(Key::BTA_PIN),
    new SimpleKeypress<'b'>(Key::BTB_PIN),
    new SimpleKeypress<'c'>(Key::BTC_PIN),
    new SimpleKeypress<'d'>(Key::BTD_PIN),
    new SimpleKeypress<'f'>(Key::FXL_PIN),
    new SimpleKeypress<'x'>(Key::FXR_PIN)
);
KeypadProfile kpp2 = KeypadProfile(
    new ProfileSwitch(Key::START_PIN),
    new SimpleKeypress<'q'>(Key::BTA_PIN),
    new SimpleKeypress<'w'>(Key::BTB_PIN),
    new SimpleKeypress<'e'>(Key::BTC_PIN),
    new SimpleKeypress<'r'>(Key::BTD_PIN),
    new SimpleKeypress<'o'>(Key::FXL_PIN),
    new SimpleKeypress<'p'>(Key::FXR_PIN)
);
// ==================================

void setup() {

    // Arduino Setup
    msInterruptSetup();   // Timer3 Setup 1ms Interrupt (16MHz Ext. Clk)
    Serial.begin(115200); // Start Serial Debug Output

    // Profile Init
    keypad.setProfile(&kpp);
    
//  PT_INIT(&pt);
//  tlcSpiInitialize();
//  lightingStructInitialize();
//  SPI.beginTransaction(TLC_SPI_SETTINGS);

}

// Main execution (ONLY FAST EXECUTING CODE!!!)
// Slower code should be encased in a protothread so that the function is chunked into small sections of code so other functions can update.
void loop() {
    faders.updateLeft();
    faders.updateRight();
    keypad.process();
}
