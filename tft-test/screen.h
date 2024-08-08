#ifndef SCREEN_H_
#define SCREEN_H_

// Uses Adafruit HX8357D Breakout
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"

#define TFT_CS 8
#define TFT_DC 7
#define TFT_RST 6

#define UI_INITIAL_OFFSET 8
#define UI_HEXPAIR_X_OFFSET 34
#define UI_HEXPAIR_Y_OFFSET 26

class Screen {
  public:
    Screen() {}

    void start();
    void drawHexRow(uint8_t row, uint8_t values[6], bool highlighted);
    void drawHexPair(uint16_t row, uint16_t index, uint8_t value, bool highlighted);

  private:
    const Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
};

#endif
