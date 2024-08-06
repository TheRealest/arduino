#include "uiStateManager.h"
#include "uiState/mainUiState.cpp"

UIStateManager::UIStateManager(MCP23017& mcp) :
  mcp(mcp),
  rotaryEncoderA(mcp, BANK_A, 6, 7, 5),
  rotaryEncoderB(mcp, BANK_A, 3, 4, 2),
  screen() {
    currentState = new MainUIState();
  }

void UIStateManager::start() {
  rotaryEncoderA.start();
  rotaryEncoderB.start();
  screen.start();
  drawEntireScreen();
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
  if (rotaryStateChangeA != 0 ||
      switchStateChangeA != 0 ||
      rotaryStateChangeB != 0 ||
      switchStateChangeB != 0) {
    currentState->updateScreen(screen);
  }
}

void UIStateManager::drawEntireScreen() {
  for (uint8_t i = 0; i < 8; i++) {
    screen.testHexPair(
        UI_INITIAL_OFFSET,
        UI_INITIAL_OFFSET + (UI_HEXPAIR_Y_OFFSET * i),
        0
        );
  }
}
