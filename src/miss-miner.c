#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../lib/custom_io.h"
#include "../lib/inject.h"
#include "../lib/map.h"

char *target;
char *shellcode;
char *output;

int main(int argc , char **argv){

	basic_map *map = mapCreate();
	printf("%i\n" , mapAdd(map, "key", argv[1]));
	printf("%s\n",mapKeyLookup(map, "key"));
	mapDestroy(map);
	return 2;
	compound_file *cf = fileToBuffer("test.bin");
	if(!cf)
		return 1;
	cavelist *cl = getCaves(cf);
	if(!cl)
		return 2;

	compound_file *cf_shell = fileToBuffer("test.shell");
	if(!cf_shell)
		return 3;

	if(!injectShellcode(cl , cf , cf_shell)){
		puts("Could not inject the shellcode!");
		return 4;
	}

	printf("Write Result %i\n",compoundFileToFile(cf,"test.injected.bin"));

	freeCaves(cl);
	destroyCompoundFile(cf);
	return 0;
}
