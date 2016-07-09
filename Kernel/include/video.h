#ifndef __SOUNDBLASTEROS__VIDEO__
#define __SOUNDBLASTEROS__VIDEO__

#include <stdint.h>
#include <types.h>

typedef struct {
	int x, y;
} point;

typedef struct {
	char c;
	color co;
} charco;

static const color red = {255, 0, 0};
static const color orange = {255, 140, 0};
static const color yellow = {255, 255, 0};
static const color limegreen = {50, 205, 0};
static const color brightgreen = {0, 255, 0};
static const color blue = {0, 0, 255};
static const color dodgerblue = {30, 144, 255};
static const color indigo = {199, 21, 133};
static const color violet = {75, 0, 130};
static const color aqua = {0, 200, 200};
static const color black = {0, 0, 0};
static const color white = {255, 255, 255};
static const color brown = {139, 69, 19};
static const color cyan = {0, 139, 139};
static const color gold = {255, 215, 0};
static const color crimson = {220, 20, 60};
static const color pink = {255, 205, 180};
static const color purple = {153, 50, 204};

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