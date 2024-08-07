#ifndef UI_STATE_MANAGER_H_
#define UI_STATE_MANAGER_H_

#include "mcp23017.h"
#include "rotaryEncoder.h"
#include "screen.h"
#include "dataState.h"

#include "uiState/uiState.h"

#define UI_INITIAL_OFFSET 8
#define UI_HEXPAIR_X_OFFSET 34
#define UI_HEXPAIR_Y_OFFSET 26


class UIStateManager {
  public:
    UIStateManager(MCP23017& mcp);

    void start();
    void update();

  private:
    const MCP23017& mcp;
    RotaryEncoder rotaryEncoderA;
    RotaryEncoder rotaryEncoderB;
    Screen screen;
    DataState dataState;
    UIState* currentState;
};

#endif
