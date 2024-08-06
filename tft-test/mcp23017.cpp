#include "mcp23017.h"

void MCP23017::start() {
  Wire.begin();
  Wire.setClock(400000);
  Wire.setWireTimeout(3000, true);
}

// lowest bit is pin zero, 0 is output and 1 is input
void MCP23017::setDirection(uint8_t bank, uint8_t direction) {
  writeToRegister(bank, direction);
}

void MCP23017::setPinDirection(uint8_t bank, uint8_t pin, uint8_t direction) {
  uint8_t address = bank;
  uint8_t directionValue = readRegister(address);

  if (direction) {
    directionValue |= (1 << pin);
  } else {
    directionValue &= ~(1 << pin);
  }

  writeToRegister(address, directionValue);
}

// lowest bit is pin zero, 1 means pullup enabled
void MCP23017::setPullupEnabled(uint8_t bank, uint8_t enabled) {
  writeToRegister((0xC | bank), enabled);
}

void MCP23017::setPinPullupEnabled(uint8_t bank, uint8_t pin, uint8_t enabled) {
  uint8_t address = 0xC | bank;
  uint8_t enabledValue = readRegister(address);

  if (enabled) {
    enabledValue |= (1 << pin);
  } else {
    enabledValue &= ~(1 << pin);
  }

  writeToRegister(address, enabledValue);
}

void MCP23017::writeOutputBank(uint8_t bank, uint8_t value) {
  writeToRegister((0x12 | bank), value);
}

void MCP23017::writeOutputPin(uint8_t bank, uint8_t pin, uint8_t value) {
  uint8_t bankValue = readInputBank(bank);
  if (value) {
    bankValue |= (1 << pin);
  } else {
    bankValue &= ~(1 << pin);
  }
  writeOutputBank(bank, bankValue);
}

uint8_t MCP23017::readInputBank(uint8_t bank) {
  return readRegister(0x12 | bank);
}

uint8_t MCP23017::readInputPin(uint8_t bank, uint8_t pin) {
  return (readInputBank(bank) >> pin) & 1;
}

void MCP23017::writeToRegister(uint8_t address, uint8_t value) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission(true);
}

uint8_t MCP23017::readRegister(uint8_t address) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(address);
  Wire.endTransmission(false);

  Wire.requestFrom(i2cAddress, (uint8_t)1, (uint8_t)true);
  return Wire.read();
}
