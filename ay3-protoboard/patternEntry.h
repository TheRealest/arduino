#ifndef PATTERN_ENTRY_H_
#define PATTERN_ENTRY_H_

#include <Arduino.h>

class PatternEntry {
  public:
    PatternEntry(String note) : note(note) {};
    PatternEntry() : note("---") {};

    String note;

    float noteFrequency();
};

#endif
