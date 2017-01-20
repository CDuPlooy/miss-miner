#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../lib/custom_io.h"
#include "../lib/inject.h"
#include "../lib/map.h"
#include "../lib/PE.h"
#include "../lib/DOS.h"

char *target;
char *shellcode;
char *output;

int main(int argc , char **argv){
	compound_file *cf = fileToBuffer("test.bin");
	if(!cf)
		return 1;
	IMAGE_DOS_HEADER *idh = (void *)cf->buffer;
	IMAGE_NT_HEADER *inh = (void *)(cf->buffer + idh->e_lfanew);
	PE_STRUCTURE pe;
	pe.image_dos_header = idh;
	pe.image_nt_header = inh;
	pe.buffer = cf->buffer;
	pe.size = cf->size;

	printf("%x||%x\n",pe.image_nt_header->image_optional_header.checkSum, checksum(&pe));
	destroyCompoundFile(cf);
	return 0;
}
