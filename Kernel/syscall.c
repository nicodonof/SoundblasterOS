static void syscallHandler(int index,int fd, char c, char * desc){
	switch(index){
		case 1:  //read
			desc = getKey();
			break;
		case 2: //write
			vPrintChar(c);
			break;
	}
	_EOI();
} 