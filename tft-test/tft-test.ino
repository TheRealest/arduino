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

void loop() {
  uiStateManager.update();
}
