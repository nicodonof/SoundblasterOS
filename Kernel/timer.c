
int seconds = 0;
int timer = 0;

void keyboarddddd(){
	if(!(timer++%18)){
		seconds++;
		vPrintDec(seconds);
	}
	changeSelector();
}

void sleep(int time){
	int aux = seconds;
	while(aux+time>seconds);
}