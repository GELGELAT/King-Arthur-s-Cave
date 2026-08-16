#include "Generators.h"
void generate_cave_cellular_smoothing(GAME_DATA* game_data)
{
    /*
    создаём карту соседних стен
    случайно разбрасываем стены
    смотрим карту соседних стен
    применяем клеточное сглаживание
    */
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    Allocator* alloc_awp = create_alloc(1024*1024);
    adjacent_walls_map* adjacent_walls_map = create_adjacent_walls_map(alloc_awp,tilesX,tilesY);
    random_filling(game_data);
    for (int i = 0; i<3;i++)
    {
        build_adjacent_walls_map(game_data,adjacent_walls_map);
        cellular_smoothing(game_data,adjacent_walls_map);
    }
    destroy_allocator(alloc_awp);
}