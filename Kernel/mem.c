#include <stdint.h>
#include <mem.h>

#define GB 0x40000000

uint64_t pageSize = 0x1000;
uint64_t * stackStart	= (uint64_t*) (10*0x100000);
uint64_t * stackEnd		= (uint64_t*) (12*0x100000);
uint64_t * stackCurrent;

int totalPages;

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
			sPrint("i: Pos de la pag: ");
			sPrintHex(startOfPages + i*(pageSize));
			sPrint(" - Pos en stack: ");
			sPrintHex(stackCurrent);
			sPrint("\n");
		}
		stackCurrent--;
	}

	sPrint("curr:    \t");
	sPrintHex(stackCurrent);
	sPrintNl();
	uint64_t * asd = 0;
	for(i=0; i<totalPages;i++){
		asd = pageAlloc();
		if(i%12000 == 0){
			sPrintDec(i);
			sPrint(": ");
			sPrintHex(asd);
			sPrintNl();
		}
	}

	sPrintHex(*stackCurrent);

	pageFree((uint64_t *) 0x654);
	sPrint("currPost:\t");
	sPrintHex(stackCurrent);
	sPrint(" ");
	sPrintHex(*(stackCurrent));
	sPrintNl();

	pageFree();
	sPrint("currPost:\t");
	sPrintHex(stackCurrent);
	sPrint(" ");
	sPrintHex(*(stackCurrent));
	sPrintNl();

	pageFree();
	sPrint("currPost:\t");
	sPrintHex(stackCurrent);
	sPrint(" ");
	sPrintHex(*(stackCurrent));
	sPrintNl();

	pageAlloc();
	sPrint("currPost:\t");
	sPrintHex(stackCurrent);
	sPrint(" ");
	sPrintHex(*(stackCurrent));
	sPrintNl();
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