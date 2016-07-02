#ifndef SEMAPHORE_H
#define SEMAPHORE_H

struct ProcessNode{
	int pid;
	struct ProcessNode	* next;	
};
typedef struct ProcessNode pNode;

struct Semaphore{
	int		value;
	pNode *	first;
	pNode *	last;
};
typedef struct Semaphore Semaphore;



#endif
