#include "lib.h"
#include "shell.h"
#include "int80.h"
#include "game.h"

typedef struct{
    char name[24];
    void * instp;
}packash;

typedef struct{
    int row;
    int col;    
}pointAux;

void game_input(){
    print("Start GameInput Process\n");
	void * inputQ;
	while(inputQ == 0){
		syscaller(18, 0, "gameinputq", 0, inputQ); //syscall get gameinputq
	}

    while(1){
        char auxer = getChar();
        if(auxer != 0){ 
            switch(auxer){
                case 'a':
                case 'd':
                case '\n':
                case '\b':
                	syscaller(20,inputQ, &auxer,0, 0);		//syscall send auxer to gameinputq                               
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
	char* msg;
	syscaller(17,0, "gameaudioq",0, &soundQ);//syscall start queue named gameaudioq
	while(1){
		while(msg == 0){
			syscaller(21,0, &soundQ,0, &msg); //syscall get message from soundQ
		}
		switch(*msg){
            case 'b':
            	//syscall beep
            	break;
            case 'n':
            	//syscall boop
            	break;
            case 'm':
            	//syscall play song
            	break;
            case 'p':  
            	//syscall pause song
            	break;                            
        } 
		msg = 0;
	}
	
    return;
}

void game_render(){
    print("Start GameRender Process\n");
	void * inputQ;
	syscaller(17,0, "gameinputq",0, inputQ); //syscall start queue gameinputq
	void * soundQ;
	while(soundQ == 0){
		syscaller(18,0, "gameaudioq",0, soundQ);//syscall get queue named gameaudioq
	}
    print("Presione ENTER para empezar el juego\n");
    print("Presione Q para salir\n");
    long timeStart;
    syscaller(6,0,&timeStart,0,0);  // syscall que pide timeStart
    long timeNow;


    syscaller(20, soundQ, "m", 0, 0);		//syscall send "start music (m)" to gameaudioq 
    
    int random;
 
    int pos_player = 0;
    int puntaje = 0;
    char input;
    int x_x = 0;

    char board[5][20]; 


    while(!x_x){
       
    //----------------------TIME----------------------------------

        syscaller(6,0,&timeNow,0,0); //syscall para pedir timeNow
        if((timeNow - timeStart) >9){
            timeStart = timeNow;
            
            for (int i = 0; i < 5; i++)
            {
                for (int j = 20; i > 0; i--)
                {
                    if(j==0){
                        board[i][j] = ' ';
                    }
                    else if(j==20 && board[i][j] == 'O' && board[i][j-1] == 'V'){
                        x_x = 1;
                    }
                    else{
                        board[i][j] = board[i][j-1];
                    }
                }
            }

            syscaller(16,0,&random,0,0);    //poneeeeele que devuelve entre 0 y 4
            board[random%5][0] = 'V';

        }

    //----------------------INPUT---------------------------------

        syscaller(21,inputQ, 0,0, &input); //getinput(): syscall get message from inputQ
        if(input == 'a'){           
            pos_player = (pos_player + 404) % 5;     //obfuscatedCode9.31
        }
        else if(input == 'd'){
            pos_player = (pos_player + 931) % 5;
        }
        else if(input == '\b'){
            syscaller(20, soundQ, "p", 0, 0);		//syscall send "stop music (p)" to gameaudioq 
            x_x=1;                                     //no morimo'
        }

    //----------------------RENDER---------------------------------
       
        // syscaller(3,0,0,0,0);       //clearScreen   
        // printGame();
        
        printBoard(board);
    
    //----------------------GUIDO----------------------------------

    }
    print("Su puntaje es: %d\n", puntaje);
    print("Presione enter para salir\n");
    print("Presione R para reintentar\n");


    return;
}

packash * auxPackInput;
packash * auxPackSound; 
void game(){
    
    print("Game not implemented yet...\n");

    // create process with this function: game_input();
    print("Creating gameinput process\n");
    strcpy(auxPackInput->name,"gameInput",strlen("gameInput"));
    auxPackInput->instp = game_input;
    print("name AuxPackInput: ");
    print(auxPackInput->name);
    print("\n");
    int pid2;
    print("before gameinput syscall\n");
    syscaller(12,0,auxPackInput,1,&pid2);
    print("after gameinput syscall\n");
    
    // create process with this function: game_sound();
    print("Creating gamesound process\n");
    strcpy(auxPackSound->name,"gameSound",strlen("gameSound"));
    auxPackSound->instp = game_sound;
    int pid;
    syscaller(12,0,auxPackSound,1,&pid);
    
    game_render();
}  

/*    #include "game.h"
    #include "lib.h"
    #include "shell.h"
    #include "int80.h"


typedef struct{
    int row;
    int col;    
}pointAux;*/

    void printBoard(){//char board[][]){
    	syscaller(3,0,0,0,0);
        pointAux * auxPoint, * auxPoint2;

        auxPoint->col = 20; 
        auxPoint->row = 20;

        

        for (int i = 0; i < 16; i++)
        {
             auxPoint2->col = 30 + i;
            
            
            for (int j = 2; j < 22; j++)
            { 
                auxPoint2->row = j;
                syscaller(24, '|', auxPoint2, 0, 0);
            
            }

        }
           

        return;

  //       point * p1 ,* p2, * p3;
  //       p1->x = 700; p1->y = 0; 
  //       p2->x = 700; p2->y = 600;
  //       p3->x = 700; p3->y = 0; 
  //       syscaller(22, 0, p3, "yellow", p2);
  //       p2->x = 100; p2->y = 600; // Imprime las lineas de los costados aunq sean mas feas que teofilo.
  //       p3->x = 100; p3->y = 0; 
  //       syscaller(22, 0, p3, "yellow", p2);

    }
