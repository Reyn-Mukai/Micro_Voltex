#include <Arduino.h>
#include <Mouse.h>
#include <Keyboard.h>
#include "./src/Encoder/Encoder.h"
#include "Input.h"
#include "Lighting.h"

// Button Input Pins
#define BTA_PIN     A0
#define BTB_PIN     A1
#define BTC_PIN     A2
#define BTD_PIN     A3
#define FXL_PIN     A4
#define FXR_PIN     A5
#define START_PIN   12
#define SERVICE_PIN 10
#define TEST_PIN    11

// Encoder Pins
#define ENC_1_PIN_A 0
#define ENC_1_PIN_B 1
#define ENC_2_PIN_A 3
#define ENC_2_PIN_B 2

// Software Debounce Interval (ms)
#define DEBOUNCE 10

// Encoder
Encoder encLeft(ENC_1_PIN_A, ENC_1_PIN_B);
Encoder encRight(ENC_2_PIN_A, ENC_2_PIN_B);

// Global Input Struct
input_type inputStruct;

void inputPinInitialize() {
  // Pin Mode Declarations
  pinMode(BTA_PIN, INPUT_PULLUP);
  pinMode(BTB_PIN, INPUT_PULLUP);
  pinMode(BTC_PIN, INPUT_PULLUP);
  pinMode(BTD_PIN, INPUT_PULLUP);
  pinMode(FXL_PIN, INPUT_PULLUP);
  pinMode(FXR_PIN, INPUT_PULLUP);
  pinMode(SERVICE_PIN, INPUT_PULLUP);
  pinMode(TEST_PIN, INPUT_PULLUP);
  pinMode(START_PIN, INPUT_PULLUP);
}

void inputStructInitialize() {
  inputStruct.buttonPin[0] = BTA_PIN;
  inputStruct.buttonPin[1] = BTB_PIN;
  inputStruct.buttonPin[2] = BTC_PIN;
  inputStruct.buttonPin[3] = BTD_PIN;
  inputStruct.buttonPin[4] = FXL_PIN;
  inputStruct.buttonPin[5] = FXR_PIN;
  inputStruct.buttonPin[6] = START_PIN;
  inputStruct.buttonPin[7] = SERVICE_PIN;
  inputStruct.buttonPin[8] = TEST_PIN;

  memset(inputStruct.keyTimer, 0, 9 * sizeof(unsigned long));

  memset(inputStruct.buttonState, false, 2);

  inputStruct.asciiKey[0] = 0x64;
  inputStruct.asciiKey[1] = 0x66;
  inputStruct.asciiKey[2] = 0x6A;
  inputStruct.asciiKey[3] = 0x6B;
  inputStruct.asciiKey[4] = 0x6D;
  inputStruct.asciiKey[5] = 0x63;
  inputStruct.asciiKey[6] = 0x31;
  inputStruct.asciiKey[7] = 0x00;
  inputStruct.asciiKey[8] = 0x00;

  inputStruct.asciiKeyAlt[0] = 0x00;
  inputStruct.asciiKeyAlt[1] = 0x00;
  inputStruct.asciiKeyAlt[2] = 0x00;
  inputStruct.asciiKeyAlt[3] = 0x00;
  inputStruct.asciiKeyAlt[4] = 0x00;
  inputStruct.asciiKeyAlt[5] = 0x00;
  inputStruct.asciiKeyAlt[6] = 0x00;
  inputStruct.asciiKeyAlt[7] = 0x5B;
  inputStruct.asciiKeyAlt[8] = 0x5D;
}

void checkAllKeyEvents() {
  for (unsigned char i = 0; i < 9; ++i) {
    if (digitalRead(inputStruct.buttonPin[i]) == LOW && inputStruct.buttonState[i] == false) {
      Keyboard.press(inputStruct.asciiKey[i]);
      inputStruct.buttonState[i] = true;
      inputStruct.keyTimer[i] = millis();
    }
    else if (digitalRead(inputStruct.buttonPin[i]) == HIGH && inputStruct.buttonState[i] == true && millis() - inputStruct.keyTimer[i] > DEBOUNCE) {
      Keyboard.release(inputStruct.asciiKey[i]);
      inputStruct.buttonState[i] = false;
    }
  }
}

void encFuncLeft() {
  if (encLeft.read() != 0) {
    pixelEncoderSetLeftFlag();
    Mouse.move(encLeft.read(), 0, 0);
  }
  encLeft.write(0);
}

void encFuncRight() {
  if (encRight.read() != 0) {
    pixelEncoderSetRightFlag();
    Mouse.move(0, encRight.read(), 0);
  }
  encRight.write(0);
}
