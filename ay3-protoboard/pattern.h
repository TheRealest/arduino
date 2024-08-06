#ifndef PATTERN_H_
#define PATTERN_H_

#include <Arduino.h>
#include "patternEntry.h"
#include "ay3.h"

class Pattern {
  public:
    Pattern(AY3 ay3, String notation, uint8_t channel);
    PatternEntry* entries;

    const String notation;
    float bpm = 240.0f;

    void play();
    void pause();
    void togglePlaying();
    void update();

    void setBpm(float bpm);

  private:
    const AY3 ay3;
    const uint8_t channel;

    bool isPlaying = false;
    uint8_t entryPosition = 0;
    uint32_t entryStartTime = 0;

    PatternEntry* parseNotation(String notation);
    void startEntry(PatternEntry entry);
};

#endif
