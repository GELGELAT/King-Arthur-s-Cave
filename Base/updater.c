#include "updater.h"

#define time_between_actions 15
#define first_state 1
#define second_state 2
#define third_state 2
#define DIE_TIME 35
bool step_flag = false;

void GAME_UPDATE(GAME_DATA *game_data,GAME_ANIM* game_anim)
{
    pos_player_updater(game_data,game_anim);
    camera_updater(game_data);
    main_action_map_updater(game_data,game_anim);
    update_items_animations(game_anim);
    update_ememies_animations(game_anim);
    update_player_animations(game_anim);
}

void camera_updater(GAME_DATA *game_data)
{
    game_data->misc->camera.offset = (Vector2){ game_data->misc->monitor_size.monitor_width/2.0f, game_data->misc->monitor_size.monitor_height/2.0f };
    game_data->misc->camera.target = game_data->player->player_pos->position_pixels->pos_pixels;;
}
bool pos_player_updater(GAME_DATA *game_data,GAME_ANIM* game_anim)
{
    int action_flag = -1;
    int dx[] = {0,1,0,-1,0};
    int dy[] = {-1,0,1,0,0};
    int step_direction=-1;
    int new_pos_x,new_pos_y;
    //if (action_counter >time_between_actions)
    //pr_int(game_data->maps->pos_map->amount_actions);
    while (game_data->maps->actins_map->amount_actions_main_queue ==0)
    {
        
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
        if(IsKeyPressed(KEY_SPACE))
        {
            step_direction =4;
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
                Vector2 old_tile = {old_tile_x,old_tile_y};
                //game_data->player->player_pos->position_pixels->pos_pixels = new_pos;
                game_data->player->player_pos->position_tiles->pos_tiles = new_tile;
                Action* moving = create_action(game_data->allocators->alloc_data,MAIN_MAP,PLAYER,-1,FORWARD,MOVING,END,-1,-1,
                &game_data->player->player_pos->position_pixels->pos_pixels,old_tile,new_tile,1,5);
                append_action_to_actions_map(game_data,moving);
                
                
            

            }
            if ((map[new_tile_x][new_tile_y] == 'w'))
            {
                Vector2 new_tile = {new_tile_x,new_tile_y};
                Vector2 old_tile = {old_tile_x,old_tile_y};
                Action* mine = create_action(game_data->allocators->alloc_data,MAIN_MAP,PLAYER,-1,FORWARD,MINE,END,-1,-1,
                &game_data->player->player_pos->position_pixels->pos_pixels,old_tile,new_tile,1,5);
                Action* moving = create_action(game_data->allocators->alloc_data,MAIN_MAP,PLAYER,-1,BACK,MOVING,END,-1,-1,
                &game_data->player->player_pos->position_pixels->pos_pixels,new_tile ,old_tile,1,5);
                mine->queue->ending_action=moving;
                append_action_to_actions_map(game_data,mine);
                //map[new_tile_x][new_tile_y] = 'f';

                //cells_map->cells[new_tile_x][new_tile_y]->objects[0] = textur(floor_textur,-1); 

                
            }
            if ((map[new_tile_x][new_tile_y] == 'b'))
            {
                
            }
            if ((map[new_tile_x][new_tile_y] == 's'))
            {
                
            }
            if ((map[new_tile_x][new_tile_y] == 'm'))
            {
                Vector2 new_tile = {new_tile_x,new_tile_y};
                Vector2 old_tile = {old_tile_x,old_tile_y};
                Action* attack = create_action(game_data->allocators->alloc_data,MAIN_MAP,PLAYER,-1,FORWARD,ATTACK,END,-1,-1,
                &game_data->player->player_pos->position_pixels->pos_pixels,old_tile,new_tile,1,5);
                Action* moving = create_action(game_data->allocators->alloc_data,MAIN_MAP,PLAYER,-1,BACK,MOVING,END,-1,-1,
                &game_data->player->player_pos->position_pixels->pos_pixels,new_tile ,old_tile,1,5);
                attack->queue->ending_action=moving;
                append_action_to_actions_map(game_data,attack);
                //player_attaks(game_data,game_anim,new_tile_x,new_tile_y);
            }

            
            
        }
        if (game_data->maps->actins_map->amount_actions_main_queue ==0)
        {   
            if (step_flag)
            {
                after_step(game_data);
            }
        }
        return true;
    }
    
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



