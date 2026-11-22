#ifndef VOID_LINKED_LIST_H
#define VOID_LINKED_LIST_H
#include "Allocator.h"
#include <stdlib.h>
#include <stdbool.h>
typedef struct Llist Llist;

typedef struct Llist
{
    void* data;
    Llist* next;
}Llist;



Llist *llist_create(void *data);

void llist_destroy(Llist *lst, void (*free_fn)(void *data));

Llist *llist_append(Llist *lst, void *data);

Llist *llist_find_and_delete(Llist *lst, bool (*match)(void *data, void *ctx), void *ctx, void (*free_fn)(void *data));

size_t llist_size(Llist *lst);

void llist_foreach(Llist *lst, void (*fn)(void *data, void *ctx), void *ctx);
#endif
