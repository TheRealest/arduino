#include "valueSelectedUiState.h"
#include "rowSelectedUiState.h"

void ValueSelectedUIState::handleEncoderARotaryStateChange(int8_t change) {
  uint8_t oldValue = dataState.rows[selectedRow].values[selectedValue];
  uint8_t newValue;
  if (oldValue == 0xFF && change == 1) {
    newValue = 0;
  } else if (oldValue == 0 && change == -1) {
    newValue = 0xFF;
  } else {
    newValue = oldValue + change;
  }

  dataState.rows[selectedRow].values[selectedValue] = newValue;
  drawValue();
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
