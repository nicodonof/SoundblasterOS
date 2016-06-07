#include <serial.h>
#include <debugger.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };

void sPrint(const char* s) {
	for (int i = 0; s[i] != 0; i++) {
		write_serial(s[i]);
	}
}

void sPrintNl() {
	write_serial('\n');
}

void sPrintDec(uint64_t value)
{
	sPrintBase(value, 10);
}

void sPrintHex(uint64_t value)
{
	sPrintBase(value, 16);
}

void sPrintBin(uint64_t value)
{
	sPrintBase(value, 2);
}

void sPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    sPrint(buffer);
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

