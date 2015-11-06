#include "timer.h"
#include "keyboard.h"
int seconds = 0;
int timer = 0;

void keyboarddddd(){
	if(!(timer++%18)){
		seconds++;
	}
	changeSelector();
	pianoModer();
	return;
}

int getSeconds(){
	return seconds;
}

int getTimer(){
	return timer;
}

void sleep(int time){
	int aux = seconds;
	while(aux+time>seconds);
	return;
}