#include "pattern.h"

Pattern::Pattern(AY3 ay3, String notation, uint8_t channel) : ay3(ay3), notation(notation), channel(channel) {
  this->notation.trim();
  entries = parseNotation(notation);
}

void Pattern::play() {
  isPlaying = true;
  ay3.setAmplitudeStatic(channel, 0xF);
  startEntry(entries[entryPosition]);
}

void Pattern::pause() {
  isPlaying = false;
  ay3.silence();
}

void Pattern::togglePlaying() {
  if (isPlaying) {
    pause();
  } else {
    play();
  }
}

void Pattern::update() {
  if (!isPlaying) return;

  uint32_t noteLengthMicros = (60.0f / bpm) * 1000000.0f;
  if (micros() - entryStartTime > noteLengthMicros) {
    entryPosition++;
    if (entryPosition >= 16) {
      entryPosition = 0;
    }

    startEntry(entries[entryPosition]);
  }
}

void Pattern::setBpm(float bpm) {
  if (bpm <= 0.0f) return;
  this->bpm = bpm;
}

PatternEntry* Pattern::parseNotation(String notation) {
  static PatternEntry entries[16];

  String lines[16];
  int startIndex = 0;
  int endIndex;
  int linesIndex = 0;

  if (notation.charAt(0) == '\n') {
    startIndex = 1;
  }

  while (startIndex < notation.length()) {
    endIndex = notation.indexOf("\n", startIndex);
    if (endIndex == -1) {
      endIndex = notation.length();
    }
    lines[linesIndex] = notation.substring(startIndex, endIndex);
    linesIndex++;
    startIndex = endIndex + 1;
  }

  for (int i = 0; i < 16; i++) {
    String line = lines[i];

    if (line.length() == 0) {
      entries[i] = PatternEntry();
      continue;
    }

    String note = line.substring(0, 3);
    entries[i] = PatternEntry(note);
  }

  return entries;
}

void Pattern::startEntry(PatternEntry entry) {
  entryStartTime = micros();

  ay3.setNoteFrequency(channel, entry.noteFrequency());
  //ay3.setAmplitudeStatic(channel, 0xF);
  ay3.setChannelEnabled(channel, false, true);
  ay3.setChannelEnabled(channel, true, false);
}
