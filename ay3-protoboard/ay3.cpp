#include <Arduino.h>
#include "ay3.h"

void AY3::start() {
  // set all pins to output
  mcp.setDirection(outputMcpBank, 0);
  mcp.setPinDirection(modeMcpBank, bdirPin, 0);
  mcp.setPinDirection(modeMcpBank, bc1Pin, 0);

  // disable everything
  writeToRegister(MIXER, 0xFF);
  setAmplitudeStatic(TONE_A, 0);
  setAmplitudeStatic(TONE_B, 0);
  setAmplitudeStatic(TONE_C, 0);
}

void AY3::setNoteFrequency(uint8_t channel, float frequency) {
  float tp_exact = (AY3_CLOCK_FREQ / frequency) / 16;
  uint16_t tp = tp_exact;

  uint8_t fine_tune = tp & 0xFF;
  uint8_t coarse_tune = tp >> 8;
  coarse_tune &= 0x0F;

  channel *= 2;
  writeToRegister(channel, fine_tune);
  writeToRegister((channel + 1), coarse_tune);
}

// amplitude is 4 bits, 0-0xF
void AY3::setAmplitudeStatic(uint8_t channel, uint8_t amplitude) {
  channel += 010;
  amplitude &= 0xF;
  writeToRegister(channel, amplitude);
}

// enables/disables amplitude envelope mode
void AY3::setAmplitudeEnvelope(uint8_t channel) {
  channel += 010;
  writeToRegister(channel, 0x10);
}

// shape is 3 bits, 0-7 -- see manual for descriptions
void AY3::setEnvelopeShape(uint8_t shape) {
  shape = (shape & 0x7) | 0x8;
  writeToRegister(ENVELOPE_SHAPE, shape);
}

// ranges from 0.06Hz to 3906Hz
void AY3::setEnvelopeFrequency(float frequency) {
  float tp_exact = (AY3_CLOCK_FREQ / frequency) / 256;
  uint16_t tp = tp_exact;

  uint8_t fine_tune = tp & 0xFF;
  uint8_t coarse_tune = tp >> 8;

  writeToRegister(ENVELOPE, fine_tune);
  writeToRegister((ENVELOPE + 1), coarse_tune);
}

void AY3::setChannelEnabled(uint8_t channel, bool noiseControl, bool enabled) {
  uint8_t pin = channel + (noiseControl ? 3 : 0);

  // enabled low
  if (enabled) {
    channelEnabledValue &= ~(1 << pin);
  } else {
    channelEnabledValue |= (1 << pin);
  }

  writeToRegister(MIXER, channelEnabledValue);
}

void AY3::silence() {
  setAmplitudeStatic(TONE_A, 0);
  setAmplitudeStatic(TONE_B, 0);
  setAmplitudeStatic(TONE_C, 0);
  writeToRegister(MIXER, 0xFF);
}

void AY3::setModeInactive() {
  uint8_t value = (0 << bdirPin) | (0 << bc1Pin);
  mcp.writeOutputBank(modeMcpBank, value);
}

void AY3::setModeWrite() {
  uint8_t value = (1 << bdirPin) | (0 << bc1Pin);
  mcp.writeOutputBank(modeMcpBank, value);
}

void AY3::setModeLatch() {
  uint8_t value = (1 << bdirPin) | (1 << bc1Pin);
  mcp.writeOutputBank(modeMcpBank, value);
}

void AY3::writeToRegister(uint8_t reg, uint8_t value) {
  mcp.writeOutputBank(outputMcpBank, reg);
  setModeLatch();
  setModeInactive();
  delayMicroseconds(1);

  mcp.writeOutputBank(outputMcpBank, value);
  setModeWrite();
  setModeInactive();
  delayMicroseconds(1);
}
