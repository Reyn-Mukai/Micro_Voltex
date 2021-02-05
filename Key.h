#ifndef KEY_H
#define KEY_H

#include "KeypadProfile.h"

template<const char T>
char SimpleKeypress(void){ return T; }

class Key{
  
    public:
    
        struct ButtonState{
            bool depressed = false;
            unsigned long delta = 0;
        };
        
        Key(KeypressCallback cb){ this->valuecb = cb; }
        
        void setState( ButtonState state ){ this->state = state; }
        ButtonState getState(){ return this->state; };
        
        void setValuecb( KeypressCallback cb ){ this->valuecb = cb; }
        char getValue(){ return this->valuecb(); };
        
        
    private:
        KeypressCallback valuecb;
        ButtonState state;
    
};

#endif
