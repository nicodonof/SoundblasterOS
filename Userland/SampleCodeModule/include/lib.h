#ifndef __SOUNDBLASTEROS__LIB__
#define __SOUNDBLASTEROS__LIB__

#include <stdint.h>

uint64_t syscaller(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);

char getChar();
void putChar(char c);
void write(int fd, char * buff, int size);
void read(int fd,char * destination);

#endif