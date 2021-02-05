#ifndef KEY_H
#define KEY_H

#include <Arduino.h>

#include "KeypadProfile.h"

template<const char T>
char SimpleKeypress(void){ return T; }

class Key{
  
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
    
        static const int debounceMs = 10;
        
        struct ButtonState{
            bool depressed = false;
            unsigned long lastUpdate = 0;
        };
        
        Key(PinId pin, KeypressCallback* cb);
        
        void setState( ButtonState state );
        ButtonState getState();
        
        void setValuecb( KeypressCallback* cb );
        char getValue();
        void process();      
        
    private:
        ButtonState state{};
        PinId pin;
        KeypressCallback* valuecb;
        void inputPinInitialize();
    
};

#endif
