#ifndef SEMAPHORE_H
#define SEMAPHORE_H

struct ProcessNode{
	int pid;
	struct ProcessNode* next;	
};
typedef struct ProcessNode pNode;

struct Semaphore{
	int		value;
	int     dead;
	pNode*	firstPID;
	pNode*	lastPID;
};
typedef struct Semaphore Semaphore;

Semaphore *startSemaphore(unsigned int value);
void stopSemaphore(Semaphore *semaphore);
int wait(Semaphore *semaphore);
void signal(Semaphore *semaphore);

#endif
