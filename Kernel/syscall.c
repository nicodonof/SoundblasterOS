#include <stdint.h>

uint64_t syscallHandler(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest){
	int counter = 0;
	switch(index){
		case 1:  //read
			*dest = getKey();
			break;
		case 2: //write
			while(counter < buffSize){
				vPrintChar((char)buff[counter++]);
			}
			break;
	}

	
} 



//SUDO MODPROBE PCSPKR
//SUDO apt-get beep