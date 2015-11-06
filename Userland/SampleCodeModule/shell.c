#include "shell.h"
#include "lib.h"
#include "int80.h"

char auxer = 0;
int time = 0;

void shell(){
    
    printOsName();
    
    
    while(1){
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
    if(*s != 'c' && *s != 'q' && *s != 'i' && *s != 'h' && *s != 'b' && *s != 'p'){
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
                clear();
                return;
            }
        break;
        case 'a':
            if(strcmp(s,"itunes")){
                clear();
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
    int auxFreq = 44000;// 44100
    write(1,"BEEP !\n",7);
    syscaller(4,auxFreq,0,1/*time*/,0);//en size va el time en secs(?))
}

void clear(){
    syscaller(3,0,0,0,0);
    printOsName();
}

int strcmp(const char * str1, const char * str2){
    int i;
    for(i=0;str1[i] != 0;i++)
        if(str1[i] != str2[i])
            return 0;
    if(str2[i] != 0)
        return 0;
    return 1;
}



int strlen(const char * s){
    int n=0;
    while(*s++ != 0)
        n++;
    return n;
}

void str0(char * s){
    while(*s){
        if(*s == ' ')
            *s = 0;
        s++;
    }
}

void help(){
    char *clear  = "clear    Clears the terminal screen\n";
    char *quit   = "quit     Quits the OS\n";
    char *beep   = "beep     Makes a beep sound\n";
    char *itunes = "itunes   Itunes\n";
    char *piano  = "piano    Magic at the tip of your fingers\n";
    char *help   = "help     Shows this message.. duh.\n";

    write(1,clear,strlen(clear));
    write(1,quit,strlen(quit));
    write(1,beep,strlen(beep));
    write(1,itunes,strlen(itunes));
    write(1,piano,strlen(piano));
    write(1,help,strlen(help));
}

int notefreqs[7][12] = {
    {  16,  17,  18,  19,  20,  21,  23,  24,  26,  27,  29,  30},
    {  32,  34,  36,  38,  41,  43,  46,  49,  52,  55,  58,  61},
    {  65,  69,  73,  77,  82,  87,  92,  98,  104, 110, 116, 123},
    {  130, 138, 146, 155, 164, 174, 185, 196, 207, 220, 233, 247},
    {  261, 277, 293, 311, 329, 349, 369, 392, 415, 440, 466, 493}, // MEDIO
    {  523, 554, 587, 622, 659, 698, 739, 784, 830, 880, 932, 987},
    {  1046,1108,1174,1244,1318,1396,1479,1567,1661,1760,1864,1975}
};

/*
    DO D
    RE F
    MI G
    FA H
    SOL I
    LA J
    Si K
*/
int note[7] = { 26163, 29366, 32963, 34923, 39200, 44000, 49388};

int keyToNotefreq(char key){
    int keyToNoteTable[26] = {22000/*A (LA mas grave) */,0,0,26163 /* D (DO)*/,0,note[1] /* F (RE)*/,note[2] /* G (MI)*/, note[3] /* H (FA)*/,41530,
                              note[4] /* J (SOL)*/,note[5] /* K (LA)*/, note[6] /* L (SI)*/,0,0,1,1, 0,1,24694,1,1,0,0,0,1,0};
    return (0x1234dd / (keyToNoteTable[key - 'a'] / 100));
}

int isValidNote(char key){
    return (key == 's' || key == 'i' || key == 'a' || key == 'd' || key == 'f' ||key == 'g' ||key == 'h' ||key == 'j' ||key == 'k' || key == 'l');
}

static uint8_t * const memory = (uint8_t*)0x5000F9;

void piano(){
    clear();
    write(1,"Welcome to the Piano ! To exit press the enter key.\n",52);
    write(1,memory,strlen(memory));
    write(1,"1. Piano\n", 9);
    write(1,"2. Ode To Joy\n", 14);
    do{
        auxer = getChar();
    } while (auxer != '1' && auxer != '2');
    clear();
    syscaller(5,1,0,0,0);
    if(auxer == '2')
        playSong1();
    else{
        do{
            auxer = getChar();
            if(auxer != 0 && isValidNote(auxer)){
                syscaller(4,keyToNotefreq(auxer),0,1,0);
            }
        } while (auxer != '\n');
    }
    syscaller(5,0,0,0,0);
    clear();    
}

int getSeconds(){
    time=0;
    syscaller(6,0,0,0,&time);
    return time;
}

#define freq(a,b) (0x1234dd/notefreqs[a-'0'-1][b-'A'])

int getRealTime(char c){
    if(c=='0')
        return 1;
    if(c=='5')
        return 5;
    return (c-'0')*2;
}

void playSong1(){
    while(1){
        int i = 0;
        while(memory[i]!=0){
            syscaller(7,freq(memory[i+1], memory[i]) ,0,1,0);
            i+=2;
            sleep(getRealTime(memory[i++]));
            syscaller(8,0,0,0,0);
            sleep(getRealTime(memory[i++]));

        }
    }
}






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
                 };*/
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
}


void sleep(int time){
    int taux = getSeconds();
    while(taux + time > getSeconds());
}