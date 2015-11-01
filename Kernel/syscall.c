#include <stdint.h>

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
				vPrintDec(*buff);
			if(buffSize == 1)
				vPrintChar(*buff);
			else
				vPrintN(buff, buffSize);
			break;
	}

	return 0;
} 



//SUDO MODPROBE PCSPKR
//SUDO apt-get beep