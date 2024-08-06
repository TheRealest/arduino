#ifndef AY3_H_
#define AY3_H_

#include "mcp23017.h"

#define AY3_CLOCK_FREQ (1000000.0f)

#define TONE_A (0)
#define TONE_B (1)
#define TONE_C (2)
#define NOISE (3)

#define MIXER (7)

#define ENVELOPE (013)
#define ENVELOPE_SHAPE (015)

class AY3 {
  public:
    AY3(
        MCP23017& mcp,
        uint8_t outputMcpBank,
        uint8_t modeMcpBank,
        uint8_t bdirPin,
        uint8_t bc1Pin
       ) : mcp(mcp), outputMcpBank(outputMcpBank), modeMcpBank(modeMcpBank), bdirPin(bdirPin), bc1Pin(bc1Pin) {}

    void start();

    void setNoteFrequency(uint8_t channel, float frequency);

    void setAmplitudeStatic(uint8_t channel, uint8_t amplitude);
    void setAmplitudeEnvelope(uint8_t channel);

    void setChannelEnabled(uint8_t channel, bool noiseControl, bool enabled);

    void setEnvelopeShape(uint8_t shape);
    void setEnvelopeFrequency(float frequency);

    void silence();

  private:
    MCP23017& mcp;
    const uint8_t outputMcpBank;
    const uint8_t modeMcpBank;
    const uint8_t bdirPin;
    const uint8_t bc1Pin;

    uint8_t channelEnabledValue = 0xFF;

    void setModeInactive();
    void setModeWrite();
    void setModeLatch();

    void writeToRegister(uint8_t reg, uint8_t value);
};

#endif
