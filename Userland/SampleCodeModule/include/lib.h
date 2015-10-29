#ifndef libh
#define libh

char getChar();
void putChar(char c);
void write(int fd, char * buff, int size);
void read(int fd,char * destination);