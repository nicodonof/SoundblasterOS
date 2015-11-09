#ifndef __SOUNDBLASTEROS__PCSPKR__
#define __SOUNDBLASTEROS__PCSPKR__

#include <stdint.h>
#define freqParser(a,b) (0x1234dd/notefreqs[a-'0'-1][b-'A'])

int freqToColorAndPos(int freq);
void makeSound(int freq, int time);
void sounderC(uint16_t freq);
void stopSounderC();

#endif