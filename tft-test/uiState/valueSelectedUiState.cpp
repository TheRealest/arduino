#include "valueSelectedUiState.h"
#include "rowSelectedUiState.h"

void ValueSelectedUIState::handleEncoderARotaryStateChange(int8_t change) {
  int8_t newValue = dataState.rows[selectedRow].values[selectedValue] + change;
  if (newValue < 0) {
    newValue = 0x8F;
  }

  drawValue();

  dataState.rows[selectedRow].values[selectedValue] = newValue;
}

void ValueSelectedUIState::handleEncoderBSwitchStateChange(int8_t change) {
  if (change == 1) {
    stateManager.transitionTo(new RowSelectedUIState(stateManager, dataState, screen, selectedRow, selectedValue));
  }
}

void ValueSelectedUIState::drawValue() {
  screen.drawHexPair(
      selectedRow,
      selectedValue,
      dataState.rows[selectedRow].values[selectedValue],
      true
      );
}
