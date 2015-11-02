#ifndef __SOUNDBLASTEROS__SHELL__
#define __SOUNDBLASTEROS__SHELL__

#include "lib.h"

char getChar();
void putChar(char c);
void write(int fd, char * buff, int size);
void read(int fd,char * destination);

void shell();
void printOsName();

#endif
