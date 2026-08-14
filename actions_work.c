#include "actions_work.h"
void append_action_to_actions_map(GAME_DATA* game_data,Action* action)
{
    ActionsMap* action_maps = game_data->maps->actins_map;
    int map_number = action->flow;

    int* main_amount = &action_maps->amount_actions_main_queue;
    int* effect_amount = &action_maps->amount_actions_effects_queue;
    if (map_number == MAIN_MAP)
    {
        action_maps->actions_main_queue[*main_amount]=action;
        *main_amount +=1;
    }
    else if (map_number == EFFECT_MAP)
    {
        action_maps->actions_effects_queue[*effect_amount] = action;
        *effect_amount+=1;
    }
    

}

void main_action_map_updater(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    Action** action_maps = game_data->maps->actins_map->actions_main_queue;
    int* amount = &game_data->maps->actins_map->amount_actions_main_queue;
    for (int i =0;i<*amount;i++)
    {
        //pr_int(*amount);
        Action* current_action = action_maps[i];
        float current_fill = current_action->misc->current_fill;
        float max_fill = current_action->misc->max_fill;
        if (current_fill >=max_fill)
        {
            delete_action_from_main_action_map(game_data,i);
            continue;
        }
        int movement_type = current_action->main->movement_type;
        
        if (movement_type == WITHOUT_MOVING)
        {
            without_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type == FORWARD)
        {
            forward_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type == BACK)
        {
            back_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type == RANDOM_MOVING)
        {
            random_movement_action_update(game_data,game_anim,current_action);
            
        }
    }
}
void delete_action_from_main_action_map(GAME_DATA* game_data,int current_pos_at_map)
{
    int* amount = &game_data->maps->actins_map->amount_actions_main_queue;
    Action** map = game_data->maps->actins_map->actions_main_queue;
    for (int i=current_pos_at_map;i<*amount-1;i++)
    {
        map[i] =map[i+1];
    }
    *amount-=1;
    
}
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
                        int enemy_index = action->object->object_index;
                        Enemy* enemy = get_enemy_from_enemy_map(game_data,enemy_index);
                        enemy->current_animation[0] = &enemy->enemy_animations->breathe;
                        enemy->current_animation[0]->currentFrame =rand_num_within(0,3);
                        
                        
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
                }
                else if (action_type == MINE)
                {
                    game_data->player->current_anim[0] = &game_data->player->player_anim->player_mine_animation;
                    game_data->player->current_anim[0]->currentFrame =0;
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
void back_movement_action_update(GAME_DATA* game_data,GAME_ANIM* game_anim,Action* action)
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
        float new_pixel_pos_y = new_tile_y*64+32;
        /*
        float old_pixel_pos_x = old_tile_x*64+32;
        float old_pixel_pos_y = old_tile_y*64+32;
        float new_pixel_pos_y = new_tile_y*64+32;
        float new_pixel_pos_x = new_tile_x*64+32;
        float directing_x = new_pixel_pos_x-old_pixel_pos_x;
        float directing_y = new_pixel_pos_y-old_pixel_pos_y;
        
        */
       
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
                enemy_animation_direction(-directing_x,-directing_y,enemy);
                
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
                player_animation_direction(-directing_x,-directing_y,game_data->player);
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
                if (*cur_pixel_pos_y >=new_tile_y*64+32)
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

void random_movement_action_update(GAME_DATA* game_data,GAME_ANIM* game_anim,Action* action)
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
                else if (action_type == DIE)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->die;
                    enemy->current_animation[0]->currentFrame =0;
                    enemy->current_animation[0]->framesCounter = 0;
                }
                enemy_animation_direction(-directing_x,-directing_y,enemy);
                
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
                //player_animation_direction(-directing_x,-directing_y,game_data->player);
            }
            
        
            
            *current_state = FIRST_STAGE;
        }
        if (*current_state==FIRST_STAGE)
        {
            action->misc->current_fill +=1;
            bool ending_flag_x = false;
            bool ending_flag_y = false;
            float speed = action->misc->speed;
            float* cur_pixel_pos_x = &action->pos->position_pixels->x;
            float* cur_pixel_pos_y = &action->pos->position_pixels->y;
            
            if (action->misc->current_fill <action->misc->max_fill)
            {
                *cur_pixel_pos_x += rand_num_within(-speed,speed);
        

                *cur_pixel_pos_y += rand_num_within(-speed,speed);
    
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
                        else if (action_type == DIE)
                        {
                            
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
        float new_pixel_pos_x = new_tile_x*64+32;
        float new_pixel_pos_y = new_tile_y*64+32;

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
                else if (action_type == DIE)
                {
                    enemy->current_animation[0] = &enemy->enemy_animations->die;
                    enemy->current_animation[0]->currentFrame =0;
                    enemy->current_animation[0]->framesCounter = 0;
                }
                enemy_animation_direction(-directing_x,-directing_y,enemy);
                
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
                //player_animation_direction(-directing_x,-directing_y,game_data->player);
            }
            
        
            
            *current_state = FIRST_STAGE;
        }
        if (*current_state==FIRST_STAGE)
        {
            action->misc->current_fill +=action->misc->speed;
            bool ending_flag_x = false;
            bool ending_flag_y = false;
            float speed = action->misc->speed;
            float* cur_pixel_pos_x = &action->pos->position_pixels->x;
            float* cur_pixel_pos_y = &action->pos->position_pixels->y;
            
            if (action->misc->current_fill <action->misc->max_fill)
            {
                //if ()
                *cur_pixel_pos_x += rand_num_within(-speed,speed);
        

                *cur_pixel_pos_y += rand_num_within(-speed,speed);
                if (new_pixel_pos_x-16 -*cur_pixel_pos_x>=0)
                {
                    *cur_pixel_pos_x += rand_num_within(speed,speed*2);
                }
                if (new_pixel_pos_x+16 -*cur_pixel_pos_x<=0)
                {
                    *cur_pixel_pos_x -= rand_num_within(speed,speed*2);
                }
                if (new_pixel_pos_y-16 -*cur_pixel_pos_y>=0)
                {
                    *cur_pixel_pos_y += rand_num_within(speed,speed*2);
                }
                if (new_pixel_pos_y+16 -*cur_pixel_pos_y<=0)
                {
                    *cur_pixel_pos_y -= rand_num_within(speed,speed*2);
                }
    
            }
            else
            {
                ending_flag_x = true;
            }
            if ((int)action->misc->current_fill % 8 ==0)
            {
            
                if (object_type == ENEMY)
                {
                    if (action_type == ATTACK)
                    {
                        int enemy_index = action->object->object_index;
                        
                        Enemy* enemy = get_enemy_from_enemy_map(game_data,enemy_index);
                        Enemy* enemy_accepting = get_enemy_from_enemy_map(game_data,action->object->affected_index);
                        
                        
                        enemy_fast_attack(game_data,game_anim,enemy,enemy_accepting);
                        enemy_life_check(game_data,game_anim,enemy_accepting);
                    }
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
                            
                        }
                    }
                    else if (object_type == ENEMY)
                    {
                        int enemy_index = action->object->object_index;
                        Enemy* enemy = get_enemy_from_enemy_map(game_data,enemy_index);
                        if (action_type == ATTACK)
                        {
                            
                        }
                        else if (action_type == DIE)
                        {
                            
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
    
}
void player_animation_direction(int directing_x,int directing_y,Player* player)
{
    int width = player->player_anim->player_breathe_animation.frameWidth;
    if (directing_x>0)
    {
        player->player_anim->player_attack_animation.cur_frameRec.width = -width;
        player->player_anim ->player_breathe_animation.cur_frameRec.width= -width;
        player->player_anim->player_walk_animation.cur_frameRec.width = -width;
        player->player_anim->player_mine_animation.cur_frameRec.width = -width;
        //player->player_anim. = -width;
       // player->player_anim = -width;
    }
    if (directing_x<0)
    {
        
        player->player_anim->player_attack_animation.cur_frameRec.width = width;
        player->player_anim ->player_breathe_animation.cur_frameRec.width= width;
        player->player_anim->player_walk_animation.cur_frameRec.width = width;
        player->player_anim->player_mine_animation.cur_frameRec.width = width;
       // player->player_anim = width;
       // player->player_anim = width;
    }
    
}
void enemy_animation_direction(int directing_x,int directing_y,Enemy* enemy)
{
    int width = enemy->enemy_animations->breathe.frameWidth;
    if (directing_x>0)
    {
        enemy->enemy_animations->walk.cur_frameRec.width = -width;
        enemy->enemy_animations->attack.cur_frameRec.width = -width;
        enemy->enemy_animations->breathe.cur_frameRec.width = -width;
        enemy->enemy_animations->die.cur_frameRec.width = -width;
    }
    if (directing_x<0)
    {
        enemy->enemy_animations->walk.cur_frameRec.width = width;
        enemy->enemy_animations->attack.cur_frameRec.width = width;
        enemy->enemy_animations->breathe.cur_frameRec.width = width;
        enemy->enemy_animations->die.cur_frameRec.width = width;
    }
    
}
/*
void delete_action_from_action_map(GAME_DATA* game_data,int cur_pos_at_map)
{
    int* amount = &game_data->maps->pos_map->amount_actions;
    Action* map = game_data->maps->pos_map->actions_queue;
    for (int i=cur_pos_at_map;i<*amount-1;i++)
    {
        map[i] =map[i+1];
    }
    *amount-=1;
    
}
void action_q_updater(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    ActionMap* pos_q_map = game_data->maps->pos_map;
    int* amount = &pos_q_map->amount_actions;
    for (int i =0;i<*amount;i++)
    {
        //pr_int(*amount);
        Action* cur_action = &pos_q_map->actions_queue[i];
        int cur_action_index = cur_action->action;
        if (cur_action_index == WALK)
        {
            forward_movement_action_update(game_data,cur_action,i);
            
        }
        else if (cur_action_index == ATTACK)
        {
            forward_and_backward_movement_action_update(game_data,cur_action,i);
            
        }
        else if (cur_action_index == DIE)
        {
            random_movements_action_update(game_data,game_anim,cur_action,i);
            
        }
    }
}
void random_movements_action_update(GAME_DATA* game_data,GAME_ANIM* game_anim,Action* action,int cur_pos_at_map)
{
    int old_tile_x,old_tile_y;
    if (action->current_state == first_state)
    {
        if (action->index_enemies != -1)
        {
            
            Enemy* enemy = game_data->maps->enemy_map->enemy_map[action->index_enemies];
            //pr_int(enemy->enemy_main->index);
            enemy->current_animation[0] = &enemy->enemy_animations->die;
            enemy->current_animation[0]->currentFrame =0;
            enemy->current_animation[0]->framesCounter = 0;
        }
        
        action->current_state = second_state;
    }
    action->current_fill++;
    bool flag_x = false;
    bool flag_y = false;
    float speed = action->speed;
    float* cur_pixel_pos_x = &action->position_pixels->x;
    float* cur_pixel_pos_y = &action->position_pixels->y;
    old_tile_x = action->old_tile.x;
    old_tile_y = action->old_tile.y;
    float new_tile_x = action->new_tile.x;
    float new_tile_y = action->new_tile.y;
    float directing_x = new_tile_x-old_tile_x;
    float directing_y = new_tile_y-old_tile_y;

    if (action->current_state == 2)
    {
        if (action->current_fill <DIE_TIME)
        {
            *cur_pixel_pos_x += rand_num_within(-speed,speed);
    

            *cur_pixel_pos_y += rand_num_within(-speed,speed);
  
        }
        else
        {
            flag_x = true;
        }

    }
    
    if (flag_x || flag_y)
    {
        if (action->index_enemies != -1)
        {
            //pr_int(23124);
            
            Enemy* enemy = game_data->maps->enemy_map->enemy_map[action->index_enemies];
            game_data->maps->cells_map->cells[old_tile_x][old_tile_y]->objects[2] = NULL;
            game_data->maps->collision_map->grid[old_tile_x][old_tile_y] = 'f';
            game_data->maps->enemy_map->index_map[old_tile_x][old_tile_y] = -1;
            items_drop(game_data,game_anim,enemy,(int)old_tile_x,(int)old_tile_y);
            delete_from_move_queue(game_data,enemy->enemy_main->index);
            
        }
        delete_action_from_action_map(game_data,cur_pos_at_map);
    }
    

}
void forward_and_backward_movement_action_update(GAME_DATA* game_data,Action* action,int cur_pos_at_map)
{

    float old_tile_x = action->old_tile.x;
    float old_tile_y = action->old_tile.y;
    float new_tile_x = action->new_tile.x;
    float new_tile_y = action->new_tile.y;
    float directing_x = new_tile_x-old_tile_x;
    float directing_y = new_tile_y-old_tile_y;
    if (action->current_state == first_state)
    {
        if (action->index_enemies != -1)
        {
            //pr_int(action->index_enemies);
            Enemy* enemy = game_data->maps->enemy_map->enemy_map[action->index_enemies];
            enemy->current_animation[0] = &enemy->enemy_animations->attack;
            enemy->current_animation[0]->currentFrame =0;
            enemy->current_animation[0]->framesCounter = 0;
            enemy_animation_direction(directing_x,directing_y,enemy);
        }
        if (action->index_enemies == -1)
        {
            game_data->player->current_anim[0] = &game_data->player->player_anim->player_attack_animation;
            player_animation_direction(game_data->player,directing_x,directing_y);
        }
        
        action->current_state = second_state;
    }
    bool flag_x = false;
    bool flag_y = false;
    float speed = action->speed;
    float* cur_pixel_pos_x = &action->position_pixels->x;
    float* cur_pixel_pos_y = &action->position_pixels->y;
    

    if (action->current_state == 3)
    {
        if (directing_x>0)
        {
            *cur_pixel_pos_x -= speed;
            if (*cur_pixel_pos_x < old_tile_x*64+32 )
            {
                *cur_pixel_pos_x = old_tile_x*64+32;
                flag_x = true;
            }
        }
        if (directing_x<0)
        {
            *cur_pixel_pos_x += speed;
            if (*cur_pixel_pos_x > old_tile_x*64+32 )
            {
                *cur_pixel_pos_x = old_tile_x*64+32;
                flag_x = true;
            }
        }
        if (directing_y>0)
        {
            *cur_pixel_pos_y -= speed;
            if (*cur_pixel_pos_y < old_tile_y*64+32)
            {
                *cur_pixel_pos_y = old_tile_y*64+32;
                flag_y = true;
            }
        }
        if (directing_y<0)
        {
            *cur_pixel_pos_y += speed;
            if (*cur_pixel_pos_y > old_tile_y*64+32)
            {
                *cur_pixel_pos_y = old_tile_y*64+32;
                flag_y = true;
            }
        }
    }
    else if (action->current_state == 2)
    {
        if (directing_x>0)
        {
            *cur_pixel_pos_x += speed;
            if (*cur_pixel_pos_x > new_tile_x*64+32 )
            {
                *cur_pixel_pos_x = new_tile_x*64+32;
                action->current_state = 3;
            }
        }
        if (directing_x<0)
        {
            *cur_pixel_pos_x -= speed;
            if (*cur_pixel_pos_x < new_tile_x*64+32 )
            {
                *cur_pixel_pos_x = new_tile_x*64+32;
                action->current_state = 3;
            }
        }
        if (directing_y>0)
        {
            *cur_pixel_pos_y += speed;
            if (*cur_pixel_pos_y > new_tile_y*64+32)
            {
                *cur_pixel_pos_y = new_tile_y*64+32;
                action->current_state = 3;
            }
        }
        if (directing_y<0)
        {
            *cur_pixel_pos_y -= speed;
            if (*cur_pixel_pos_y < new_tile_y*64+32)
            {
                *cur_pixel_pos_y = new_tile_y*64+32;
                action->current_state = 3;
            }
        }
    }
    
    
    if (flag_x || flag_y)
    {
        if (action->index_enemies != -1)
        {
            //pr_int(23124);
            Enemy* enemy = game_data->maps->enemy_map->enemy_map[action->index_enemies];
            enemy->current_animation[0] = &enemy->enemy_animations->breathe;
            enemy->current_animation[0]->currentFrame = rand_num_within(0,3);
            action->current_state = first_state;
        }
        if (action->index_enemies == -1)
        {
            game_data->player->current_anim[0] = &game_data->player->player_anim->player_breathe_animation;
        }
        delete_action_from_action_map(game_data,cur_pos_at_map);
    }
    
}
void forward_movement_action_update(GAME_DATA* game_data,Action* action,int cur_pos_at_map)
{
    float old_tile_x = action->old_tile.x;
    float old_tile_y = action->old_tile.y;
    float new_tile_x = action->new_tile.x;
    float new_tile_y = action->new_tile.y;
    float directing_x = new_tile_x-old_tile_x;
    float directing_y = new_tile_y-old_tile_y;
    if (action->current_state == first_state)
    {
        if (action->index_enemies != -1)
        {
           // pr_int(action->index_enemies);
           
            Enemy* enemy = game_data->maps->enemy_map->enemy_map[action->index_enemies];
            enemy->current_animation[0] = &enemy->enemy_animations->walk;
            enemy->current_animation[0]->currentFrame =0;
            enemy->current_animation[0]->framesCounter = 0;
            enemy_animation_direction(directing_x,directing_y,enemy);
        }
        if (action->index_enemies == -1)
        {
            game_data->player->current_anim[0] = &game_data->player->player_anim->player_walk_animation;
            player_animation_direction(game_data->player,directing_x,directing_y);
        }
        
        action->current_state = second_state;
    }
    bool flag_x = false;
    bool flag_y = false;
    float speed = action->speed;
    float* cur_pixel_pos_x = &action->position_pixels->x;
    float* cur_pixel_pos_y = &action->position_pixels->y;
    
    if (action->current_state == second_state)
    {
        if (directing_x>0)
        {
            *cur_pixel_pos_x += speed;
            if (*cur_pixel_pos_x >= new_tile_x*64+32 )
            {
                *cur_pixel_pos_x -= speed;
                flag_x = true;
            }
        }
        if (directing_x<0)
        {
            *cur_pixel_pos_x -= speed;
            if (*cur_pixel_pos_x < new_tile_x*64+32 )
            {
                *cur_pixel_pos_x = new_tile_x*64+32;
                flag_x = true;
            }
        }
        if (directing_y>0)
        {
            *cur_pixel_pos_y += speed;
            if (*cur_pixel_pos_y > new_tile_y*64+32)
            {
                *cur_pixel_pos_y = new_tile_y*64+32;
                flag_y = true;
            }
        }
        if (directing_y<0)
        {
            *cur_pixel_pos_y -= speed;
            if (*cur_pixel_pos_y < new_tile_y*64+32)
            {
                *cur_pixel_pos_y = new_tile_y*64+32;
                flag_y = true;
            }
        }
    }
    
    if (flag_x || flag_y)
    {
        if (action->index_enemies != -1)
        {
            Enemy* enemy = game_data->maps->enemy_map->enemy_map[action->index_enemies];
            enemy->current_animation[0] = &enemy->enemy_animations->breathe;
            enemy->current_animation[0]->currentFrame =rand_num_within(0,3);
        }
        if(action->index_enemies == -1)
        {
            game_data->player->current_anim[0] = &game_data->player->player_anim->player_breathe_animation;
        }
        delete_action_from_action_map(game_data,cur_pos_at_map);
    }
}

void player_animation_direction(Player* player,int directing_x,int directing_y)
{
    int width = player->player_anim->player_breathe_animation.frameWidth;
    if (directing_x>0)
    {
        player->player_anim->player_attack_animation.cur_frameRec.width = -width;
        player->player_anim ->player_breathe_animation.cur_frameRec.width= -width;
        player->player_anim->player_walk_animation.cur_frameRec.width = -width;
        //player->player_anim. = -width;
       // player->player_anim = -width;
    }
    if (directing_x<0)
    {
        
        player->player_anim->player_attack_animation.cur_frameRec.width = width;
        player->player_anim ->player_breathe_animation.cur_frameRec.width= width;
        player->player_anim->player_walk_animation.cur_frameRec.width = width;
       // player->player_anim = width;
       // player->player_anim = width;
    }
    
}
void enemy_animation_direction(int directing_x,int directing_y,Enemy* enemy)
{
    int width = enemy->enemy_animations->breathe.frameWidth;
    if (directing_x>0)
    {
        enemy->enemy_animations->walk.cur_frameRec.width = -width;
        enemy->enemy_animations->attack.cur_frameRec.width = -width;
        enemy->enemy_animations->breathe.cur_frameRec.width = -width;
        enemy->enemy_animations->die.cur_frameRec.width = -width;
    }
    if (directing_x<0)
    {
        enemy->enemy_animations->walk.cur_frameRec.width = width;
        enemy->enemy_animations->attack.cur_frameRec.width = width;
        enemy->enemy_animations->breathe.cur_frameRec.width = width;
        enemy->enemy_animations->die.cur_frameRec.width = width;
    }
    
}

*/