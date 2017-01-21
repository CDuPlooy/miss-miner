#include "../lib/inject.h"


// Opaque types , Only this module needs to see them.

#define INJECT_STATE_NONE 0
#define INJECT_STATE_PARSING 1

short injectData(struct _PE_STRUCTURE *pe , compound_file *shellcode){
	return 1;
}
