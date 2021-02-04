#ifndef KEYPAD_H
#define KEYPAD_H

#include <Arduino.h>

class Keypad{
    public:
        
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

        struct ButtonState{
            bool depressed = false;
            unsigned long delta = 0;
        };

        Keypad();
        void updateKey(PinId, ButtonState&);

        static const int debounceMs = 10;

        
    private:


        void inputPinInitialize();    // Set Button Pin Mode
        void inputStructInitialize(); // Initialize Button Struct
};

#endif
