#include <Wire.h>

void writeToRegister(int address, int value) {
  Wire.beginTransmission(0x20);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}

int readRegister(int address) {
  Wire.beginTransmission(0x20);
  Wire.write(address);
  Wire.endTransmission();

  Wire.requestFrom(0x20, 1);
  return Wire.read();
}

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // set direction of A all to input
  writeToRegister(0, 0xFF);
  // set A pullups all on
  writeToRegister(0xc, 0xFF);
  // set direction of B 0-4 to output
  writeToRegister(0x1, 0b11100000);

  digitalWrite(12, LOW);
  delay(1);
  digitalWrite(12, HIGH);
}

int x = 0;
void loop() {
  writeToRegister(0x13, x);

  x++;
  x %= 32;

  // flash LED
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);

  Serial.println(String(readRegister(0x12), BIN));
  // Serial.println(String((readRegister(0x13) >> 5), BIN));
}