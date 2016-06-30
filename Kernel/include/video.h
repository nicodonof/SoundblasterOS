#ifndef __SOUNDBLASTEROS__VIDEO__
#define __SOUNDBLASTEROS__VIDEO__

#include <stdint.h>
#include <types.h>

typedef struct {
	unsigned int x, y;
} point;

typedef struct {
	char c;
	color co;
} charco;
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

void putPixel(int x, int y, color c);
void putPixels(color c);
void draw_text(char* text, int length, point start, int size, color c);
void draw_schar(char to, point where, color c);
void draw_char(char to, point where, int size, color c);
point toPoint(unsigned int x, unsigned int y);
void put_pixel(unsigned int x, unsigned int y, color c);

#endif