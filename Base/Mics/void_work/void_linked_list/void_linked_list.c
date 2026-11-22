#include "void_linked_list.h"
Llist* llist_create(void* data)
{
    Llist* lst = malloc(sizeof(Llist));
    if (!lst) return NULL;
    lst->data=data;
    lst->next=NULL;
    lst->previous=NULL;
    return lst;
}
LlistManager* llist_manager_create()
{
    LlistManager* lstm = malloc(sizeof(LlistManager));
    if(!lstm)return NULL;
    lstm->head=llist_create(NULL);
    lstm->tail = llist_create(NULL);
    lstm->head->next=lstm->tail;
    lstm->head->previous = NULL;
    lstm->tail->previous = lstm->head;
    lstm->size=0;
    return lstm;

}
LlistManager* llist_append(LlistManager* lstm, void* data)
{
    Llist* nlst=llist_create(data);
    
    Llist* last_lst=lstm->tail->previous;
    last_lst->next=nlst;
    nlst->previous=last_lst;
    nlst->next=lstm->tail;
    lstm->tail->previous=nlst;
    lstm->size++;
    
    return lstm;
}
void llist_delete(Llist* lst,void(*del_data)(void* data))
{
    Llist* prev = lst->previous;
    Llist* next = lst->next;
    prev->next=next;
    next->previous=prev;
    del_data(lst->data);
    free(lst);

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


void llist_check_and_delete_or_activate(LlistManager* list_manager
    ,bool (*match_fn)(void* ctx)
    ,void (*delete_fn)(void* ctx)
    ,void (*activate_fn)(void* ctx, void* ctx1,void* ctx2), void* ctx1,void* ctx2)
{
    Llist* start = list_manager->head->next;
    Llist* end = list_manager->tail;
    Llist* current=start;
    while (current!=end)
    {
        void* data = current->data;
        Llist* temp = current;
        current = current->next;
        if(match_fn(data))
        {
            activate_fn(data,ctx1,ctx2);
        }
        else
        {
            llist_delete(temp,delete_fn);
            list_manager->size--;
        }
    }
    
}
Llist* llist_get_last(Llist* lst)
{
    Llist* cur_lst = lst;
    while (cur_lst->next)
    {
        cur_lst=cur_lst->next;
        
    }
    return cur_lst;
}