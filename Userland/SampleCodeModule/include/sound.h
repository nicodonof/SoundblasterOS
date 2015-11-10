#ifndef SOUNDH
#define SOUNDH
#define ODETOJOY (uint8_t*) 0x500000
#define TETRIS (uint8_t*) 0x5000F9
#define MARIO (uint8_t*) 0x5001DA



void playSong(int song);
void playNote(char note, char octave, int length, int delay);

#endif