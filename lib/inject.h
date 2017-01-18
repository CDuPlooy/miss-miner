#ifndef INJECT_GUARD
#define INJECT_GUARD
//Includes
#include "custom_io.h"
#include <sys/types.h>

//Typedefs
typedef struct cl{
	off_t start;
	off_t end;
	struct cl *next;
}cavelist;	//A linked list representing code caves.

//Functions
cavelist *getCaves( compound_file *cf );
void freeCaves(cavelist *cl);
#endif
