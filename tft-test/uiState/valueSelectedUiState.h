#ifndef VALUE_SELECTED_UI_STATE_H_
#define VALUE_SELECTED_UI_STATE_H_

#include "uiState.h"

class ValueSelectedUIState : public UIState {
  public:
    ValueSelectedUIState(
        StateManager& stateManager,
        DataState& dataState,
        Screen& screen,
        uint8_t selectedRow,
        uint8_t selectedValue) :
      UIState(stateManager, dataState, screen),
      selectedRow(selectedRow),
      selectedValue(selectedValue) {}

    void enter() {}
    void exit() {}

    void handleEncoderARotaryStateChange(int8_t change);
    void handleEncoderASwitchStateChange(int8_t change) {}
    void handleEncoderBRotaryStateChange(int8_t change) {}
    void handleEncoderBSwitchStateChange(int8_t change);

  private:
    uint8_t selectedRow;
    uint8_t selectedValue;

    void drawValue();
};

#endif
