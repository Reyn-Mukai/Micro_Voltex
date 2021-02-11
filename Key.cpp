#include "Key.h"
#include <Keyboard.h>

Key::Key(PinId pin) : 
    pin(pin)
{
    inputPinInitialize();
}

void Key::setState( KeyState state ){
    this->state = state;
}

KeyState Key::getState() const {
    return this->state; 
};

void Key::inputPinInitialize(){
    pinMode(this->pin, INPUT_PULLUP);
}
