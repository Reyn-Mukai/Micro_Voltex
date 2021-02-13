#include <Arduino.h>
#include <math.h>

#include "Setup.h"
#include "Faders.h"
#include "Keypad.h"
#include "KeypadProfile.h"
#include "Key.h"
#include "Overglow.h"

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
class NoInput : public Key{
    public:
        using Key::Key;
    private:
        void onKeyPress() override{
        }
        void onKeyHold() override{
        }
        void onKeyRelease() override{
        }
};

// === Profiles =====================
KeypadProfile kpp = KeypadProfile(
    new NoInput(Key::START_PIN),
    new NoInput(Key::BTA_PIN),
    new NoInput(Key::BTB_PIN),
    new NoInput(Key::BTC_PIN),
    new NoInput(Key::BTD_PIN),
    new NoInput(Key::FXL_PIN),
    new NoInput(Key::FXR_PIN)
//    new ProfileSwitch(Key::START_PIN),
//    new SimpleKeypress<'a'>(Key::BTA_PIN),
//    new SimpleKeypress<'b'>(Key::BTB_PIN),
//    new SimpleKeypress<'c'>(Key::BTC_PIN),
//    new SimpleKeypress<'d'>(Key::BTD_PIN),
//    new SimpleKeypress<'f'>(Key::FXL_PIN),
//    new SimpleKeypress<'x'>(Key::FXR_PIN)
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

struct pt ept;

// 24-bit (12 bit getters)
// 8bits * 3 = 24 bits (2 12bit numbers)
//struct tbi{
//    unsigned int value: 12;
//};

// python3: a = [round(4095*m.sin(m.pi*x/64)) for x in range(0, 64)]
int it = 0;
bool up = true;
unsigned long prev = 0;
int lut[64] = {
    0, 2, 10, 22, 39, 61, 88, 120, 156, 197, 242, 291, 345, 403, 465, 530, 
    600, 672, 749, 828, 910, 995, 1082, 1172, 1264, 1358, 1453, 1550, 1648, 
    1747, 1847, 1947, 2048, 2148, 2248, 2348, 2447, 2545, 2642, 2737, 2831, 
    2923, 3013, 3100, 3185, 3267, 3346, 3423, 3495, 3565, 3630, 3692, 3750, 
    3804, 3853, 3898, 3939, 3975, 4007, 4034, 4056, 4073, 4085, 4093
};

void setup() {

    // Arduino Setup
    msInterruptSetup();   // Timer3 Setup 1ms Interrupt (16MHz Ext. Clk)
    Serial.begin(115200); // Start Serial Debug Output

    // Profile Init
    keypad.setProfile(&kpp);
    
    PT_INIT(&ept);
    overglow.initialize();
    overglow.lightingStructInitialize();
    SPI.beginTransaction(overglow.TLC_SPI_SETTINGS);
    
    for(auto i : overglow.lightingStruct.ledId){
        overglow.tlcSpiWrite(i, 4095, 4095, 4095);
    }
    overglow.tlcSpiUpdate();

    prev = millis();

}

// Main execution (ONLY FAST EXECUTING CODE!!!)
// Slower code should be encased in a protothread so that the function is chunked into small sections of code so other functions can update.
void loop() {
    faders.updateLeft();
    faders.updateRight();
    keypad.process();

    // Breathe lighting
    auto delta = millis() - prev;
    if(delta >= 25){
//        auto c = lut[(it < 64) ? it++ : it=0];
        int c = lut[it];
        Serial.println(c, DEC);
        if(up){
            if(it >= 63){
                up = false;
                it--;
            } else {
                it++;
            }
        }else{
            if(it <= 0){
                up = true;
                it++;
            } else {
                it--;
            }
        }
        for(auto i : overglow.lightingStruct.ledId){
            overglow.tlcSpiWrite(i, c, c, c);
        }
        overglow.tlcSpiUpdate();
        prev = millis();
    }
}
