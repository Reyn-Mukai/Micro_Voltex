#ifndef KEYPAD_H
#define KEYPAD_H

#include "KeypadProfile.h"
#include "Key.h"
        
class Keypad{
  
    public:
        Keypad(KeypadProfile*);
        void process();
        
    private:
        Key buttons[7]; 
        
};

#endif
