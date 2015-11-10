#include "shell.h"
#include <stdint.h>
#include "sound.h"

static uint8_t * const memory = (uint8_t*)0x5000F9;



extern int quitF;
extern int auxer;

void beep(){
    char noteB = 'l';
        //int auxFreq = 0x1234dd / 440;// 44100
        //write(1,"BEEP !\n",7);
        //syscaller(4,auxFreq,0,1/*time*/,0);//en size va el time en secs(?))
    syscaller(9,noteB,0,1,0);
    sleep(2);
    syscaller(8,0,0,0,0);
}

void boop(){
    char noteE = 'g';
        //int auxFreq = 0x1234dd / 440;// 44100
        //write(1,"BOOP !\n",7);
        //syscaller(4,auxFreq,0,1/*time*/,0);//en size va el time en secs(?))
    syscaller(9,noteE,0,1,0);
    sleep(2);
    syscaller(8,0,0,0,0);
}

void itunes(){
    clear();
    write(1,"Itunes Revolutionary musicPlayer!\nMusic available (press the number to play):\n",78);
    write(1,"    1. Ode To Joy\n", 18);
    write(1,"    2. Tetris Theme\n", 21);
    write(1,"    3. Mario Theme\n", 20);

    do{
        auxer = getChar();
    } while (auxer != '1' && auxer != '2' && auxer != '3' && auxer != '4');
    clear();
    syscaller(5,1,0,0,0);
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

    write(1,clear,strlen(clear));
    write(1,quit,strlen(quit));
    write(1,shutdown,strlen(shutdown));
    write(1,beep,strlen(beep));
    write(1,boop,strlen(boop));
    write(1,itunes,strlen(itunes));
    write(1,piano,strlen(piano));
    write(1,help,strlen(help));
}

void piano(){
    clear();
    write(1,"Welcome to the Piano ! To exit press the enter key.\n",52);
    syscaller(5,1,0,0,0);
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

void quit(){
      //VIDEO
    clearAll();
    
    for(int i = 0; i<6;i++)
        write(1,"                                                                                  ",80);

    printOsLogo();

    for(int i = 0; i<3;i++)
        write(1,"                                                                                  ",80);

    write(1,"                       You can turn off the computer now.                         ",80);

    for(int i = 0; i<5;i++)
        write(1,"                                                                                  ",80);


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