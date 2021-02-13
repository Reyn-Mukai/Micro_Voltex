#ifndef OVERGLOW_H
#define OVERGLOW_H

#include <SPI.h>

class Overglow{
    public:
    
        // TLC5947 Pins
        enum Pins{
            TLC_DATA = 4,
            TLC_CLK  = 5,
            TLC_LAT  = 6,
            TLC_OE   = 7
        };

        enum LedId{
            START_ID = 0,
            BTA_ID   = 3,
            BTB_ID   = 1,
            BTC_ID   = 2,
            BTD_ID   = 6,
            FXL_ID   = 5,
            FXR_ID   = 4
        };
        
        void setLed(unsigned char id, unsigned short r, unsigned short g, unsigned short b);
        void flush();

        Overglow();
        
    private:
        static SPISettings TLC_SPI_SETTINGS;
        unsigned char spiBuffer[48];
       
        void initPins();
        
};

extern Overglow overglow;

#endif
