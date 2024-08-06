#include "patternEntry.h"

// note frequencies for A4 to G#4
const float NOTE_FREQ[12] = {
  220.0,
  233.1,
  246.9,
  261.6,
  277.2,
  293.7,
  311.1,
  329.6,
  349.2,
  370,
  392,
  415.3
};

// note names for A to G#
const String NOTE_NAMES[12] = {
  "A-",
  "A#",
  "B-",
  "C-",
  "C#",
  "D-",
  "D#",
  "E-",
  "F-",
  "F#",
  "G-",
  "G#"
};

float PatternEntry::noteFrequency() {
  if (note == "---") return 0; 

  int octave = note.charAt(2) - '0';
  int relativeOctave = octave - 4;
  int noteIndex = -1;

  for (int i = 0; i < 12; i++) {
    if (note.substring(0, 2) == NOTE_NAMES[i]) {
      noteIndex = i;
      break;
    }
  }
  if (noteIndex == -1) return 0;

  return NOTE_FREQ[noteIndex] * pow(2, relativeOctave);
}
