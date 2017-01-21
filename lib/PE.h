#ifndef PE_H
#define PE_H
// Includes
#include <inttypes.h>
#include <sys/types.h>
#include <string.h>

#include "DOS.h"
// Defines
#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES 16
#define IMAGE_SIZEOF_SHORT_NAME 8

// Structures
typedef struct _IMAGE_DATA_DIRECTORY{
	uint32_t VirtualAddress;
	uint32_t Size;
	}_IMAGE_DATA_DIRECTORY;

typedef struct IMAGE_OPTIONAL_HEADER{
	  uint16_t                magic;
	  unsigned char           majorLinkerVersion;
	  unsigned char           minorLinkerVersion;
	  uint32_t                sizeOfCode;
	  uint32_t                sizeOfInitializedData;
	  uint32_t                sizeOfUninitializedData;
	  uint32_t                addressOfEntryPoint;
	  uint32_t                baseOfCode;
	  uint32_t                baseOfData;
	  uint32_t                imageBase;
	  uint32_t                sectionAlignment;
	  uint32_t                fileAlignment;
	  uint16_t                majorOperatingSystemVersion;
	  uint16_t                minorOperatingSystemVersion;
	  uint16_t                majorImageVersion;
	  uint16_t                minorImageVersion;
	  uint16_t                majorSubsystemVersion;
	  uint16_t                minorSubsystemVersion;
	  uint32_t                win32VersionValue;
	  uint32_t                sizeOfImage;
	  uint32_t                sizeOfHeaders;
	  uint32_t                checkSum;
	  uint16_t                subsystem;
	  uint16_t                dllCharacteristics;
	  uint32_t                sizeOfStackReserve;
	  uint32_t                sizeOfStackCommit;
	  uint32_t                sizeOfHeapReserve;
	  uint32_t                sizeOfHeapCommit;
	  uint32_t                loaderFlags;
	  uint32_t                numberOfRvaAndSizes;
	  _IMAGE_DATA_DIRECTORY dataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
} _IMAGE_OPTIONAL_HEADER;

typedef struct _IMAGE_FILE_HEADER _IMAGE_FILE_HEADER;
typedef struct __IMAGE_OPTIONAL_HEADER __IMAGE_OPTIONAL_HEADER;


typedef struct _IMAGE_FILE_HEADER{
	uint16_t  machine;
     uint16_t  numberOfSections;
     uint32_t timeDateStamp;
     uint32_t pointerToSymbolTable;
     uint32_t numberOfSymbols;
     uint16_t  sizeOfOptionalHeader;
     uint16_t  characteristics;
} IMAGE_FILE_HEADER;


typedef struct _IMAGE_NT_HEADER{
	uint32_t signature;
	_IMAGE_FILE_HEADER image_file_header;
	_IMAGE_OPTIONAL_HEADER image_optional_header;
} IMAGE_NT_HEADER;


typedef struct _IMAGE_SECTION_HEADER {
  	  unsigned char  name[IMAGE_SIZEOF_SHORT_NAME];
  	   union {
		    uint32_t physicalAddress;
		    uint32_t virtualSize;
	  } Misc;
	  uint32_t virtualAddress;
	  uint32_t sizeOfRawData;
	  uint32_t pointerToRawData;
	  uint32_t pointerToRelocations;
	  uint32_t pointerToLinenumbers;
	  uint16_t numberOfRelocations;
	  uint16_t numberOfLinenumbers;
	  uint32_t characteristics;
} IMAGE_SECTION_HEADER;

typedef struct _PE_STRUCTURE{
	struct _IMAGE_DOS_HEADER *image_dos_header;
	struct _IMAGE_NT_HEADER *image_nt_header;
	struct _IMAGE_SECTION_HEADER *image_section_header;
	unsigned char *buffer;
	off_t size;
}PE_STRUCTURE;



// Functions
uint32_t pe_checksum(PE_STRUCTURE *pe); //Based on http://forum.sysinternals.com/optional-header-checksum-calculation_topic24214.html


#endif
