#ifndef MSGQUEUE_H
#define MSGQUEUE_H

struct MsgQ{
	unsigned int 	ID;
	unsigned int 	name;
	Semaphore*	 	sem;
	unsigned int    receiver;
	int 			dead;
	Msg*			first;
	Msg*			last;
}; 

typedef struct MsgQ MessageQueue;

struct MsgNode{
	char * msg;
	struct msgNode* next;	
};

typedef struct msgNode Msg;

#endif