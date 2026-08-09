#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocator.h"



Allocator* create_alloc(size_t initial_size)
{
    Allocator* alloc = malloc(sizeof(Allocator));
    if (alloc == NULL)
    {
        printf("Error alloc");
        return NULL;
    }
    alloc->memory = malloc(initial_size);
    if (alloc->memory == NULL)
    {
        printf("Error alloc memory");
        free(alloc);
        return NULL;
    }
    alloc->size = initial_size;
    alloc->used = 0;
    return alloc;
}
Allocator* growing_alloc(Allocator* alloc, size_t right_size)
{
    if (alloc == NULL) return NULL;
    size_t old_size;
    size_t new_size = alloc->size;
    while (new_size < alloc->used+right_size)
    {
        old_size = new_size;
        new_size = (size_t)(new_size * 2);
        if (new_size < old_size)
        {
            new_size= old_size + right_size;
            break;
        }
    }
    char* new_link = realloc(alloc->memory,new_size);
    if (new_link == NULL)
    {
        printf("erroe grow memory");
        return NULL;
    }
    alloc->memory = new_link;
    alloc->size = new_size;
    return(alloc);
}
void* alloc_alloc(Allocator* alloc, size_t right_size)
{
    if (alloc->size< alloc->used+right_size)
    {
        if (growing_alloc(alloc, right_size) ==NULL)
        {
            printf("erroe alloc");
            return NULL;
        }
    }
    void* link = alloc->memory + alloc->used;
    alloc->used += right_size;
    return link;
}

void destroy_allocator(Allocator* alloc) 
{
    if (alloc == NULL) return;
    free(alloc->memory);
    free(alloc);
}

