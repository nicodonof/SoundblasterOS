#include <lib.h>

typedef struct process
{
	int pid;
	char * name;
	uint64_t stack;
	uint64_t cr3;
} process;

int strlen(const char * str);
void * malloc(int len);

process createProcess(char * name){
	/*process p = (uint64_t) malloc(sizeof (process));
	p.name = malloc(strlen(name)+1);
	memcpy(p.name, name, strlen(name)+1);
	p.pid = 123;*/
}