#ifndef MSGQUEUE_H
#define MSGQUEUE_H

#include <semaphore.h>

typedef struct MsgNode Msg;
struct MsgNode{
	char msg;
	Msg* next;	
};


typedef struct MsgQ MessageQueue;
struct MsgQ{
	unsigned int 	ID;
	char*		 	name;
	Semaphore*	 	sem;
//	unsigned int    receiver;
	int 			dead;
	Msg*			first;
	Msg*			last;
}; 

MessageQueue* openMsgQ(char *name);
MessageQueue* getMsgQ(char *name);
void closeMsgQ(MessageQueue* q);
void sendMsg(MessageQueue* q,char msg);
void receiveMsg(MessageQueue* q, char *ret);
char** getOpenedQueues();

#endif