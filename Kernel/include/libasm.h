#ifndef __SOUNDBLASTEROS__LIBASM__
#define __SOUNDBLASTEROS__LIBASM__

#include <stdint.h>

extern void outb(uint8_t info, uint16_t port);
extern uint8_t inb(uint8_t port);

#endif