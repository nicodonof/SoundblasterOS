#include <lib.h>
#include <msgQueue.h>
#include <mem.h>
#include <process.h>
#include <debugger.h>
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
			//auxQueue->receiver = getCurrent()->pid;
			auxQueue->ID = i;
			auxQueue->name = name;
			auxQueue->dead = 0;
			auxQueue->first = 0;
			auxQueue->last = 0;
			qNames[i] = name;
			queue[i] = auxQueue;
			//sPrintf("Abro la msgque %s en la dir %x\n" , auxQueue->name, auxQueue);
			//sPrintf("Mi PID: %d El receiver: %d\n" , getCurrent()->pid, auxQueue->receiver);
			return auxQueue;
		}
	}
	return 0;
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
void sendMsg(MessageQueue* q,char msg){
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
void receiveMsg(MessageQueue* q, char * ret){
	// sPrintf("Entro al receiveMsg\n");
	waitSemaphore(q->sem);
	// sPrintf("salgo del waitSemaphore queue: %s pid: %d\n",q->name, getCurrent()->pid);
	// sPrintf("Qdir %x\n", &q);
	// sPrintf("Qdir %x\n", q);
	// sPrintf("Qdir %x\n", *q);
	//if(getCurrent()->pid == q->receiver){
	//	sPrintf("ADENTRO: Mi PID: %d El receiver: %d\n" , getCurrent()->pid, q->receiver);
		if(q->first != 0){
			// sPrintf("HAY UN MESSAGE\n");
			// sPrintf("Qdir1 %x\n", q);
			Msg* node = q->first;
			q->first = q->first->next;
			// sPrintf("Qdir2 %x\n", q);
			if(q->dead == 1 && q->first == 0){
				sPrintf("DEAD:Qdir3 %x\n", q);
				destroyMsgQ(q);
			}
			signalSemaphore(q->sem);
			// sPrintf("node: %c\n", node->msg);
			// sPrintf("Qdir4 %x\n", q);
			*ret = node->msg;
			return/* node->msg*/;
		}
		// sPrintf("NO HAY UN MESSAGE\n");
	//}
	//sPrintf("AFUERA: Mi PID: %d El receiver: %d\n" , getCurrent()->pid, q->receiver);
	signalSemaphore(q->sem);
	return;
}

//MessageQueue is kill.
void destroyMsgQ(MessageQueue* q){
	sPrintf("Q with name: %s is kill." , q->name);
	queue[q->ID] = 0;
	qNames[q->ID] = 0;
}

//Returns a vector of opened queues names 
char** getOpenedQueues(){
	char* openedQs[MAX_QUEUES];
	int j = 0;
	for (int i = 0; i < MAX_QUEUES; ++i)
	{
		if(qNames[i] != 0){
			openedQs[j] = qNames[i];
			j++;
		}
	}
	return openedQs;
}