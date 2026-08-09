#include "updater.h"

bool step_flag = false;

void GAME_UPDATE(GAME_DATA *game_data,GAME_ANIM* game_anim)
{
    pos_player_updater(game_data,game_anim);
    camera_updater(game_data);
    update_animations(game_anim);
}

void camera_updater(GAME_DATA *game_data)
{
    game_data->misc->camera.offset = (Vector2){ game_data->misc->monitor_size.monitor_width/2.0f, game_data->misc->monitor_size.monitor_height/2.0f };
    game_data->misc->camera.target = game_data->player->player_pos->position_pixels->pos_pixels;;
}

bool pos_player_updater(GAME_DATA *game_data,GAME_ANIM* game_anim)
{
    int dx[] = {0,1,0,-1};
    int dy[] = {-1,0,1,0};
    int step_direction=-1;
    int new_pos_x,new_pos_y;

    char** map = game_data->maps->collision_map->grid;
    CellsMap* cells_map = game_data->maps->cells_map;

    int pixels_step = game_data->maps->cells_map->tileSize;
    if(IsKeyPressed(KEY_W))
    {
        step_direction = 0;
    }
    if(IsKeyPressed(KEY_D))
    {
        step_direction= 1;
    }
    if(IsKeyPressed(KEY_S))
    {
        step_direction =2;
    }
    if(IsKeyPressed(KEY_A))
    {
        step_direction =3;
    }
    
    if (step_direction != -1)
    {
        step_flag = true;
        int old_tile_x = game_data->player->player_pos->position_tiles->pos_tiles.x;
        int old_tile_y = game_data->player->player_pos->position_tiles->pos_tiles.y;

        int new_tile_x = game_data->player->player_pos->position_tiles->pos_tiles.x+dx[step_direction];
        int new_tile_y = game_data->player->player_pos->position_tiles->pos_tiles.y+dy[step_direction];    

        new_pos_x = game_data->player->player_pos->position_pixels->pos_pixels.x+dx[step_direction]*pixels_step;
        new_pos_y = game_data->player->player_pos->position_pixels->pos_pixels.y+dy[step_direction]*pixels_step;

        
        

        if (map[new_tile_x][new_tile_y] == 'f')
        {
            
            delete_from_item_anim_queue(game_data,game_anim,player_ground_check(game_data,new_tile_x,new_tile_y));
            map[old_tile_x][old_tile_y] = 'f';
            map[new_tile_x][new_tile_y] = 'p';

            cells_map->cells[old_tile_x][old_tile_y]->objects[2] = NULL; 

            cells_map->cells[new_tile_x][new_tile_y]->objects[2] = "player"; 

            Vector2 new_pos = {new_pos_x,new_pos_y};
            Vector2 new_tile = {new_tile_x,new_tile_y};
            game_data->player->player_pos->position_pixels->pos_pixels = new_pos;
            game_data->player->player_pos->position_tiles->pos_tiles = new_tile;
            
           

        }
        if ((map[new_tile_x][new_tile_y] == 'w'))
        {
            map[new_tile_x][new_tile_y] = 'f';

            cells_map->cells[new_tile_x][new_tile_y]->objects[0] = textur(floor_textur,-1); 

            
        }
        if ((map[new_tile_x][new_tile_y] == 'b'))
        {
            
        }
        if ((map[new_tile_x][new_tile_y] == 's'))
        {
            
        }
        if ((map[new_tile_x][new_tile_y] == 'm'))
        {
            player_attaks(game_data,game_anim,new_tile_x,new_tile_y);
        }

        if (step_flag)
        {
            after_step(game_data);
        }
        
    }
    
    return true;
}
void after_step(GAME_DATA* game_data)
{
    player_review(game_data);
    enemies_finding(game_data);
    enemies_moving(game_data);
    //printf("%d\n",game_data->player->player_stats->player_characteristics->heal_points);
    //enemy_moving(game_data,game_data->maps->enemy_map->enemy_map[0]);
    //enemy_moving(game_data,game_data->maps->enemy_map->enemy_map[1]);
    step_flag = false;
}