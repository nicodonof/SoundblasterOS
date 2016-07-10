#include "lib.h"
#include "shell.h"
#include "int80.h"
#include "game.h"
#include "sound.h"
#include "syscall.h"

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
	void * inputQ = 0;
	while(inputQ == 0){
		syscaller(GET_MSGQ, 0, "gameinputq", 0, &inputQ); //syscall get gameinputq
	}
	while(1){
		char auxer = getChar();
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
					break;		
			} 
			if(auxer == '\b'){
				break;
			}   
		}	
	}
	return;
}
	void game_sound(){
		void* soundQ;
		char msg = 0;

	syscaller(OPEN_MSGQ,0, "gameaudioq",0, &soundQ);//syscall start queue named gameaudioq
	while(1){		
		while(msg == 0){
			syscaller(RECEIVE_MSG_FROM_Q ,0, &soundQ,0, &msg); //syscall get message from soundQ
		}
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
			syscaller(STOP_SOUND,0,0,0,0);
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
	void * inputQ;
	syscaller(OPEN_MSGQ,0, "gameinputq",0, &inputQ); //syscall start queue gameinputq
	void * soundQ = 0;
	while(soundQ == 0){
		syscaller(GET_MSGQ,0, "gameaudioq",0, &soundQ);//syscall get queue named gameaudioq
	}
	clear();
	long timeStart;
	syscaller(GET_TIMER,0,&timeStart,0,0);  // syscall que pide timeStart
	long timeNow;

	syscaller(SEND_MSG_TO_Q, 'm', &soundQ, 0, 0);		//syscall send "start music (m)" to gameaudioq 

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
	//imprime las lineas 
	int i,j;
	point p1, p2;
	for(i=128; i<1024; i+=128){
		for(j=-1; j<2; j++){
			p1.x = i+j; p1.y = 0;
			p2.x = i+j; p2.y = 768;
			syscaller(DRAW_LINE, 0, &p1, 0, &p2);
		}
	}

	point ppp;
	ppp.x = 128 * pos_player + 128 + 13;
	ppp.y = 658;
	syscaller(DRAW_TRIANG, 100, &ppp, 0, 3);

	while(!x_x){

	//----------------------TIME----------------------------------

		if(counters>25){
			random = maxrand(pos_player+1, 9);
			if(random < 6){
				
				if(tot<10){
					point pp;
					pp.x = 128 * random + 128 + 38;
					pp.y = 10;
					array[parr%10] = pp;
					present[parr%10] = 1;
					syscaller(DRAW_REC, 50, &array[parr%10], 50, 1); 
					parr++;
					tot++;
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
					syscaller(DRAW_REC,50, &array[k], 60, 2); // borra
					present[k] = 0;
					tot--;
				} else {
					array[k].y+=3;
					syscaller(DRAW_REC, 50, &array[k], 50, 1);
					if(array[k].y > 658 && (array[k].x - 128 - 38) / 128 == pos_player)
						x_x = 1;
				}
			}
		}

	//----------------------INPUT---------------------------------


		syscaller(RECEIVE_MSG_FROM_Q,0,&inputQ,0, &input); //getinput(): syscall get message from inputQ
		if(input != 0){
			if(input == 'a'){	
				prev_pos = pos_player;	   
				pos_player = (pos_player + 5) % 6;	 //obfuscatedCode9.31
			}
			else if(input == 'd'){
				prev_pos = pos_player;
				pos_player = (pos_player + 931) % 6;
				syscaller(SEND_MSG_TO_Q, 'd' , &soundQ, 0, 0);
			}
			else if(input == '\b'){
				syscaller(SEND_MSG_TO_Q, 'p' , &soundQ, 0, 0);	 //syscall send "stop music (p)" to gameaudioq 
				x_x=1;									 //no morimo'
			}

			ppp.x = 128 * pos_player + 128 + 13;
			ppp.y = 658;
			syscaller(DRAW_TRIANG, 100, &ppp, 0, 3);

			ppp.x = 128 * prev_pos + 128 + 13;
			ppp.y = 658;
			syscaller(DRAW_TRIANG, 100, &ppp, 0, 2);
			input = 0;
		}

		

	//----------------------GUIDO----------------------------------

	}
	syscaller(STOP_SOUND,0,0,0,0);
	clear();
	syscaller(SEND_MSG_TO_Q, 'p', &soundQ, 0, 0);	  //syscall send "stop music (p)" to gameaudioq 
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
	syscaller(CLEAR,0,0,0,0);
	syscaller(BOOL_KEY,1,0,0,0);
	// create process with this function: game_input();
	strcpy(auxPackInput->name,"gameInput",strlen("gameInput"));
	auxPackInput->instp = game_input;
	int * pidInput;
	syscaller(CREATE_PROCESS,0,auxPackInput,1,&pidInput);

	// create process with this function: game_sound();
	strcpy(auxPackSound->name,"gameSound",strlen("gameSound"));
	auxPackSound->instp = game_sound;
	int * pidSound;
	syscaller(CREATE_PROCESS,0,auxPackSound,1,&pidSound);
	while(game_render());
	syscaller(CLEAR,0,0,0,0); 
	syscaller(END_PROCESS,0,0,pidInput,0); 
	syscaller(END_PROCESS,0,0,pidSound,0); 
	syscaller(BOOL_KEY,0,0,0,0); 
	return;
}  
