#ifndef KEYPADPROFILE_H
#define KEYPADPROFILE_H

#include "Key.h"

struct KeypadProfile{
    KeypadProfile();
    KeypadProfile(Key*, Key*, Key*, Key*, Key*, Key*, Key*);
    Key* START;
    Key* BTA;
    Key* BTB;
    Key* BTC;
    Key* BTD;
    Key* FXL;
    Key* FXR;
//    Switch* SW;
};

#endif
