#include "lib.h"
#include "shell.h"
#include "int80.h"
#include "game.h"
#include "syscall.h"

char auxer = 0;
int time = 0;
int quitF = 0;

void shell(){
    osInit();
    
    while(!quitF){
        write(1,"SoundblasterOS> ",16);
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
                        syscaller(PIANO,'g',0,0,0);
                } else
                buffer[i++] = auxer;
            }         
        } while (auxer != '\n');
        buffer[i-1] = 0;
        parser(buffer,1);
    }
}

void printOsName(){
    print("<=============================== SoundblasterOS ===============================>");
}
typedef struct{
    char name[24];
    void * instp;
}packash;
packash * auxPack;

int wrapProcess(char * name, void * instp){
    packash * auxPack;
    strcpy(auxPack->name,name,strlen(name));
    auxPack->instp = instp;
    int pid;
    syscaller(CREATE_PROCESS,0,auxPack,-1,&pid);
    return pid;
}

void parser(char * s, int size){
    int p;
    size = &p;
    if(*s != 'c' && *s != 'q' && *s != 'i' && *s != 'h' && *s != 'b' && *s != 'p' && *s != 's' && *s != 'g' && *s != 'o'){
        print("No se reconoce el comando. Intente nuevamente.\n");
        return;
    }
    
    strcpy(auxPack->name, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 24); 

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
                strcpy(auxPack->name,"itunes",strlen("itunes"));
                auxPack->instp = itunes;
                int pid;
                syscaller(CREATE_PROCESS,0,auxPack,1,&pid);
                return;
            }
            break;
        case 'o':
            if(strcmp(s,"oq")){
                strcpy(auxPack->name,"openedQs",strlen("openedQs"));
                auxPack->instp = printAllOpenedQueues;
                int pid;
                syscaller(CREATE_PROCESS,0,auxPack,1,&pid);
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
                strcpy(auxPack->name,"beep",strlen("beep"));
                auxPack->instp = beep;
                int pid;
                syscaller(CREATE_PROCESS,0,auxPack,1,&pid);
                return;
            }else if(strcmp(s,"boop")){
                strcpy(auxPack->name,"boop",strlen("boop"));
                auxPack->instp = boop;
                int pid;
                syscaller(CREATE_PROCESS,0,auxPack,1,&pid);
                return;
            }else if(strcmp(s,"bg")){
                if(strcmp(s+3,"itunes")){                
                    strcpy(auxPack->name,"itunes",strlen("itunes"));
                    auxPack->instp = pItunes;
                    int pid;
                    syscaller(CREATE_PROCESS,0,auxPack,0,&pid);
                    return;
                }else if(strcmp(s+3,"stop")){
                    syscaller(END_PROCESS,0,0,0,0);
                    return;                    
                }
            }
            break;
        case 'p':
            if(strcmp(s,"piano")){
                strcpy(auxPack->name,"piano",strlen("piano"));
                auxPack->instp = piano;
                int pid;
                syscaller(CREATE_PROCESS,0,auxPack,1,&pid);
                return;
            }else if (strcmp(s,"ps")){
                strcpy(auxPack->name,"ps",strlen("ps"));
                auxPack->instp = ps;
                int pid;
                syscaller(CREATE_PROCESS,0,auxPack,1,&pid);
                

                return;
            }
            break;
        case 'g':
            if(strcmp(s,"game")){
                strcpy(auxPack->name,"game",strlen("game"));
                auxPack->instp = game;
                int pid;
                syscaller(CREATE_PROCESS,0,auxPack,1,&pid);
                return;
            }
            break;
    }
    print("No se reconoce el comando. Intente nuevamente.\n");
    return ;
}



void clearAll(){
    syscaller(CLEAR,0,0,0,0);
}




int isValidNote(char key){
    return (key == 'd' || key == 'f' ||key == 'g' ||key == 'h' ||key == 'j' ||key == 'k' || key == 'l' 
        || key == 'r' || key == 't' || key == 'u' ||key == 'i' ||key == 'o');
}



int getSeconds(){
    time=0;
    syscaller(GET_TIMER,0,0,0,&time);
    return time;
}


/*Parsea el timer del data module y lo pasa al tiempo "real" que usamos para el sonido*/
int getRealTime(char c){
    if(c=='9')
        return 0;
    if(c=='0')
        return 1;
    if(c=='5')
        return 5;
    return (c-'0')*2;
}

/*funcion que podria estar hecha (deberia) en la parte del timer pero por distintos problemas esta hecho aca */
void sleep(int time){
    int taux = getSeconds();
    while(taux + time > getSeconds());
}



void printOsLogo(){
    print("    _____                       _ ____  _           _             ____   _____  ");
    print("   / ____|                     | |  _ \\| |         | |           / __ \\ / ____| ");
    print("  | (___   ___  _   _ _ __   __| | |_) | | __ _ ___| |_ ___ _ __| |  | | (___   ");
    print("   \\___ \\ / _ \\| | | | '_ \\ / _` |  _ <| |/ _` / __| __/ _ \\ '__| |  | |\\___ \\  ");
    print("   ____) | (_) | |_| | | | | (_| | |_) | | (_| \\__ \\ ||  __/ |  | |__| |____) | ");
    print("  |_____/ \\___/ \\__,_|_| |_|\\__,_|____/|_|\\__,_|___/\\__\\___|_|   \\____/|_____/  ");
    print("                                                                                ");
}

void osInit(){
    syscaller(BOOL_KEY,1,0,0,0);
    //VIDEO
    for(int i = 0; i<2;i++)
        print("                                                                                ");

    printOsLogo();

    for(int i = 0; i<9;i++)
        print("                                                                                ");
    
    //AUDIO
    syscaller(PLAY_SOUND_ONLY,'k',0,1,0);
    sleep(2);
    syscaller(STOP_SOUND,0,0,0,0);

    syscaller(PLAY_SOUND_ONLY,'g',0,1,0);
    sleep(2);
    syscaller(STOP_SOUND,0,0,0,0);

    syscaller(PLAY_SOUND_ONLY,'l',0,1,0);
    sleep(5);
    syscaller(STOP_SOUND,0,0,0,0);

    //CLEAN
    sleep(5);

    syscaller(BOOL_KEY,0,0,0,0);
    clear();
    syscaller(CLEAR_BUFFER,0,0,0,0);
}

