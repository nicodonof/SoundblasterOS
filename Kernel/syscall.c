#include <stdint.h>
#include "keyboard.h"
#include "video.h"
#include "pcspkr.h"
#include "timer.h"

extern int keyboardActivated;
extern int pianoMode;

uint64_t syscallHandler(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	char aux; //DESPUES SACAR EL SWITCH
	switch(index){
		case 1:  //read
			aux = getKey();
			if(aux != 0){
				*dest = aux;
			}
			break;
		case 2: //write
			if(buffSize == 0)
				vPrintDec((char)*buff);
			if(buffSize == 1)
				vPrintChar(*buff);
			else
				vPrintN(buff, buffSize);
			break;
		case 3: //clear
			vClear();
			break;
		case 4: //piano
			makeSound(fd, buffSize);
			break;
		case 5: //bool key
			keyboardActivated = !fd;
			pianoMode = fd;
			break;
		case 6: //getseconds
			*dest = getTimer();
			break;
		case 7: //playtime
			makeSound(fd,buffSize);
			break;
		case 8: //stopsound
			stopSounderC();
			break;



	}

	return 0;
} 
