#include <stdint.h>
#include "keyboard.h"
#include "video.h"
#include "pcspkr.h"
#include "timer.h"
#include "syscall.h"

extern int keyboardActivated;
extern int pianoMode;

void (* syscallFunctions[10])(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest) = {0, readSC, writeSC, clearSC, pianoSC, boolkeySC, getTimerSC, playTimeSC, stopsoundSC, playSoundOnlySC};

uint64_t syscallHandler(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	 //DESPUES SACAR EL SWITCH
	
	(*syscallFunctions[index])(fd, buff, buffSize, dest);


	return 0;
} 

void readSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	char aux;
	aux = getKey();
			if(aux != 0){
				*dest = aux;
			}
}

void writeSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	if(buffSize == 0)
				vPrintDec(*buff);
			if(buffSize == 1)
				vPrintChar(*buff);
			else
				vPrintN(buff, buffSize);
}
void clearSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	vClear();
}

void pianoSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	playPianoKey(fd);
}

void boolkeySC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	keyboardActivated = !fd;
	pianoMode = fd;
}

void getTimerSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	*dest = getTimer();
}

void playTimeSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	makeSound(fd, buffSize);
}

void stopsoundSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	stopSounderC();
}

void playSoundOnlySC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	playKeyNote(fd);
}

