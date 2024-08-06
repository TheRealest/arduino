#include "mcp23017.h"
#include "rotaryEncoder.h"
#include "uiStateManager.h"

#define RESET_PIN (12)
#define CLOCK_PIN (9)

MCP23017 mcp(0);
UIStateManager uiStateManager(mcp);

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

void setup() {
  Serial.begin(9600);
  Serial.println("OK");

  resetChips();
  enableClock();

  mcp.start();
  uiStateManager.start();
}

//int8_t rotaryCounter1 = 0;
//
//void handleDebugEncoder1(RotaryEncoder& encoder) {
//  int8_t rotaryStateChange = encoder.getRotaryStateChange();
//  int8_t switchStateChange = encoder.getSwitchStateChange();
//
//  if (rotaryStateChange != 0) {
//    rotaryCounter1 += rotaryStateChange;
//    if (rotaryCounter1 < 0) {
//      rotaryCounter1 = 0;
//    }
//    if (rotaryCounter1 > 0xFF) {
//      rotaryCounter1 = 0xFF;
//    }
//    screen.testHexPair(UI_INITIAL_OFFSET, UI_INITIAL_OFFSET, rotaryCounter1);
//  }
//
//  if (switchStateChange != 0) {
//    screen.testHexPair(UI_INITIAL_OFFSET, UI_INITIAL_OFFSET + UI_HEXPAIR_Y_OFFSET, switchStateChange);
//  }
//}
//
//int8_t rotaryCounter2 = 0;
//
//void handleDebugEncoder2(RotaryEncoder& encoder) {
//  int8_t rotaryStateChange = encoder.getRotaryStateChange();
//  int8_t switchStateChange = encoder.getSwitchStateChange();
//
//  if (rotaryStateChange != 0) {
//    rotaryCounter2 += rotaryStateChange;
//    if (rotaryCounter2 < 0) {
//      rotaryCounter2 = 0;
//    }
//    if (rotaryCounter2 > 0xFF) {
//      rotaryCounter2 = 0xFF;
//    }
//    screen.testHexPair(UI_INITIAL_OFFSET + UI_HEXPAIR_X_OFFSET, UI_INITIAL_OFFSET, rotaryCounter2);
//  }
//
//  if (switchStateChange != 0) {
//    screen.testHexPair(UI_INITIAL_OFFSET + UI_HEXPAIR_X_OFFSET, UI_INITIAL_OFFSET + UI_HEXPAIR_Y_OFFSET, switchStateChange);
//  }
//}

void loop() {
  uiStateManager.update();
  //handleDebugEncoder1(rotaryEncoder1);
  //handleDebugEncoder2(rotaryEncoder2);
}
