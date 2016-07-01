#include <lib.h>
#include <process.h>
#include <debugger.h>
#include <mem.h>

int strlen(const char * str);
void * malloc(int len);

process * createProcess(char * name){
	process * p = malloc(sizeof(process)); 
	//p->name = malloc(strlen(name)+1);
	memset(p->name, 0, 24);
	memcpy(p->name, name, strlen(name)+1);
	p->pid = 123;
	sPrintf("\n%x\n", p->name);
	p->stack = pageAlloc();
	sPrintf("st: %x", p->stack);
	return p;
}