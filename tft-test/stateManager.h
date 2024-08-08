#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_

#include "mcp23017.h"
#include "rotaryEncoder.h"
#include "screen.h"
#include "dataState.h"

#include "uiState/uiState.h"

class StateManager {
  public:
    StateManager(MCP23017& mcp);

    void start();
    void update();
    void transitionTo(UIState* newState);

  private:
    const MCP23017& mcp;
    RotaryEncoder rotaryEncoderA;
    RotaryEncoder rotaryEncoderB;
    Screen screen;
    DataState dataState;
    UIState* currentState;
};

#endif
