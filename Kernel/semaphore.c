#include <semaphore.h>
#include <mem.h>	
#include <process.h>

void destroySemaphore(Semaphore *semaphore);

//Creates a semaphore
Semaphore *startSemaphore(unsigned int value){
	Semaphore *semaphore = malloc(sizeof(Semaphore));
	semaphore->value = value;
	semaphore->firstPID = 0;
	semaphore->lastPID = 0;
	return semaphore;
}

//Sends a semaphore to its death. Cannot be used after this.
void stopSemaphore(Semaphore *semaphore){
	semaphore->dead = 1;
	if(semaphore->firstPID == 0)
		destroySemaphore(semaphore);
}

//Destroys a semaphore
void destroySemaphore(Semaphore *semaphore){
	// freePIDQueue(semaphore);       								 //TODO: FREE PIDQUEUE
	// free(semaphore);               								 //TODO: FREE SEMAPHORE
}

//Sleep until semaphore lets me (Could be immediate). 
//If semaphore is dead returns 0.
int waitSemaphore(Semaphore *semaphore){
	while(1){
		if(semaphore->dead == 1)
			return 0;
		if(semaphore->value > 0){
			semaphore->value--;
			return 1;
		}

		pNode * node = malloc(sizeof(pNode));
		process * p = getCurrent();
		node->pid = p->pid;
		node->next = 0;

		if(semaphore->firstPID == 0){
			semaphore->firstPID = node;
			semaphore->lastPID = node;
		}
		else{
			semaphore->lastPID->next = node;
			semaphore->lastPID = node;
		}

		sleepProcess(node->pid);
	}
	return 0;
}


//Wakes up next task or semaphoreValue++;
void signalSemaphore(Semaphore *semaphore){
	if ( semaphore->firstPID == 0 ){
		if(semaphore->dead == 1)
			destroySemaphore(semaphore);
		else
			semaphore->value++;
		return;
	}
	//pNode *node = semaphore->firstPID;
	// free(node);													//TODO: FREE NODE
	semaphore->firstPID = semaphore->firstPID->next;
	if(semaphore->firstPID != 0)
		wakePrecess(semaphore->firstPID);
}