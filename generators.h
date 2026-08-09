#ifndef GENERATORS_H
#define GENERATORS_H
#include "structurs.h"
#include <stdlib.h> 
#include "misc.h"

typedef struct adjacent_walls_map
{
    int** grid;
}adjacent_walls_map;

adjacent_walls_map *create_adjacent_walls_map(Allocator *alloc, int tilesX, int tilesY);

void build_adjacent_walls_map(GAME_DATA *game_data, adjacent_walls_map *adjacent_walls_map);

void print_adjacent_walls_map(GAME_DATA *game_data, adjacent_walls_map *adjacent_walls_map);

void random_filling(GAME_DATA *game_data);

void cellular_smoothing(GAME_DATA *game_data, adjacent_walls_map *adjacent_walls_map);

void generate_cave_cellular_smoothing(GAME_DATA *game_data);

#endif

