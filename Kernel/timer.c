#include "timer.h"
#include "keyboard.h"
#include "debugger.h"
int seconds = 0;
int timer = 0;

/*Timer Handler*/
void keyboarddddd(){
	if(!(timer++%18)){
		seconds++;
	}
	//sPrintf("t:%d\n",timer);
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

