#ifndef MAIN_UI_STATE_H_
#define MAIN_UI_STATE_H_

#include "uiState.h"
#include <Arduino.h>

class MainUIState : public UIState {
  public:
    MainUIState() : UIState() {};

    void handleEncoderARotaryStateChange(int8_t change);
    void handleEncoderASwitchStateChange(int8_t change);
    void handleEncoderBRotaryStateChange(int8_t change) {}
    void handleEncoderBSwitchStateChange(int8_t change) {}

    void updateScreen(Screen& screen);

  private:
    int8_t highlightedRow = 0;
};

#endif
