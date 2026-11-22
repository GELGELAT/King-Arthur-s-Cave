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
    Llist*previous;
}Llist;

typedef struct {
    Llist* head;
    Llist* tail;
    size_t size;
} LlistManager;



Llist *llist_create(void *data);

LlistManager *llist_manager_create();

LlistManager *llist_append(LlistManager *lstm, void *data);

void llist_delete(Llist *lst, void (*del_data)(void *data));
Llist *llist_find_and_delete(Llist *lst, bool (*match)(void *data, void *ctx), void *ctx, void (*free_fn)(void *data));
size_t llist_size(Llist *lst);
void llist_check_and_delete_or_activate(LlistManager *list_manager, bool (*match_fn)(void *ctx), void (*delete_fn)(void *ctx), void (*activate_fn)(void *ctx, void *ctx1, void *ctx2), void *ctx1, void *ctx2);
Llist *llist_get_last(Llist *lst);



#endif
