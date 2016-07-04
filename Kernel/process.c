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
	nullProcess = createProcess("null", 0);
	current = nullProcess;
	nullProcess->next = createProcess("shell",processShell); 	
	
	forceScheduler();
}

static void wrapper(EntryPoint func){
	//sPrintf("func: %x\n", func);
	func();
	//sPrintf("asd\n");
	forceScheduler();
}

process * createProcess(char * name, void * funct){
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
	current->next = p;
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
		if(aux->pid == nullProcess->pid){
			current = aux->next;  
			sPrintf("curr: %s\n", current->name);
		} else {
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