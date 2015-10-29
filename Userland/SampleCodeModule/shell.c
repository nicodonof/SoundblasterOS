
char getChar();
void putChar(char c);
void write(int fd, char * buff, int size);
void read(int fd,char * destination);

static char dest = -1;

void shell(){

	printOsName();

	char aux = 0;
	while(1){
		int counterBuffer = 0;
		write(1, "SoundblasterOS> ", 16);
		do{
			aux = getChar();
		} while (aux != '\n');
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