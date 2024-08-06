#ifndef UI_STATE_H_
#define UI_STATE_H_

#include "../screen.h"

class UIState {
  public:
    UIState() {}

    virtual void handleEncoderARotaryStateChange(int8_t change) = 0;
    virtual void handleEncoderASwitchStateChange(int8_t change) = 0;
    virtual void handleEncoderBRotaryStateChange(int8_t change) = 0;
    virtual void handleEncoderBSwitchStateChange(int8_t change) = 0;

    virtual void updateScreen(Screen& screen) = 0;
};

#endif
