#ifndef CUSTOM_IO_PE_H
#define CUSTOM_IO_PE_H
#include "PE.h"
#include "custom_io.h"

struct _PE_STRUCTURE *loadPE(const char *filename){
	struct _PE_STRUCTURE *pe = malloc(sizeof(struct _PE_STRUCTURE));
	if(!pe)
		return NULL;

	compound_file *cf = fileToBuffer(filename);
	if(!cf){
		free(pe);
		return NULL;
	}

	pe->image_dos_header = (void *)cf->buffer;
	pe->image_nt_header = (void *)cf->buffer + pe->image_dos_header->e_lfanew;
	pe->buffer = cf->buffer;
	pe->size = cf->size;
	free(cf);
	return pe;
}

#endif
