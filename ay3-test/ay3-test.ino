const int CLOCK_PIN = 9;
const int RESET_PIN = 8;
const int BC1_PIN = A5;
const int BDIR_PIN = A4;

const int SWITCH_PIN = 12;

const int BIT_TO_PIN_MAPPING[] = {10, 11, 2, 3, 4, 5, 6, 7};

const int NOTE_FREQ[] = {220, 233.1, 246.9, 261.6, 277.2, 293.7, 311.1, 329.6, 349.2, 370, 392, 415.3};

// MODE HELPERS
void setModeInactive() {
  digitalWrite(BDIR_PIN, LOW);
  digitalWrite(BC1_PIN, LOW);
}

void setModeWrite() {
  digitalWrite(BDIR_PIN, HIGH);
  digitalWrite(BC1_PIN, LOW);
}

void setModeLatch() {
  digitalWrite(BDIR_PIN, HIGH);
  digitalWrite(BC1_PIN, HIGH);
}

void writeToBus(int value) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(BIT_TO_PIN_MAPPING[i], (value & 1));
    value >>= 1;
  }

  // PORTD = value;
}

void setRegister(int reg, int value) {
  setModeLatch();
  writeToBus(reg);
  setModeInactive();

  setModeWrite();
  writeToBus(value);
  setModeInactive();
}

// only works for tone generator A
// 
void setNoteFreq(float note_freq) {
  float clock_freq = 1000000;
  float tp_exact = (clock_freq / note_freq) / 16;
  int tp = tp_exact;
  int fine_tune = tp & 255;
  int coarse_tune = tp >> 8;
  setRegister(0, fine_tune);
  setRegister(1, coarse_tune);
}

int outA = 1;
int outB = 1;
String direction = "none";
// returns 1 when a clockwise click is complete, -1 for ccw, 0 otherwise
int getRotaryStateChange() {
  int newOutA = digitalRead(A0);
  int newOutB = digitalRead(A1);

  if (outA == newOutA && outB == newOutB) {
    return 0;
  }

  // start direction
  if (direction == "none") {
    if (newOutB == 0) {
      direction = "clockwise";
    } else {
      direction = "counterclockwise";
    }
  }

  int result = 0;
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

int switchVal = 1;
// returns 1 on press, -1 on release, 0 if state doesn't change
int getSwitchStateChange() {
  int newSwitchVal = digitalRead(SWITCH_PIN);

  int result = 0;
  if (switchVal != newSwitchVal) {
    if (newSwitchVal == 0) {
      result = 1;
    } else {
      result = -1;
    }
  }

  switchVal = newSwitchVal;
  return result;
}

// MAIN FUNCTIONS
void setup() {
  // TIMER SETUP
  // output on pin 9
  TCCR1A = bit(COM1A0);
  // PWM up to 255, divide clock by 8 (1 MHz)
  TCCR1B = bit(WGM12) | bit(CS11);

  // PIN SETUP
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(BC1_PIN, OUTPUT);
  pinMode(BDIR_PIN, OUTPUT);

  for(int i = 0; i < 8; i++) {
    pinMode(BIT_TO_PIN_MAPPING[i], OUTPUT);
  }
  writeToBus(0);

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // RESET AY-3-8910
  digitalWrite(RESET_PIN, LOW);
  delay(1);
  digitalWrite(RESET_PIN, HIGH);

  // SERIAL ENABLE
  Serial.begin(9600);

  // testing
  // tone A amplitude max

  // disable everything except tone A
  setRegister(7, 0376);
}

void loop() {
  // setNoteFreq(261.6);
  // delay(1000);
  // setNoteFreq(329);
  // delay(1000);
  // setNoteFreq(392);
  // delay(1000);

  handleRotaryStateChange();
  handleSwitchStateChange();
}

int currentNote = 0;
void handleRotaryStateChange() {
  int rotaryChange = getRotaryStateChange();
  if (rotaryChange == 0) { return; }

  currentNote += rotaryChange + 12;
  currentNote %= 12;
  Serial.println(NOTE_FREQ[currentNote]);
  setNoteFreq(NOTE_FREQ[currentNote]);
}

int toneAmplitudeA = 0;
void handleSwitchStateChange() {
  int switchChange = getSwitchStateChange();
  if (switchChange == 1) {
    toneAmplitudeA ^= 0xF;
    Serial.println(toneAmplitudeA, HEX);
    setRegister(010, toneAmplitudeA);
  }
}
