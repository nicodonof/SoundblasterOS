#include <semaphore.h>
#include <mem.h>												//TODO: ADD INCLUDE FOR TASK OR SCHEDULER?

//Creates a semaphore
Semaphore *startSemaphore(unsigned int value){
	Semaphore *semaphore = malloc(sizeof(Semaphore)); 			//TODO: MALLOC SEMAPHORE
	semaphore->value = value;
	semaphore->firstPID = 0;
	semaphore->lastPID = 0;
	return sem;
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
int wait(Semaphore *semaphore){
	if(semaphore->dead == 1)
		return 0;
	if(semaphore->value > 0){
		semaphore->value--;
		return 1;
	}

	pNode * node = malloc(sizeof(pNode));

	pNode->pid = getpid();   									//TODO: GETPID
	pNode->next = 0;

	if(semaphore->firstPID == 0){
		semaphore->firstPID = node;
		semaphore->lastPID = node;
	}
	else{
		semaphore->lastPID->next = node;
		semaphore->lastPID = node;
	}

	sleep(node->pid);											//TODO: SLEEP PROCESS
	wait(semaphore);
}


//Wakes up next task or semaphoreValue++;
void signal(Semaphore *semaphore){
	if ( semaphore->firstPID == 0 ){
		if(semaphore->dead == 1)
			destroySemaphore(semaphore);
		else
			semaphore->value++;
		return;
	}
	pNode *node = semaphore->firstPID;
	// free(node);													//TODO: FREE NODE
	semaphore->firstPID = semaphore->firstPID->next;
	if(semaphore-firstPID != 0)
		wakeUp(semaphore->firstPID);
}