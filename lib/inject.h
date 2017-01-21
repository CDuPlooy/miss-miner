#ifndef INJECT_GUARD
#define INJECT_GUARD
//Includes
#include "custom_io.h"
#include "PE.h"
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
#endif
