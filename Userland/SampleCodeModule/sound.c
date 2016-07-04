#include "sound.h"
#include <stdint.h>
static uint8_t * const songsDirections[4] = {ODETOJOY, TETRIS, MARIO, SECRET};

extern auxer;

/*Corre alguna de las canciones*/
void playSong(int song){
    auxer = 0;
    int i = 0;
    while(songsDirections[song][i]!=0 && auxer != '\n'){
        auxer = getChar();
        playNote(songsDirections[song][i], songsDirections[song][i+1], getRealTime(songsDirections[song][i+2]), getRealTime(songsDirections[song][i+3]));
        i+=4;
    }    
}

/*Corre alguna de las canciones sin frenar*/
void playSongNoStop(int song){
    auxer = 0;
    int i = 0;
    while(songsDirections[song][i]!=0){
        auxer = getChar();
        playNoteNoVid(songsDirections[song][i], songsDirections[song][i+1], getRealTime(songsDirections[song][i+2]), getRealTime(songsDirections[song][i+3]));
        i+=4;
    }
}

/*Playeae una nota en tal octava de tanta duracion y de tanto delay entre ella y la siguiente nota.*/
void playNote(char note, char octave, int length, int delay){
   syscaller(7,note,0, octave,0);
   sleep(length);
   syscaller(8,0,0,0,0);
   sleep(delay);
}

/*Playeae una nota en tal octava de tanta duracion y de tanto delay entre ella y la siguiente nota.*/
void playNoteNoVid(char note, char octave, int length, int delay){
   syscaller(23,note,0, octave,0);
   sleep(length);
   syscaller(8,0,0,0,0);
   sleep(delay);
}