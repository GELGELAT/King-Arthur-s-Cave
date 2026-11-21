#include "EnemyPath.h"
void clear_visited_tiles(GAME_DATA *game_data)
{
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    char** visited_map = game_data->misc->path->visited_tiles;
    for (int x =0;x<tilesX;x++)
    {
        for (int y =0;y<tilesY;y++)
        {
            visited_map[x][y] = '0';
        }


    }
}



Vector2* path_finding(Allocator* alloc_path,GAME_DATA *game_data,Enemy* enemy,int mode)
{

    clear_visited_tiles(game_data);
    int start_posX = enemy->enemy_position->position_tiles->pos_tiles.x;
    int start_posY = enemy->enemy_position->position_tiles->pos_tiles.y;
    bool find_flag = false;
    
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;

    int new_x,new_y;
    int size = tilesX * tilesY;
    
    int dx[] = {0,1,0,-1};
    int dy[] = {-1,0,1,0};
    
    int head = 0, tail = 0;

    Vector2 **parent_map = game_data->misc->path->parents_position_tiles;
    char** visited_map = game_data->misc->path->visited_tiles;
    char** colid_map = game_data->maps->collision_map->grid;
    Vector2* queue=alloc_alloc(alloc_path,size*sizeof(Vector2));

    queue[0] = (Vector2){start_posX,start_posY};
    visited_map[start_posX][start_posY] = '1';
    tail+=1;
    parent_map[start_posX][start_posY] = (Vector2){-1,-1};

    while(head<tail && !find_flag)
    {
        Vector2 current_tile = queue[head];
        head+=1;
        int current_x = current_tile.x;
        int current_y = current_tile.y;

        visited_map[current_x][current_y] = '1';

        
        for (int i = 0; i<4;i++)
        {
            new_x = current_x + dx[i];
            new_y = current_y + dy[i];
            if (new_x < 0)
            {
                new_x = 0;
            }
            if (new_y < 0)
            {
                new_y = 0;
            }
            if (new_x >= game_data->maps->cells_map->tilesX)
            {
                new_x = game_data->maps->cells_map->tilesX-1;
            }
            if (new_y >= game_data->maps->cells_map->tilesY)
            {
                new_y  = game_data->maps->cells_map->tilesY-1;
            }

            if (colid_map[new_x][new_y] == 'p')
            {
                parent_map[new_x][new_y] = (Vector2){current_x,current_y};
                return restore_path(alloc_path,game_data,enemy,new_x,new_y);
            }
            else if ( mode == 1 &&colid_map[new_x][new_y] != 'w'&& colid_map[new_x][new_y] != 'b' && visited_map[new_x][new_y] != '1')
            {
                
                queue[tail] = (Vector2){new_x,new_y};
                tail+=1;
                parent_map[new_x][new_y] = (Vector2){current_x,current_y};
                visited_map[new_x][new_y] = '1';
            }
            else if (mode == 2 && colid_map[new_x][new_y] != 'w'&& colid_map[new_x][new_y] != 'b' && visited_map[new_x][new_y] != '1' && colid_map[new_x][new_y] != 'm')
            {
                queue[tail] = (Vector2){new_x,new_y};
                tail+=1;
                parent_map[new_x][new_y] = (Vector2){current_x,current_y};
                visited_map[new_x][new_y] = '1';
            }
        }
    }
    return restore_path(alloc_path,game_data,enemy,-1,-1);

}

int amount;
Vector2* restore_path(Allocator* alloc_path, GAME_DATA* game_data, Enemy* enemy, int player_pos_x, int player_pos_y)
{
    Vector2 **parent_map = game_data->misc->path->parents_position_tiles;

    // не нашли
    if (player_pos_x == -1 && player_pos_y == -1)
    {
        Vector2* path_to_player = alloc_alloc(alloc_path, sizeof(Vector2));
        path_to_player[0] = (Vector2){-1, -1};
        enemy->enemy_misc->path_len = 0; 
        return path_to_player;
    }
    int start_x = enemy->enemy_position->position_tiles->pos_tiles.x;
    int start_y = enemy->enemy_position->position_tiles->pos_tiles.y;


    int path_length = 0;
    int cur_x = player_pos_x;
    int cur_y = player_pos_y;

    while (cur_x != -1 && cur_y != -1) 
    {
        if (cur_x ==start_x&& cur_y ==start_y) 
        {
            break; 
        }
        path_length++;
        int next_x = parent_map[cur_x][cur_y].x;
        int next_y = parent_map[cur_x][cur_y].y;
        cur_x = next_x;
        cur_y = next_y;
    }

    enemy->enemy_misc->path_len = path_length;
    if (path_length ==0) 
    {
        Vector2* path_to_player = alloc_alloc(alloc_path, sizeof(Vector2));
        path_to_player[0] = (Vector2){-1, -1};
        return path_to_player;
    }
    Vector2* path_to_player = alloc_alloc(alloc_path, sizeof(Vector2) *path_length);
    cur_x = player_pos_x;
    cur_y = player_pos_y;
//заполняем обратно чтоб первый 
    for (int i= path_length-1;i >= 0;i--)
    {
        path_to_player[i] = (Vector2){(float)cur_x, (float)cur_y};
        
        int next_x = parent_map[cur_x][cur_y].x;
        int next_y = parent_map[cur_x][cur_y].y;
        cur_x = next_x;
        cur_y = next_y;
    }    
    return path_to_player;
}