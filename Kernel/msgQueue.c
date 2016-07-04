#include <lib.h>
#include <msgQueue.h>
#include <mem.h>
#include <process.h>

void destroyMsgQ(MessageQueue* q);

#define MAX_QUEUES 50

static MessageQueue* queue[MAX_QUEUES];
static char* qNames[MAX_QUEUES];

//Creates a messageQ if it doesnt exist. Returns 0 if it cannot create it.
MessageQueue* openMsgQ(char *name){
	for (int i = 0; i < MAX_QUEUES; ++i){
		if(strcmp(qNames[i],name))
			return queue[i];
	}

	for (int i = 0; i < MAX_QUEUES; ++i){
		if(qNames[i] == 0){
			MessageQueue *auxQueue = malloc(sizeof(MessageQueue));
			auxQueue->sem = startSemaphore(1);
			auxQueue->receiver = getCurrent()->pid;
			auxQueue->ID = i;
			auxQueue->name = name;
			auxQueue->dead = 0;
			qNames[i] = name;
			queue[i] = auxQueue;
			return auxQueue;
		}
	}
	return 44;
}

//Gives a message queue if it exists, returns 0 if not.
MessageQueue* getMsgQ(char *name){
	for (int i = 0; i < MAX_QUEUES; ++i){
		if(strcmp(qNames[i],name))
			return queue[i];
	}
	return 0;
}

//Sends msgQueue to die :(
void closeMsgQ(MessageQueue* q){
	waitSemaphore(q->sem);
	q->dead = 1;
	if(q->first == 0)
		destroyMsgQ(q);
	signalSemaphore(q->sem);
}

//Sends a message through the message queue.
void sendMsg(MessageQueue* q,char* msg){
	waitSemaphore(q->sem);
	Msg* newMsg = malloc(sizeof(Msg));
	newMsg->msg = msg;
	newMsg->next = 0;
	if(q->first == 0){
		q->first = newMsg;
		q->last = newMsg;
	}
	else{
		q->last->next = newMsg;
		q->last = newMsg;
	}
	signalSemaphore(q->sem);
}

//Gets back a message from the messageQueue and erases it.
char* receiveMsg(MessageQueue* q){
	waitSemaphore(q->sem);
	
	if(getCurrent()->pid == q->receiver){
		if(q->first != 0){
			Msg* node = q->first;
			q->first = q->first->next;
			if(q->dead == 1 && q->first == 0)
				destroyMsgQ(q);
			signalSemaphore(q->sem);
			return node->msg;
		}
	}
	signalSemaphore(q->sem);
	return 0;
}

//MessageQueue is kill.
void destroyMsgQ(MessageQueue* q){
	queue[q->ID] = 0;
	qNames[q->ID] = 0;
}