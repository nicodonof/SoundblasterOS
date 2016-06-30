#include "timer.h"
#include "keyboard.h"
int seconds = 0;
int timer = 0;

/*Timer Handler*/
void keyboarddddd(){
	if(!(timer++%18)){
		seconds++;
	}
	pianoModer();
	changeSelector();
	return;
}

/*gettea los seconds*/
int getSeconds(){
	return seconds;
}

/* gettea el timer*/
int getTimer(){
	return timer;
}

