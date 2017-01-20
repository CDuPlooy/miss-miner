#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../lib/custom_io.h"
#include "../lib/inject.h"
#include "../lib/map.h"
#include "../lib/PE.h"
#include "../lib/DOS.h"
#include "../lib/custom_io_pe.h"

char *target;
char *shellcode;
char *output;

int main(int argc , char **argv){
	PE_STRUCTURE *pe = loadPE("test.bin");

	printf("%x||%x\n",pe->image_nt_header->image_optional_header.checkSum, pe_checksum(pe));
	free(pe->buffer);
	free(pe);

	return 0;
}
