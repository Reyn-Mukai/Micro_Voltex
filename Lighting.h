typedef struct {
  unsigned char ledId [7];
} lighting_type;

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} rgb_u08_type;

typedef struct {
  unsigned short r;
  unsigned short g;
  unsigned short b;
} rgb_u16_type;

extern unsigned long msCounter;
extern input_type inputStruct;

void lightingStructInitialize();

void rand256(unsigned char *input);

void generateInverseLogCurve();

void tlcSpiInitialize();

void pixelInitialize();

void tlcSpiWrite(unsigned char id, unsigned short r, unsigned short g, unsigned short b);

void tlcSpiUpdate();

void tlcButtonReactive();

void tlcButtonReactiveFade(unsigned short stepInterval);

void pixelBreatheFixed(unsigned short stepInterval, unsigned char r, unsigned char g, unsigned char b);

void pixelBreatheRandom(unsigned short stepInterval);

void pixelColorShift(unsigned short stepInterval, unsigned char stepLevels);

void pixelButtonReactive();

void pixelEncoderSetLeftFlag();

void pixelEncoderSetRightFlag();

void pixelEncoderReactiveFade(unsigned short stepInterval);

void pixelUpdate();
