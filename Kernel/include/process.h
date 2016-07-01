#ifndef PROCESS_H
#define PROCESS_H

typedef struct{
	int pid;
	char * name;
	uint64_t stack;
	uint64_t cr3;
} process;

process * createProcess(char * name);

#endif