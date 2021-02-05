#include "Key.h"
#include <Keyboard.h>

Key::Key(PinId pin, KeypressCallback* cb){
    this->valuecb = cb;
    this->pin = pin;
    inputPinInitialize();
//    this->state.lastUpdate = millis();
}

void Key::setState( ButtonState state ){
    this->state = state; 
}

Key::ButtonState Key::getState(){
    return this->state; 
};

void Key::setValuecb( KeypressCallback* cb ){
    this->valuecb = cb; 
}

char Key::getValue(){
    return (*this->valuecb)(); 
};

void Key::process(){
    const bool wasDepressed = this->state.depressed == true;
    const bool isDepressed = digitalRead(this->pin) == LOW;
    const auto isDebounced = [=]() -> bool { return millis() - this->state.lastUpdate >= Key::debounceMs; };
        
    if ( isDepressed && !wasDepressed ) {
        Serial.println("pressed");
        Keyboard.press(this->getValue());
        this->state.depressed = true;
        this->state.lastUpdate = millis();
    }
    else if ( !isDepressed && wasDepressed && isDebounced() ) {
        Serial.println("depressed");
        Keyboard.release(this->getValue());
        this->state.depressed = false;
    }
}

void Key::inputPinInitialize(){
    pinMode(this->pin, INPUT_PULLUP);
}
