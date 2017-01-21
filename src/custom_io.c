#include "../lib/custom_io.h"

compound_file *fileToBuffer( const char *filename ){
	compound_file *cf = malloc(sizeof(compound_file));
	if(!cf)
		return NULL;

	struct stat stStat;
	if(stat(filename, &stStat) != 0)
		goto cleanup_fileToBuffer_compoundFile;

	cf->size = stStat.st_size;
	uchar *buffer = malloc(stStat.st_size * sizeof(uchar));
	if(!buffer)
		goto cleanup_fileToBuffer_compoundFile;

	FILE *src = fopen(filename, "rb"); // Open the file in read mode - binary.
	if(!src)
		goto cleanup_fileToBuffer_buffer;


	//Read the entire file into the buffer.

	if(fread(buffer, 1, stStat.st_size, src) != stStat.st_size || ferror(src) ) //This is ugly , i'll optimise the block sizes at a later time.
		goto cleanup_fileToBuffer_buffer;

	fclose(src);
	cf->buffer = buffer;
	return cf;

	//Recovery
	cleanup_fileToBuffer_buffer:
		free(buffer);
		if(src)
			fclose(src);
	cleanup_fileToBuffer_compoundFile:
		free(cf);
		return NULL;
}

short bufferToFile( uchar *buffer , off_t size , const char *filename){
	FILE *dst = fopen(filename,"wb");
	if(!dst)
		return CIOE_FILE_CREATION;

	if(fwrite(buffer,sizeof(unsigned char),size,dst) != size){
		fclose(dst);
		return CIOE_FILE_WRITE;
	}

	fclose(dst);
	return CIOE_OK;
}

short compoundFileToFile( compound_file *cf , const char *filename ){
		return bufferToFile(cf->buffer , cf->size , filename);
}

void destroyCompoundFile( compound_file *cf ){
	for(off_t i = 0 ; i < cf->size ; i++)
		cf->buffer[i] = 0;
	free(cf->buffer);
	cf->buffer = NULL;
	cf->size = 0;
	free(cf);
	cf = NULL;
}
