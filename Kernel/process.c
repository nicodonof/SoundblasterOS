#include <lib.h>
#include <process.h>
#include <debugger.h>
#include <mem.h>
#include "lib.h"

int strlen(const char * str);
void * malloc(int len);

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
typedef int (*EntryPoint)();

static process *last;
static process *current;
static process *shellProc;
static process *nullProcess;

static uint64_t nextPid = 1;

void initProcesses(){
    nullProcess = createProcess("null", 0,0);
    nullProcess->state = INACTIVE;

    current = nullProcess;
    current->next = nullProcess;
    last = nullProcess;
    
    shellProc = createProcess("shell",processShell,0);  
    nullProcess->next = shellProc;
    forceScheduler();
}

static void wrapper(EntryPoint func){
    //sPrintf("func: %x\n", func);
    if(current->noVideo){
    	func();
    }else{
    	func();
    }
    
    //sPrintf("asd\n");
    process * aux = current->next;
    sPrintf("\nTERMINE :%s\n",current->name);
    last->next = current->next;
    current = current->next;
    shellProc->state = ACTIVE;
    forceScheduler();
    
    sPrintf("\nTERMINE DE VUELTA: ahora viene:%s\n",current->name);
}

process * createProcess(char * name, void * funct,int newProcess){
    process * p = malloc(sizeof(process)); 
    //p->name = malloc(strlen(name)+1);
    memset(p->name, 0, 24);
    memcpy(p->name, name, strlen(name)+1);
    p->pid = getNewPid();
    //sPrintf("\n%x\n", p->name);
    p->stack = pageAlloc();
    //sPrintf("st: %x\n", p->stack);
    p->quantum = 1;
    p->instp = (void *)wrapper;
    //sPrintf("%s: %x %x\n", p->name, p->instp, funct);
    newProcessContext(p,funct);
    sPrintf("%s: %x %x %x\n", p->name, p->instp, funct, p->stack);
    //sPrintf("\nStack pointer: %x\n",p->stack);    
    p->next = current->next;
    p->state = ACTIVE;
    if(newProcess == 1){
        sPrintf("shell state: ianctive\n");
        shellProc->state = INACTIVE;
    } else if(newProcess == 2){
    	shellProc->state = ACTIVE;
    	p->noVideo = 1;
    }


    current->next = p;
    last = current;
    process * auxi = (p->next);
    process * auxi2 = (current->next);
    sPrintf("CREO EL PROCESO %s %s, QUE VIENE DESPUES DE %s Y DPS VIENE %s\n",p->name,p->state?"activo":"inactivo",last->name,auxi->name);
    return p;
}

static uint64_t getNewPid(){
    uint64_t pid = nextPid;
    nextPid++;
    return pid;
}

static uint64_t processShell() {
    //sPrintf("%x\n", processShell);
    ((EntryPoint)sampleCodeModuleAddress)();
    return 0;
}

process * getCurrent() {
    return current;
}

void processNext() {
    //sPrintf("curr: %s\n", current->name);
    if(current != 0 && current->next != 0){
        process * aux;
        do{
            aux = current->next;
            last = current;
            current = current->next;
        }while(aux->state == INACTIVE);

    }
}

uint64_t getQuantum(){
    ////sPrintf("q: %d", current->quantum);
    return current->quantum;
}

void decQuantum(){
    if(current->quantum > 0){
    //  //sPrintf("dq: %d", current->quantum);
        current->quantum--;
    }
}

void sleepProcess(int pid){
	process * aux = findProcessByPid(pid);
	aux->state = INACTIVE;
	if(current == aux){ // SI ESTA CORRIENDO DORMILO YAAAAAAA
		forceScheduler();
	}
}

void wakePrecess(int pid){
	process * aux = findProcessByPid(pid);
	aux->state = ACTIVE;
}

process * findProcessByPid(int pid){
	process * aux = current;
	while(aux->pid != pid){
        aux = current->next;
    }
    return aux;	
}

void printPidList(){
    process * aux = current->next;
    while(current != aux){
        vPrint("Process name: ");        
        vPrint(current->name);
        vPrint(", pid: ");
        vPrintDec(current->pid);
        vPrint("\n");
        aux = current->next;
    }
}