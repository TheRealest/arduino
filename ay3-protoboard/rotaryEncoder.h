#ifndef ROTARY_ENCODER_H_
#define ROTARY_ENCODER_H_

#include "mcp23017.h"

#define ROTARY_ENCODER_SWITCH_THROTTLE_MS (500)

class RotaryEncoder {
  public:
    RotaryEncoder(
        MCP23017& mcp,
        uint8_t mcpBank,
        uint8_t aPin,
        uint8_t bPin,
        uint8_t switchPin
        ) : mcp(mcp), mcpBank(mcpBank), aPin(aPin), bPin(bPin), switchPin(switchPin) {}

    void start();
    uint8_t getRotaryStateChange();
    uint8_t getSwitchStateChange();

  private:
    MCP23017& mcp;
    const uint8_t mcpBank;
    const uint8_t aPin;
    const uint8_t bPin;
    const uint8_t switchPin;

    uint8_t outA = 1;
    uint8_t outB = 1;
    String direction = "none";

    uint8_t switchValue = 1;
    uint8_t switchThrottleTimer = 0;
};

#endif
