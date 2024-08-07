#ifndef ROW_SELECTED_UI_STATE_H_
#define ROW_SELECTED_UI_STATE_H_

#include "uiState.h"

class RowSelectedUIState : public UIState {
  public:
    RowSelectedUIState(
        StateManager& stateManager,
        DataState& dataState,
        Screen& screen,
        uint8_t selectedRow,
        uint8_t highlightedValue = 0) :
      UIState(stateManager, dataState, screen),
      selectedRow(selectedRow),
      highlightedValue(highlightedValue) {}

    void enter();
    void exit() {}

    void handleEncoderARotaryStateChange(int8_t change);
    void handleEncoderASwitchStateChange(int8_t change);
    void handleEncoderBRotaryStateChange(int8_t change) {}
    void handleEncoderBSwitchStateChange(int8_t change);

  private:
    uint8_t selectedRow;
    uint8_t highlightedValue;

    void drawValue(uint8_t valueIndex, bool highlighted);
};

#endif
