#include <stdint.h>

uint64_t syscallHandler(uint64_t index,uint64_t fd, uint64_t c, void * desc){
	
	
	vPrintDec(index);
	vPrintChar(' ');
	vPrintDec(fd);
	vPrintChar(' ');
	vPrintDec(c);
	vPrintChar(' ');
	vPrintDec(&desc);
	vNewline();
	
	switch(index){
		case 1:  //read
			desc = getKey();
			break;
		case 2: //write
			vPrintChar((char)c);
			break;
	}

	
} 