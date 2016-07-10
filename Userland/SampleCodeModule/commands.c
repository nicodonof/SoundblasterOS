#include "shell.h"
#include <stdint.h>
#include "sound.h"
#include "syscall.h"

static uint8_t * const memory = (uint8_t*)0x5000F9;



extern int quitF;
extern int auxer;

/*Boop*/
void beep(){
    char noteB = 'l';
        
    syscaller(PLAY_SOUND_ONLY,noteB,0,1,0);
    sleep(2);
    syscaller(STOP_SOUND,0,0,0,0);
}

/*Beep*/
void boop(){
    char noteE = 'g';
        
    syscaller(PLAY_SOUND_ONLY,noteE,0,1,0);
    sleep(2);
    syscaller(STOP_SOUND,0,0,0,0);
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
    syscaller(BOOL_KEY,1,0,0,0);
    do{
        auxer = getChar();
    } while (auxer != '1' && auxer != '2' && auxer != '3' && auxer != '4' && auxer != '\n');
    clear();
    if(auxer == '\n'){
        syscaller(BOOL_KEY,0,0,0,0);
        return;
    }
    syscaller(BOOL_KEY,1,0,2,0);
        playSong(auxer - '1');
    syscaller(BOOL_KEY,0,0,0,0);
    clear();
}

void ps(){
    syscaller(LIST_PROCESS,0,0,1,0);
}

void pItunes(){
    playSongNoStop(2);
}

void clear(){
     syscaller(CLEAR,0,0,0,0);
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
    char *openedQueues    = "openedqueues     Shows the opened message queues\n";
    char *bg       = "bg [command] [parameters]     Runs the command with parameters in background\n";
    char *help     = "help      Shows this message.. duh.\n";

    print(clear);
    print(quit);
    print(shutdown);
    print(beep);
    print(boop);
    print(itunes);
    print(piano);
    print(openedQueues);
    print(bg);
    print(help);
}

/*Activa el piano*/
void piano(){
    clear();
    print("Welcome to the Piano ! To exit press the enter key.\n");
    syscaller(BOOL_KEY,1,0,1,0);
    do{
        auxer = getChar();
        if(auxer != 0 && isValidNote(auxer))
            syscaller(PIANO,auxer,0,1,0);
        if('1' <= auxer && auxer <= '7')
            syscaller(CHANGE_OCTAVE,auxer,0,0,0);
    } while (auxer != '\n');
    syscaller(BOOL_KEY,0,0,0,0);
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

    syscaller(PLAY_SOUND_ONLY,'l',0,1,0);
    sleep(2);
    syscaller(STOP_SOUND,0,0,0,0);
    syscaller(PLAY_SOUND_ONLY,'j',0,1,0);
    sleep(2);
    syscaller(STOP_SOUND,0,0,0,0);
    syscaller(PLAY_SOUND_ONLY,'g',0,1,0);
    sleep(5);
    syscaller(STOP_SOUND,0,0,0,0);

    //Enter the void
    quitF = 1;
}

void printAllOpenedQueues(){
    char* queues[100];
    int i = 0;
    print("\n");
    print("All opened queues:\n");
    syscaller(26,0,0,0,queues);
    while(queues[i] != 0){
        print(queues[i]);
        print("\n");
        i++;
    }
}