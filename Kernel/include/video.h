#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

void vScroller();
uint16_t charColor(char c,char color);
void vPrint(const char * string);
void vPrintChar(char character);
void vNewline();
void vPrintDec(uint64_t value);
void vPrintHex(uint64_t value);
void vPrintBin(uint64_t value);
void vPrintBase(uint64_t value, uint32_t base);
void vClear();

#endif