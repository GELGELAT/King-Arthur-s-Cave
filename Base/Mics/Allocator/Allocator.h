#include <stdio.h>
#ifndef ALLOCATOR_H
#define ALLOCATOR_H


typedef struct allocator
{
    char* memory; //работаем с чар для арефметических действий
    size_t size,used;
}Allocator;



Allocator *create_alloc(size_t initial_size);

Allocator *growing_alloc(Allocator *alloc, size_t right_size);

void *alloc_alloc(Allocator *alloc, size_t right_size);

void destroy_allocator(Allocator *alloc);











#endif


