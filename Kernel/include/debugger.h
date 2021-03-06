#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>

void sPrint(const char* s);
void sPrintNl();

void fprintf(int fd, char* fmt, ...) __attribute__ ((format (printf, 2, 3)));;
void sPrintf(char* fmt, ...) __attribute__ ((format (printf, 1, 2)));

void sPrintDec(uint64_t value);
void sPrintHex(uint64_t value);
void sPrintBin(uint64_t value);
void sPrintBase(uint64_t value, uint32_t base);

#endif