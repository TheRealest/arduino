#ifndef UI_STATE_H_
#define UI_STATE_H_

#include "../stateManager.h"
#include "../dataState.h"
#include "../screen.h"

// forward declaration
class StateManager;

class UIState {
  public:
    UIState(StateManager& stateManager, DataState& dataState, Screen& screen) : stateManager(stateManager), dataState(dataState), screen(screen) {}

    virtual void enter() = 0;
    virtual void exit() = 0;

    virtual void handleEncoderARotaryStateChange(int8_t change) = 0;
    virtual void handleEncoderASwitchStateChange(int8_t change) = 0;
    virtual void handleEncoderBRotaryStateChange(int8_t change) = 0;
    virtual void handleEncoderBSwitchStateChange(int8_t change) = 0;

  protected:
    StateManager& stateManager;
    DataState& dataState;
    Screen& screen;
};

#endif
