#include "CaveGenerator.h"
adjacent_walls_map* create_adjacent_walls_map(Allocator* alloc,int tilesX,int tilesY)
{
    adjacent_walls_map* adjacent_walls_map = alloc_alloc(alloc,sizeof(adjacent_walls_map));
    adjacent_walls_map->grid = (int**)alloc_alloc(alloc,tilesX*sizeof(int*));
    for(int x = 0;x<tilesX;x++)
    {
        adjacent_walls_map->grid[x] = alloc_alloc(alloc,tilesY*sizeof(int));

    }
    return adjacent_walls_map;
}

void build_adjacent_walls_map(GAME_DATA* game_data,adjacent_walls_map* adjacent_walls_map)
{
    int dx[] = {0,1,1,1,0,-1,-1,-1};
    int dy[] = {-1,-1,0,1,1,1,0,-1};
    char** map =game_data->maps->collision_map->grid;
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    for (int x = 0;x<tilesX;x++)
    {
        for (int y = 0; y< tilesY;y++)
        {
            if (x == 0 || y == 0 || x == tilesX - 1 || y == tilesY - 1)
            {
                
            }
            else
            {
                int walls_count = 0;
                for (int i = 0;i<8;i++)
                {
                    if (map[x+dx[i]][y+dy[i]] == 'w')
                    {
                        walls_count+=1;
                    }

                }
                adjacent_walls_map->grid[x][y]=walls_count;
                
            }
        }
    }
}
void print_adjacent_walls_map(GAME_DATA* game_data,adjacent_walls_map* adjacent_walls_map)
{
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    for (int x = 0;x<tilesX;x++)
    {
        for (int y = 0; y< tilesY;y++)
        {
            printf("%d",adjacent_walls_map->grid[y][x]);

        }
        printf("\n");
    }
}

void random_filling(GAME_DATA *game_data)
{
    float percentage_fill = 0.4;
    float percentage_filling = 0.4;

    int counter_fill = 0;

    char **map = game_data->maps->collision_map->grid;

    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;

    int map_size = tilesX * tilesY;

    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            if (counter_fill < map_size * percentage_fill)
            {
                if (x == 0 || y == 0 || x == tilesX - 1 || y == tilesY - 1)
                {
                    map[x][y] = 'w';
                }
                else
                {
                    if (rand_num_within(1, 10) <= (int)(percentage_filling * 10))
                    {
                        map[x][y] = 'w';
                        counter_fill += 1;
                    }
                }
            }
        }
    }
}

void cellular_smoothing(GAME_DATA* game_data,adjacent_walls_map* adjacent_walls_map)
{
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    int death_limit = 2;
    int birth_limit = 4;
    
    char** map = game_data->maps->collision_map->grid;

    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            if (x == 0 || y == 0 || x == tilesX - 1 || y == tilesY - 1)
            {
                map[x][y] = 'b';
            }
            else if (map[x][y] == 'w' && adjacent_walls_map->grid[x][y] <=death_limit)
            {
                map[x][y] = 'f';
            }
            else if (map[x][y] == 'f' && adjacent_walls_map->grid[x][y] >=birth_limit)
            {
                map[x][y] = 'w';
            }
        }
    }
}




