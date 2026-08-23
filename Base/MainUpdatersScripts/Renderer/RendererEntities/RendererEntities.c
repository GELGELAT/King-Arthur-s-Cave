#include "RendererEntities.h"

void draw_enemy(GAME_DATA* game_data)
{
    EnemyMap* enemy_map = game_data->maps->enemy_map;
    Enemy** enemy_arr = enemy_map->move_queue;
    int* amount = &enemy_map->move_queue_amount;
    for (int i =0;i<*amount;i++)
    {
        Enemy* cur_enemy = enemy_arr[i];
        /*
        for (int i = 0;i<4;i++)
        {
            if (cur_enemy->enemy_main->name==enemy_texturs[i])
            {
                //draw_animation(&cur_anim,pos_1,64,64,4,0);
                DrawCircle(cur_enemy->enemy_position->position_pixels->pos_pixels.x,cur_enemy->enemy_position->position_pixels->pos_pixels.y, 32.0f, color_enemy_texturs[i]);
            }
        }
            */
        if (cur_enemy->current_animation != NULL)
        {
            //cur_enemy->current_animation = &cur_enemy->enemy_animations->breathe;
            //pr_int(cur_enemy->current_animation->framesCounter);
            int pos_x = cur_enemy->enemy_position->position_pixels->pos_pixels.x -cur_enemy->enemy_animations->alignment_x;
            int pos_y =cur_enemy->enemy_position->position_pixels->pos_pixels.y -cur_enemy->enemy_animations->alignment_y;
            //pr_int(cur_enemy->current_animation->texture.id);
            draw_animation(cur_enemy->current_animation[0],(Vector2){pos_x,pos_y},cur_enemy->enemy_animations->size_x,cur_enemy->enemy_animations->size_y,4,0);
        }
        
        
    }
        
        
    
}

void draw_item(GAME_DATA* game_data,GAME_ANIM* game_anim,char** objects,int x,int y,Vector2 pos_1,Vector2 pos_2)
{
    
    int** item_index_map = game_data->maps->items_map->index_map;
    int index_item = item_index_map[(int)y][(int)x];
    //print_int_map(game_data,item_index_map);
    if(index_item <=-1)
    {
        return;
    }
    Item* item = game_data->maps->items_map->items_map[index_item];
    int textur_id = item->item_main->textur_index;
    int pos_index = item->item_main->pos_index;
    
    for (int i = 0;i<4;i++)
    {
        if (objects[1]==armor_chest_texturs[i])
        {
            Animation cur_anim = get_item_animation(game_anim,index_item);
            draw_animation(&cur_anim,pos_1,64,64,4,0);
            //DrawCircle(pos_1.x+32,pos_1.y+32, 20.0f, color_armor_chest_texturs[i]);        
        }
        else if (objects[1]==weapon_texturs[i])
        {
            Animation cur_anim = get_item_animation(game_anim,index_item);
            draw_animation(&cur_anim,pos_1,64,64,4,0);
            //DrawCircle(pos_1.x+32,pos_1.y+32, 10.0f, color_weapon_texturs[i]);
                

        }
        else if (objects[1]==HELMET_texturs[i])
        {
            Animation cur_anim = get_item_animation(game_anim,index_item);
            draw_animation(&cur_anim,pos_1,64,64,4,0);
            //DrawCircle(pos_1.x+32,pos_1.y+32, 5.0f, color_HELMET_texturs[i]);
                

        }
    }
    
    for (int i = 0;i<3;i++)
    {
        if (objects[1]==coins_texturs[i])
        {
            
            any_coins_draw(game_anim, pos_1,i,textur_id,pos_index);
        }
        else if (objects[1]==heals_texturs[i])
        {
            Animation cur_anim = get_item_animation(game_anim,index_item);
            draw_animation(&cur_anim,pos_1,32,32,pos_index,0);
            //DrawCircle(pos_1.x+32,pos_1.y+32, 5.0f, RED);
                

        }
        else if (objects[1]==experience_texturs[i])
        {
            Animation cur_anim = get_item_animation(game_anim,index_item);
            draw_animation(&cur_anim,pos_1,32,32,pos_index,0);
            //DrawCircle(pos_1.x+32,pos_1.y+32, 5.0f, BLUE);
                

        }
    }

}

void player_draw(GAME_DATA *game_data)
{

     
            //pr_int(cur_enemy->current_animation->texture.id);
    Player* player = game_data->player;
    int pos_player_x = player->player_pos->position_pixels->pos_pixels.x-player->player_anim->player_action_animation->alignment_x;
    int pos_player_y =player->player_pos->position_pixels->pos_pixels.y-player->player_anim->player_action_animation->alignment_y;
    int pos_head_x = player->player_pos->head_pos->current_pos.x;
    int pos_head_y =player->player_pos->head_pos->current_pos.y;

    draw_animation(player->current_animations->current_anim[0],(Vector2){pos_player_x,pos_player_y},player->player_anim->player_action_animation->size_x,player->player_anim->player_action_animation->size_y,4,0);
    draw_animation(player->current_animations->current_equipment_anim->current_armor_anim[0],*equipment_pos_list[ARMOR_CHEST],player->player_anim->player_head_animation->size_x,player->player_anim->player_head_animation->size_y,4,0);
    draw_animation(player->current_animations->current_head_anim[0],(Vector2){pos_head_x,pos_head_y},player->player_anim->player_head_animation->size_x,player->player_anim->player_head_animation->size_y,4,0);
    draw_animation(player->current_animations->current_equipment_anim->current_helmet_anim[0],*equipment_pos_list[HELMET],player->player_anim->player_head_animation->size_x,player->player_anim->player_head_animation->size_y,4,0);
    draw_animation(player->current_animations->current_equipment_anim->current_sword_anim[0],*equipment_pos_list[WEAPON],player->player_anim->player_head_animation->size_x,player->player_anim->player_head_animation->size_y,4,sword_rotate[current_direction]);
    //DrawCircle(game_data->player->player_pos->position_pixels->pos_pixels.x,game_data->player->player_pos->position_pixels->pos_pixels.y, 32.0f, GOLD); 

}
int rand_pos[4][2] = {{0,0},{0,32},{32,0},{32,32}};
void any_coins_draw(GAME_ANIM* game_anim, Vector2 pos,int coins_type, int frame_index,int pos_index)
{

    
    Texture2D coins_list = game_anim->texturs->items_texturs->misc_texturs->coins_texturs->coins;
    if (coins_type == small)
    {
        Rectangle source = game_anim->texturs->items_texturs->misc_texturs->coins_texturs->small_frames[frame_index];
        Rectangle dest = {pos.x+rand_pos[pos_index][0],pos.y+rand_pos[pos_index][1],48,48};
        DrawTexturePro(coins_list,source,dest,(Vector2){0,0}, 0, WHITE);
    }
    else if (coins_type == medium)
    {
        Rectangle source = game_anim->texturs->items_texturs->misc_texturs->coins_texturs->medium_frames[frame_index];
        Rectangle dest = {pos.x+rand_pos[pos_index][0],pos.y+rand_pos[pos_index][1],48,48};
        DrawTexturePro(coins_list,source,dest,(Vector2){0,0}, 0, WHITE);
    }
    
}