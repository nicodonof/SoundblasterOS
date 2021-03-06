#include <stdint.h>
#include <mem.h>
#include "lib.h"

#define GB 0x40000000

uint64_t pageSize = 0x1000;
uint64_t * stackStart	= (uint64_t*) (10*0x100000);
uint64_t * stackEnd		= (uint64_t*) (12*0x100000);
uint64_t * stackCurrent;
uint64_t * mallocStart = (uint64_t*) (6*0x100000);
uint64_t * currMalloc = (uint64_t*) (6*0x100000);

int totalPages;

//malloc vien billa
void * malloc(int len){
	currMalloc += (uint64_t)len;
	return currMalloc;
}

void initPageStack(){
	
	totalPages = (GB/2) / pageSize; //512 mb
	stackCurrent = stackEnd;
	uint64_t startOfPages = (uint64_t) stackEnd;
	int i;
	// Se paginiza un giga en un stack
	for(i = 0; i < totalPages; i++){ 
		*stackCurrent = startOfPages + i*(pageSize);
		stackCurrent--;
	}

	uint64_t * asd = 0;

	pageAlloc(); //dummy no time to fix
	
	
} 


uint64_t * pageAlloc(){
	uint64_t * ans;
	if(stackCurrent == stackEnd){
		sPrint("No memory.");
		return -1;
	}
	ans = *stackCurrent;
	stackCurrent++;
	return ans;
}

void pageFree(uint64_t * page){
	if(stackCurrent == stackStart)
		sPrint("No pages left to free.");
	stackCurrent--;
	*stackCurrent = page;
}

/*basado en sebikul*/
void newProcessContext(process * proc,void * func) {
	int interr = disableOrEnableInterrupts(0);
  
	context_t* context = (context_t*)proc->stack;// - sizeof(context_t);

	context->gs = 	0x01;
	context->fs = 	0x02;
	context->r15 =  0x03;
	context->r14 =  0x04;
	context->r13 =  0x05;
	context->r12 =  0x06;
	context->r11 =  0x07;
	context->r10 =  0x08;
	context->r9 = 	0x09;
	context->r8 = 	0x0A;
	context->rsi =  0x0B;
	context->rdi =  (uint64_t)func;
	context->rbp =  0x0D;
	context->rdx =  0x0E;
	context->rcx =  0x0F;
	context->rbx =  0x010;
	context->rax =  0x011;

	context->rip =  proc->instp;//direccion de retorno que levanta con el iretq
	context->cs = 	0x008;
	context->rflags=0x202;
	context->rsp = (proc->stack);
	context->ss = 	0x000;
	context->base = 0x000;

	disableOrEnableInterrupts(1);
}