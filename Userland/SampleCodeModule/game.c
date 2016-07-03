// #include "lib.h"
// #include "shell.h"
// #include "int80.h"


// void game(){
//     print("Game not implemented yet...");
//     return;
//     //------------------------------
//     //messageQueue input y sound
//     if(!fork()){
//         game_render();
//         }
//     else if(!fork()){
//         game_sound();
//     }
//     else{
//         game_input();
//     }
// }   

// void game_input(){

//     while(1){
//         auxer = getChar();
//         if(auxer != 0){ 
//             switch(auxer){
//                 case 'a':
//                 case 'd':
//                 case '\n':
//                 case '\b':  
//                 //send auxer mqueue render                               
//             } 
//             if(auxer='\b'){
//                 break;
//             }          
//         } 
//     }    
//     return;
// }

// void game_sound(){
//     return;
// }

// void game_render(){
//     printf("Presione ENTER para empezar el juego\n");
//     printf("Presione Q para salir\n");
   
//     long timeStart;
//     syscaller(6,0,&timeStart,0,0);  // syscall que pide timeStart
//     long timeNow;


//     startMusic();
    
//     int random;
 
//     int pos_player = 0;
//     int puntaje = 0;
//     char input;
//     int x_x = 0;

//     char board[5][20]; 


//     while(!x_x){
       
//     //----------------------TIME----------------------------------

//         syscaller(6,0,&timeNow,0,0); //syscall para pedir timeNow
//         if((timeNow - timeStart) >9){
//             timeStart = timeNow;
            
//             for (int i = 0; i < 5; i++)
//             {
//                 for (int j = 20; i > 0; i--)
//                 {
//                     if(j==0){
//                         board[i][j] = ' ';
//                     }
//                     else if(j==20 && board[i][j] == 'O' && board[i][j-1] == 'V'){
//                         x_x = 1;
//                     }
//                     else{
//                         board[i][j] = board[i][j-1];
//                     }
//                 }
//             }

//             syscaller(16,0,&random,0,0);    //poneeeeele que devuelve entre 0 y 4
//             board[random%5][0] = 'V';

//         }

//     //----------------------INPUT---------------------------------

//         input = getInput();
//         if(input == 'a'){           
//             pos_player = (pos_player + 404) % 5;     //obfuscatedCode9.31
//         }
//         else if(input == 'd'){
//             pos_player = (pos_player + 931) % 5;
//         }
//         else if(input == '\b'){
//             stopDaMusic();
//             x_x=1;                                     //no morimo'
//         }

//     //----------------------RENDER---------------------------------
       
//         // syscaller(3,0,0,0,0);       //clearScreen   
//         // printGame();
        
//         printBoard(board);
    
//     //----------------------GUIDO----------------------------------

//     }
//     printf("Su puntaje es: %d\n", puntaje);
//     printf("Presione enter para salir\n");
//     printf("Presione R para reintentar\n");


//     return;
// }

//     