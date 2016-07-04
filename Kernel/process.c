#include <lib.h>
#include <process.h>
#include <debugger.h>
#include <mem.h>

int strlen(const char * str);
void * malloc(int len);

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
typedef int (*EntryPoint)();

static process *last;
static process *current;
static process *nullProcess;

static uint64_t nextPid = 1;

void initProcesses(){
	nullProcess = createProcess("null", 0,1);
	current = nullProcess;
	current->next = nullProcess;
	last = nullProcess;
	nullProcess->next = createProcess("shell",processShell,1); 	
	
	forceScheduler();
}

static void wrapper(EntryPoint func){
	//sPrintf("func: %x\n", func);
	func();
	//sPrintf("asd\n");
	process * aux = current->next;
	sPrintf("\nTERMINE :%s\n",aux->name);
	last->next = current->next;
	current = current->next;
	current->state = ACTIVE;
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
	p->quantum = 50;
	p->instp = (void *)wrapper;
	//sPrintf("%s: %x %x\n", p->name, p->instp, funct);
	newProcessContext(p,funct);
	sPrintf("%s: %x %x %x\n", p->name, p->instp, funct, p->stack);
	//sPrintf("\nStack pointer: %x\n",p->stack);	
	p->next = current->next;
	p->state = ACTIVE;
	if(newProcess){
		sPrintf("Seteo %s en inactive \n", current->name);
		current->state = INACTIVE;
	}

	current->next = p;
	last = current;
	process * auxi = (p->next);
	process * auxi2 = (current->next);
	sPrintf("CREO EL PROCESO %s, QUE VIENE DESPUES DE %s Y DPS VIENE %s\n",p->name,last->name,auxi->name);
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
		process * aux = current->next;
		if(aux->pid == nullProcess->pid || aux->state == INACTIVE){
			//Salteo uno
			last = current;
			current = aux->next;
			sPrintf("curr: %s\n", current->name);
		} else {
			last = current;
			current = current->next;
			sPrintf("curr: %s\n", current->name);
		}
	}
}

uint64_t getQuantum(){
	////sPrintf("q: %d", current->quantum);
	return current->quantum;
}

void decQuantum(){
	if(current->quantum > 0){
	//	//sPrintf("dq: %d", current->quantum);
		current->quantum--;
	}
}