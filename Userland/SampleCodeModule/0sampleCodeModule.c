#include <stdint.h>


extern char bss;
extern char endOfBinary;


void * memset(void * destiny, int32_t c, uint64_t length);

static char dest = -1;

char getChar();
void putChar(char c);

int main() {
	//Clean BSS
	memset(&bss, 0, &endOfBinary - &bss);

	//All the following code may be removed 
	
	//putChar('s');

	write(1,"aa", 2);
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

void read(int fd,char * destination){
	return syscaller(1,fd,0,0,destination);
}

void write(int fd, uint64_t * buff, int size){
	return syscaller(2,fd, buff, size, 0);
}

char getChar(){
	dest = -1; // para ver si cambia
	read(1,&dest);
	if(dest != -1)
		putChar(dest);
	return dest;
}

void putChar(char c){
	write(1, &c,1);
}