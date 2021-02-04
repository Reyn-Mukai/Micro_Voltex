#ifndef KEYPADPROFILE_H
#define KEYPADPROFILE_H

#include "GlowProfile.h"

using KeypressCallback = char (*)(void);

class KeypadProfile{
    public:
        KeypressCallback START    = [](){ return '1'; };
        KeypressCallback BUTTON_A = [](){ return 'D'; };
        KeypressCallback BUTTON_B = [](){ return 'F'; };
        KeypressCallback BUTTON_C = [](){ return 'J'; };
        KeypressCallback BUTTON_D = [](){ return 'K'; };
        KeypressCallback FX_L     = [](){ return 'M'; };
        KeypressCallback FX_R     = [](){ return 'C'; };
};

#endif
