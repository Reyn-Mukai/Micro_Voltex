#ifndef KEYPAD_H
#define KEYPAD_H

#include "KeypadProfile.h"

class Keypad{
    
    public:
        Keypad();
        Keypad(KeypadProfile* profile);
        void process();
        void setProfile(KeypadProfile*);
        KeypadProfile* getProfile();
        
    private:
        KeypadProfile* profile;

};

extern Keypad keypad;

#endif
