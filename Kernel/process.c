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
    if(current->noVideo){
    	func();
    }else{
    	func();
    }
    
    //sPrintf("asd\n");
    process * aux = current->next;
    last->next = current->next;
    current = current->next;
    shellProc->state = ACTIVE;
    
    current->state = INACTIVE;
    forceScheduler();
    
}

process * createProcess(char * name, void * funct,int newProcess){
    process * p = malloc(sizeof(process)); 
    memset(p->name, 0, 24);
    memcpy(p->name, name, strlen(name)+1);
    p->pid = getNewPid();
    p->stack = pageAlloc();
    p->quantum = 2;
    p->instp = (void *)wrapper;
    newProcessContext(p,funct);
    p->next = current->next;
    p->state = ACTIVE;
    if(newProcess == 1){
        shellProc->state = INACTIVE;
    } else if(newProcess == 2){
    	shellProc->state = ACTIVE;
    	p->noVideo = 1;
    }


    current->next = p;
    last = current;
    process * auxi = (p->next);
    process * auxi2 = (current->next);
    return p;
}

static uint64_t getNewPid(){
    uint64_t pid = nextPid;
    nextPid++;
    return pid;
}

static uint64_t processShell() {
    ((EntryPoint)sampleCodeModuleAddress)();
    return 0;
}

process * getCurrent() {
    return current;
}

void processNext() {
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
    return current->quantum;
}

void decQuantum(){
    if(current->quantum > 0){
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
        aux = aux->next;
    }
    return aux;	
}

void printPidList(){
    process * aux = current;

    do{
        if(aux->pid!=1){
            vPrint("Process name: ");        
            vPrint(aux->name);
            vPrint(", pid: ");
            vPrintDec(aux->pid);
            vPrint("\n");
        }
        aux = aux->next;
    } while(current != aux);
}

void killProcess(int pid){
    process * auxCurr = current->next;
    process * auxPrev = current;
    while(auxCurr->pid != pid){
        auxPrev = auxCurr;
        auxCurr = auxCurr->next;
    }
    auxPrev->next = auxCurr->next;
    pageFree(auxCurr->stack);
    return;
}