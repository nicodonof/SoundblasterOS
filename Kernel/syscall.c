#include <stdint.h>
#include "keyboard.h"
#include "video.h"
#include "pcspkr.h"
#include "timer.h"
#include "syscall.h"
#include "process.h"
#include "debugger.h"
#include "msgQueue.h"

extern int keyboardActivated;
extern int videoMode;
extern color background;

void (* syscallFunctions[27])(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest) = 
{0, readSC, writeSC, clearSC, pianoSC, boolkeySC,
	getTimerSC, playTimeSC, stopsoundSC, playSoundOnlySC, changeOctaveSC, 
	clearBufferSC,createProcessSC, endProcessSC, listProcessSC, nextProcessSC, 
	drawRecSC, openMsgQSC, getMsgQSC, closeMsgQSC, sendMsgToQSC, 
	receiveMsgFromQSC, drawLineSC, playSoundNoVideoSC, printCharInPosSC, drawTriangSC, 
	getOpenedQueueNamesSC};

uint64_t syscallHandler(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){


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
	if(buffSize == 0){
			//sPrintf("%d", *buff);
		vPrintDec((int)*buff);
	}
	if(buffSize == 1)
		vPrintChar(*buff);
	else
		vPrintN((char *)buff, buffSize);
}
void clearSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	vClear();
}

void pianoSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	if(buffSize)
		playPianoKey(fd);
	else
		playKeyNote(fd);
}

void boolkeySC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	keyboardActivated = !fd;
	videoMode = buffSize;
}

void getTimerSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	uint64_t** dest2 = (uint64_t**)dest;
	*dest2 = getTimer();
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

void changeOctaveSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	changeOctave(fd);
}

void clearBufferSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	clearBuffer();
}
typedef struct{
	char name[24];
	void * instp;
}packash;


void createProcessSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){

	userToKernel();

	packash* auxPack = (packash*) buff;
	sPrintf("s:%s\n",auxPack->name);
	process * aux = createProcess(auxPack->name,auxPack->instp,buffSize);
	*dest = aux->pid;
	kernelToUser();

	forceScheduler();
	sPrintf("Termina de correr: %s\n ",aux->name);
}

void endProcessSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){

}

void listProcessSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	printPidList();
}

void nextProcessSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	//Ceder el procesador al proceso siguiente (fuertemente recomendada por roro)
}

void drawRecSC(uint64_t fd, uint64_t * buff, uint64_t buffSize, uint64_t * dest){
	color c;
	switch((int)dest){
		case 0: c=yellow; break;
		case 1: c=red; break;
		case 2: c=background; break;
		case 3: c=brightgreen; break;
	}
	draw_frect((point*)buff, fd, buffSize, c);
}

void openMsgQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	uint64_t** dest2 = (uint64_t**)dest;
	*dest2 = openMsgQ((char *) buff);
}

void getMsgQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	uint64_t** dest2 = (uint64_t**)dest;
	*dest2 = getMsgQ((char *) buff);
}

void closeMsgQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	closeMsgQ((MessageQueue *)fd);
}

void sendMsgToQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	sendMsg(*buff, fd);
}

void receiveMsgFromQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	uint64_t** dest2 = (uint64_t**)buff;
	uint64_t** dest3 = (uint64_t**)dest;

	receiveMsg(*buff, dest);
}

void drawLineSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	draw_line((point*)buff, (point*)dest, yellow);
}

void playSoundNoVideoSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	makeSoundNoVideo(fd, buffSize);
}

void printCharInPosSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){

	vPrintCharInPos((char) fd, ((point*)buff)->x, ((point*)buff)->y);

}

void drawTriangSC(uint64_t fd, uint64_t * buff, uint64_t buffSize, uint64_t * dest){
	color c;
	switch((int)dest){
		case 0: c=yellow; break;
		case 1: c=red; break;
		case 2: c=background; break;
		case 3: c=brightgreen; break;
	}
	draw_triang((point*)buff, fd, c);
}

void getOpenedQueueNamesSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	sPrintf("BEFORE NAMES.\n");
	dest = getOpenedQueues();
	sPrintf("AFTER NAMES.\n");
}