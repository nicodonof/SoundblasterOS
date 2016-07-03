#ifndef MEM_H
#include <stdint.h>
#include "process.h"

uint64_t * pageAlloc();

void pageFree();

void initPageStack();

void * malloc(int len);

void newProcessContext(process * proc,void * func);

#endif