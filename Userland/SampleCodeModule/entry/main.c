#include <stdint.h>

extern char bss;
extern char endOfBinary;

void * memset(void * destiny, int32_t c, uint64_t length);

void shell();

int main() {
	memset(&bss, 0, &endOfBinary - &bss);

	shell();

	return 0xDEADBEEF;
}

void * memset(void * destiation, int32_t c, uint64_t length) {
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destiation;

	while(length--)
		dst[length] = chr;

	return destiation;
}