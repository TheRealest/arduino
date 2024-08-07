#ifndef UI_STATE_H_
#define UI_STATE_H_

#include "../screen.h"
#include "../dataState.h"

class UIState {
  public:
    UIState(DataState& dataState, Screen& screen) : dataState(dataState), screen(screen) {}

    virtual void enter() = 0;

    virtual void handleEncoderARotaryStateChange(int8_t change) = 0;
    virtual void handleEncoderASwitchStateChange(int8_t change) = 0;
    virtual void handleEncoderBRotaryStateChange(int8_t change) = 0;
    virtual void handleEncoderBSwitchStateChange(int8_t change) = 0;

  protected:
    DataState& dataState;
    Screen& screen;
};

#endif
