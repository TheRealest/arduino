#include "rowSelectedUiState.h"
#include "mainUiState.h"

void RowSelectedUIState::enter() {
  for (uint8_t i = 0; i < 6; i++) {
    drawValue(i, (i == highlightedValue));
  }
}

void RowSelectedUIState::handleEncoderARotaryStateChange(int8_t change) {
  int8_t newHighlightedValue = highlightedValue + change;
  if (newHighlightedValue > 5) {
    newHighlightedValue = 0;
  } else if (newHighlightedValue < 0) {
    newHighlightedValue = 5;
  }

  drawValue(highlightedValue, false);
  drawValue(newHighlightedValue, true);

  highlightedValue = newHighlightedValue;
}

void RowSelectedUIState::handleEncoderASwitchStateChange(int8_t change) {
  if (change == 1) {
    dataState.rows[selectedRow].values[highlightedValue]++;
    drawValue(highlightedValue, true);
  }
}

void RowSelectedUIState::handleEncoderBSwitchStateChange(int8_t change) {
  if (change == 1) {
    stateManager.transitionTo(new MainUIState(stateManager, dataState, screen, selectedRow));
  }
}

void RowSelectedUIState::drawValue(uint8_t valueIndex, bool highlighted) {
  screen.drawHexPair(
      selectedRow,
      valueIndex,
      dataState.rows[selectedRow].values[valueIndex],
      highlighted
      );
}
