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

basic_map *mapCreate_fromParams(int argc , char **argv){ // TODO: This should be written differently.
	if(argc <= 1)
		return NULL;

	basic_map *map = mapCreate();
	if(!map)
		return NULL;

	// We want to loop through the command line parameters mapping options.
	// Any option which does not directly map to state is mapped to (NULL)

	for(size_t i = 1 ; i < argc ; i+=2){
		if(argv[i][0] == '-'){
			if(i + 1 < argc){
				if(argv[i+1][0] != '-'){
					mapAdd(map, argv[i], argv[i+1]);
				}
				else{
					mapAdd(map, argv[i], "(null)");
					i--;
				}
			}
		}
	}
	return map;
}


short _mapKeyExist(basic_map *map, char *key){
	for( size_t i = 0 ; i < map->size ; i++ )
		if(!strcmp(vVector_at(map->key, i),key))
			return 1;
	return 0;
}

short _mapValueExist(basic_map *map, char *value){
	for( size_t i = 0 ; i < map->size ; i++ )
		if(!strcmp(vVector_at(map->value, i),value))
			return 1;
	return 0;
}
