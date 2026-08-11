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
    action_q_updater(game_data,game_anim);
    update_items_animations(game_anim);
    update_ememies_animations(game_anim);
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
    while (game_data->maps->pos_map->amount_actions ==0)
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
                //game_data->player->player_pos->position_pixels->pos_pixels = new_pos;
                game_data->player->player_pos->position_tiles->pos_tiles = new_tile;
                append_to_action_map(game_data,(Vector2){old_tile_x,old_tile_y},new_tile,&game_data->player->player_pos->position_pixels->pos_pixels,WALK,5,-1);
                
                
            

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

            
            
        }
        if (game_data->maps->pos_map->amount_actions ==0)
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



void append_to_action_map(GAME_DATA* game_data,Vector2 old_tile,Vector2 new_tile,Vector2* pos_pixels,int cur_action,float speed,int enemy_index)
{
    Action action = create_action(game_data->allocators->alloc_data,pos_pixels,old_tile,new_tile,speed,cur_action,enemy_index);
    ActionMap* pos_q_map = game_data->maps->pos_map;
    int* amount = &pos_q_map->amount_actions;
    pos_q_map->actions_queue[*amount] = action;
    *amount+=1;

}
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
            walk_action_update(game_data,cur_action,i);
            
        }
        else if (cur_action_index == ATTACK)
        {
            attack_action_update(game_data,cur_action,i);
            
        }
        else if (cur_action_index == DIE)
        {
            die_action_update(game_data,game_anim,cur_action,i);
            
        }
    }
}
void die_action_update(GAME_DATA* game_data,GAME_ANIM* game_anim,Action* action,int cur_pos_at_map)
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
void attack_action_update(GAME_DATA* game_data,Action* action,int cur_pos_at_map)
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
            animation_direction(directing_x,directing_y,enemy);
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
        delete_action_from_action_map(game_data,cur_pos_at_map);
    }
    
}
void walk_action_update(GAME_DATA* game_data,Action* action,int cur_pos_at_map)
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
            animation_direction(directing_x,directing_y,enemy);
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
        delete_action_from_action_map(game_data,cur_pos_at_map);
    }
}

void animation_direction(int directing_x,int directing_y,Enemy* enemy)
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
