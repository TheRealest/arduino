#ifndef MCP23017_H_
#define MCP23017_H_

#include <Wire.h>

#define BANK_A (0)
#define BANK_B (1)

class MCP23017 {
  public:
    MCP23017(uint8_t _i2cAddress) : i2cAddress(_i2cAddress | 0x20) {}

    void start();

    void setDirection(uint8_t bank, uint8_t direction);
    void setPinDirection(uint8_t bank, uint8_t pin, uint8_t direction);
    void setPullupEnabled(uint8_t bank, uint8_t enabled);
    void setPinPullupEnabled(uint8_t bank, uint8_t pin, uint8_t enabled);

    void writeOutputBank(uint8_t bank, uint8_t value);
    void writeOutputPin(uint8_t bank, uint8_t pin, uint8_t value);

    uint8_t readInputBank(uint8_t bank);
    uint8_t readInputPin(uint8_t bank, uint8_t pin);

  private:
    const uint8_t i2cAddress;

    void writeToRegister(uint8_t address, uint8_t value);
    uint8_t readRegister(uint8_t address);
};

#endif
