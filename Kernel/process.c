#include <lib.h>
#include <process.h>
#include <debugger.h>
#include <mem.h>

int strlen(const char * str);
void * malloc(int len);

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
typedef int (*EntryPoint)();

static process *current;
static process *nullProcess;

static uint64_t nextPid = 1;

void initProcesses(){
	current = nullProcess;
	nullProcess->next = createProcess("shell",processShell); 	
	forceScheduler();

	sPrintf("sali del coso");
}

static void wrapper(EntryPoint func){
	func();
	forceScheduler();
}

process * createProcess(char * name, void * funct){
	process * p = malloc(sizeof(process)); 
	//p->name = malloc(strlen(name)+1);
	memset(p->name, 0, 24);
	memcpy(p->name, name, strlen(name)+1);
	p->pid = getNewPid();
	sPrintf("\n%x\n", p->name);
	p->stack = pageAlloc();
	sPrintf("st: %x\n", p->stack);
	p->quantum = 5;
	p->instp = (void *)wrapper;
	sPrintf("%s: %x %x %x\n", p->name, p->instp, funct, (void*)processShell);
	newProcessContext(p,funct);
	sPrintf("%s: %x %x %x\n", p->name, p->instp, funct, (void*)processShell);
	sPrintf("\nStack pointer: %x\n",p->stack);
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
		current = current->next;
	}	
}

uint64_t getQuantum(){
	return current->quantum;
}

void decQuantum(){
	if(current->quantum > 0)
		current->quantum--;
}