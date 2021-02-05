#ifndef KEYPAD_H
#define KEYPAD_H

#include <Arduino.h>

#include "KeypadProfile.h"
#include "Key.h"
        
class Keypad{
  
    public:
        static const int debounceMs = 10;
        enum PinId{
            BTA_PIN     = A0,
            BTB_PIN     = A1,
            BTC_PIN     = A2,
            BTD_PIN     = A3,
            FXL_PIN     = A4,
            FXR_PIN     = A5,
            START_PIN   = 12,
            SERVICE_PIN = 10,
            TEST_PIN    = 11
        };
        struct KeypinPair{
            PinId pin;
            Key key;
        };
        void updateKey(PinId, Key::ButtonState&);
        Keypad(KeypadProfile);
        KeypinPair buttons[7]; 
        
    private:
        void inputPinInitialize();    // Set Button Pin Mode
        void inputStructInitialize(); // Initialize Button Struct
        
};

#endif
