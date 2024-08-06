#include "mcp23017.h"
#include "rotaryEncoder.h"
#include "ay3.h"
#include "pattern.h"

#define RESET_PIN (12)
#define CLOCK_PIN (9)

MCP23017 mcp(0);
RotaryEncoder rotaryEncoder1(mcp, BANK_A, 3, 4, 2);
RotaryEncoder rotaryEncoder2(mcp, BANK_A, 6, 7, 5);
AY3 ay3(mcp, BANK_B, BANK_A, 1, 0);


String notation = R"NOTES(
C-4
E-4
G-4
C-4
F-4
A-5
B-4
D-4
G-4
C-4
E-4
G-4
)NOTES";
Pattern pattern(ay3, notation, TONE_A);

void resetChips() {
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
  delay(1000);
  digitalWrite(RESET_PIN, HIGH);
  delay(100);
}

void enableClock() {
  // output on pin 9
  TCCR1A = bit(COM1A0);
  // PWM up to 255, divide clock by 8 (1 MHz)
  TCCR1B = bit(WGM12) | bit(CS11);

  // PIN SETUP
  pinMode(CLOCK_PIN, OUTPUT);
}

void handleBpmEncoder(RotaryEncoder& encoder) {
  int8_t rotaryStateChange = encoder.getRotaryStateChange();
  int8_t switchStateChange = encoder.getSwitchStateChange();

  if (rotaryStateChange != 0) {
    pattern.setBpm(pattern.bpm + (rotaryStateChange * 5));
  }

  if (switchStateChange == 1) {
    pattern.togglePlaying();
  }
}

bool envelopeEnabled = false;
uint8_t envelopeMode = 0;
float envelopeFrequency = 1.0;
void handleEnvelopeEncoder(RotaryEncoder& encoder) {
  int8_t rotaryStateChange = encoder.getRotaryStateChange();
  int8_t switchStateChange = encoder.getSwitchStateChange();

  if (rotaryStateChange != 0) {
    envelopeFrequency += rotaryStateChange * 1.0;
    if (envelopeFrequency < 1.0) {
      envelopeFrequency = 1.0;
    }
    ay3.setEnvelopeFrequency(envelopeFrequency);
    Serial.print("Envelope frequency: ");
    Serial.println(envelopeFrequency);
  }

  if (switchStateChange == 1) {
    if (!envelopeEnabled) {
      envelopeEnabled = true;
      ay3.setAmplitudeEnvelope(TONE_A);
      ay3.setEnvelopeShape(envelopeMode);
      Serial.println("Envelope enabled, mode 0");
    } else {
      envelopeMode++;
      if (envelopeMode >= 8) {
        envelopeMode = 0;
        envelopeEnabled = false;
        ay3.setAmplitudeStatic(TONE_A, 0xF);
        Serial.println("Envelope disabled");
      } else {
        ay3.setEnvelopeShape(envelopeMode);
        Serial.print("Envelope mode ");
        Serial.println(envelopeMode);
      }
    }
  }
}

void handleDebugRotaryEncoder(const char* name, RotaryEncoder& encoder) {
  int8_t rotaryStateChange = encoder.getRotaryStateChange();
  int8_t switchStateChange = encoder.getSwitchStateChange();

  if (rotaryStateChange != 0) {
    Serial.print(name);
    Serial.print(" rotated: ");
    Serial.println(rotaryStateChange);
  }

  if (switchStateChange != 0) {
    Serial.print(name);
    Serial.print(" switched: ");
    Serial.println(switchStateChange);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("OK");

  resetChips();
  enableClock();

  mcp.start();
  rotaryEncoder1.start();
  rotaryEncoder2.start();
  ay3.start();

  // test AY-3-8910
  //ay3.setChannelEnabled(TONE_A, false, true);
  //ay3.setAmplitudeStatic(TONE_A, 0xF);
  //ay3.setNoteFrequency(TONE_A, 220);

  for (int i = 0; i < 16; i++) {
    Serial.print(pattern.entries[i].note + ": ");
    Serial.println(pattern.entries[i].noteFrequency());
  }

  pattern.play();
}

void loop() {
  handleBpmEncoder(rotaryEncoder1);
  handleEnvelopeEncoder(rotaryEncoder2);

  pattern.update();
}
