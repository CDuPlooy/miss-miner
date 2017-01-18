#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../lib/custom_io.h"

int main(int argc , char **argv){
	compound_file *cf = fileToBuffer(argv[0]);
	compoundFileToFile(cf,"test.out");
	free(cf->buffer);
	free(cf);
	return 0;
}
