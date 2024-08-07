#include "mainUiState.h"
#include "rowSelectedUiState.h"

void MainUIState::enter() {
  for (uint8_t i = 0; i < 8; i++) {
    drawRow(i, (i == highlightedRow));
  }
}

void MainUIState::exit() {
  drawRow(highlightedRow, false);
}

void MainUIState::handleEncoderARotaryStateChange(int8_t change) {
  uint8_t newHighlightedRow;
  if (highlightedRow == 7 && change == 1) {
    newHighlightedRow = 0;
  } else if (highlightedRow == 0 && change == -1) {
    newHighlightedRow = 7;
  } else {
    newHighlightedRow = highlightedRow + change;
  }

  drawRow(highlightedRow, false);
  drawRow(newHighlightedRow, true);

  highlightedRow = newHighlightedRow;
}

void MainUIState::handleEncoderASwitchStateChange(int8_t change) {
  if (change == 1) {
    stateManager.transitionTo(new RowSelectedUIState(stateManager, dataState, screen, highlightedRow));
  }
}

void MainUIState::drawRow(uint8_t index, bool highlighted) {
  screen.drawHexRow(
      index,
      dataState.rows[index].values,
      highlighted
      );
}


void MainUIState::drawValue(uint8_t rowIndex, uint8_t valueIndex, bool highlighted) {
  screen.drawHexPair(
      rowIndex,
      valueIndex,
      dataState.rows[rowIndex].values[valueIndex],
      highlighted
      );
}
