#ifndef KEY_H
#define KEY_H

#include <Arduino.h>
#include <Keyboard.h>

struct KeyState{
    bool depressed = false;
    unsigned long lastUpdate = 0;
};

class Key{
  
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
        

        Key(PinId pin);
        
        KeyState getState() const;
        void setState( KeyState state );
        bool wasDepressed(){
            return this->state.depressed == true;
        }
        bool isDepressed(){
            return digitalRead(this->pin) == LOW;
        }
        bool isDebounced(){
            return (millis() - this->state.lastUpdate) >= (Key::debounceMs);
        }
        void process(){
            if ( this->isDepressed() && !this->wasDepressed() ) { // Pressed
                this->onKeyPress();
                this->state.depressed = true;
                this->state.lastUpdate = millis();
            } else if ( this->isDepressed() && this->wasDepressed() ){ // Held
                this->onKeyHold();
            } else if ( !this->isDepressed() && this->wasDepressed() && this->isDebounced() ) { // Released
                this->onKeyRelease();
                this->state.depressed = false;
            }
        }
    private:
    
        virtual void onKeyPress(){}
        virtual void onKeyHold(){}
        virtual void onKeyRelease(){}
        
        const PinId pin;
        KeyState state;
        
        void inputPinInitialize();
    
};

template<char C>
class SimpleKeypress : public Key{
    public:
        using Key::Key;
    private:
        void onKeyPress() override{ 
            Keyboard.press(C);
        }
        void onKeyHold() override{
        }
        void onKeyRelease() override{
            Keyboard.release(C);
        }
};
#endif
