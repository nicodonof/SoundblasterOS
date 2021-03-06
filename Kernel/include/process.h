#ifndef PROCESS_H
#define PROCESS_H

#define ACTIVE 1
#define INACTIVE 0

typedef struct{
	int pid;
	char name[24];
	uint64_t * stack;
	struct process *next;
	//uint64_t cr3;
	uint64_t quantum;
	void * instp;
	int state;
	int noVideo;
} process;

typedef struct {
	uint64_t gs;
	uint64_t fs;
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rsi;
	uint64_t rdi;
	uint64_t rbp;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rbx;
	uint64_t rax;
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
	uint64_t ss;

	uint64_t base;
} context_t;

process * createProcess(char * name, void * funct,int state);
static uint64_t processShell();
static uint64_t getNewPid();
void initProcesses();
process * getCurrent();
void processNext();
uint64_t getQuantum();
void decQuantum();
void sleepProcess(int pid);
void wakePrecess(int pid);
process * findProcessByPid(int pid);
void printPidList();
void killProcess();
#endif