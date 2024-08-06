#include "screen.h"

void Screen::start() {
  tft.begin();

  tft.fillScreen(HX8357_BLACK);
  tft.setTextColor(HX8357_WHITE);
  tft.setTextSize(2);
}

void Screen::testHexPair(uint16_t x, uint16_t y, uint8_t value) {
  tft.fillRect(x, y, 30, 22, HX8357_BLACK);
  tft.setCursor(x + 4, y + 4);
  if (value < 0x10) {
    tft.print("0");
    tft.print(value, HEX);
  } else {
    tft.print(value, HEX);
  }
}
