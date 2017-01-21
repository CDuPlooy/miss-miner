#ifndef INJECT_GUARD
#define INJECT_GUARD
//Includes
#include "custom_io.h"
#include <string.h>
#include <sys/types.h>

//Typedefs
typedef struct cl{
	off_t start;
	off_t end;
	struct cl *next;
}cavelist;	//A linked list representing code caves.

typedef struct inject_d{
	off_t offset;
	off_t virtualAddress;
}inject_data;

//Functions
cavelist *getCaves( compound_file *cf );
cavelist *checkCaveList( cavelist *cl , size_t size);
void freeCaves(cavelist *cl );
short injectShellcode(cavelist *cl , compound_file *cf_res , compound_file *cf_shellcode , inject_data *id);
#endif
