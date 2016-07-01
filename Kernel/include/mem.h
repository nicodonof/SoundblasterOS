#ifndef LIB_H


#include <stdint.h>

uint64_t * pageAlloc();

void pageFree();

void initPageStack();

void * malloc(int len);

#endif