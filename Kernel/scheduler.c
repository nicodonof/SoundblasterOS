#include <stdint.h>
#include "process.h"
extern void * kernel_stack;

void* schedulerToKernel(uint64_t * stackPointer){
	process *current = processGetCurrent();

	if (current != 0) { //NULL
		current->stack = stackPointer;
	}

	return kernel_stack;
}


void* schedlerToUser(){
	process *proc = processGetCurrent();
	//proc->quantum = QUANTUM;
	//writeCR3(proc->cr3);

	return proc->stack;
}