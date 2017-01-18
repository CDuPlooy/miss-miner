#ifndef CUSTOM_IO_GUARD
#define CUSTOM_IO_GUARD
//#includes
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

//typedefs
typedef unsigned char uchar;
typedef struct cf{
	uchar *buffer;
	off_t size;
	}compound_file;

//#defines
#define CIO_BLOCK_SIZE 4086
#define CIOE_OK 0
#define CIOE_FILE_CREATION 1
#define CIOE_FILE_WRITE 2

//Functions
compound_file *fileToBuffer( char *filename );
short bufferToFile( uchar *buffer , off_t size , char *filename);
short compoundFileToFile( compound_file *cf , char *filename );
void destroyCompoundFile( compound_file *cf );
#endif
