#ifndef MAIN_UI_STATE_H_
#define MAIN_UI_STATE_H_

#include "uiState.h"

class MainUIState : public UIState {
  public:
    MainUIState(StateManager& stateManager, DataState& dataState, Screen& screen, int8_t highlightedRow = 0) : UIState(stateManager, dataState, screen), highlightedRow(highlightedRow) {}

    void enter();
    void exit() {}

    void handleEncoderARotaryStateChange(int8_t change);
    void handleEncoderASwitchStateChange(int8_t change);
    void handleEncoderBRotaryStateChange(int8_t change) {}
    void handleEncoderBSwitchStateChange(int8_t change) {}

  private:
    void drawRow(uint8_t index, bool highlighted);
    void drawValue(uint8_t rowIndex, uint8_t valueIndex, bool highlighted);

    int8_t highlightedRow;
};

#endif
