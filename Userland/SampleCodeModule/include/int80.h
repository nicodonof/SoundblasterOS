#ifndef __SOUNDBLASTEROS__INT80__
#define __SOUNDBLASTEROS__INT80__

#include <stdint.h>

extern uint64_t syscaller(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize , uint64_t * dest);

#endif
