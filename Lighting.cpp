#include <Arduino.h>
#include <SPI.h>
#include "./src/NeoPixel/Adafruit_NeoPixel.h"
#include "Input.h"
#include "Lighting.h"

// TLC5947 Pins
#define TLC_DATA 4
#define TLC_CLK  5
#define TLC_LAT  6
#define TLC_OE   7

// NeoPixel
#define PIXEL_COUNT 8

// LED Lighting Levels
#define LIGHTING_LEVELS 64

SPISettings TLC_SPI_SETTINGS(8000000, MSBFIRST, SPI_MODE0);

Adafruit_NeoPixel pixel(PIXEL_COUNT, 8, NEO_GRB + NEO_KHZ800);

unsigned char ledSpiBuffer[48];
bool pixelEncoderLeftFlag;
bool pixelEncoderRightFlag;

// LED Lighting
float logArray[LIGHTING_LEVELS];

lighting_type lightingStruct;

void lightingStructInitialize() {
  lightingStruct.ledId[0] = 0;
  lightingStruct.ledId[1] = 3;
  lightingStruct.ledId[2] = 1;
  lightingStruct.ledId[3] = 2;
  lightingStruct.ledId[4] = 6;
  lightingStruct.ledId[5] = 5;
  lightingStruct.ledId[6] = 4;
}

void rand256(unsigned char *input) {
  // Faster Than Random(x,y) 6us vs. 80us
  *input = *input ^ (unsigned char)(micros()) ^ (unsigned char)(millis());
}

void generateInverseLogCurve() {
  for (unsigned char i = 1; i < (LIGHTING_LEVELS + 1); ++i) {
    //logArray[LIGHTING_LEVELS - i] = (unsigned char)((log(i) / log(64)) * 255);
    if (i == 1) {
      logArray[LIGHTING_LEVELS - i] = 1;
    }
    else {
      logArray[LIGHTING_LEVELS - i] = (float)(1.0 - ((log(i) / log(64))));
    }
  }
}

