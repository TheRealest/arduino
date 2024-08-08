#include "screen.h"

void Screen::start() {
  tft.begin();

  tft.fillScreen(HX8357_BLACK);
  tft.setTextColor(HX8357_WHITE);
  tft.setTextSize(2);
}

    void drawHexRow(uint8_t row, uint8_t values[6], bool highlight);
    void drawHexPair(uint16_t row, uint16_t index, uint8_t value, bool highlight);

void Screen::drawHexPair(uint16_t row, uint16_t index, uint8_t value, bool highlight) {
  uint16_t backgroundColor;
  uint16_t x = UI_INITIAL_OFFSET + (UI_HEXPAIR_X_OFFSET * index);
  uint16_t y = UI_INITIAL_OFFSET + (UI_HEXPAIR_Y_OFFSET * row);

  if (highlight) {
    backgroundColor = HX8357_RED;
    tft.setTextColor(HX8357_BLACK);
  } else {
    backgroundColor = HX8357_BLACK;
    tft.setTextColor(HX8357_WHITE);
  }

  tft.fillRect(x, y, 30, 22, backgroundColor);
  tft.setCursor(x + 4, y + 4);
  if (value < 0x10) {
    tft.print("0");
    tft.print(value, HEX);
  } else {
    tft.print(value, HEX);
  }
}
