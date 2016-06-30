#include <video.h>
#include <font.h>
#include <debugger.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

int deleteCounter = 0;
static char buffer[64] = { '0' };
static uint16_t * const video = (uint16_t*)0xB8000;
static int row = 0;
static int col = 0;
static const uint32_t width = 80;
static const uint32_t height = 40 ;
color background = {50,205,0};
color letter = {255,0,0};
uint8_t cColor = 7;
int videoMode = 0; // 0 = consoleMode, 1 = pianoMode, 2 = itunesMode;
int timerTick = 0;
int xRes;
int yRes;
int bpp;
char vidMem[40][80];
uint32_t * mem;
char * mem2;


extern keyboardActivated;

color red = {255, 0, 0};
color orange = {255, 140, 0};
color yellow = {255, 255, 0};
color limegreen = {50, 205, 0};
color brightgreen = {0, 255, 0};
color blue = {0, 0, 255};
color dodgerblue = {30, 144, 255};
color indigo = {199, 21, 133};
color violet = {75, 0, 130};
color aqua = {0, 200, 200};
color black = {0, 0, 0};
color white = {255, 255, 255};
color brown = {139, 69, 19};
color cyan = {0, 139, 139};
color gold = {255, 215, 0};
color crimson = {220, 20, 60};
color pink = {255, 205, 180};
color purple = {153, 50, 204};
float libDraw_text_character_spacing = 1.2;

void vInit(){
	xRes = *((uint16_t*) 0x5084);
	yRes = *((uint16_t*) 0x5086);
	bpp = *((uint8_t*) 0x5088);
	mem = (uint32_t*) 0x5080;
	mem2 = *mem;
	memset(vidMem, 0, sizeof(char)*80*40);
	putPixels(background);
	sPrintf("xr: %d\n",xRes);
	sPrintf("yr: %d\n",yRes);
}
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

void vColor(char colour){
	cColor = colour;
}

void vResetColor(){
	cColor = 7;
}

void vPrintCharColor(char c, char co){
	vColor(co);
	vPrintChar(c);
	vResetColor();
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
	}
	else if(character == '\b')
		vDeleteLastChar();
	else if(col == width){
		if(row == height-1)
			vScroller();
		else
			row++;
		col = 0;
		
		point p;
		p.y= yRes/height * row + 5; 
		p.x= xRes/width * col - 5;
		draw_schar(character, p, letter);
		charco cc;
		cc.c=character; 
		cc.co=letter;
		vidMem[row][col] = character;
		video[width * row + col] = charColor(character, cColor);
		col++;
		deleteCounter++;
	} else {
		
		point p;
		p.y= yRes/height * row + 5; 
		p.x= xRes/width * col - 5;
		draw_schar(character, p, letter);
		vidMem[row][col] = character;
		video[width * row + col] = charColor(character, cColor);
		char c = vidMem[row][col];
		sPrintf("%d ", c);	
		sPrintf("%c %d %d\n", character, cColor, charColor(character,cColor));
		getChhhar();
		col++;
		deleteCounter++;
	}
}

uint16_t charColor(char c,char cColor){
	uint16_t pakash = (uint16_t) c;
	return (pakash | (cColor << 8));
}

void getChhhar(){
}

void vPrintCharInPos(char character, int row2, int col2){
	point p;
	p.y= yRes/height * row2 + 5; 
	p.x= xRes/width * col2 - 5;
	if(character == 15){
		draw_schar(character, p, background);
	} else {
		draw_schar(character, p, letter);
	}
	vidMem[row2][col2] = character;
	video[width * row2 + col2] = charColor(character, cColor);
}

void vPrintCharColorInPos(char character, char co, int row2, int col2){
	point p;
	p.y= yRes/height * row2 + 5; 
	p.x= xRes/width * col2 - 5;
	draw_schar(character, p, letter);	

	vColor(co);
	vidMem[row2][col2] = character;
	for (int i = 0; i < height; ++i)	{
		for (int j = 0; j < width; ++j)		{
			sPrintf("%c",vidMem[i][j]);
		}
		sPrintf("\n");
	}
	video[width * row2 + col2] = charColor(character, cColor);
	vResetColor();
}

/*Selector que no esta hecho con hardware porque no llegmos*/
void vPrintSelector(int boolSelector){
	if(!keyboardActivated){
		return;
	}	
	if(boolSelector)
		video[width * row + col] = charColor(' ', 0x70);
	else
		video[width * row + col] = charColor(' ', 0x07);
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
	vPrintCharInPos(15,row,col);
	deleteCounter--;
}


void vNewline()
{
	int cColor2 = cColor;
	vResetColor();
	do{
		point p;
		p.y = yRes/height * row + 5;
		p.x = xRes/width * col - 5;
		vidMem [row][col] = 15;
		draw_schar(15, p, background);
		video[width * row +col] = charColor(' ',cColor);
		col++;
	}
	while(col != width);
		row++;
	col = 0;
	cColor = cColor2;
}


