#include <video.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

int deleteCounter = 0;
static char buffer[64] = { '0' };
static uint16_t * const video = (uint16_t*)0xB8000;
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
	deleteCounter = 0;
}

void vPrintN(const char * string, int n){
	int i;

	for (i = 0; string[i] != 0 && i < n; i++)
		vPrintChar(string[i]);	
	deleteCounter = 0;
}

void vPrintChar(char character)
{
	if(character == '\n'){
		if(row == height - 1)
			vScroller();
		else 
			vNewline();
		deleteCounter = 0;
	}
	else if (character == '\t'){
		vPrintChar(' ');// ES ASI PQ SE RESETEA DELETE COUNTER EN EL vPrint
		vPrintChar(' ');
		vPrintChar(' ');
		vPrintChar(' ');
		deleteCounter += 4;
	}
	else if(character == '\b')
		vDeleteLastChar();
	else if(col == width){
		if(row == height-1)
			vScroller();
		else
			row++;
		col = 0;
		video[width * row + col] = charColor(character, color);
		col++;
		deleteCounter++;
	} else {
		video[width * row + col] = charColor(character, color);
		col++;
		deleteCounter++;
	}
}
void vPrintCharInPos(char character, int row2, int col2){
	video[width * row2 + col2] = charColor(character, color);
}

void vPrintSelector(int boolSelector){
	if(boolSelector)
		video[width * row + col] = charColor(' ', 0xFF);
	else
		video[width * row + col] = charColor(' ', 0);
}

void vDeleteLastChar(){
	if(deleteCounter == 0)
		return;
	vPrintCharInPos(' ',row,col); // para deletear el selector
	if(col == 0){
		col = width-1;
		row--;
	} else
		col--;
	vPrintCharInPos(' ',row,col);
	deleteCounter--;
}

uint16_t charColor(char c,char color){
	uint16_t pakash = (uint16_t) c;
	return (pakash | (color << 8));
}

void vNewline()
{
	do{
		video[width * row +col] = charColor(' ',color);
		col++;
	}
	while(col != width);
		row++;
	col = 0;
}

void vScroller(){
	int i,j;
	vPrintCharInPos(' ',row,col);// borra el selector
	for(i=2;i<height;i++){
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


