//#ifndef OVERGLOW_H
//#define OVERGLOW_H
//
//#include <SPI.h>
//#include "pt.h"
//
//class Overglow{
//    public:
//    private:
//};
//
//typedef struct {
//  unsigned char ledId [7];
//} lighting_type;
//SPISettings TLC_SPI_SETTINGS(8000000, MSBFIRST, SPI_MODE0);
//unsigned char ledSpiBuffer[48];
//lighting_type lightingStruct;
//
//void lightingStructInitialize() {
//  lightingStruct.ledId[0] = 0;
//  lightingStruct.ledId[1] = 3;
//  lightingStruct.ledId[2] = 1;
//  lightingStruct.ledId[3] = 2;
//  lightingStruct.ledId[4] = 6;
//  lightingStruct.ledId[5] = 5;
//  lightingStruct.ledId[6] = 4;
//}
//// TLC5947 Pins7
//enum Pins{
//    TLC_DATA = 4,
//    TLC_CLK = 5,
//    TLC_LAT = 6,
//    TLC_OE = 7
//};
//void tlcSpiInitialize() {
//    // Initialize SPI Pins
//    pinMode(MOSI, OUTPUT);
//    pinMode(SCK, OUTPUT);
//  
//    // Ensure SPI Isn't Affected By Floating Chip Select
//    pinMode(SS, OUTPUT);
//  
//    // Initialize TLC Specific Pins
//    pinMode(TLC_LAT, OUTPUT);
//    pinMode(TLC_OE, OUTPUT);
//  
//    // Ensure TLC GPIO Doesn't Pull SPI (High Impedance)
//    pinMode(TLC_DATA, INPUT);
//    pinMode(TLC_CLK, INPUT);
//  
//    digitalWrite(TLC_OE, LOW);
//}
//void tlcSpiWrite(unsigned char id, unsigned short r, unsigned short g, unsigned short b) {
//    static unsigned short offset = 0;
//  
//    offset = (7 - id) * 4.5;
//  
//    // Odd Channel Byte Aligned
//    if (id % 2 == 1) {
//        ledSpiBuffer[offset] = (unsigned char)(b >> 4);
//        ledSpiBuffer[offset + 1] = (unsigned char)((b << 4) | (g >> 8));
//        ledSpiBuffer[offset + 2] = (unsigned char)(g);
//        ledSpiBuffer[offset + 3] = (unsigned char)(r >> 4);
//        ledSpiBuffer[offset + 4] |= (unsigned char)((r << 4) & 0xF0);
//    }
//    // Even Channel 4-Bit Offset
//    else {
//        ledSpiBuffer[offset] |= (unsigned char)(b >> 8);
//        ledSpiBuffer[offset + 1] = (unsigned char)(b);
//        ledSpiBuffer[offset + 2] = (unsigned char)(g >> 4);
//        ledSpiBuffer[offset + 3] = (unsigned char)((g << 4) | (r >> 8));
//        ledSpiBuffer[offset + 4] = (unsigned char)(r);
//    }
//}
//
//void tlcSpiUpdate() {
//    // Output TLC GS Data
//    SPI.beginTransaction(TLC_SPI_SETTINGS);
//    for (unsigned char i = 0; i < 36; ++i) {
//        SPI.transfer(ledSpiBuffer[i]);
//    }
//    SPI.endTransaction();
//  
//    // Latch TLC GS Shift Register
//    PORTD |= 0b10000000;
//    PORTD &= 0b01111111;
//  
//    // Clear SPI Buffer Array
//    memset(&ledSpiBuffer[0], 0, sizeof(ledSpiBuffer));
//}
//
//struct pt pt;
//unsigned long previousUpdate = micros();
//PT_THREAD(LinearBreatheUpdate(struct pt *pt)){
//    PT_BEGIN(pt);
//    
//    
//    unsigned long delta = micros() - previousUpdate;
//    PT_WAIT_UNTIL(pt, delta >= 16666);
//    auto value = round( 2048 * pow( sin(PI * millis()/1000/5 ), 2) );
//    for(auto i : lightingStruct.ledId){
//        tlcSpiWrite(i, value, value, value);
//    }
//    tlcSpiUpdate();
//    previousUpdate = micros();
//    
//    PT_END(pt);
//}
//
//#endif
