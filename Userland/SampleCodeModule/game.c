#include "lib.h"
#include "shell.h"
#include "int80.h"
#include "game.h"
#include "sound.h"

typedef struct{
	char name[24];
	void * instp;
}packash;

typedef struct{
	int row;
	int col;	
}pointAux;

int random_seed=1;

void game_input(){
	print("Start GameInput Process\n");
	void * inputQ = 0;
	while(inputQ == 0){
		syscaller(18, 0, "gameinputq", 0, &inputQ); //syscall get gameinputq
	}
	print("GET: gameInput Q\n");
	while(1){
		char auxer = getChar();
		//putChar(auxer);
		if(auxer != 0){ 
			switch(auxer){
				case 'a':
				syscaller(20, 'a', &inputQ, 0, 0);
				break;
				case 'd':
				syscaller(20, 'd', &inputQ, 0, 0);
				break;
				case '\n':
				case '\b':
					syscaller(20,auxer, &inputQ,0, 0);		//syscall send auxer to gameinputq		
				} 
				if(auxer == '\b'){
					break;
				}   
			}	
		}
		return;
	}
	void game_sound(){
		print("Start GameAudio Process\n");
		void* soundQ;
		char msg = 0;

	syscaller(17,0, "gameaudioq",0, &soundQ);//syscall start queue named gameaudioq
	print("CREATE: gameaudio Q\n");
	while(1){		
		while(msg == 0){
			syscaller(21,0, &soundQ,0, &msg); //syscall get message from soundQ
		}
		putChar(msg);

		switch(msg){
			case 'b':
				//syscall beep
			break;
			case 'n':
				//syscall boop
			break;
			case 'm':
			playSongNoStop(2);
			break;
			case 'p':
			syscaller(8,0,0,0,0);
			break;					   
		} 
		msg = 0;
	}

	return;
}

int maxrand(int seed,int max){
	random_seed = random_seed+seed * 1103515245 +12345;
	return (unsigned int)(random_seed / 65536) % (max+1); 
}

