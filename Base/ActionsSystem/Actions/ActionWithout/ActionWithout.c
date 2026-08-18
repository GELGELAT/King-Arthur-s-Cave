#include "ActionWithout.h"

void without_movement_action_update(GAME_DATA* game_data,GAME_ANIM* game_anim,Action* action)
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
                else if (action_type == PREPARATION)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->breathe;
                    enemy->current_animation[0]->currentFrame =0;
                    enemy->current_animation[0]->framesCounter = 0;
                    enemy->enemy_misc->activated = true;
                }
                else if (action_type == DIE)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->corpse;
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
                }
                else if (action_type == MINE)
                {
                    game_data->player->current_anim[0] = &game_data->player->player_anim->player_mine_animation;
                }
                player_animation_direction(directing_x,directing_y,game_data->player);
            }
            
        
            
            *current_state = FIRST_STAGE;
        }
        if (*current_state==FIRST_STAGE)
        {
            bool ending_flag_x = false;
            bool ending_flag_y = false;
            float speed = action->misc->speed;
            float* cur_pixel_pos_x = &action->pos->position_pixels->x;
            float* cur_pixel_pos_y = &action->pos->position_pixels->y;
            action->misc->current_fill+=speed;
            if (action->misc->current_fill <action->misc->max_fill)
            {
                
    
            }
            else
            {
                ending_flag_x = true;
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
                        if (action_type == DIE)
                        {
                            
                            int enemy_index = action->object->object_index;
                            Enemy* enemy = get_enemy_from_enemy_map(game_data,enemy_index);
                            int enemy_x = (int)enemy->enemy_position->position_tiles->pos_tiles.x;
                            int enemy_y = (int)enemy->enemy_position->position_tiles->pos_tiles.y;
                            items_drop(game_data,game_anim,enemy,(int)enemy_x,(int)enemy_y);
                            game_data->maps->cells_map->cells[enemy_x][enemy_y]->objects[2] = NULL;
                            game_data->maps->collision_map->grid[enemy_x][enemy_y] = 'f';
                            game_data->maps->enemy_map->index_map[enemy_x][enemy_y] = -1;
                            delete_from_move_queue(game_data,enemy_index);
                        }
                        else
                        {
                        
                            int enemy_index = action->object->object_index;
                            Enemy* enemy = get_enemy_from_enemy_map(game_data,enemy_index);
                            enemy->current_animation[0] = &enemy->enemy_animations->breathe;
                            enemy->current_animation[0]->currentFrame =rand_num_within(0,3);
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
    else if (during_type == DURING)
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
                else if (action_type == PREPARATION)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->breathe;
                    enemy->current_animation[0]->currentFrame =0;
                    enemy->current_animation[0]->framesCounter = 0;
                    enemy->enemy_misc->activated = true;
                }
                else if (action_type == FALL)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->fall;
                    enemy->current_animation[0]->currentFrame =0;
                    enemy->current_animation[0]->framesCounter = 0;
                    
                }
                else if (action_type == CORPSE)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->corpse;
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
                }
                else if (action_type == MINE)
                {
                    game_data->player->current_anim[0] = &game_data->player->player_anim->player_mine_animation;
                }
                player_animation_direction(directing_x,directing_y,game_data->player);
            }
            
        
            
            *current_state = FIRST_STAGE;
        }
        if (*current_state==FIRST_STAGE)
        {
            bool ending_flag_x = false;
            bool ending_flag_y = false;
            float speed = action->misc->speed;
            float* cur_pixel_pos_x = &action->pos->position_pixels->x;
            float* cur_pixel_pos_y = &action->pos->position_pixels->y;
            action->misc->current_fill+=speed;
            if (action->misc->current_fill <action->misc->max_fill)
            {
                
    
            }
            else
            {
                ending_flag_x = true;
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
                        if (action_type == CORPSE)
                        {

                        }
                        else
                        {
                            int enemy_index = action->object->object_index;
                            Enemy* enemy = get_enemy_from_enemy_map(game_data,enemy_index);
                            enemy->current_animation[0] = &enemy->enemy_animations->breathe;
                            enemy->current_animation[0]->currentFrame =rand_num_within(0,3);
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
    else if (during_type == START)
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
                else if (action_type == PREPARATION)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->preparation;
                    enemy->current_animation[0]->currentFrame =rand_num_within(0,1);
                    enemy->current_animation[0]->framesCounter = 0;
                    enemy->enemy_misc->activated = true;
                }
                else if (action_type == FALL)
                {
                    pr_int(444);
                    enemy->current_animation[0] = &enemy->enemy_animations->fall;
                    enemy->current_animation[0]->currentFrame =0;
                    enemy->current_animation[0]->framesCounter = 0;
                }
                else if (action_type == CORPSE)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->corpse;
                    enemy->current_animation[0]->currentFrame =0;
                    enemy->current_animation[0]->framesCounter = 0;
                }
                else if (action_type == BREATH)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->breathe;
                    enemy->current_animation[0]->currentFrame =0;
                    enemy->current_animation[0]->framesCounter = 0;
                }
                else if (action_type == DIE)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->breathe;
                    enemy->current_animation[0]->currentFrame =0;
                    enemy->current_animation[0]->framesCounter = 0;
                    int enemy_index = action->object->object_index;
                    Enemy* enemy = get_enemy_from_enemy_map(game_data,enemy_index);
                    int enemy_x = (int)enemy->enemy_position->position_tiles->pos_tiles.x;
                    int enemy_y = (int)enemy->enemy_position->position_tiles->pos_tiles.y;
                    items_drop(game_data,game_anim,enemy,(int)enemy_x,(int)enemy_y);
                    game_data->maps->cells_map->cells[enemy_x][enemy_y]->objects[2] = NULL;
                    game_data->maps->collision_map->grid[enemy_x][enemy_y] = 'f';
                    game_data->maps->enemy_map->index_map[enemy_x][enemy_y] = -1;
                    delete_from_move_queue(game_data,enemy_index);
                }
                else if (action_type == RECEIVING_DAMAGE)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->receiving_damage;
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
                }
                else if (action_type == MINE)
                {
                    game_data->player->current_anim[0] = &game_data->player->player_anim->player_mine_animation;
                }
                player_animation_direction(directing_x,directing_y,game_data->player);
            }
            
        
            
            *current_state = FIRST_STAGE;
        }
        if (*current_state==FIRST_STAGE)
        {
            bool ending_flag_x = false;
            bool ending_flag_y = false;
            float speed = action->misc->speed;
            float* cur_pixel_pos_x = &action->pos->position_pixels->x;
            float* cur_pixel_pos_y = &action->pos->position_pixels->y;
            action->misc->current_fill+=speed;
            if (action->misc->current_fill <action->misc->max_fill)
            {
                
    
            }
            else
            {
                ending_flag_x = true;
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
                        }
                    }
                    else if (object_type == ENEMY)
                    {
                        
                       
                    }
                    append_action_to_actions_map(game_data,ending_action);
                    next_action_flag = true;
                }

                if (!next_action_flag)
                {
                    if (object_type == ENEMY)
                    {
                        if (action_type == CORPSE)
                        {

                        }
                        else if (action_type == DIE)
                        {
                            
                            
                        }
                        else
                        {
                             
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