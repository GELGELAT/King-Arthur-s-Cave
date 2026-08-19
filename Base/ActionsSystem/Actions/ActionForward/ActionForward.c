#include "ActionForward.h"
void forward_movement_action_update(GAME_DATA* game_data,GAME_ANIM* game_anim,Action* action)
{
    int during_type = action->main->during_type;
    if (during_type == END)
    {
        
        int* current_state = &action->misc->current_state;

        int object_type = action->object->object_type;
        int action_type = action->main->action_type;

        float old_tile_x = action->pos->old_tile.x;
        float old_tile_y = action->pos->old_tile.y;
        float new_tile_x = action->pos->new_tile.x;
        float new_tile_y = action->pos->new_tile.y;
        float directing_x = new_tile_x-old_tile_x;
        float directing_y = new_tile_y-old_tile_y;
        
        if (*current_state== ZERO_STAGE)
        {
            Action* beginning_action = action->queue->beginning_action;
            if (beginning_action !=NULL)
            {
                append_action_to_actions_map(game_data,beginning_action);
            }
            if (object_type == ENEMY)
            {
                int enemy_index = action->object->object_index;
                Enemy* enemy = get_enemy_from_enemy_map(game_data,enemy_index);
                if (action_type == MOVING)
                {
                    
                    enemy->current_animation[0] = &enemy->enemy_animations->walk;
                    enemy->current_animation[0]->currentFrame =0;
                    enemy->current_animation[0]->framesCounter = 0;
                }
                else if (action_type == ATTACK)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->attack;
                    enemy->current_animation[0]->currentFrame =0;
                    enemy->current_animation[0]->framesCounter = 0;
                }
                enemy_animation_direction(directing_x,directing_y,enemy);
                
            }
            else if (object_type == PLAYER)
            {
                if (action_type == MOVING)
                {
                    game_data->player->current_anim[0] = &game_data->player->player_anim->player_walk_animation;
                }
                else if (action_type == ATTACK)
                {
                    game_data->player->current_anim[0] = &game_data->player->player_anim->player_attack_animation;
                    game_data->player->current_anim[0]->currentFrame =0;
                    game_data->player->current_anim[0]->framesCounter = 0;
                }
                else if (action_type == MINE)
                {
                    game_data->player->current_anim[0] = &game_data->player->player_anim->player_mine_animation;
                    game_data->player->current_anim[0]->currentFrame =0;
                    game_data->player->current_anim[0]->framesCounter = 0;
                }
                player_animation_direction(directing_x,directing_y,game_data->player);
            }
            play_full_animation(game_data,action,directing_x,directing_y);
            
            *current_state = FIRST_STAGE;
        }
        if (*current_state==FIRST_STAGE)
        {
            bool ending_flag_x = false;
            bool ending_flag_y = false;
            float speed = action->misc->speed;
            float* cur_pixel_pos_x = &action->pos->position_pixels->x;
            float* cur_pixel_pos_y = &action->pos->position_pixels->y;
            
            if (directing_x>0)
            {
                *cur_pixel_pos_x += speed;
                if (*cur_pixel_pos_x >= new_tile_x*64+32 )
                {
                    *cur_pixel_pos_x = new_tile_x*64+32;
                    ending_flag_x = true;
                }
            }
            if (directing_x<0)
            {
                *cur_pixel_pos_x -= speed;
                if (*cur_pixel_pos_x <= new_tile_x*64+32 )
                {
                    *cur_pixel_pos_x = new_tile_x*64+32;
                    ending_flag_x = true;
                }
            }
            if (directing_y>0)
            {
                *cur_pixel_pos_y += speed;
                if (*cur_pixel_pos_y >= new_tile_y*64+32)
                {
                    *cur_pixel_pos_y = new_tile_y*64+32;
                    ending_flag_y = true;
                }
            }
            if (directing_y<0)
            {
                *cur_pixel_pos_y -= speed;
                if (*cur_pixel_pos_y <= new_tile_y*64+32)
                {
                    *cur_pixel_pos_y = new_tile_y*64+32;
                    ending_flag_y = true;
                }
            }
            
            
            if (ending_flag_x || ending_flag_y)
            {
                bool next_action_flag = false;
                Action* ending_action = action->queue->ending_action;
                if (ending_action !=NULL)
                {
                    if (object_type == PLAYER)
                    {
                        if (action_type == ATTACK)
                        {
                            player_attaks(game_data,game_anim,action->pos->new_tile.x,action->pos->new_tile.y);
                            Enemy* enemy = get_enemy_from_enemy_map(game_data,action->object->affected_index);
                            Action* receiving_damage = create_action(game_data->allocators->alloc_data,MAIN_MAP,action->object->affected_type,action->object->affected_index,RANDOM_MOVING,RECEIVING_DAMAGE,START,-1,-1,
                            &enemy->enemy_position->position_pixels->pos_pixels,action->pos->new_tile,action->pos->new_tile,ENEMY_RECEIVING_DAMAGE_TIME_ANIM,1,5);
                            append_action_to_actions_map(game_data,receiving_damage);
                        }
                        else if (action_type == MINE)
                        {
                            int new_tile_x = action->pos->new_tile.x;
                            int new_tile_y = action->pos->new_tile.y;
                            char** map = game_data->maps->collision_map->grid;
                            CellsMap* cells_map = game_data->maps->cells_map;
                            map[new_tile_x][new_tile_y] = 'f';

                            cells_map->cells[new_tile_x][new_tile_y]->objects[0] = textur(floor_textur,-1); 
                        }
                    }
                    else if (object_type == ENEMY)
                    {
                        int enemy_index = action->object->object_index;
                        Enemy* enemy = get_enemy_from_enemy_map(game_data,enemy_index);
                        if (action_type == ATTACK)
                        {
                            enemy_attack(game_data,enemy);
                        }
                    }
                    append_action_to_actions_map(game_data,ending_action);
                    next_action_flag = true;
                }

                if (!next_action_flag)
                {
                    if (object_type == ENEMY)
                    {
                        int enemy_index = action->object->object_index;
                        Enemy* enemy = get_enemy_from_enemy_map(game_data,enemy_index);
                        enemy->current_animation[0] = &enemy->enemy_animations->breathe;
                        enemy->current_animation[0]->currentFrame =rand_num_within(0,3);
                        if (enemy->enemy_animations->skin == CHICKEN_ZOMBIE || enemy->enemy_animations->skin == ARM_ZOMBIE)
                        {
                            plus_to_stamina(enemy);
                        }
                        
                    }
                    else if (object_type == PLAYER)
                    {
                        game_data->player->current_anim[0] = &game_data->player->player_anim->player_breathe_animation;
                    }
                }
                
                action->misc->current_fill = action->misc->max_fill;
            }
        }
        
    }
    
}