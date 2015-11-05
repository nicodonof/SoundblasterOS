#include "shell.h"

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

float notefreqs[7][13] = {
    {0.0,   16.35,  17.32,  18.35,  19.45,  20.60,  21.83,  23.12,  24.50,  25.96,  27.50,  29.14,  30.87},
    {0.0,   32.70,  34.65,  36.71,  38.89,  41.20,  43.65,  46.25,  49.00,  51.91,  55.00,  58.27,  61.74},
    {0.0,   65.41,  69.30,  73.42,  77.78,  82.41,  87.31,  92.50,  98.00,  103.83, 110.00, 116.54, 123.47},
    {0.0,   130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94},
    {0.0,   261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88}, // MEDIO
    {0.0,   523.25, 554.37, 587.33, 622.25, 659.26, 698.46, 739.99, 783.99, 830.61, 880.00, 932.33, 987.77},
    {0.0,   1046.50,1108.73,1174.66,1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760.00,1864.66,1975.53}
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
    int keyToNoteTable[26] = {0,0,0,26163 /* D (DO)*/,0,note[1] /* F (RE)*/,note[2] /* G (MI)*/, note[3] /* H (FA)*/,1,
                              note[4] /* J (SOL)*/,note[5] /* K (LA)*/, note[6] /* L (SI)*/,0,0,1,1, 0,1,0,1,1,0,0,0,1,0};
    return (0x1234dd / (keyToNoteTable[key - 'a'] / 100));
}

int isValidNote(char key){
    return (key == 'd' || key == 'f' ||key == 'g' ||key == 'h' ||key == 'j' ||key == 'k' || key == 'l');
}

void piano(){
    syscaller(5,1,0,0,0);
    clear();
    write(1,"Welcome to the Piano ! To exit press the enter key.\n",52);
    playSong();
    do{
        auxer = getChar();
        if(auxer != 0 && isValidNote(auxer)){
            syscaller(4,keyToNotefreq(auxer),0,1,0);
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

void playSong(){
    char song[30] = {'g','g','h','j','j','h','g','f','d','d','f','g','g','f','f',
                     'g','g','h','j','j','h','g','f','d','d','f','g','f','d','d'};
    char time[30] = {   4,4,4,4,4,4,4,4,4,4,4,4,8,2,8,
                        4,4,4,4,4,4,4,4,4,4,4,4,8,2,8 };
    char pause[30] = {  4,4,4,4,4,4,4,4,4,4,4,4,4,4,8,
                        4,4,4,4,4,4,4,4,4,4,4,4,4,4,8 };
    int i = 0;
    while(1){
        for (i=0;i<30;i++){
            syscaller(7,keyToNotefreq(song[i]),0,1,0);
            int taux = getSeconds();
            while(taux + time[i] > getSeconds());
            syscaller(8,0,0,0,0);
            taux = getSeconds();
            while(taux + pause[i] > getSeconds());

        }
    }
}