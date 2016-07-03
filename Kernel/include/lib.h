#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);
int strlen(const char * s);
int disableOrEnableInterrupts(int flagger);
int strcmp(const char * str1, const char * str2);

#endif