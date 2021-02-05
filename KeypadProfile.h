#ifndef KEYPADPROFILE_H
#define KEYPADPROFILE_H

//#include "Keypad.h"

using KeypressCallback = char (*)(void);

class KeypadProfile{
    public:
        KeypressCallback START = [](){ return '1'; };
        KeypressCallback BTA   = [](){ return 'D'; };
        KeypressCallback BTB   = [](){ return 'F'; };
        KeypressCallback BTC   = [](){ return 'J'; };
        KeypressCallback BTD   = [](){ return 'K'; };
        KeypressCallback FXL   = [](){ return 'M'; };
        KeypressCallback FXR   = [](){ return 'C'; };
};

#endif
