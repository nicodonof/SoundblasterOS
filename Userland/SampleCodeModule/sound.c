#include "sound.h"
#include <stdint.h>
static uint8_t * const songsDirections[3] = {ODETOJOY, TETRIS, MARIO};

extern auxer;

void playSong(int song){
    auxer = 0;
    while(auxer != '\n'){
        int i = 0;
        while(songsDirections[song][i]!=0 && auxer != '\n'){
            auxer = getChar();
            playNote(songsDirections[song][i], songsDirections[song][i+1], getRealTime(songsDirections[song][i+2]), getRealTime(songsDirections[song][i+3]));
            i+=4;
        }
    }
}

void playNote(char note, char octave, int length, int delay){
   syscaller(7,note,0, octave,0);
   sleep(length);
   syscaller(8,0,0,0,0);
   sleep(delay);
}