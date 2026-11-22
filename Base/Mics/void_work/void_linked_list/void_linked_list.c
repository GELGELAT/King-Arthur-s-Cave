#include "void_linked_list.h"
Llist* llist_create(void* data)
{
    Llist* lst = malloc(sizeof(Llist));
    if (!lst) return NULL;
    lst->data=data;
    lst->next=NULL;
    return lst;
}
void llist_destroy(Llist* lst,void(*free_fn)(void*data))
{
    Llist* cur_lst = lst;
    Llist* temp;
    while (cur_lst)
    {
        if(cur_lst->data)
        free_fn(cur_lst->data);
        temp = cur_lst;
        cur_lst=cur_lst->next;
        free(temp);
    }
}
Llist* llist_append(Llist* lst, void* data)
{
    if(!lst)
    return llist_create(data);
    Llist* cur_lst = lst;
    while (cur_lst->next)
    {
        cur_lst=cur_lst->next;
    }
    cur_lst->next=llist_create(data);
    return lst;
}

Llist* llist_find_and_delete(Llist* lst, bool (*match)(void* data, void* ctx), void* ctx,void(*free_fn)(void*data))
{
    if(!lst)
    return NULL;
    Llist* cur_lst = lst;
    Llist* temp = NULL;
    while (cur_lst)
    {
        if(match(cur_lst->data,ctx))
        {
            if(!temp)
            {
                temp = cur_lst->next;
                free_fn(cur_lst->data);
                free(cur_lst);
                return temp;
            }
            else
            {
                temp->next=cur_lst->next;
                free_fn(cur_lst->data);
                free(cur_lst);
                return lst;
            }
        }
        else
        {
            temp = cur_lst;
            cur_lst =cur_lst->next;
        }
    }
    return lst;
}

size_t llist_size(Llist* lst)
{
    size_t size =0;
    if (!lst) return size;
    Llist* cur_lst = lst;
    while (cur_lst)
    {
        size++;
        cur_lst=cur_lst->next;
        
    }
    return size;
}
void llist_foreach(Llist* lst, void (*fn)(void* data, void* ctx), void* ctx)
{
    if (!lst) return;
    Llist* cur_lst = lst;
    while (cur_lst)
    {
        fn(cur_lst->data,ctx);
        cur_lst=cur_lst->next;
        
    }
}