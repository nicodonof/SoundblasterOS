#include <stdint.h>
char getChar();
void putChar(char c);
void write(int fd, char * buff, int size);
void read(int fd,char * destination);
uint64_t syscaller(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);

char desto = -1;
char auxer = 0;
char * aux;

void shell(){

	printOsName();

	
	while(1){
		write(1, "SoundblasterOS> ", 16);
		do{
			auxer = getChar();
			if(auxer != 0)
				putChar(auxer);
		} while (auxer != '\n');
	}
}

void printOsName(){
	putChar('<');
//	for (int i = 0; i < 78; ++i){
//			putChar('-');
//	}
	write(1,"================================ SoundblasterOS ================================",78);
	putChar('>');
}



void read(int fd,char * destination){
	syscaller(1,fd,0,0,(uint64_t*) destination);
}

void write(int fd, char * buff, int size){
	syscaller(2,fd, (uint64_t*) buff, size, 0);
}

char getChar(){
	char c = 0; // para ver si cambia
	read(1,&c);
	return c;
}

void putChar(char c){
	write(1, &c,1);
}
