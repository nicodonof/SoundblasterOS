#ifndef PROCESS_H
#define PROCESS_H

typedef struct{
	int pid;
	char name[24];
	uint64_t * stack;
	//uint64_t cr3;
} process;

process * createProcess(char * name, void * funct);

#endif