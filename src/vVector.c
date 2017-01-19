#include <stdlib.h>
#include <string.h>
#include "../lib/vVector.h"

vVector *vVector_init(){
	vVector *new_vector = malloc(sizeof(vVector));
	if( !new_vector )
		goto cleanup;

	new_vector->_basePointerSize = VVECTOR_CHUNK_SIZE;
	new_vector->data = malloc(sizeof(void *) * VVECTOR_CHUNK_SIZE);
	if( !new_vector->data )
		goto cleanup_two;

	for(size_t i = 0 ; i < VVECTOR_CHUNK_SIZE ; i++ )
		new_vector->data[i] = NULL;
	new_vector->size = 0;

	return new_vector;

	cleanup_two:
		free(new_vector);
	cleanup:
		return NULL;
}

short vVector_grow(vVector *vector){
	void **back = vector->data;
	vector->data = realloc(vector->data, vector->_basePointerSize * 2 * sizeof(void *));
	if( !vector->data ){
		vector->data = back;
		return 1;
	}
	for( size_t i = vector->_basePointerSize  ; i < vector->_basePointerSize * 2 ; i++ )
		vector->data[i] = NULL;
	vector->_basePointerSize *= 2;
	return 0;
}

short vVector_pushback(vVector *vector , void *target){
	if(vector->size == vector->_basePointerSize){
              short ret = vVector_grow(vector);
              if( ret != 0 )
                    return ret;
        }

	  vector->data[vector->size] = target;
	  vector->size++;
	  return 0;
}

void vVector_popback(vVector *vector , short delete){
	if( vector->size > 0){
		void *tmp = vector->data[vector->size];
		vector->data[vector->size] = NULL;
		vector->size--;
		if( delete )
			free(tmp);
	}
}

void vVector_destroy(vVector *vector){
	size_t i;
	for(i = 0 ; i < vector->_basePointerSize ; i++)
		vector->data[i] = NULL;

	free(vector->data);
	vector->data = NULL;

	free(vector);
	vector = NULL;

	return;
}

void *vVector_at(vVector *vector , size_t n){
	if(vector->size < n)
		return NULL;
	return vector->data[n];
}
