#include "KeypadProfile.h"

KeypadProfile::KeypadProfile() :
    START(new Key(Key::START_PIN)),
    BTA(new Key(Key::BTA_PIN)),
    BTB(new Key(Key::BTB_PIN)),
    BTC(new Key(Key::BTC_PIN)),
    BTD(new Key(Key::BTD_PIN)),
    FXL(new Key(Key::FXL_PIN)),
    FXR(new Key(Key::FXR_PIN))
{
  
}

KeypadProfile::KeypadProfile(
    Key* START, 
    Key* BTA, 
    Key* BTB, 
    Key* BTC, 
    Key* BTD, 
    Key* FXL, 
    Key* FXR
) : KeypadProfile() {
    this->START = START;
    this->BTA = BTA;
    this->BTB = BTB;
    this->BTC = BTC;
    this->BTD = BTD;
    this->FXL = FXL;
    this->FXR = FXR;
}
