#include "rotaryEncoder.h"
#include <Arduino.h>

void RotaryEncoder::start() {
  mcp.setPinDirection(mcpBank, aPin, 1);
  mcp.setPinDirection(mcpBank, bPin, 1);
  mcp.setPinDirection(mcpBank, switchPin, 1);

  mcp.setPinPullupEnabled(mcpBank, aPin, 1);
  mcp.setPinPullupEnabled(mcpBank, bPin, 1);
  mcp.setPinPullupEnabled(mcpBank, switchPin, 1);
}

// returns 1 when a clockwise click is complete, -1 for ccw, 0 otherwise
uint8_t RotaryEncoder::getRotaryStateChange() {
  uint8_t newOutA = mcp.readInputPin(mcpBank, aPin);
  uint8_t newOutB = mcp.readInputPin(mcpBank, bPin);

  if (outA == newOutA && outB == newOutB) {
    return 0;
  }

  // start direction
  if (direction == "none") {
    if (newOutB == 0) {
      direction = "clockwise";
    } else if (newOutA == 0) {
      direction = "counterclockwise";
    }
  }

  uint8_t result = 0;

  // transition complete
  if (newOutA == 1 && newOutB == 1) {
    if (direction == "clockwise" && outA == 0) {
      result = 1;
    } else if (direction == "counterclockwise" && outB == 0) {
      result = -1;
    }
    direction = "none";
  }

  outA = newOutA;
  outB = newOutB;
  return result;
}

// returns 1 on press, -1 on release, 0 if state doesn't change
uint8_t RotaryEncoder::getSwitchStateChange() {
  uint8_t newswitchValue = mcp.readInputPin(mcpBank, switchPin);

  uint8_t result = 0;
  if (switchValue != newswitchValue) {
    if ((millis() - switchThrottleTimer) < ROTARY_ENCODER_SWITCH_THROTTLE_MS) {
      switchThrottleTimer = millis();
      switchValue = newswitchValue;
      return 0;
    }
    if (newswitchValue == 0) {
      result = 1;
      switchThrottleTimer = millis();
    } else {
      result = -1;
      switchThrottleTimer = millis();
    }
  }

  switchValue = newswitchValue;
  return result;
}
