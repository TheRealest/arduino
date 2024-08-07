#include "mainUiState.h"

void MainUIState::enter() {
  for (uint8_t i = 0; i < 8; i++) {
    drawValue(i, (i == highlightedRow));
  }
}

void MainUIState::handleEncoderARotaryStateChange(int8_t change) {
  int8_t newHighlightedRow = highlightedRow + change;
  if (newHighlightedRow > 7) {
    newHighlightedRow = 0;
  } else if (newHighlightedRow < 0) {
    newHighlightedRow = 7;
  }

  drawValue(highlightedRow, false);
  drawValue(newHighlightedRow, true);

  highlightedRow = newHighlightedRow;
}

void MainUIState::handleEncoderASwitchStateChange(int8_t change) {
  if (change == 1) {
    dataState.values[highlightedRow]++;
    drawValue(highlightedRow, true);
  }
}

void MainUIState::drawValue(uint8_t index, bool highlighted) {
  screen.testHexPair(
      UI_INITIAL_OFFSET,
      UI_INITIAL_OFFSET + (UI_HEXPAIR_Y_OFFSET * index),
      dataState.values[index],
      highlighted
      );
}
