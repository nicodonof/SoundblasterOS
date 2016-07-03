#include <stdint.h>
#include <mem.h>

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
	
	totalPages = GB / pageSize;
	stackCurrent = stackEnd;
	uint64_t startOfPages = (uint64_t) stackEnd;
	sPrint("paginas ");
	sPrintDec(totalPages);
	sPrint(" ");
	sPrintHex(stackCurrent);
	sPrint("\n");
	int i;
	// Se paginiza un giga en un stack
	for(i = 0; i < totalPages; i++){ 
		*stackCurrent = startOfPages + i*(pageSize);
		if(i%12000 == 0){
			sPrintf("%d: Pos: %x - Pos Stack: %x \n", i, *stackCurrent, stackCurrent);
		}
		stackCurrent--;
	}

	uint64_t * asd = 0;
	/*for(i=0; i<totalPages;i++){
		asd = pageAlloc();
		if(i%12000 == 0){
			sPrintf("%d: %x\n",i,asd);
		}
	}*/
	pageAlloc(); //dummy no time to fix

	// pageFree((uint64_t *) asd);
	// sPrintf("currPost:\t%x %x\n", stackCurrent, *stackCurrent);

	// pageFree();
	
	// sPrintf("currPost:\t%x %x\n", stackCurrent, *stackCurrent);
	
	// pageFree();
	
	// sPrintf("currPost:\t%x %x\n", stackCurrent, *stackCurrent);
	
	
	
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

void newProcessContext(process * proc,void * func) {

  //uint64_t saved_cr3 = readCR3();
  //writeCR3(originalCR3);

  /* Write the registers in the stack */
	context_t* context = (context_t*)proc->stack;

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

//	writeCR3(saved_cr3);
}