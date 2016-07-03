#include "lib.h"
#include "shell.h"
#include "int80.h"


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
                        syscaller(4,'g',0,0,0);
                } else
                    buffer[i++] = auxer;
            }         
        } while (auxer != '\n');
        buffer[i-1] = 0;
        parser(buffer,1);
    }
}

void printOsName(){
    write(1,"<=============================== SoundblasterOS ===============================>",80);
}
typedef struct{
    char name[24];
    void * instp;
}packash;
void parser(char * s, int size){
    if(*s != 'c' && *s != 'q' && *s != 'i' && *s != 'h' && *s != 'b' && *s != 'p' && *s != 's' && *s != 'g'){
    	print("No se reconoce el comando. Intente nuevamente.\n");
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
                packash * auxPack;
                strcpy(auxPack->name,"itunes",strlen("itunes"));
                auxPack->instp = itunes;
                int pid;
                syscaller(12,0,auxPack,-1,&pid);
                write(1,&pid,0);
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
        case 'g':
            if(strcmp(s,"game")){
                game();
                return;
            }
        break;
    }
    print("No se reconoce el comando. Intente nuevamente.\n");
    return ;
}



void clearAll(){
    syscaller(3,0,0,0,0);
}




int isValidNote(char key){
    return (key == 'd' || key == 'f' ||key == 'g' ||key == 'h' ||key == 'j' ||key == 'k' || key == 'l' 
            || key == 'r' || key == 't' || key == 'u' ||key == 'i' ||key == 'o');
}



int getSeconds(){
    time=0;
    syscaller(6,0,0,0,&time);
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
    syscaller(5,1,0,0,0);
    //VIDEO
    for(int i = 0; i<2;i++)
        print("                                                                                ");

    printOsLogo();

    for(int i = 0; i<9;i++)
        print("                                                                                ");
    
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

    syscaller(5,0,0,0,0);
    clear();
    syscaller(11,0,0,0,0);
}

void game(){
    print("Game not implemented yet...");
    return; //?
    // FORK DE SOUND
    // FORK DE VIDEO
    
    int randoms[3];
    syscaller(16,0,&random[0],0,0);//hacer syscall de get random
    syscaller(16,0,&random[1],0,0);
    syscaller(16,0,&random[2],0,0);
    int posicionDelJugador = 0;
    // 0 1 (posicion del jugador)
    // 2 3
    // El fork del video (hablar con teo de comm) se encarga de:
        // poner la circulo arriba isq (personaje)
        // poner la flecha de random[0] arriba der
        // poner la flecha de random[1] abajo isq
        // poner la flecha de random[2] abajo der
    int puntaje = 0;
    long timeStart;
    long GAME_DURATION = 177777; // ??? que esto tenga sentido
    syscaller(17,0,&timeStart,0,0); // syscall que agarra epoch o alguna manera de gettear el start time para chequear cuanto time paso
    while(timeStart < GAME_DURATION){
        //wait for input del usuario ?
        //poray aca tenes que inventarte orto "mode" aparte de pianoModer y shellModer
        //para leer el keypress
        //if(toke el key correcto){
        //  puntaje++;
        //  play good sound!
        //  posicionDelJugador = (posicionDelJugador + 1) % 4
        //  reiniciarLasFlechas(posicionDelJugador);
        //} else {
        //  puntaje--;
        //  play bad sound :(
        //  reiniciarLasFlechas(posicionDelJugador);
        //}
    }
    //clear screen syscall
    printf("Su puntaje es: %d\n", puntaje);
    printf("Precione enter para salir\n");
    printf("Precione R para reintenter\n");
    //?????
}