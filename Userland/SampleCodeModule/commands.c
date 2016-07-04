#include "shell.h"
#include <stdint.h>
#include "sound.h"

static uint8_t * const memory = (uint8_t*)0x5000F9;



extern int quitF;
extern int auxer;

/*Boop*/
void beep(){
    char noteB = 'l';
        
    syscaller(9,noteB,0,1,0);
    sleep(2);
    syscaller(8,0,0,0,0);
}

/*Beep*/
void boop(){
    char noteE = 'g';
        
    syscaller(9,noteE,0,1,0);
    sleep(2);
    syscaller(8,0,0,0,0);
}

/*Activa el programa para escuchar canciones*/
void itunes(){
    char * st1 = "Itunes Revolutionary musicPlayer!\nMusic available (press the number to play):\n";
    char * st2 = "    1. Ode To Joy\n";
    char * st3 = "    2. Tetris Theme\n";
    char * st4 = "    3. Mario Theme\n";
    char * st5 = "Or press enter to exit.\n";
    clear();
    print(st1);
    print(st2);
    print(st3);
    print(st4);
    print(st5);
    syscaller(5,1,0,0,0);
    do{
        auxer = getChar();
    } while (auxer != '1' && auxer != '2' && auxer != '3' && auxer != '4' && auxer != '\n');
    clear();
    if(auxer == '\n'){
        syscaller(5,0,0,0,0);
        return;
    }
    syscaller(5,1,0,2,0);
        playSong(auxer - '1');
    syscaller(5,0,0,0,0);
    clear();
}

void clear(){
     syscaller(3,0,0,0,0);
     printOsName();
}


void help(){
    char *clear    = "clear     Clears the terminal screen\n";
    char *quit     = "quit      Quits the OS\n";
    char *shutdown = "shutdown  Quits the OS\n";
    char *beep     = "beep      Makes a beep sound\n";
    char *boop     = "boop      Makes a boop sound\n";
    char *itunes   = "itunes    Itunes\n";
    char *piano    = "piano     Magic at the tip of your fingers\n";
    char *help     = "help      Shows this message.. duh.\n";

    print(clear);
    print(quit);
    print(shutdown);
    print(beep);
    print(boop);
    print(itunes);
    print(piano);
    print(help);
}

/*Activa el piano*/
void piano(){
    clear();
    print("Welcome to the Piano ! To exit press the enter key.\n");
    syscaller(5,1,0,1,0);
    do{
        auxer = getChar();
        if(auxer != 0 && isValidNote(auxer))
            syscaller(4,auxer,0,1,0);
        if('1' <= auxer && auxer <= '7')
            syscaller(10,auxer,0,0,0);
    } while (auxer != '\n');
    syscaller(5,0,0,0,0);
    clear();    
}

/*Imprime cosas y hace que retorne shell/main, a kernel, que tambien retorna y haltea en el loader.asm*/
void quit(){
      //VIDEO
    clearAll();
    
    for(int i = 0; i<6;i++)
        print("                                                                                ");

    printOsLogo();

    for(int i = 0; i<3;i++)
        print("                                                                                ");

    print("                      You can turn off the computer now.                        ");

    for(int i = 0; i<5;i++)
        print("                                                                                ");


    //AUDIO

    syscaller(9,'l',0,1,0);
    sleep(2);
    syscaller(8,0,0,0,0);
    syscaller(9,'j',0,1,0);
    sleep(2);
    syscaller(8,0,0,0,0);
    syscaller(9,'g',0,1,0);
    sleep(5);
    syscaller(8,0,0,0,0);

    //Enter the void
    quitF = 1;
}