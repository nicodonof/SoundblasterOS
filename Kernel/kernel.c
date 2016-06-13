#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <types.h>
#include <video.h>
#include <serial.h>
#include <debugger.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;
extern int countTimer;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;





typedef int (*EntryPoint)();

DESCR_INT *idt = (DESCR_INT*) 0;

void _EOI();
void keyboardHandler();
void timerHandler();
uint64_t syscallHandlerA(uint64_t index,uint64_t fd, uint64_t * buff,uint64_t buffSize ,uint64_t dest);
void changeSelector();
void sounderC(int freq);

void setup_IDT_entry (DESCR_INT *idt, int index, word selector, ddword offset, byte access);

void picMasterMask(uint8_t num);
void picSlaveMask(uint8_t num);
void _sti();

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
		);
}

void * initializeKernelBinary()
{
	

	char buffer[10];


	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	

	clearBSS(&bss, &endOfKernel - &bss);

	init_serial();
	sPrintNl();
	sPrint("Serial Inicializado\n");

	return getStackBase();
}






int main()
{	

	setup_IDT_entry(idt, 0x20, 0x08, &timerHandler, 0x8E);
	setup_IDT_entry(idt, 0x21, 0x08, &keyboardHandler, 0x8E);
	setup_IDT_entry(idt, 0x80, 0x08, &syscallHandlerA, 0x8E);

	picMasterMask(0xFC);
	picSlaveMask(0xFF);
	_sti();
	initPageStack();
	putPixels();
	vClear();
	((EntryPoint)sampleCodeModuleAddress)();

	return 0;
}






void setup_IDT_entry (DESCR_INT *idt, int index, word selector, ddword offset, byte access) {
	idt[index].selector = selector;
	idt[index].offset_l = offset & 0xFFFF;
	idt[index].offset_m = (offset & 0xFFFF0000) >> 16;
	idt[index].offset_h = (offset & 0xFFFFFFFF00000000) >> 32;
	idt[index].access = access;
	idt[index].cero = 0;
	idt[index].zero = 0;
}