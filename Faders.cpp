#include <Mouse.h>

#include "Faders.h"

Faders faders = Faders();

void Faders::updateLeft() {
  if (encLeft.read() != 0) {
    //pixelEncoderSetLeftFlag();
    Mouse.move(encLeft.read(), 0, 0);
  }
  encLeft.write(0);
}
void Faders::updateRight() {
  if (encRight.read() != 0) {
    //pixelEncoderSetRightFlag();
    Mouse.move(0, encRight.read(), 0);
  }
  encRight.write(0);
}
