#ifndef SCREEN_H_
#define SCREEN_H_

// Uses Adafruit HX8357D Breakout
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"

#define TFT_CS 8
#define TFT_DC 7
#define TFT_RST 6

class Screen {
  public:
    Screen() {}

    void start();
    void testHexPair(uint16_t x, uint16_t y, uint8_t value, bool highlight);

  private:
    const Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
};

#endif
