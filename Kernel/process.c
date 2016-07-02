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
static process *null_process;

static process *foreground[4] = {0};

static uint64_t nextPid = 1;

void initProcesses(){
	createProcess("shell",processShell);
}

process * createProcess(char * name, void * funct){
	process * p = malloc(sizeof(process)); 
	//p->name = malloc(strlen(name)+1);
	memset(p->name, 0, 24);
	memcpy(p->name, name, strlen(name)+1);
	p->pid = getNewPid();
	sPrintf("\n%x\n", p->name);
	p->stack = pageAlloc();
	sPrintf("st: %x", p->stack);
	p->quantum = 100;
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
