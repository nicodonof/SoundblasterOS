#ifndef __SOUNDBLASTEROS__KEYBOARD__
#define __SOUNDBLASTEROS__KEYBOARD__

#define NUMLOCK 0xFFFFFFC5
#define LSHIFTR 0xFFFFFFAA
#define RSHIFTR 0xFFFFFFB6
#define CAPS 0x3A
#define LSHIFT 0x2A
#define RSHIFT 0x36
#define isNotAlpha(x) (x < 16 || (x > 25 && x < 30) || (x > 38 && x < 44) || (x > 50))

void write_key(char scancode);
char getKey();
char getNotLastKey();
void changeSelector();

#endif