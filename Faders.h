#ifndef FADERS_H
#define FADERS_H

#include "src/Encoder/Encoder.h"

class Faders{
    public:
        enum PinId{
            ENC_1_PIN_A = 0,
            ENC_1_PIN_B = 1,
            ENC_2_PIN_B = 2,
            ENC_2_PIN_A = 3
        };
        void updateLeft();
        void updateRight();
    private:
        Encoder encLeft  = Encoder(ENC_1_PIN_A, ENC_1_PIN_B);
        Encoder encRight = Encoder(ENC_2_PIN_A, ENC_2_PIN_B);
};

extern Faders faders;

#endif
