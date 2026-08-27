#include "UpdaterStep.h"
bool enemy_step_flag = false;
int player_action_move_dx[] = {0,1,0,-1,0};
int player_action_move_dy[] = {-1,0,1,0,0};
void pos_player_updater(GAME_DATA *game_data,GAME_ANIM* game_anim)
{
    player_actions_logic(game_data,game_anim);
    enemies_actions_logic(game_data);
}
void after_step(GAME_DATA* game_data)
{
    player_review(game_data);
    enemies_finding(game_data);
    enemies_moving(game_data);
    enemy_step_flag = false;
}
void enemies_actions_logic(GAME_DATA* game_data)
{
    if (game_data->maps->actins_map->amount_actions_main_queue ==0)
    {   
        if (enemy_step_flag)
        {
            after_step(game_data);
        }
    }
}
void player_actions_logic(GAME_DATA *game_data,GAME_ANIM* game_anim)
{
    if (game_data->maps->actins_map->amount_actions_main_queue ==0) //пока нет активных действий
    {
        
        int player_step_direction=-1;
        card_actions_logic(game_data); //карты действий
        moves_actions_logic(game_data,game_anim,&player_step_direction); //движение игорка через движения
        
    }
}
void card_actions_logic(GAME_DATA* game_data)
{

    if(IsKeyPressed(KEY_ONE))
    {
        
        actions_mark_tiles(game_data,game_data->player->player_pos->position_tiles->pos_tiles,actions_tiles_glow_plus_one,actions_tiles_glow_plus_one_amount);
        game_data->maps->actins_map->current_state = 1;
    }
    if ( game_data->maps->actins_map->current_state == 1)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            Vector2 mouseScreen = GetMousePosition();
            Vector2 mouseWorld = GetScreenToWorld2D(mouseScreen, game_data->misc->camera);
            bool a = actions_mouse_click_check(game_data,(Vector2){mouseWorld.x/64, mouseWorld.y/64});
            //printf("%d\n", a);
            actions_clear_mark_tiles(game_data);
            game_data->maps->actins_map->current_state = 0;
        }
    }
        
}

int moves_actions_logic(GAME_DATA* game_data,GAME_ANIM* game_anim,int* player_step_direction)
{
    char** map = game_data->maps->collision_map->grid;
    if(IsKeyPressed(KEY_W))
    {
        *player_step_direction = 0;
    }
    if(IsKeyPressed(KEY_D))
    {
        *player_step_direction= 1;
    }
    if(IsKeyPressed(KEY_S))
    {
        *player_step_direction =2;
    }
    if(IsKeyPressed(KEY_A))
    {
        *player_step_direction =3;
    }
    if(IsKeyPressed(KEY_SPACE))
    {
        *player_step_direction =4;
    }
    if (*player_step_direction != -1)
    {
        enemy_step_flag = true;
        int old_tile_x = game_data->player->player_pos->position_tiles->pos_tiles.x;
        int old_tile_y = game_data->player->player_pos->position_tiles->pos_tiles.y;

        int new_tile_x = game_data->player->player_pos->position_tiles->pos_tiles.x+player_action_move_dx[*player_step_direction];
        int new_tile_y = game_data->player->player_pos->position_tiles->pos_tiles.y+player_action_move_dy[*player_step_direction];                
        

        if (map[new_tile_x][new_tile_y] == 'f')
        {
            
            delete_from_item_anim_queue(game_data,game_anim,player_ground_check(game_data,game_anim,new_tile_x,new_tile_y));
            map[old_tile_x][old_tile_y] = 'f';
            map[new_tile_x][new_tile_y] = 'p';

 

            Vector2 new_tile = {new_tile_x,new_tile_y};
            Vector2 old_tile = {old_tile_x,old_tile_y};
            game_data->player->player_pos->position_tiles->pos_tiles = new_tile;
            Action* moving = create_action(game_data->allocators->alloc_data,MAIN_MAP,PLAYER,-1,movement_forward_none,action_moving_none,END,-1,-1,
            &game_data->player->player_pos->position_pixels->pos_pixels,old_tile,new_tile,PLAY_FULL_ANIM,2,PLAYER_WALK_SPEED_ANIM);
            append_action_to_actions_map(game_data,moving);
            
            
        

        }
        if ((map[new_tile_x][new_tile_y] == 'w'))
        {
            Vector2 new_tile = {new_tile_x,new_tile_y};
            Vector2 old_tile = {old_tile_x,old_tile_y};
            Action* mine = create_action(game_data->allocators->alloc_data,MAIN_MAP,PLAYER,-1,movement_forward_none,action_mine_none,END,-1,-1,
            &game_data->player->player_pos->position_pixels->pos_pixels,old_tile,new_tile,PLAY_FULL_ANIM,1,PLAYER_MINE_SPEED_ANIM);
            Action* moving = create_action(game_data->allocators->alloc_data,MAIN_MAP,PLAYER,-1,movement_back_none,action_moving_none,END,-1,-1,
            &game_data->player->player_pos->position_pixels->pos_pixels,new_tile ,old_tile,PLAY_FULL_ANIM,2,PLAYER_WALK_SPEED_ANIM);
            mine->queue->ending_action=moving;
            append_action_to_actions_map(game_data,mine);

            
        }
        if ((map[new_tile_x][new_tile_y] == 'b'))
        {
            
        }
        if ((map[new_tile_x][new_tile_y] == 's'))
        {
            
        }
        if ((map[new_tile_x][new_tile_y] == 'm'))
        {
            int index = game_data->maps->enemy_map->index_map[new_tile_x][new_tile_y];
            Enemy* enemy = get_enemy_from_enemy_map(game_data,index);
            Vector2 new_tile = {new_tile_x,new_tile_y};
            Vector2 old_tile = {old_tile_x,old_tile_y};
            Action* attack = create_action(game_data->allocators->alloc_data,MAIN_MAP,PLAYER,-1,movement_forward_none,action_attack_none,END,ENEMY,index,
            &game_data->player->player_pos->position_pixels->pos_pixels,old_tile,new_tile,PLAY_FULL_ANIM,1,PLAYER_ATTACK_SPEED_ANIM);
            Action* moving = create_action(game_data->allocators->alloc_data,MAIN_MAP,PLAYER,-1,movement_back_none,action_moving_none,END,-1,-1,
            &game_data->player->player_pos->position_pixels->pos_pixels,new_tile ,old_tile,PLAY_FULL_ANIM,2,PLAYER_WALK_SPEED_ANIM);
            attack->queue->ending_action=moving;
            
            append_action_to_actions_map(game_data,attack);
        }

        
        
    }
}