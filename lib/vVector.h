#ifndef VVECTOR_H
#define VVECTOR_H
//Includes
#include <stddef.h>

//defines
#define VVECTOR_CHUNK_SIZE 250

//structures
typedef struct vVector{
size_t _basePointerSize;
size_t size;
void **data;
}vVector , V_VECTOR;

//functions
vVector *vVector_init();
void vVector_destroy(vVector *vector);
short vVector_grow(vVector *vector);
short vVector_pushback(vVector *vector , void *target);
void vVector_popback(vVector *vector , short delete);
void *vVector_at(vVector *vector, size_t n);


#endif
