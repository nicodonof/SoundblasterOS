#include "shell.h"
#include "int80.h"

static char dest = 0;
char c = 0;

void read(int fd,char * destination){
    syscaller(1,fd,0,0,(uint64_t*) destination);
}

void write(int fd, char * buff, int size){
    syscaller(2,fd, (uint64_t*) buff, size, 0);
}

char getChar(){
    c = 0; // para ver si cambia
    read(1,&c);
    return c;
}

void putChar(char c){
    write(1, &c,1);
}