void tlcSpiInitialize() {
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

void pixelInitialize() {
  // Start Neopixels
  pixel.begin();
  pixel.show();
}

void tlcSpiWrite(unsigned char id, unsigned short r, unsigned short g, unsigned short b) {
  static unsigned short offset = 0;

  offset = (7 - id) * 4.5;

  // Odd Channel Byte Aligned
  if (id % 2 == 1) {
    ledSpiBuffer[offset] = (unsigned char)(b >> 4);
    ledSpiBuffer[offset + 1] = (unsigned char)((b << 4) | (g >> 8));
    ledSpiBuffer[offset + 2] = (unsigned char)(g);
    ledSpiBuffer[offset + 3] = (unsigned char)(r >> 4);
    ledSpiBuffer[offset + 4] |= (unsigned char)((r << 4) & 0xF0);
  }
  // Even Channel 4-Bit Offset
  else {
    ledSpiBuffer[offset] |= (unsigned char)(b >> 8);
    ledSpiBuffer[offset + 1] = (unsigned char)(b);
    ledSpiBuffer[offset + 2] = (unsigned char)(g >> 4);
    ledSpiBuffer[offset + 3] = (unsigned char)((g << 4) | (r >> 8));
    ledSpiBuffer[offset + 4] = (unsigned char)(r);
  }
}

void tlcSpiUpdate() {
  // Output TLC GS Data
  SPI.beginTransaction(TLC_SPI_SETTINGS);
  for (unsigned char i = 0; i < 36; ++i) {
    SPI.transfer(ledSpiBuffer[i]);
  }
  SPI.endTransaction();

  // Latch TLC GS Shift Register
  PORTD |= 0b10000000;
  PORTD &= 0b01111111;

  // Clear SPI Buffer Array
  memset(&ledSpiBuffer[0], 0, sizeof(ledSpiBuffer));
}

void tlcButtonReactive() {
  for (unsigned char i = 0; i < 7; ++i) {
    if (inputStruct.buttonState[i] == true) {
      switch (i) {
        case 0:
        case 1:
        case 2:
        case 3:
          tlcSpiWrite(lightingStruct.ledId[i], 0, 0, 2048);
          break;
        case 4:
        case 5:
          tlcSpiWrite(lightingStruct.ledId[i], 2048, 96, 0);
          break;
        case 6:
          tlcSpiWrite(lightingStruct.ledId[i], 1024, 1024, 1024);
          break;
      }
    }
    else {
      tlcSpiWrite(lightingStruct.ledId[i], 0, 0, 0);
    }
  }
}

void tlcButtonReactiveFade(unsigned short stepInterval) {
  static unsigned long lastDegenUpdate[7] = {0, 0, 0, 0, 0, 0, 0};
  static unsigned char degenLevel[7] = {0, 0, 0, 0, 0, 0, 0};

  for (unsigned char i = 0; i < 7; ++i) {
    if (inputStruct.buttonState[i] == true) {
      switch (i) {
        case 0:
        case 1:
        case 2:
        case 3:
          tlcSpiWrite(lightingStruct.ledId[i], 0, 0, 2048 * logArray[LIGHTING_LEVELS - 1]);
          break;
        case 4:
        case 5:
          tlcSpiWrite(lightingStruct.ledId[i], 2048 * logArray[LIGHTING_LEVELS - 1], 96 * logArray[LIGHTING_LEVELS - 1], 0);
          break;
        case 6:
          tlcSpiWrite(lightingStruct.ledId[i], 2048 * logArray[degenLevel[i]], 257 * logArray[degenLevel[i]], 968 * logArray[degenLevel[i]]);
          break;
      }
      lastDegenUpdate[i] = msCounter;
      degenLevel[i] = 63;
    }
    else {
      if (msCounter - lastDegenUpdate[i] >= stepInterval && degenLevel[i] > 0) {
        lastDegenUpdate[i] = msCounter;
        --degenLevel[i];
        switch (i) {
          case 0:
          case 1:
          case 2:
          case 3:
            tlcSpiWrite(lightingStruct.ledId[i], 0, 0, 2048 * logArray[degenLevel[i]]);
            break;
          case 4:
          case 5:
            tlcSpiWrite(lightingStruct.ledId[i], 2048 * logArray[degenLevel[i]], 96 * logArray[degenLevel[i]], 0);
            break;
          case 6:
            tlcSpiWrite(lightingStruct.ledId[i], 2048 * logArray[degenLevel[i]], 257 * logArray[degenLevel[i]], 968 * logArray[degenLevel[i]]);
            break;
        }
      }
    }
  }
}

void pixelBreatheFixed(unsigned short stepInterval, unsigned char r, unsigned char g, unsigned char b) {
  static unsigned long lastBreatheUpdate = 0;
  static unsigned char lastInverseLogLevel = 0;
  static bool breatheIncreasing = true;

  if (msCounter - lastBreatheUpdate >= stepInterval) {
    if (breatheIncreasing) {
      if (lastInverseLogLevel < LIGHTING_LEVELS - 1) {
        ++lastInverseLogLevel;
      }
      else {
        breatheIncreasing = false;
      }
    }
    else {
      if (lastInverseLogLevel > 0) {
        --lastInverseLogLevel;
      }
      else {
        breatheIncreasing = true;
      }
    }
    for (unsigned char i = 0; i < PIXEL_COUNT; ++i) {
      pixel.setPixelColor(i, r * logArray[lastInverseLogLevel], g * logArray[lastInverseLogLevel], b * logArray[lastInverseLogLevel]);
    }
    lastBreatheUpdate = msCounter;
  }
}

void pixelBreatheRandom(unsigned short stepInterval) {
  static unsigned long lastBreatheUpdate = 0;
  static unsigned char lastInverseLogLevel = 0;
  static unsigned char r;
  static unsigned char g;
  static unsigned char b;
  static bool breatheIncreasing = true;

  if (msCounter - lastBreatheUpdate >= stepInterval) {
    if (!lastInverseLogLevel)
    {
      rand256(&r);
      rand256(&g);
      rand256(&b);
    }

    if (breatheIncreasing) {
      if (lastInverseLogLevel < LIGHTING_LEVELS - 1) {
        ++lastInverseLogLevel;
      }
      else {
        breatheIncreasing = false;
      }
    }
    else {
      if (lastInverseLogLevel > 0) {
        --lastInverseLogLevel;
      }
      else {
        breatheIncreasing = true;
      }
    }

    for (unsigned char i = 0; i < PIXEL_COUNT; ++i) {
      pixel.setPixelColor(i, r * logArray[lastInverseLogLevel], g * logArray[lastInverseLogLevel], b * logArray[lastInverseLogLevel]);
    }

    lastBreatheUpdate = msCounter;
  }
}

void pixelColorShift(unsigned short stepInterval, unsigned char stepLevels) {
  static unsigned long lastShiftUpdate = 0;
  static float rDelta = 0;
  static float gDelta = 0;
  static float bDelta = 0;
  static float r = 0;
  static float g = 0;
  static float b = 0;
  static unsigned char shiftIndex = 0;

  static unsigned char temp;
  static unsigned long temp1;
  static unsigned long temp2;

  if (msCounter - lastShiftUpdate >= stepInterval) {
    if (shiftIndex >= stepLevels || shiftIndex == 0) {
      shiftIndex = 0;

      temp1 = micros();
      rand256(&temp);
      rand256(&temp);
      rand256(&temp);
      temp2 = micros();

      Serial.print("Rand256 - ");
      Serial.println(temp2 - temp1);

      temp1 = micros();
      rDelta = random(0, 255);
      gDelta = random(0, 255);
      bDelta = random(0, 255);
      temp2 = micros();

      Serial.print("Random  - ");
      Serial.println(temp2 - temp1);

      rDelta = (rDelta - r) / stepLevels;
      gDelta = (gDelta - g) / stepLevels;
      bDelta = (bDelta - b) / stepLevels;
    }

    if (shiftIndex < stepLevels) {
      r += rDelta;
      g += gDelta;
      b += bDelta;

      ++shiftIndex;

      for (unsigned char i = 0; i < PIXEL_COUNT; ++i) {
        pixel.setPixelColor(i, (unsigned char)r, (unsigned char)g, (unsigned char)b);
      }

      lastShiftUpdate = msCounter;
    }
  }
}

void pixelButtonReactive() {
  for (unsigned char i = 0; i < sizeof(lightingStruct.ledId); ++i) {
    if (inputStruct.buttonState[i] == true) {
      switch (i) {
        case 0:
          pixel.setPixelColor(1, 0, 0, 255);
          break;
        case 1:
          pixel.setPixelColor(0, 0, 0, 255);
          break;
        case 2:
          pixel.setPixelColor(7, 0, 0, 255);
          break;
        case 3:
          pixel.setPixelColor(6, 0, 0, 255);
          break;
        case 4:
          pixel.setPixelColor(2, 255, 36, 0);
          pixel.setPixelColor(3, 255, 36, 0);
          break;
        case 5:
          pixel.setPixelColor(4, 255, 12, 0);
          pixel.setPixelColor(5, 255, 12, 0);
          break;
        case 6:
          pixel.setPixelColor(0, 255, 32, 120);
          pixel.setPixelColor(7, 255, 32, 120);
          break;
      }
    }
    /*else {
      switch (i) {
        case 0:
          pixel.setPixelColor(1, 0, 0, 0);
          break;
        case 1:
          pixel.setPixelColor(0, 0, 0, 0);
          break;
        case 2:
          pixel.setPixelColor(7, 0, 0, 0);
          break;
        case 3:
          pixel.setPixelColor(6, 0, 0, 0);
          break;
        case 4:
          pixel.setPixelColor(2, 0, 0, 0);
          pixel.setPixelColor(3, 0, 0, 0);
          break;
        case 5:
          pixel.setPixelColor(4, 0, 0, 0);
          pixel.setPixelColor(5, 0, 0, 0);
          break;
        case 6:
          if (buttonState[1] == false) {
            pixel.setPixelColor(0, 0, 0, 0);
          }
          if (buttonState[2] == false) {
            pixel.setPixelColor(7, 0, 0, 0);
          }
          break;
      }
      }*/
  }
}

void pixelEncoderSetLeftFlag() {
  pixelEncoderLeftFlag = true;
}

void pixelEncoderSetRightFlag() {
  pixelEncoderRightFlag = true;
}

void pixelEncoderReactiveFade(unsigned short stepInterval) {
  static unsigned long lastDegenUpdate = 0;
  static unsigned char leftDegenLevel = 0;
  static unsigned char rightDegenLevel = 0;

  if (msCounter - lastDegenUpdate >= stepInterval) {


    lastDegenUpdate = msCounter;
  }
}

void pixelUpdate() {
  pixel.show();
}
