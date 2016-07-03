#include <lib.h>
#include <msgQueue.h>
#include <semaphore.h>

#define MAX_QUEUES 50

static MsgQueue* queue[MAX_QUEUES];
static char** qNames[MAX_QUEUES];

MsgQueue openMsgQ(char *name){
	for (int i = 0; i < MAX_QUEUES; ++i){
		if(strcmp(qNames[i],name))
			return pipes[i];
	}
	for (int i = 0; i < MAX_QUEUES; ++i){
		if(qNames[i] == 0){
			MsgQueue *auxQueue = malloc(sizeof(Msg));
			auxQueue->semaphore = startSemaphore(1);
			auxQueue->receiver = getPID();
			auxQueue->ID = i;
			auxQueue->name = name;
			auxQueue->dead = 0;
			qNames[i] = name;
			queue[i] = auxQueue;
			return auxQueue;
		}
	}
	return 0;
}

int closeMsgQ(MsgQueue q){
	q->dead = 1;
	if(q->first == 0)
		destroyMsgQ(q);
}

void sendMsg(MsgQueue q,char* msg){
	wait(q->semaphore);
	Msg newMsg = malloc(sizeof(Msg));
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
	signal(q->semaphore);
}

char* receiveMsg(MsgQueue q){
	wait(q->semaphore);
	if(getPID() == q->receiver){
		if(q->first != 0){
			MsgNode* node = q->first;
			q->first = q->first->next;
			if(q->dead == 1 && q->first == 0)
				destroyMsgQ(q);
			signal(q->semaphore);
			return node->msg;
		}
	}
	signal(q->semaphore);
	return 0;
}

void destroyMsgQ(MsgQueue q){
	queue[q->ID] = 0;
	qNames[q->ID] = 0;
}