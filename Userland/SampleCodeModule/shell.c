#include "lib.h"
#include "shell.h"
#include "int80.h"
static uint8_t * const songsDirections[3] = {ODETOJOY, TETRIS, MARIO};
static uint8_t * const memory = (uint8_t*)0x5000F9;
char auxer = 0;
int time = 0;
int quitF = 0;

void shell(){
    osInit();
    
    while(!quitF){
        write(1, "SoundblasterOS> ", 16);
        int i = 0;
        char buffer[75];
        auxer = 0;
        do{
            auxer = getChar();
            if(auxer != 0){
                if(auxer == '\b'){
                    if(i>0)
                        i--;
                    else
                        beep();
                } else
                    buffer[i++] = auxer;
            }         
        } while (auxer != '\n');
        buffer[i-1] = 0;
        parser(buffer,1);
    }
}

void printOsName(){
    putChar('<');
    write(1,"================================ SoundblasterOS ================================",78);
    putChar('>');
}

void parser(char * s, int size){
    if(*s != 'c' && *s != 'q' && *s != 'i' && *s != 'h' && *s != 'b' && *s != 'p' && *s != 's'){
    	write(1,"No se reconoce el comando. Intente nuevamente.\n",47);
        return;
    }
    
    str0(s);
	
    switch(*s){
        case 'c':
            if(strcmp(s,"clear")){
                clear();
                return;
            }
        break;
        case 'q':
            if(strcmp(s,"quit")){
                quit();
                return;
            }
        break;
        case 's':
            if(strcmp(s,"shutdown")){
                quit();
                return;
            }
        break;
        case 'i':
            if(strcmp(s,"itunes")){
                itunes();
                return;
            }
        break;
        case 'h':
            if(strcmp(s,"help")){
                help();
                return;
            }
        break;
        case 'b':
            if(strcmp(s,"beep")){
                beep();
                return;
            }else if(strcmp(s,"boop")){
                boop();
                return;
            }
        break;
        case 'p':
            if(strcmp(s,"piano")){
                piano();
                return;
            }
        break;
    }
    write(1,"No se reconoce el comando. Intente nuevamente.\n",47);
    return ;
}

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
    } while (auxer != '1' && auxer != '2' && auxer != '3');
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

void clearAll(){
    syscaller(3,0,0,0,0);
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


int isValidNote(char key){
    return (key == 'd' || key == 'f' ||key == 'g' ||key == 'h' ||key == 'j' ||key == 'k' || key == 'l' 
            || key == 'r' || key == 't' || key == 'u' ||key == 'i' ||key == 'o');
}


void piano(){
    clear();
    write(1,"Welcome to the Piano ! To exit press the enter key.\n",52);
    syscaller(5,1,0,0,0);
    do{
        auxer = getChar();
        if(auxer != 0 && isValidNote(auxer)){
            syscaller(4,auxer,0,1,0);
        }
    } while (auxer != '\n');
    syscaller(5,0,0,0,0);
    clear();    
}

int getSeconds(){
    time=0;
    syscaller(6,0,0,0,&time);
    return time;
}



int getRealTime(char c){
    if(c=='0')
        return 1;
    if(c=='5')
        return 5;
    return (c-'0')*2;
}


void playSong(int song){
    auxer = 0;
    while(auxer != '\n'){
        int i = 0;
        while(songsDirections[song][i]!=0 && auxer != '\n'){
            auxer = getChar();
            playNote(songsDirections[song][i], songsDirections[song][i+1], getRealTime(songsDirections[song][i+2]), getRealTime(songsDirections[song][i+3]));
            i+=4;
        }
    }
}

void playNote(char note, char octave, int length, int delay){
   syscaller(7,note,0, octave,0);
   sleep(length);
   syscaller(8,0,0,0,0);
   sleep(delay);
}
void sleep(int time){
    int taux = getSeconds();
    while(taux + time > getSeconds());
}

void printOsLogo(){
    write(1,"     _____                       _ ____  _           _             ____   _____   ",80);
    write(1,"    / ____|                     | |  _ \\| |         | |           / __ \\ / ____|  ",80);
    write(1,"   | (___   ___  _   _ _ __   __| | |_) | | __ _ ___| |_ ___ _ __| |  | | (___    ",80);
    write(1,"    \\___ \\ / _ \\| | | | '_ \\ / _` |  _ <| |/ _` / __| __/ _ \\ '__| |  | |\\___ \\   ",80);
    write(1,"    ____) | (_) | |_| | | | | (_| | |_) | | (_| \\__ \\ ||  __/ |  | |__| |____) |  ",80);
    write(1,"   |_____/ \\___/ \\__,_|_| |_|\\__,_|____/|_|\\__,_|___/\\__\\___|_|   \\____/|_____/   ",80);
    write(1,"                                                                                  ",80);
}

void osInit(){

    //VIDEO
    for(int i = 0; i<9;i++)
        write(1,"                                                                                  ",80);

    printOsLogo();

    for(int i = 0; i<9;i++)
        write(1,"                                                                                  ",80);
    
    //AUDIO
    syscaller(9,'k',0,1,0);
    sleep(2);
    syscaller(8,0,0,0,0);

    syscaller(9,'g',0,1,0);
    sleep(2);
    syscaller(8,0,0,0,0);

    syscaller(9,'l',0,1,0);
    sleep(5);
    syscaller(8,0,0,0,0);

    //CLEAN
    sleep(5);
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
/*

void playSong2(){
    
    /*char song[56] = {E,B4,C,D,C,B4,
                     A4,A4,C,E,D,C,
                     B4,C,D,E,
                     C,A4,A4,A4,B4,C,
                     D,F,A,G,F,
                     E,C,E,D,C,
                     B4,B4,C,D,E,
                     C,A4,A4,
                     E,C,D,B4,C,A4,
                     GS,B4,E,C,D,B4,
                     C,E,A,GS
                 };
    //char song[56] = {   E,L,A,C,A,L,J,J,A,E,C,A,L,A,C,E,A,J,J,J,L,A,C,F,J,H,F,E,A,E,C,A,L,L,A,C,E,A,J,J,E,A,C,L,A,J,I,L,E,A,C,L,A,E,J,I

    
                     
    char time[56] = {   4,2,2,4 ,2,2, 4,2,2, 4,2,2,8,4,4,
                        4,4,4,2,2,2,2,5,2,4,2,2,8,2,4,
                        2,2,4,2,2,4,4,4,4,4,8,8,8,8,8,
                        8,8,4,4,8,8,8,8,4,8,8
                };
    char pause[56] = {  4,4,4,4,4,4,4,4,4,4,4,4,1,4,4,
                        4,4,4,1,1,4,4,4,4,4,4,4,1,4,4,
                        4,4,4,4,4,4,4,4,4,8,4,4,4,4,4,
                        4,4,4,8,4,4,4,4,4,4,12
                };
    int i = 0;
    while(1){
        for (i=0;i<56;i++){
     //       syscaller(7,keyToNotefreq(song[i]),0,1,0);
            sleep(time[i]);
            syscaller(8,0,0,0,0);
            sleep(pause[i]/2);
        }
    }
}*/


