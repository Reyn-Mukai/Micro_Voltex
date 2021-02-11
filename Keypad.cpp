#include "Keypad.h"

Keypad keypad = Keypad();

Keypad::Keypad() : profile(new KeypadProfile()) {}
Keypad::Keypad( KeypadProfile* profile ) : profile(profile) {}

void Keypad::process(){
    this->profile->START->process();
    this->profile->BTA->process();
    this->profile->BTB->process();
    this->profile->BTC->process();
    this->profile->BTD->process();
    this->profile->FXL->process();
    this->profile->FXR->process();
}

void Keypad::setProfile( KeypadProfile* profile ){
    this->profile = profile;
}

KeypadProfile* Keypad::getProfile(){
    return this->profile;
}
