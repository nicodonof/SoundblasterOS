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

int strcmp(const char * str1, const char * str2){
    int i;
    for(i=0;str1[i] != 0;i++)
        if(str1[i] != str2[i])
            return 0;
    if(str2[i] != 0)
        return 0;
    return 1;
}

void print(char * s){
    while (*s++!=0){
        putChar(*s);
    }
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