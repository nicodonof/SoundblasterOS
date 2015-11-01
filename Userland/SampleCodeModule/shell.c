#include <stdint.h>
char getChar();
void putChar(char c);
void write(int fd, char * buff, int size);
void read(int fd,char * destination);
uint64_t syscaller(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);



void shell(){

	printOsName();
	char aux = 0;
	
	while(1){
		write(1, "SoundblasterOS> ", 16);
		do{
			aux = getChar();
			if(aux != 0)
				write(1,aux,1);
		} while (aux != '\n');
	}
}

void printOsName(){
	putChar('<');
	write(1,"================================ SoundblasterOS ================================",78);
	putChar('>');
}



void read(int fd,char * destination){
	syscaller(1,fd,0,0,destination);
}

void write(int fd, char * buff, int size){
	syscaller(2,fd, buff, size, 0);
}

char getChar(){
	char c = 0;
	//read(1,&c);
	return c;
}

void putChar(char c){
	write(1, &c,1);
}
