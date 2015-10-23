#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <types.h>
#include <video.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

DESCR_INT *idt = (DESCR_INT*) 0;

void _EOI();
void keyboardHandler();
void timerHandler();

static void syscallHandler(int index,int fd, char c, void * desc);

void setup_IDT_entry (DESCR_INT *idt, int index, word selector, ddword offset, byte access);

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
	



/*	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();*/
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	/*ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();*/

	clearBSS(&bss, &endOfKernel - &bss);

	/*ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();*/
	return getStackBase();
}

int main()
{	

	setup_IDT_entry(idt, 0x20, 0x08, &timerHandler, 0x8E);
	setup_IDT_entry(idt, 0x21, 0x08, &keyboardHandler, 0x8E);
//	setup_IDT_entry(idt, 0x80, 0x08, &syscallHandler, 0x8E);

	picMasterMask(0xFC);
	picSlaveMask(0xFF);
	_sti();

	vClear();
	
	

	/*ncPrint("[Kernel Main]");
	ncNewline();
	ncPrint("  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	ncNewline();
	ncPrint("  Calling the sample code module returned: ");*/
	((EntryPoint)sampleCodeModuleAddress)();
	//ncPrintHex(();
	
	return 0;
}




void keyboarddddd(){
	vPrint("a");
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
