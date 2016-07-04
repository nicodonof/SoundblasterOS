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
                    syscaller(20,inputQ, &auxer,0, 0);      //syscall send auxer to gameinputq                               
                    break;
                    case 'd':
                    syscaller(20,inputQ, &auxer,0, 0);      //syscall send auxer to gameinputq                               
                    break;
                    case '\n':
                    syscaller(20,inputQ, &auxer,0, 0);      //syscall send auxer to gameinputq                              
                    break;
                    case '\b':
                	syscaller(20,inputQ, &auxer,0, 0);		//syscall send auxer to gameinputq                               
                }        
            } 
            if(auxer == '\b'){
                break;
            }   
        }    
        return;
    }

void game_sound(){
    print("Start GameAudio Process\n");
	void* soundQ;
	char msg = 0;
	syscaller(17,0, "gameaudioq",0, &soundQ);//syscall start queue named gameaudioq
    playSongNoStop(2);
    while(1){
		
        while(msg == 0){
			syscaller(21,0, &soundQ,0, &msg); //syscall get message from soundQ
		}
        playSongNoStop(2);
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
	syscaller(17,0, "gameinputq",0, &inputQ); //syscall start queue gameinputq
	void * soundQ = 0;
	while(soundQ == 0){
		syscaller(18,0, "gameaudioq",0, &soundQ);//syscall get queue named gameaudioq
	}

    long timeStart;
    syscaller(6,0,&timeStart,0,0);  // syscall que pide timeStart
    long timeNow;

    syscaller(20, 'm', &soundQ, 0, 0);		//syscall send "start music (m)" to gameaudioq 

    int random_seed;

    int pos_player = 2;
    int puntaje = 0;
    char input;
    int x_x = 0;

    int auxI;
    int auxJ;

    char board[5][20];

    for (int a = 0; a < 20; a++){
        for (int b = 0; b < 5; b++){
         board[b][a] = 15;
         }
    }

 int counters=0;

 while(!x_x){

    //----------------------TIME----------------------------------

        //syscaller(6,0,&timeNow,0,0); //syscall para pedir timeNow
    if(counters>50){
        int j= 19;
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

        random_seed= random_seed+random_seed * 1103515245 +1234;
        random_seed= (unsigned int)(random_seed / 65536) % (5); 
        board[random_seed][0] = 'V';
        counters = 0;

    }else{
        counters++;
    }

    //----------------------INPUT---------------------------------

        syscaller(21,0,&inputQ,0, &input); //getinput(): syscall get message from inputQ
        if(input == 'a'){           
            pos_player = (pos_player + 404) % 5;     //obfuscatedCode9.31
        }
        else if(input == 'd'){
            pos_player = (pos_player + 931) % 5;
        }
        else if(input == '\b'){
            syscaller(20, 'p' , &soundQ, 0, 0);		//syscall send "stop music (p)" to gameaudioq 
            x_x=1;                                     //no morimo'
        }

    //----------------------RENDER---------------------------------

        // syscaller(3,0,0,0,0);       //clearScreen   
        pointAux * auxPoint, * auxPoint2;

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
        }
    //----------------------GUIDO----------------------------------

    }
    syscaller(8,0,0,0,0);
    print("Su puntaje es: 35\n");
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

    // void printBoard(char ** board){
    // 	syscaller(3,0,0,0,0);
    //     pointAux * auxPoint, * auxPoint2;

    //     auxPoint->col = 20; 
    //     auxPoint->row = 20;


    //     for (int j = 2; j < 22; j++)
    //     { 
    //         auxPoint2->row = j;
    //         for (int i = 30; i < 41; i++)
    //         {
    //             auxPoint2->col = i;

    //             if(i%2 == 0){   
    //                 syscaller(24, '|', auxPoint2, 0, 0);
    //             }
    //             else{
    //                 syscaller(24,board[(i/2)-15][j-2],auxPoint2,0,0);
    //             }


    //        }

    //     }   


    //        return;
    //   }
  //       point * p1 ,* p2, * p3;
  //       p1->x = 700; p1->y = 0; 
  //       p2->x = 700; p2->y = 600;
  //       p3->x = 700; p3->y = 0; 
  //       syscaller(22, 0, p3, "yellow", p2);
  //       p2->x = 100; p2->y = 600; // Imprime las lineas de los costados aunq sean mas feas que teofilo.
  //       p3->x = 100; p3->y = 0; 
  //       syscaller(22, 0, p3, "yellow", p2);

