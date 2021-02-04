#include <Arduino.h>
#include <Mouse.h>
#include <Keyboard.h>

#include "Controller.h"
#include "./src/Encoder/Encoder.h"

Controller::Controller(){
  inputPinInitialize();
//  buttonStates = arx::map<ButtonId, ButtonState>();
//  auto a = Controller::ButtonState('1');
//  Controller::buttonStates.insert( Controller::BTA_PIN, a );
//    {BTB_PIN,     ButtonState('2')},
//    {BTC_PIN,     ButtonState('3')},
//    {BTD_PIN,     ButtonState('4')},
//    {FXL_PIN,     ButtonState('5')},
//    {FXR_PIN,     ButtonState('6')},
//    {START_PIN,   ButtonState('7')},
//    {SERVICE_PIN, ButtonState('8')},
//    {TEST_PIN,    ButtonState('9')}
//  };
}

void Controller::inputPinInitialize(){
  // Pin Mode Declarations
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

void Controller::updateLeftEncoder() {
  if (encLeft.read() != 0) {
    //pixelEncoderSetLeftFlag();
    Mouse.move(encLeft.read(), 0, 0);
  }
  encLeft.write(0);
}
void Controller::updateRightEncoder() {
  if (encRight.read() != 0) {
    //pixelEncoderSetRightFlag();
    Mouse.move(0, encRight.read(), 0);
  }
  encRight.write(0);
}

void Controller::updateKey(Controller::ButtonId id, Controller::ButtonState& state){
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
