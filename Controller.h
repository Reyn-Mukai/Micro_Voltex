#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "./src/Encoder/Encoder.h"

class Controller{
  public:
    
    // === Definitions =======
    enum ButtonId{
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
    enum EncoderId{
      ENC_1_PIN_A = 0,
      ENC_1_PIN_B = 1,
      ENC_2_PIN_B = 2,
      ENC_2_PIN_A = 3
    };
    struct ButtonState{
      ButtonState(signed char a){
        this->ascii = a;
      }
      signed char ascii = 0x00;
      bool depressed = false;
      unsigned long timer = 0;
    };
    // =======================

    // === Public Functions ==
    Controller();
    void updateLeftEncoder();
    void updateRightEncoder();
    void updateKey(ButtonId, ButtonState&);
    // =======================

    // === Public Values =====
    static const int DebounceInterval = 10;
    // =======================
    
  private:
    Encoder encLeft  = Encoder(ENC_1_PIN_A, ENC_1_PIN_B);
    Encoder encRight = Encoder(ENC_2_PIN_A, ENC_2_PIN_B);
    void inputPinInitialize();    // Set Button Pin Mode
    void inputStructInitialize(); // Initialize Button Struct
};

#endif
