#include "Input.h"
#include "Lighting.h"

// LED Lighting Refresh Rate (ms)
#define REFRESH_RATE 4

// 1ms Tasking
unsigned long msCounter;
bool oneMsFlag;

void setup() {
  // Timer3 Setup 1ms Interrupt (16MHz Ext. Clk)
  noInterrupts();
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3 = 0;

  // COM3A Compare Match Register
  OCR3A = 250;
  // CTC Enable
  TCCR3B |= (1 << WGM32);
  // Prescaler 64
  TCCR3B |= (0 << CS32);
  TCCR3B |= (1 << CS31);
  TCCR3B |= (1 << CS30);
  // Enable COMP3A match register
  TIMSK3 |= (1 << OCIE3A);
  interrupts();

  // Set Button Pin Mode
  inputPinInitialize();

  // Initialize Button Struct
  inputStructInitialize();

  // Initialize Lighting Struct
  lightingStructInitialize();

  // Initialize SPI and GPIO for TLC5947
  tlcSpiInitialize();

  // Initialize Pixels
  pixelInitialize();

  // Start Serial Debug Output
  Serial.begin(115200);

  // Generate Lighting Inverse Log Curve
  generateInverseLogCurve();
}

ISR(TIMER3_COMPA_vect)
{
  ++msCounter;
  oneMsFlag = true;
}

void loop() {
  backgroundTask();
  oneMsTask();

  //testCode();
}

void testCode() {
  
}

void backgroundTask() {
  checkAllKeyEvents();
  encFuncLeft();
  encFuncRight();
}

void oneMsTask() {
  static long temp;
  static long temp2;
  if (oneMsFlag)
  {

    temp = micros();
    if (msCounter % 2 == 0 && msCounter % 4 == 0)
    {
      //tlcButtonReactive();
      tlcButtonReactiveFade(1);

      tlcSpiUpdate();
    }
    else if (msCounter % 2 == 0) {
      //pixelBreatheFixed(25, 255, 32, 120);
      pixelBreatheRandom(25);
      //pixelColorShift(100, 32);
      pixelButtonReactive();

      pixelUpdate();
    }
    temp2 = micros();

    if(msCounter % 1000 == 0)
    {
      
    }

    //Serial.println(temp2 - temp);
  }

  oneMsFlag = false;
}
