#include "mainUiState.h"

void MainUIState::handleEncoderARotaryStateChange(int8_t change) {
  highlightedRow += change;
  if (highlightedRow > 7) {
    highlightedRow = 0;
  } else if (highlightedRow < 0) {
    highlightedRow = 7;
  }
  Serial.print("Highlighted row: ");
  Serial.println(highlightedRow);
}

void MainUIState::handleEncoderASwitchStateChange(int8_t change) {
  Serial.print("Switch state change: ");
  Serial.println(change);
  // TODO
}

void MainUIState::updateScreen(Screen& screen) {
  Serial.println("Updating screen");
  // TODO
}
