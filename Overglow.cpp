#include "Overglow.h"

Overglow overglow = Overglow();

SPISettings Overglow::TLC_SPI_SETTINGS = SPISettings(8000000, MSBFIRST, SPI_MODE0);
