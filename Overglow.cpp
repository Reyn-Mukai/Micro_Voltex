#include "Overglow.h"

Overglow overglow = Overglow();

SPISettings Overglow::TLC_SPI_SETTINGS = SPISettings(8000000, MSBFIRST, SPI_MODE0);

Overglow::Overglow(){
    this->initPins();
    SPI.beginTransaction(Overglow::TLC_SPI_SETTINGS);
}

void Overglow::initPins() {
    // Initialize SPI Pins
    pinMode(MOSI, OUTPUT);
    pinMode(SCK, OUTPUT);
  
    // Ensure SPI Isn't Affected By Floating Chip Select
    pinMode(SS, OUTPUT);
  
    // Initialize TLC Specific Pins
    pinMode(TLC_LAT, OUTPUT);
    pinMode(TLC_OE, OUTPUT);
  
    // Ensure TLC GPIO Doesn't Pull SPI (High Impedance)
    pinMode(TLC_DATA, INPUT);
    pinMode(TLC_CLK, INPUT);
  
    digitalWrite(TLC_OE, LOW);
}

void Overglow::setLed(unsigned char id, unsigned short r, unsigned short g, unsigned short b) {
    unsigned short offset = (7 - id) * 4.5;
  
    // Odd Channel Byte Aligned
    if (id % 2 == 1) {
        this->spiBuffer[offset] = (unsigned char)(b >> 4);
        this->spiBuffer[offset + 1] = (unsigned char)((b << 4) | (g >> 8));
        this->spiBuffer[offset + 2] = (unsigned char)(g);
        this->spiBuffer[offset + 3] = (unsigned char)(r >> 4);
        this->spiBuffer[offset + 4] |= (unsigned char)((r << 4) & 0xF0);
    }
    // Even Channel 4-Bit Offset
    else {
        this->spiBuffer[offset] |= (unsigned char)(b >> 8);
        this->spiBuffer[offset + 1] = (unsigned char)(b);
        this->spiBuffer[offset + 2] = (unsigned char)(g >> 4);
        this->spiBuffer[offset + 3] = (unsigned char)((g << 4) | (r >> 8));
        this->spiBuffer[offset + 4] = (unsigned char)(r);
    }
}

void Overglow::flush() {
    // Output TLC GS Data
    SPI.beginTransaction(Overglow::TLC_SPI_SETTINGS);
    for (int i = 0; i < 36; i++) SPI.transfer(this->spiBuffer[i]);
    SPI.endTransaction();
  
    // Latch TLC GS Shift Register
    PORTD |= 0b10000000;
    PORTD &= 0b01111111;
  
    // Clear SPI Buffer Array
    memset(&(this->spiBuffer[0]), 0, sizeof(this->spiBuffer));
}
