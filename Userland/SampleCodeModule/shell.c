#include <stdint.h>
char getChar();
void putChar(char c);
void write(int fd, char * buff, int size);
void read(int fd,char * destination);
uint64_t syscaller(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);


char auxer = 0;

void shell(){

    printOsName();

    
    while(1){
        write(1, "SoundblasterOS> ", 16);
        int i = 0;
        char buffer[25];
        do{
            auxer = 0;
            read(1,&auxer);
            if(auxer != 0)
                buffer[i++] = auxer;
        } while (auxer != '\n');
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
    if(*s != 'c' && *s != 'q' && *s != 'a')
        return;
    
    str0(s);
	
    switch(*s){
        case 'c':
            if(strcmp(s,"clear"))
                clear();
        break;
        case 'q':
            strcmp(s,"quit");
        break;
        case 'a':
            strcmp(s,"audio");
        break;
    }
}

void clear(){
    write(1,"clearcommanndo",strlen("clearcommanndo"));
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