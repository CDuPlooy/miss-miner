#include "../lib/inject.h"


// Opaque types , Only this module needs to see them.

#define INJECT_STATE_NONE 0
#define INJECT_STATE_PARSING 1

cavelist *getCaves( compound_file *cf ){	//TODO: Return a structure for error checking.
	cavelist *cl = malloc(sizeof(cavelist));
	if(!cl)
		return NULL;

	cavelist *current_cl = cl;

	short injectState = INJECT_STATE_NONE;
	off_t i = 0;
	for(; i < cf->size ; i++ ){ //Loops through the buffer
		if( cf->buffer[i] == 0 && injectState == INJECT_STATE_NONE ){
			current_cl->start = i;
			injectState = INJECT_STATE_PARSING;
		}
		else if( cf->buffer[i] != 0 && injectState == INJECT_STATE_PARSING ){
			current_cl->end = i;
			//Allocate a new structure.
			current_cl->next = malloc(sizeof(cavelist));
			if(!current_cl->next)
				break;
			current_cl = current_cl->next;
			injectState = INJECT_STATE_NONE;
		}
	}
	if(injectState == INJECT_STATE_PARSING)
		current_cl->end = i;
	current_cl->next = NULL; //Might be redundant if used outside of the upper if.

	return cl;
}
void freeCaves(cavelist *cl){
	cavelist *current = cl;
	while(current->next != NULL){
		cavelist *old = current;
		current = current->next;
		free(old);
	}
	free(current);
}
cavelist *checkCaveList( cavelist *cl , size_t size ){
	cavelist *current = cl;
	while(current != NULL){
		if(current->end - current->start > size )
			return current;
		current = current->next;
	}
	if(current->end - current->start > size )
		return current;
	return NULL;
}

short injectShellcode(cavelist *cl , compound_file *cf_res , compound_file *cf_shellcode , inject_data *id){
	cavelist *cave = checkCaveList(cl,cf_shellcode->size + 2); // As to avoid corrupting NULL terminated strings.
	if(!cave)
		return 0;
	id->offset = (off_t)(cf_res->buffer + cave->start + 2);
	memcpy((void *)id->offset ,cf_shellcode->buffer,cf_shellcode->size);
	return 1;
}
