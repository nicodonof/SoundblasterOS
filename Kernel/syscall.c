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

void (* syscallFunctions[13])(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest) = 
{0, readSC, writeSC, clearSC, pianoSC, boolkeySC, getTimerSC, 
	playTimeSC, stopsoundSC, playSoundOnlySC, changeOctaveSC, clearBufferSC,createProcessSC};

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
		
		//userToKernel();
		
		packash* auxPack = (packash*) buff;
		sPrintf("s:%s\n",auxPack->name);
		process * aux = createProcess(auxPack->name,auxPack->instp,buffSize);
		*dest = aux->pid;
		//kernelToUser();
		
		forceScheduler();
		sPrintf("SALE DE ACA\n");
	}

	void endProcess(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){

	}

	void listProcess(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){

	}

	void nextProcess(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	//Ceder el procesador al proceso siguiente (fuertemente recomendada por roro)
	}

	void randomSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){

	}

	void openMsgQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
		dest = openMsgQ((char *) buff);
	}

	void getMsgQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
		dest = getMsgQ((char *) buff);
	}

	void closeMsgQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
		closeMsgQ((MessageQueue *)fd);
	}

	void sendMsgToQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
		sendMsg((MessageQueue *) fd, (char *) buff);
	}
	
	void receiveMsgFromQSC(uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
		dest = receiveMsg((MessageQueue *) fd);
	}
