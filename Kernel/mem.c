#include <stdint.h>
#include <mem.h>

#define GB 0x40000000

uint64_t pageSize = 0x1000;
uint64_t * stackStart	= (uint64_t*) (10*0x100000);
uint64_t * stackEnd		= (uint64_t*) (12*0x100000);
uint64_t * stackCurrent;
uint64_t * mallocStart = (uint64_t*) (6*0x100000);
//uint64_t * currMalloc = mallocStart;

int totalPages;

/*void * malloc(int len){
	if(currMalloc + len > stackStart)
		return -1;
	//currMalloc
}*/

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
	for(i=0; i<totalPages;i++){
		asd = pageAlloc();
		if(i%12000 == 0){
			sPrintf("%d: %x\n",i,asd);
		}
	}


	pageFree((uint64_t *) 0x654);
	sPrintf("currPost:\t%x %x\n", stackCurrent, *stackCurrent);

	pageFree();
	
	sPrintf("currPost:\t%x %x\n", stackCurrent, *stackCurrent);
	
	pageFree();
	
	sPrintf("currPost:\t%x %x\n", stackCurrent, *stackCurrent);
	
	pageAlloc();
	
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