#ifndef MAIN_UI_STATE_H_
#define MAIN_UI_STATE_H_

#include "uiState.h"
#include <Arduino.h>

class MainUIState : public UIState {
  public:
    MainUIState(DataState& dataState, Screen& screen) : UIState(dataState, screen) {}

    void enter();

    void handleEncoderARotaryStateChange(int8_t change);
    void handleEncoderASwitchStateChange(int8_t change);
    void handleEncoderBRotaryStateChange(int8_t change) {}
    void handleEncoderBSwitchStateChange(int8_t change) {}

  private:
    void drawValue(uint8_t index, bool highlighted);

    int8_t highlightedRow = 0;
};

#endif
