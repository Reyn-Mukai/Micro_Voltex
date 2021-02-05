#include "Keypad.h"
#include "KeypadProfile.h"
#include "Key.h"

Keypad::Keypad( KeypadProfile profile ) : buttons{
    { START_PIN, Key( profile.START ) },
    { BTA_PIN,   Key( profile.BTA ) },
    { BTB_PIN,   Key( profile.BTB ) },
    { BTC_PIN,   Key( profile.BTC ) },
    { BTD_PIN,   Key( profile.BTD ) },
    { FXL_PIN,   Key( profile.FXL ) },
    { FXR_PIN,   Key( profile.FXR ) }
}{}

//Keypad::Keypad( KeypadProfile profile )
//    inputPinInitialize();
//}

void Keypad::inputPinInitialize(){
    pinMode(BTA_PIN,     INPUT_PULLUP);
    pinMode(BTB_PIN,     INPUT_PULLUP);
    pinMode(BTC_PIN,     INPUT_PULLUP);
    pinMode(BTD_PIN,     INPUT_PULLUP);
    pinMode(FXL_PIN,     INPUT_PULLUP);
    pinMode(FXR_PIN,     INPUT_PULLUP);
    pinMode(SERVICE_PIN, INPUT_PULLUP);
    pinMode(TEST_PIN,    INPUT_PULLUP);
    pinMode(START_PIN,   INPUT_PULLUP);
}


void Keypad::updateKey(Keypad::PinId id, Key::ButtonState& state){
//  if (digitalRead(Id) == LOW && inputStruct.buttonState[i] == false) {
//    Keyboard.press(inputStruct.asciiKey[i]);
//    inputStruct.buttonState[i] = true;
//    inputStruct.keyTimer[i] = millis();
//  }
//  else if (digitalRead(inputStruct.buttonPin[i]) == HIGH && inputStruct.buttonState[i] == true && millis() - inputStruct.keyTimer[i] > DEBOUNCE) {
//    Keyboard.release(inputStruct.asciiKey[i]);
//    inputStruct.buttonState[i] = false;
//  }
}
