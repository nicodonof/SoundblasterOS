#include <stdint.h>
char getChar();
void putChar(char c);
void write(int fd, char * buff, int size);
void read(int fd,char * destination);
uint64_t syscaller(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);
void help();

char auxer = 0;

void shell(){

    printOsName();

    
    while(1){
        write(1, "SoundblasterOS> ", 16);
        int i = 0;
        char buffer[75];
        do{
            auxer = 0;
            read(1,&auxer);
            if(auxer != 0){
                if(auxer == '\b'){
                    if(i>0)
                        i--;
                } else
                    buffer[i++] = auxer;
            }
                
        } while (auxer != '\n');
        write(1, buffer, strlen(buffer));
        buffer[i-1] = 0;
        parser(buffer);
    }
}

void printOsName(){
    putChar('<');
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

void parser(char * s, int size){
    if(*s != 'c' && *s != 'q' && *s != 'a' && *s != 'h'){
    	write(1,"No se reconoce el comando. Intente nuevamente.\n",47);
        return;
    }
    
    str0(s);
	
    switch(*s){
        case 'c':
            if(strcmp(s,"clear"))
                clear();
            else
            	write(1,"No se reconoce el comando. Intente nuevamente.\n",47);
        break;
        case 'q':
            if(strcmp(s,"quit"))
                clear();
            else
            	write(1,"No se reconoce el comando. Intente nuevamente.\n",47);
        break;
        case 'a':
            if(strcmp(s,"audio"))
                clear();
            else
            	write(1,"No se reconoce el comando. Intente nuevamente.\n",47);
        break;
        case 'h':
            if(strcmp(s,"help"))
                help();
            else
                write(1,"No se reconoce el comando. Intente nuevamente.\n",47);
        break;
    }
}

void clear(){
    syscaller(3,0,0,0,0);
    printOsName();
}

int strcmp(const char * str1, const char * str2){
    int i;
    for(i=0;str1[i] != 0;i++)
        if(str1[i] != str2[i])
            return 0;
    if(str2[i] != 0)
        return 0;
    return 1;
}



int strlen(const char * s){
    int n=0;
    while(*s++ != 0)
        n++;
    return n;
}

void str0(char * s){
    while(*s){
        if(*s == ' ')
            *s = 0;
        s++;
    }
}

void help(){
    char *clear = "clear    Clears the terminal screen\n";
    char *quit =  "quit     Quits the OS\n";
    char *audio = "audio    Performs Magic\n";
    char *help =  "help     Shows this message.. duh.\n";

    write(1,clear,strlen(clear));
    write(1,quit,strlen(quit));
    write(1,audio,strlen(audio));
    write(1,help,strlen(help));
}