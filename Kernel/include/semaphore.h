#ifndef SEMAPHORE_H
#define SEMAPHORE_H

typedef struct ProcessNode pNode;
struct ProcessNode{
	int pid;
	pNode* next;	
};

typedef struct Semaphore Semaphore;
struct Semaphore{
	int		value;
	int     dead;
	pNode*	firstPID;
	pNode*	lastPID;
};


Semaphore *startSemaphore(unsigned int value);
void stopSemaphore(Semaphore *semaphore);
int wait(Semaphore *semaphore);
void signal(Semaphore *semaphore);

#endif
