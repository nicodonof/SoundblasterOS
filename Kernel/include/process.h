#ifndef PROCESS_H
#define PROCESS_H

typedef struct{
	int pid;
	char name[24];
	uint64_t * stack;
	//uint64_t cr3;
	uint64_t quantum;
	void * instp;
} process;

process * createProcess(char * name, void * funct);
static uint64_t processShell();
static uint64_t getNewPid();
void initProcesses();
process * getCurrent();

#endif