int game_render(){
	print("Start GameRender Process\n");
	void * inputQ;
	syscaller(17,0, "gameinputq",0, &inputQ); //syscall start queue gameinputq
	void * soundQ = 0;
	while(soundQ == 0){
		syscaller(18,0, "gameaudioq",0, &soundQ);//syscall get queue named gameaudioq
	}
	clear();
	long timeStart;
	syscaller(6,0,&timeStart,0,0);  // syscall que pide timeStart
	long timeNow;

	syscaller(20, 'm', &soundQ, 0, 0);		//syscall send "start music (m)" to gameaudioq 

	int random;

	int pos_player = 2;
	int prev_pos = 0;
	int puntaje = 0;
	char input;
	int x_x = 0;

	int auxI;
	int auxJ;

	point array[10];
	int present[10] = {0,0,0,0,0,0,0,0,0,0};
	int parr = 0;
	int tot = 0;
	char board[5][20];

	for (int a = 0; a < 20; a++){
		for (int b = 0; b < 5; b++){
			board[b][a] = 15;
		}
	}

	int counters=0;
	//1024x768x24bit
	//imprime las lineas 
	int i,j;
	point p1, p2;
	for(i=128; i<1024; i+=128){
		for(j=-1; j<2; j++){
			p1.x = i+j; p1.y = 0;
			p2.x = i+j; p2.y = 768;
			syscaller(22, 0, &p1, 0, &p2);
		}
	}

	point ppp;
	ppp.x = 128 * pos_player + 128 + 13;
	ppp.y = 658;
	syscaller(25, 100, &ppp, 0, 3);

	while(!x_x){

	//----------------------TIME----------------------------------

		//syscaller(6,0,&timeNow,0,0); //syscall para pedir timeNow
		if(counters>25){
			/*int j= 19;
			for (; j >-1 ; j--)
			{
				int i= 0;
				for (; i<5; i++)
				{
					if(j==0){
						board[i][j] = 15;
					}
					else if(j==19 && board[i][j] == 'O' && board[i][j-1] == 'V'){
						x_x = 1;
					}
					else{
						board[i][j] = board[i][j-1];
					}
				}
			}
			
			board[pos_player][19] = 'O';
			*/
			


			random = maxrand(pos_player+1, 9);
			if(random < 6){
				
				if(tot<10){
					point pp;
					pp.x = 128 * random + 128 + 38;
					pp.y = 10;
					array[parr%10] = pp;
					present[parr%10] = 1;
					syscaller(16, 50, &array[parr%10], 50, 1); 
					parr++;
					tot++;
					//board[random][0] = 'V';

				}
			}
			puntaje++;
			counters = 0;

		}else{
			counters++;
		}
		int k;
		for(k=0;k<10;k++){
			if(present[k]){
				if(array[k].y>672){
					syscaller(16,50, &array[k], 60, 2); // borra
					present[k] = 0;
					tot--;
				} else {
					array[k].y+=3;
					syscaller(16, 50, &array[k], 50, 1);
					if(array[k].y > 658 && (array[k].x - 128 - 38) / 128 == pos_player)
						x_x = 1;
				}
		}
	}

	//----------------------INPUT---------------------------------

		//pos_player = (pos_player + 1) % 5;	 //obfuscatedCode9.31

		syscaller(21,0,&inputQ,0, &input); //getinput(): syscall get message from inputQ
		if(input != 0){
			if(input == 'a'){	
				prev_pos = pos_player;	   
				pos_player = (pos_player + 5) % 6;	 //obfuscatedCode9.31
			}
			else if(input == 'd'){
				prev_pos = pos_player;
				pos_player = (pos_player + 931) % 6;
				syscaller(20, 'd' , &soundQ, 0, 0);
			}
			else if(input == '\b'){
				syscaller(20, 'p' , &soundQ, 0, 0);	 //syscall send "stop music (p)" to gameaudioq 
				x_x=1;									 //no morimo'
			}
	
			ppp.x = 128 * pos_player + 128 + 13;
			ppp.y = 658;
			syscaller(25, 100, &ppp, 0, 3);

			ppp.x = 128 * prev_pos + 128 + 13;
			ppp.y = 658;
			syscaller(25, 100, &ppp, 0, 2);
			input = 0;
		}

		

	//----------------------RENDER---------------------------------

		// syscaller(3,0,0,0,0);	   //clearScreen   
		/*pointAux * auxPoint, * auxPoint2;

		auxPoint->col = 20; 
		auxPoint->row = 20;


		for (int j = 2; j < 22; j++)
		{ 
			auxPoint2->row = j;
			for (int i = 30; i < 41; i++)
			{
				auxPoint2->col = i;

				if(i%2 == 0){   
					syscaller(24, '|', auxPoint2, 0, 0);
				}
				else{
					auxI = (i - 30)/2;
					auxJ = j - 2;
					syscaller(24,board[auxI][auxJ],auxPoint2,0,0);
				}
			}
		}*/
	//----------------------GUIDO----------------------------------

	}
	syscaller(8,0,0,0,0);
	clear();
	syscaller(20, 'p', &soundQ, 0, 0);	  //syscall send "stop music (p)" to gameaudioq 
	print("Su puntaje es:");
	write(1, &puntaje, 0);
	print("\nPresione enter para salir\n");
	print("Presione R para reintentar\n");
	char inputChar = 's';
	while((inputChar = getChar()) == 0);
	if(inputChar == 'r')
		return 1;
	else
		return 0;

}

packash * auxPackInput;
packash * auxPackSound; 



void game(){
	syscaller(3,0,0,0,0);
	syscaller(5,1,0,0,0);
	// create process with this function: game_input();
	strcpy(auxPackInput->name,"gameInput",strlen("gameInput"));
	auxPackInput->instp = game_input;
	int * pidInput;
	syscaller(12,0,auxPackInput,1,&pidInput);

	// create process with this function: game_sound();
	strcpy(auxPackSound->name,"gameSound",strlen("gameSound"));
	auxPackSound->instp = game_sound;
	int * pidSound;
	syscaller(12,0,auxPackSound,1,&pidSound);
	while(game_render());
	clear();
	syscaller(13,0,0,pidInput,0);
	syscaller(13,0,0,pidSound,0);
	return;
}  
