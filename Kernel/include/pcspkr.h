#ifndef __SOUNDBLASTEROS__PCSPKR__
#define __SOUNDBLASTEROS__PCSPKR__

#include <stdint.h>

int freqToColorAndPos(int freq);
void makeSound(int freq, int time);
void sounderC(uint16_t freq);
void stopSounderC();

#endif