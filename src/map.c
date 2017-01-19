#include "../lib/map.h"

basic_map *mapCreate(){
	basic_map *map = malloc(sizeof(basic_map));
	map->size = 0;
	if(!map)
		return NULL;

	map->key = vVector_init();
	if(!map->key)
		return NULL;
	map->value = vVector_init();
	if(!map->value){
		free(map->key);
		free(map);
		return NULL;
	}

	return map;
}

void mapDestroy(basic_map *map){
	vVector_destroy(map->key);
	vVector_destroy(map->value);
	free(map);
}

short mapAdd(basic_map *map, char *key, char *value){
	if(vVector_pushback(map->key,key))
		return 0;
	if(vVector_pushback(map->value,value))
		return 0;

	map->size++;
	return 1;
}

char *mapKeyLookup(basic_map *map, char *key){
	for( size_t i = 0 ; i < map->size; i++ )
		if(!strcmp(vVector_at(map->key, i),key))
			return vVector_at(map->value, i);
	return NULL;
}

char *mapValueLookup(basic_map *map, char *value){
	for( size_t i = 0 ; i < map->size ; i++ )
		if(!strcmp(vVector_at(map->value, i),value))
			return vVector_at(map->key, i);
	return NULL;
}
