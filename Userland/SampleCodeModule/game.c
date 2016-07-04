#include "lib.h"
#include "shell.h"
#include "int80.h"
 
/*
void game_input(){
	void * msgInputQ;
	//while(msgQ == 0){
		//syscall getQueue gameinputq
	//}

    while(1){
        char auxer = getChar();
        if(auxer != 0){ 
            switch(auxer){
                case 'a':
                break;
                case 'd':
                break;
                case '\n':
                break;
                case '\b':
                break;
                //syscall send auxer to gameinputq                               
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
	char* msg;
	//syscall start queue named gameaudioq
	while(1){
		while(msg == 0){
			//syscall get message from soundQ
		}
		switch(auxer){
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
            	//syscall send auxer to gameinputq
            	break;                            
        } 
		msg = 0;
	}
	
    return;
}

void game_render(){
	void * inputQ;
		//syscall start queue named gameinputq
	void * soundQ;
	while(soundQ == 0){
		//syscall getQueue gamesoundq
	}
    print("Presione ENTER para empezar el juego\n");
    print("Presione Q para salir\n");
   
    long timeStart;
    syscaller(6,0,&timeStart,0,0);  // syscall que pide timeStart
    long timeNow;


    startMusic();
    
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

        input = getInput();
        if(input == 'a'){           
            pos_player = (pos_player + 404) % 5;     //obfuscatedCode9.31
        }
        else if(input == 'd'){
            pos_player = (pos_player + 931) % 5;
        }
        else if(input == '\b'){
            stopDaMusic();
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

void game(){
    print("Game not implemented yet...");
    // create process with this function: game_sound();
    strcpy(auxPack->name,"gameSound",strlen("gameSound"));
    auxPack->instp = game_sound;
    int pid;
    syscaller(12,0,auxPack,1,&pid);

    strcpy(auxPack->name,"gameInput",strlen("gameInput"));
    auxPack->instp = game_input;
    int pid2;
    syscaller(12,0,auxPack,1,&pid);
    // create process with this function: game_input();
    game_render();
}  */