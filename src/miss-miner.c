#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../lib/custom_io.h"
#include "../lib/inject.h"

int main(int argc , char **argv){
	compound_file *cf = fileToBuffer(argv[0]);
	if(!cf)
		return 1;
	cavelist *cl = getCaves(cf);
	if(!cl)
		return 2;
	cavelist *current = cl;
	while(current != NULL){
		printf("Cave:\nStart\t%zu\nEnd\t%zu\n",current->start,current->end);
		current = current->next;
	}
	// freeCaves(cl);
	destroyCompoundFile(cf);
	return 0;
}
