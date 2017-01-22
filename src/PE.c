#include "../lib/PE.h"

/*
"Sum the entire image file, excluding the CheckSum field in the optional
 * header, as an array of USHORTs, allowing any carry above 16 bits to be added
 * back onto the low 16 bits. Then add the file size to get a 32-bit value."
Code was taken and adapted from  https://github.com/FreeBSDFoundation/uefisign/blob/master/pe.c
*/
uint32_t pe_checksum(PE_STRUCTURE *pe){
	uint32_t cSum = 0;
	uint16_t tmp = 0;
	uint32_t peOffset = (void *)&(pe->image_nt_header->image_optional_header.checkSum) - (void *)pe->buffer;

	for(int i = 0 ; i + sizeof(tmp) < pe->size ; i += 2 ){
		if( i == peOffset || i == peOffset + 2 )
			tmp = 0;
		else{
			memcpy(&tmp, pe->buffer + i, sizeof(tmp));
		}

		cSum += tmp;
		cSum += cSum >> 16;
		cSum &= 0xffff;
	}

	cSum += cSum >> 16;
	cSum &= 0xffff;

	cSum += pe->size;
	return (cSum);
}

struct _IMAGE_SECTION_HEADER **pe_sections(PE_STRUCTURE *pe){
	struct _IMAGE_SECTION_HEADER **sections = malloc(sizeof(struct IMAGE_SECTION_HEADER *) * pe->image_nt_header->image_file_header.numberOfSections);
	if(!sections)
		return NULL;

		IMAGE_SECTION_HEADER *section = pe->image_section_header;
		for(size_t i = 0 ; i < pe->image_nt_header->image_file_header.numberOfSections ;i++ ){
			sections[i] = ( struct _IMAGE_SECTION_HEADER *)section;
			section = (struct _IMAGE_SECTION_HEADER *)(section->name + sizeof(struct _IMAGE_SECTION_HEADER));
		}

	return sections;
}

void *pe_map_to_buffer(PE_STRUCTURE *pe, void *addr){
	return (void *)((void *)addr - (void *)pe->buffer);
}

off_t pe_map_to_file_offset(PE_STRUCTURE *pe , void *addr){
	return (addr - (void*)(pe->buffer));
}

off_t pe_map_buffer_to_memoryEx(PE_STRUCTURE *pe, void *addr){
	return pe->image_nt_header->image_optional_header.imageBase + pe_map_to_file_offset(pe, addr);
}
