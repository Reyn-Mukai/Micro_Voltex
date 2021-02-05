#include "Keypad.h"
#include "KeypadProfile.h"
#include "Key.h"

Keypad::Keypad(KeypadProfile* profile) : buttons{
    { Key( Key::START_PIN, &(profile->START ) ) },
    { Key( Key::BTA_PIN,   &(profile->BTA ) ) },
    { Key( Key::BTB_PIN,   &(profile->BTB ) ) },
    { Key( Key::BTC_PIN,   &(profile->BTC ) ) },
    { Key( Key::BTD_PIN,   &(profile->BTD ) ) },
    { Key( Key::FXL_PIN,   &(profile->FXL ) ) },
    { Key( Key::FXR_PIN,   &(profile->FXR ) ) }
}{
    
}
void Keypad::process(){
  this->buttons[0].process();
  this->buttons[1].process();
  this->buttons[2].process();
  this->buttons[3].process();
  this->buttons[4].process();
  this->buttons[5].process();
  this->buttons[6].process();
//    for(auto i : this->buttons){
//        i.process();
//    }
}
