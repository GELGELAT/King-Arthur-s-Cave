#ifndef ALLOCATOR_STRUCT_H
#define ALLOCATOR_STRUCT_H
#include "Allocator.h"

typedef struct Allocators
{
    Allocator *alloc_data;
    Allocator *alloc_misc;

} Allocators;
#endif