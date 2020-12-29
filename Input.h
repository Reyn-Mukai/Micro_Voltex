typedef struct {
  unsigned long keyTimer    [9];
  unsigned char buttonPin   [9];
  signed char   asciiKey    [9];
  signed char   asciiKeyAlt [9];
  bool          buttonState [9];
} input_type;

void inputPinInitialize();

void inputStructInitialize();

void checkAllKeyEvents();

void encFuncLeft();

void encFuncRight();
