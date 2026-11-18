#ifndef ACTION_STRUCT_H
#define ACTION_STRUCT_H
#include "Allocator.h"
#include "raylib.h"


typedef struct ActionPosInfo
{
    Vector2* position_pixels; //указатель на позицию обьекта
    Vector2 old_tile; //страый тайл
    Vector2 new_tile; //новый тайл

}ActionPos;
typedef struct ActionMainInfo
{
    int* movement_type; //тип движения 
    int during_type; //когда должно произойти
    int* action_type; //что должно произойти
}ActionMainInfo;
typedef struct ActionObjectInfo
{
    int object_type; //тип обьекта который это делает
    int object_index; //индекс обьекта на карте
    int affected_type;
    int affected_index;
}ActionObjectInfo;
typedef struct ActionMiscInfo
{
    float amount_full_moves;
    float current_fill; //типо таймера
    float max_fill; //макс заполнение таймера
    float speed; //скорость движения
    int current_state; //текущее состояние

}ActionMiscInfo;
typedef struct ActionQueueInfo
{
    Action* beginning_action;
    Action* ending_action;

}ActionQueueInfo;
typedef struct Action
{
    ActionMainInfo* main;
    ActionPos* pos;
    ActionObjectInfo* object;
    ActionMiscInfo* misc;
    int flow;
    ActionQueueInfo* queue;
    Allocator* alloc;
    
    
}Action;

#endif