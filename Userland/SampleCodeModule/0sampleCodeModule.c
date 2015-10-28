#include <stdint.h>


extern char bss;
extern char endOfBinary;

static char dest = 0;


void * memset(void * destiny, int32_t c, uint64_t length);
uint64_t syscaller(uint64_t index,uint64_t fd ,uint64_t c,uint64_t * dest);
char getChar();

int main() {
	//Clean BSS
	memset(&bss, 0, &endOfBinary - &bss);

	//All the following code may be removed 
	
	//putChar('s');

	
	char aux = 0;
	while(1){
		do{
			
			aux = getChar();
		
		} while (aux != '\n');

	}
	
}

void * memset(void * destiation, int32_t c, uint64_t length) {
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destiation;

	while(length--)
		dst[length] = chr;

	return destiation;
}

char getChar(){
	dest = -1; // para ver si cambia
	syscaller(1,1,0, &dest);
	if(dest != -1)
		putChar(dest);
	return dest;
}

void putChar(char c){
	syscaller(2,1,c,0);
}

