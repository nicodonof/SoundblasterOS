#include <stdint.h>
#include "process.h"

extern void * kernelStack;

void* schedulerToKernel(uint64_t * stackPointer){
	process *current = getCurrent();

	if (current != 0) { //NULL
		current->stack = stackPointer;
	}

	return kernelStack;
}


void* schedulerToUser(){
	process *proc = getCurrent();
	proc->quantum = 0;
	//writeCR3(proc->cr3);
//	sPrintf("Nuevo current: %s\n", proc->name);
	return proc->stack;
}