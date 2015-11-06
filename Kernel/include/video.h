#ifndef __SOUNDBLASTEROS__VIDEO__
#define __SOUNDBLASTEROS__VIDEO__

#include <stdint.h>

void vPrint(const char * string);
void vPrintN(const char * string, int n);

void vColor(char colour);
void vResetColor();
void vPrintCharColor(char c, char co);

void vPrintChar(char character);
void vPrintCharInPos(char character, int row2, int col2);
void vPrintCharColorInPos(char character, char co, int row2, int col2);
void vPrintSelector(int boolSelector);
void vDeleteLastChar();

uint16_t charColor(char c,char color);
void vNewline();
void vScroller();
void pianoModer();
void vAntiScroller();

void vPrintDec(uint64_t value);
void vPrintHex(uint64_t value);
void vPrintBin(uint64_t value);
void vPrintBase(uint64_t value, uint32_t base);
void vClear();

#endif