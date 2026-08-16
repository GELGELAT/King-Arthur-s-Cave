#include "EnemyLogic.h"


void enemies_finding(GAME_DATA* game_data)
{
    char** col_map = game_data->maps->collision_map->grid;
    int** id_map = game_data->maps->enemy_map->index_map;
    Enemy** enemy_map = game_data->maps->enemy_map->enemy_map;

    Enemy** move_map = game_data->maps->enemy_map->move_queue;


    CellsMap* obj_map = game_data->maps->cells_map;
    CellsMap *map = game_data->maps->cells_map;

    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;

    Vector2 player_pos = game_data->player->player_pos->position_tiles->pos_tiles;

    int player_pos_x = player_pos.x;
    int player_pos_y = player_pos.y;


    int start_pos_x = player_pos.x -4;
    int start_pos_y = player_pos.y -4;

    for (int dx =0;dx<9;dx++)
    {
        for (int dy =0;dy<9;dy++)
        {
            int nx = player_pos_x + dx - 4;
            int ny = player_pos_y + dy - 4;
            
            if (nx < 0 || nx >= tilesX || ny < 0 || ny >= tilesY) 
            {
                continue; 
            }
            int current_pos_x = start_pos_x+dx;
            int current_pos_y = start_pos_y+dy;
            if ( dx == 4 && dy == 4)
            {
            }
            else
            {
                if (col_map[current_pos_x][current_pos_y]=='s')
                {
                    col_map[current_pos_x][current_pos_y] = enemy_activation(col_map,current_pos_x,current_pos_y,dx,dy);
                    if (col_map[current_pos_x][current_pos_y]=='m')
                    {
                        int current_id = id_map[current_pos_x][current_pos_y];

                        append_enemy_to_arr(game_data,enemy_map[current_id],2);

                    }
                }
                
                
            }

        }
    }
}


char enemy_activation(char** col_map,int current_pos_x,int current_pos_y,int relative_pos_x,int relative_pos_y)
{
    Vector2 first_increment = parents_visen_map[relative_pos_x][relative_pos_y][0];
    int first_increment_x = first_increment.x;
    int first_increment_y = first_increment.y;

    Vector2 second_increment = parents_visen_map[relative_pos_x][relative_pos_y][1];
    int second_increment_x = second_increment.x;
    int second_increment_y = second_increment.y;

    Vector2 queue[10000][2];
    int head = 0;
    int tail = 0;

    Vector2 first_absolut_pos = {current_pos_x+first_increment_x,current_pos_y+first_increment_y};
    Vector2 first_relative_pos = {relative_pos_x +first_increment_x,relative_pos_y+first_increment_y};

    queue[0][0] = first_absolut_pos;
    queue[0][1] = first_relative_pos;
    tail+=1;
    if (second_increment_x == 0&&second_increment_y==0)
    {

    }
    else
    {
        Vector2 second_absolut_pos = {current_pos_x+second_increment_x,current_pos_y+second_increment_y};
        Vector2 second_relative_pos = {relative_pos_x +second_increment_x,relative_pos_y+second_increment_y};
        queue[1][0] = second_absolut_pos;
        queue[1][1] = second_relative_pos;
        tail+=1;
    }
    while (head<tail)
    {
        Vector2 current_absolut_pos = queue[head][0];
        Vector2 current_relative_pos = queue[head][1];
        head+=1;
        if (col_map[(int)current_absolut_pos.x][(int)current_absolut_pos.y]=='w' )
        {

            return 's';
        }
        Vector2 current_first_increment = parents_visen_map[(int)current_relative_pos.x][(int)current_relative_pos.y][0];
        int current_first_increment_x = current_first_increment.x;
        int current_first_increment_y = current_first_increment.y;
        if (current_first_increment_x == 0 && current_first_increment_y ==0)
        {
            break;
        }
        else
        {
            Vector2 new_absolut_pos = {(int)current_absolut_pos.x+current_first_increment_x,(int)current_absolut_pos.y+current_first_increment_y};
            Vector2 new_relative_pos = {(int)current_relative_pos.x +current_first_increment_x,(int)current_relative_pos.y+current_first_increment_y};
            queue[tail][0] = new_absolut_pos;
            queue[tail][1] = new_relative_pos;
            tail+=1;
        }

        Vector2 current_second_increment = parents_visen_map[(int)current_relative_pos.x][(int)current_relative_pos.y][1];
        int current_second_increment_x = current_second_increment.x;
        int current_second_increment_y = current_second_increment.y;
        if (current_second_increment_x == 0 && current_second_increment_y ==0)
        {
        }
        else
        { 
            
            Vector2 new_absolut_pos = {(int)current_absolut_pos.x+current_second_increment_x,(int)current_absolut_pos.y+current_second_increment_y};
            Vector2 new_relative_pos = {(int)current_relative_pos.x +current_second_increment_x,(int)current_relative_pos.y+current_second_increment_y};
            queue[tail][0] = new_absolut_pos;
            queue[tail][1] = new_relative_pos;
            tail+=1;
        }
    }
    return 'm';
}