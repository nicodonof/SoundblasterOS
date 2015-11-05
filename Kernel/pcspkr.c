#include <stdint.h>
typedef enum colors { BLACK, SBLUE, SGREEN, SCYAN, SRED, SPINK, SYELLOW, SWHITE, GREY, BLUE, GREEN, CYAN, RED, PINK, YELLOW, WHITE }; 

extern void sounder();
extern void stop_sounder();
void sleepT(int);

float notefreqs[7][13] = {
	{0.0,	16.35,	17.32,	18.35,	19.45,	20.60,	21.83,	23.12,	24.50,	25.96,	27.50,	29.14,	30.87},
	{0.0,	32.70,	34.65,	36.71,	38.89,	41.20,	43.65,	46.25,	49.00,	51.91,	55.00,	58.27,	61.74},
	{0.0,	65.41,	69.30,	73.42,	77.78,	82.41,	87.31,	92.50,	98.00,	103.83,	110.00,	116.54,	123.47},
	{0.0,	130.81,	138.59,	146.83,	155.56,	164.81,	174.61,	185.00,	196.00,	207.65,	220.00,	233.08,	246.94},
	{0.0,	261.63,	277.18,	293.66,	311.13,	329.63,	349.23,	369.99,	392.00,	415.30,	440.00,	466.16,	493.88}, // MEDIO
	{0.0,	523.25,	554.37,	587.33,	622.25,	659.26,	698.46,	739.99,	783.99,	830.61,	880.00,	932.33,	987.77},
	{0.0,	1046.50,1108.73,1174.66,1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760.00,1864.66,1975.53}
};

int note[7] = { 26163, 29366, 32963, 34923, 39200, 44000, 49388 };

int freqToColorAndPos(int freq){
	for (int i = 0; i < 7; ++i){
		if((0x1234dd / (note[i] / 100)) == freq){
			return i+1;
		} 
	}
	return 1;
}


 

void makeSound(int freq, int time){
	int aux = freqToColorAndPos(freq);
	vPrintCharColorInPos(14, aux,2 ,aux * 9);
	//speaker_beep(200, 5);
	sounderC(freq);
	//while(1){
	//	vPrintDec(getSeconds());
	//}
	/*int aux = getSeconds();
	while(aux+2>getSeconds()){
		vPrintDec(aux+2);
		vPrintChar(':');
		vPrintDec(getSeconds());
		vPrintChar(' ');
	}*/
	/*sleep(2);
	stopSounderC();*/
}

void sounderC(uint16_t freq){
	outb(0xB6, 0x43);
	outb((uint8_t)freq, 0x42);
	outb((uint8_t) (freq>>8), 0x42);

	uint8_t aux = inb(0x61);
	aux = aux | 3;
	outb(aux, 0x61);
}

void stopSounderC(int time){
	uint8_t aux = inb(0x61);
	aux = aux | 252;
	outb(aux, 0x61);
}

