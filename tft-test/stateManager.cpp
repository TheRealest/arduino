#include "stateManager.h"
#include "uiState/mainUiState.cpp"
#include "uiState/rowSelectedUiState.cpp"
#include "uiState/valueSelectedUiState.cpp"

StateManager::StateManager(MCP23017& mcp) :
  mcp(mcp),
  rotaryEncoderA(mcp, BANK_A, 6, 7, 5),
  rotaryEncoderB(mcp, BANK_A, 3, 4, 2),
  screen() {
    currentState = new MainUIState(*this, dataState, screen);
  }

void StateManager::start() {
  rotaryEncoderA.start();
  rotaryEncoderB.start();
  screen.start();
  currentState->enter();
}

void StateManager::update() {
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

void StateManager::transitionTo(UIState* newState) {
  UIState* oldState = currentState;
  oldState->exit();
  newState->enter();

  currentState = newState;
  delete oldState;
}