void vScroller(){
	int i,j;
	point p;
	char c;
	vPrintCharInPos(' ',row,col);// borra el selector
	for(i=2;i<height;i++){
		for(j=0;j<width;j++){
			p.y= yRes/height * i + 5; 
			p.x= xRes/width * j - 5;
			c = vidMem[i][j];
			vidMem[i-1][j] = c;
			if(c==15){
				draw_schar(c, p, background);
			} else {
				draw_schar(c, p, letter);
			}
			video[(i-1) *width + j] = video[i* width + j]; 

		}
	}
	col = 0;
	vNewline();
	row--;
}

extern int timer;

/*Activa la caida de las notas*/
void pianoModer(){
	if(videoMode){
		vAntiScroller();
	}
}

/*Es lo q hace q caigan las letras*/
void vAntiScroller(){
	int i,j;
	point p;
	char c;
	for(i=1;i<height-2;i++){
		for(j=0;j<width;j++){
			p.y= yRes/height * (height-i-1) + 5; 
			p.x= xRes/width * j - 5;
			c = vidMem[height-i-1][j];
			vidMem[height-i][j] = c;
			uint16_t c2 = video[(height-i-1)* width + j];
			video[(height-i) *width + j] = c2;
			if(c==15){
				draw_schar(c, p, background);
			} else {
				draw_schar(c, p, letter);
			}
		}
	}
	for(j=0;j<width;j++){
		p.y= yRes/height * (2) + 5; 
		p.x= xRes/width * j - 5;
		
		vidMem[2][j] = 15; 
		draw_schar(c, p, background);
		video[2 *width + j] = ' '; 
	}
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
	int i,j;
	for (i = 0; i < height * width; i++){
		vPrintCharInPos(15,i/width,i%width);
		vidMem[i/width][i%width];
	
		video[i] = ' ' | (cColor << 8); 
	}
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


int random_seed=1;
int maxrand(int seed,int max){
	random_seed = random_seed+seed * 1103515245 +12345;
	return (unsigned int)(random_seed / 65536) % (max+1); 
}

void putPixel(int x, int y, color c){
	
	int offset = 0;
	if(x>=0 && x < xRes && y >=0 && y<yRes){
		offset = x * yRes + y;
			if (bpp == 24){
				offset = offset * 3;
				mem2[offset] = c.blue;
				mem2[offset+1] = c.green;
				mem2[offset+2] = c.red;
			} else if (bpp == 32) {
				offset = offset * 4;
				mem2[offset] = 0x00;
				mem2[offset+1] = c.red;
				mem2[offset+2] = c.blue;
				mem2[offset+3] = c.green;
			}
	}
	
}


void putPixels(color background){
	int x = 0;
	int y = 0;
	for(x = 0; x < xRes; x++){
		for(y = 0; y < yRes; y++){
				putPixel(x,y,background);
			
		}
	}
	
}

void draw_text(char* text, int length, point start, int size, color c)
{
	int i=0;
	int len=length;
	if(size==1) {
	  	for(;i<len;i++) {
	  		draw_schar(*(text+i), toPoint(start.x+i*7+2, start.y), c);
		}
		return;
	}
	draw_char(*text, toPoint(start.x+i*7*size, start.y), size, c);
	for(i=1;i<len;i++) {
	  draw_char(*(text+i), toPoint(start.x+i*7*size*libDraw_text_character_spacing, start.y), size, c);
	}
}

void draw_schar(char to, point where, color c)
{
	char *bitmap = font[to];
	int x,y,set;
	for (y=12; y >= 0; y--) {
		for (x=7; x >= 0; x--) {
			set = bitmap[y] & 1 << x;
			if(set) put_pixel(where.x+(12-x), where.y+(7-y), c);
		}
	}
}

void draw_char(char to, point where, int size, color c)
{
	char *bitmap = font[to];
	int x,y,set,xe,ye;
	for (y=12; y >= 0; y--) {
		for (x=7; x >= 0; x--) {
			set = bitmap[y] & 1 << x;
			if(set)
			  	for(xe=0;xe<size;xe++)
				  	for(ye=0;ye<size;ye++)
						put_pixel(where.x+size*(12-x)+xe, where.y+size*(7-y)+ye, c);
		}
	}
}

void put_pixel(unsigned int x, unsigned int y, color c)
{
	int offset = 0;
	if (x >= 0 && x < xRes && y >= 0 && y < yRes) // Sanity check
	{
		offset = y * xRes + x;
		if (bpp == 24)
		{
			offset = offset * 3;
			mem2[offset] = c.blue;
			mem2[offset+1] = c.green;
			mem2[offset+2] = c.red;
		}
		else if (bpp == 32)
		{
			offset = offset * 4;
			mem2[offset] = 0x00;
			mem2[offset+1] = c.red;
			mem2[offset+2] = c.blue;
			mem2[offset+3] = c.green;
		}
	}
}

point toPoint(unsigned int x, unsigned int y){point t={x,y};return t;}