#include <stdint.h>

uint64_t syscallHandler(uint64_t index,uint64_t fd, uint64_t c, uint64_t * dest){
	
	
	switch(index){
		case 1:  //read
			*dest = getKey();
			break;
		case 2: //write
			vPrintChar((char)c);
			break;
	}

	
} 



//SUDO MODPROBE PCSPKR
//SUDO apt-get beep