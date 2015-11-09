#include "pcspkr.h"
#include "video.h"
#include "libasm.h"
extern void sounder();
extern void stop_sounder();
void sleepT(int);
int sound = 0;
int lastFreq = 0;
typedef enum colors { BLACK, SBLUE, SGREEN, SCYAN, SRED, SPINK, SYELLOW, SWHITE, GREY, BLUE, GREEN, CYAN, RED, PINK, YELLOW, WHITE }; 
int notefreqs[7][12] = {
    {  16,  17,  18,  19,  20,  21,  23,  24,  26,  27,  29,  30},
    {  32,  34,  36,  38,  41,  43,  46,  49,  52,  55,  58,  61},
    {  65,  69,  73,  77,  82,  87,  92,  98,  104, 110, 116, 123},
    {  130, 138, 146, 155, 164, 174, 185, 196, 207, 220, 233, 247},
    {  261, 277, 293, 311, 329, 349, 369, 392, 415, 440, 466, 493}, // MEDIO
    {  523, 554, 587, 622, 659, 698, 739, 784, 830, 880, 932, 987},
    {  1046,1108,1174,1244,1318,1396,1479,1567,1661,1760,1864,1975}
};


int note[8] = {22000, 26163, 29366, 32963, 34923, 39200, 44000, 49388 };

int keyToNotefreq(char key){
    int keyToNoteTable[26] = {0,0,0,notefreqs[4][0] /* D (DO)*/,0,notefreqs[4][2]/* F (RE)*/,notefreqs[4][4]/* G (MI)*/,
                              notefreqs[4][5] /* H (FA)*/,notefreqs[4][8],
                              notefreqs[4][7] /* J (SOL)*/,notefreqs[4][9]/* K (LA)*/, 
                              notefreqs[4][11] /* L (SI)*/,0,0,notefreqs[4][10],0, 0,notefreqs[4][1],
                              0,notefreqs[4][3],notefreqs[4][6],0,0,0,0,0};
    return (0x1234dd / (keyToNoteTable[key - 'a']));
}

int freqToColorAndPos(int freq){
	for (int i = 0; i < 12; ++i){
		if((0x1234dd / (notefreqs[4][i]) == freq)){
			return i+1;
		}
	}
	return 1;
}


void makeSound(int note, int octave){
	int freq = freqParser(octave,note);
	int aux = freqToColorAndPos(freq);
	vPrintCharColorInPos(14, aux,2 ,aux * 6);
	if(!sound || lastFreq != freq)
		sounderC(freq);
	lastFreq = freq;
}

void playPianoKey(int freq){
	freq = keyToNotefreq(freq);
	int aux = freqToColorAndPos(freq);
	vPrintCharColorInPos(14, aux,2 ,aux * 6);
	if(!sound || lastFreq != freq)
		sounderC(freq);	
	lastFreq = freq;
}


void sounderC(uint16_t freq){
	outb(0xB6, 0x43);
	outb((uint8_t)freq, 0x42);
	outb((uint8_t) (freq>>8), 0x42);

	uint8_t aux = inb(0x61);
	if (aux!= aux | 3){
		sound = 1;
		aux = aux | 3;
		outb(aux, 0x61);
	}
}

void stopSounderC(){
	uint8_t aux = inb(0x61);
	aux = aux | 252;
	outb(aux, 0x61);
	sound = 0;
}

