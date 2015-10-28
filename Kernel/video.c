#include <video.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);


static char buffer[64] = { '0' };
static uint16_t * const video = (uint16_t*)0xB8000;
//static uint8_t * currentVideo = (uint8_t*)0xB8000;
static int row = 0;
static int col = 0;
static const uint32_t width = 80;
static const uint32_t height = 25 ;
uint8_t color = 7;

void vPrint(const char * string)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		vPrintChar(string[i]);
}

void vPrintChar(char character)
{
	video[width * row + col] = charColor(character, 0x07);
	if(character == '\n')
		vNewline();
	else if (character == '\t')
		vPrint("    ");
	else if(character == '\b')
		;
	else if(col == width-1){
		if(row == height-1)
			vScroller();
		else
			row++;
		col = 0;
	} else {
		col++;
	}
}

uint16_t charColor(char c,char color){
	uint16_t pakash = (uint16_t) c;
	return (pakash | (color << 8));
}

void vNewline()
{
	do
	{
		video[width * row +col] = charColor(' ',color);
		col++;
	}
	while(col != width);
	row++;
	col = 0;
}

void vScroller(){
	int i,j;
	for(i=1;i<height;i++){
		for(j=0;j<width;j++){
			video[(i-1) *width + j] = video[i* width + j]; 
		}
	}
	col = 0;
	vNewline();
	row--;
}

void vPrintDec(uint64_t value)
{
	vPrintBase(value, 10);
}

void vPrintHex(uint64_t value)
{
	vPrintBase(value, 16);
}

void vPrintBin(uint64_t value)
{
	vPrintBase(value, 2);
}

void vPrintBase(uint64_t value, uint32_t base)
{
    uintToBase(value, buffer, base);
    vPrint(buffer);
}

void vClear()
{
	int i;

	for (i = 0; i < height * width; i++)
		video[i] = ' ' | (color << 8); 
	row = 0;
	col = 0;
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


