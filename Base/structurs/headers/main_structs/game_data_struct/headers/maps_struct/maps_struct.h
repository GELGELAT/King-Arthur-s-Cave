#ifndef MAPS_STRUCT_H
#define MAPS_STRUCT_H

#include "raylib.h"

typedef struct Enemy Enemy;
typedef struct Action Action;

typedef struct ActionsMap
{
    LlistManager* actions_main_queue;
    LlistManager*actions_effects_queue;
    char** tiles_glow;
    int current_state;
}ActionsMap;
typedef struct EnemyMap
{
    Enemy** move_queue;
    int move_queue_amount;
    Enemy** enemy_map;
    int enemy_map_amount;
    int** index_map;
}EnemyMap;
typedef struct ItemTilesPos
{
    Vector2 pos_tiles;

}ItemTilesPos;
typedef struct ItemPixelsPos
{
    Vector2 pos_pixels;

}ItemPixelsPos;
typedef struct ItemPos
{
    ItemTilesPos* position_tiles;
    ItemPixelsPos* position_pixels;


}ItemPos;
typedef struct ItemMain
{
    char* name;
    int index;
    int value;
    int textur_index;
    int pos_index;
}ItemMain;
typedef struct Item
{
    ItemMain* item_main;
    ItemPos* item_position;
    Allocator* alloc;
}Item;

typedef struct ItemsMap
{
    int** index_map;
    Item** items_map;
    int items_map_amount;
}ItemsMap;
typedef struct FogMap
{
    char** grid;
    int tilesX;
    int tilesY;
}FogMap;
typedef struct CollisionMap
{
    char** grid;
    int tilesX;
    int tilesY;
}CollisionMap;
typedef struct Cell
{
    char** objects;
    Vector2 positin;
    int amount_objects;
}Cell;
typedef struct CellsMap
{
    Cell*** cells;
    int tilesX;
    int tilesY;
    int tileSize;
}CellsMap;
typedef struct Maps
{
    CellsMap* cells_map;
    CollisionMap* collision_map;
    FogMap* fog_map;
    ItemsMap* items_map;
    EnemyMap* enemy_map;
    ActionsMap* actins_map;
}Maps;
#endif