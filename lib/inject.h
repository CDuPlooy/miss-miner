#ifndef INJECT_GUARD
#define INJECT_GUARD
//Includes
#include "custom_io.h"
#include "PE.h"
#include <string.h>
#include <sys/types.h>

//Defines
#define INJECT_EXTRA_SPACE 16

//Typedefs
typedef struct cl{
	off_t start;
	off_t end;
}cavelist;

typedef struct inject_d{
	off_t offset_in_file;
	off_t position_in_memory;
}inject_data;


short injectData(struct _PE_STRUCTURE *pe , struct _IMAGE_SECTION_HEADER **sections , compound_file *shellcode , struct inject_d *id);
#endif
