#ifndef MAP_H
#define MAP_H
// Includes
#include <stdlib.h>
#include <string.h>
#include "vVector.h"
// Typedefs
typedef struct map{
	vVector *key;
	vVector *value;
	size_t size;
}basic_map;



// Functions

basic_map *mapCreate();
void mapDestroy(basic_map *map);
short mapAdd(basic_map *map, char *key, char *value);
char *mapKeyLookup(basic_map *map, char *key);
char *mapValueLookup(basic_map *map, char *value);
#endif
