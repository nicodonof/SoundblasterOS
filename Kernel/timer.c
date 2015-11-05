int pianoModer();

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
	int i = 0;
	while(aux+time>seconds){
		if(!(i%1000000)){
	/*		vPrintDec(aux+time);
			vPrint(":");
			vPrintDec(seconds);
			vPrintChar(' ');*/
		}
		i++;
	}
	return;
}