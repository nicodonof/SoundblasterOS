void syscallHandler(int index,int fd, char c, char * desc){
	_EOI();
	
	vPrintChar(*desc);
	
	switch(index){
		case 1:  //read
			desc = getKey();
			break;
		case 2: //write
			vPrintChar('6');
			vPrintChar(c);
			break;
		}
	
} 