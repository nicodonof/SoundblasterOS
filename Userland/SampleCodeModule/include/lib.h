#ifndef __SOUNDBLASTEROS__LIB__
#define __SOUNDBLASTEROS__LIB__

#include <stdint.h>

char getChar();
void putChar(char c);
void write(int fd, char * buff, int size);
void read(int fd,char * destination);

#endif