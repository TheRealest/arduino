#include "uiStateManager.h"
#include "uiState/mainUiState.cpp"

UIStateManager::UIStateManager(MCP23017& mcp) :
  mcp(mcp),
  rotaryEncoderA(mcp, BANK_A, 6, 7, 5),
  rotaryEncoderB(mcp, BANK_A, 3, 4, 2),
  screen() {
    currentState = new MainUIState(dataState, screen);
  }

void UIStateManager::start() {
  rotaryEncoderA.start();
  rotaryEncoderB.start();
  screen.start();
  drawEntireScreen();
  currentState->enter();
}

void UIStateManager::update() {
  int8_t rotaryStateChangeA = rotaryEncoderA.getRotaryStateChange();
  int8_t switchStateChangeA = rotaryEncoderA.getSwitchStateChange();
  int8_t rotaryStateChangeB = rotaryEncoderB.getRotaryStateChange();
  int8_t switchStateChangeB = rotaryEncoderB.getSwitchStateChange();

  if (rotaryStateChangeA != 0) {
    currentState->handleEncoderARotaryStateChange(rotaryStateChangeA);
  }
  if (switchStateChangeA != 0) {
    currentState->handleEncoderASwitchStateChange(switchStateChangeA);
  }
  if (rotaryStateChangeB != 0) {
    currentState->handleEncoderBRotaryStateChange(rotaryStateChangeB);
  }
  if (switchStateChangeB != 0) {
    currentState->handleEncoderBSwitchStateChange(switchStateChangeB);
  }
}

void UIStateManager::drawEntireScreen() {
  for (uint8_t i = 0; i < 8; i++) {
    screen.testHexPair(
        UI_INITIAL_OFFSET,
        UI_INITIAL_OFFSET + (UI_HEXPAIR_Y_OFFSET * i),
        dataState.values[i],
        false
        );
  }
}
