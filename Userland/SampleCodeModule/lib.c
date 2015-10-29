#include <stdint.h>

static char dest = 0;

uint64_t syscaller(uint64_t index,uint64_t fd ,uint64_t c,uint64_t * dest);
/*
char getChar(){
	dest = -1; // para ver si cambia
	syscaller(1,1,0, &dest);
	if(dest != -1)
		putChar(dest);
	return dest;
}

void putChar(char c){
	syscaller(2,1,c,0);
}*/