#include "AnimationsLogic.h"
#include <math.h>
void append_player_anim_to_arr(GAME_ANIM* game_anim,Animation** anim)
{
    Animation*** queue = game_anim->maps->animation_player_map->animation_map_queue;
    int amount_queue = game_anim->maps->animation_player_map->amount_animation_map_queue;

    
    queue[amount_queue] = anim;
    game_anim->maps->animation_player_map->amount_animation_map_queue +=1;
    
}
void draw_animation(Animation* anim,Vector2 pos,int size_x,int size_y,int pos_index,float rotate) 
{
    int rand_pos[5][2] = {{0,0},{0,32},{32,0},{32,32},{0,0}};
    if (!anim->isPlaying)
    {
        return;
    }
    Rectangle dest = {pos.x+rand_pos[pos_index][0],pos.y+rand_pos[pos_index][1],size_x,size_y};
    DrawTexturePro(anim->texture,anim->cur_frameRec,dest,(Vector2){0,0}, rotate, WHITE);
}
Animation get_item_animation(GAME_ANIM* game_anim,int index) 
{
    Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
    return anim_map[index];
}
void append_item_anim_to_arr(GAME_ANIM* game_anim,Animation* anim)
{
    Animation** queue = game_anim->maps->animation_items_map->animation_map_queue;
    int amount_queue = game_anim->maps->animation_items_map->amount_animation_map_queue;
    Animation* map = game_anim->maps->animation_items_map->animation_map;

    
    queue[amount_queue] = anim;
    game_anim->maps->animation_items_map->amount_animation_map_queue +=1;
    
}
void append_item_anim_to_map(GAME_ANIM* game_anim,Animation anim,int index)
{
    Animation* map = game_anim->maps->animation_items_map->animation_map;
    map[index] = anim;
    

}

void delete_from_item_anim_queue(GAME_DATA* game_data,GAME_ANIM* game_anim,int id)
{
    if (id > -1)
    {
        bool find_flag = false;
        Animation** queue = game_anim->maps->animation_items_map->animation_map_queue;
        for (int i = 0;i<game_anim->maps->animation_items_map->amount_animation_map_queue;i++)
        {
            if (!find_flag )
            {
                if(queue[i]->index == id)
                {
                    find_flag = true;
                }
            }
            else
            {
                queue[i-1] = queue[i];
            }
        }
        game_anim->maps->animation_items_map->amount_animation_map_queue -=1;
    }
    
}
void append_item_animation(GAME_ANIM* game_anim,int object_type,int textur_type,int object_id)
{
    if (object_type ==EXP)
    {   
        Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
        if (textur_type == small)
        {
            Animation small_exp_anim = game_anim->animations->items_animation->misc_animation->exps_animation->small_exp;
            small_exp_anim.currentFrame = rand_num_within(0,3);

            anim_map[object_id] = small_exp_anim;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == medium)
        {
            Animation medium_exp_anim = game_anim->animations->items_animation->misc_animation->exps_animation->medium_exp;
            //pr_int(medium_exp_anim.framesSpeed);
            medium_exp_anim.currentFrame = rand_num_within(0,3);
            anim_map[object_id] = medium_exp_anim;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
    }
    else if (object_type ==HEALS)
    {   
        Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
        if (textur_type == small)
        {
            Animation small_heal_anim = game_anim->animations->items_animation->misc_animation->heals_animation->small_heals;
            small_heal_anim.currentFrame = 0;

            anim_map[object_id] = small_heal_anim;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == medium)
        {
            Animation medium_heal_anim = game_anim->animations->items_animation->misc_animation->heals_animation->medium_heals;
            //pr_int(medium_exp_anim.framesSpeed);
            medium_heal_anim.currentFrame = 0;
            anim_map[object_id] = medium_heal_anim;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
    }
    else if (object_type ==ARMOR_CHEST) 
    {   
        Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
        if (textur_type == 0)
        {
            Animation wooden_armor = game_anim->animations->items_animation->equipment_animation->armors_animation->wooden_armor;
            wooden_armor.currentFrame = 0;

            anim_map[object_id] = wooden_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 1)
        {
            Animation leather_armor = game_anim->animations->items_animation->equipment_animation->armors_animation->leather_armor;
            //pr_int(medium_exp_anim.framesSpeed);
            leather_armor.currentFrame = 0;
            anim_map[object_id] = leather_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 2)
        {
            Animation iron_armor = game_anim->animations->items_animation->equipment_animation->armors_animation->iron_armor;
            //pr_int(medium_exp_anim.framesSpeed);
            iron_armor.currentFrame = 0;
            anim_map[object_id] = iron_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 3)
        {
            Animation mithril_armor = game_anim->animations->items_animation->equipment_animation->armors_animation->mithril_armor;
            //pr_int(medium_exp_anim.framesSpeed);
            mithril_armor.currentFrame = 0;
            anim_map[object_id] = mithril_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
    }
    else if (object_type ==WEAPON) 
    {   
        Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
        if (textur_type == 0)
        {
            Animation wooden_armor = game_anim->animations->items_animation->equipment_animation->swords_animation->wooden_weapon;
            wooden_armor.currentFrame = 0;

            anim_map[object_id] = wooden_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 1)
        {
            Animation leather_armor = game_anim->animations->items_animation->equipment_animation->swords_animation->stone_weapon;
            //pr_int(medium_exp_anim.framesSpeed);
            leather_armor.currentFrame = 0;
            anim_map[object_id] = leather_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 2)
        {
            Animation iron_armor = game_anim->animations->items_animation->equipment_animation->swords_animation->iron_weapon;
            //pr_int(medium_exp_anim.framesSpeed);
            iron_armor.currentFrame = 0;
            anim_map[object_id] = iron_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 3)
        {
            Animation mithril_armor = game_anim->animations->items_animation->equipment_animation->swords_animation->mithril_weapon;
            //pr_int(medium_exp_anim.framesSpeed);
            mithril_armor.currentFrame = 0;
            anim_map[object_id] = mithril_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
    }
    else if (object_type ==HELMET) 
    {   
        Animation* anim_map = game_anim->maps->animation_items_map->animation_map;
        if (textur_type == 0)
        {
            Animation wooden_armor = game_anim->animations->items_animation->equipment_animation->helmets_animation->wooden_HELMET;
            wooden_armor.currentFrame = 0;

            anim_map[object_id] = wooden_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 1)
        {
            Animation leather_armor = game_anim->animations->items_animation->equipment_animation->helmets_animation->leather_HELMET;
            //pr_int(medium_exp_anim.framesSpeed);
            leather_armor.currentFrame = 0;
            anim_map[object_id] = leather_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 2)
        {
            Animation iron_armor = game_anim->animations->items_animation->equipment_animation->helmets_animation->iron_HELMET;
            //pr_int(medium_exp_anim.framesSpeed);
            iron_armor.currentFrame = 0;
            anim_map[object_id] = iron_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
        else if (textur_type == 3)
        {
            Animation mithril_armor = game_anim->animations->items_animation->equipment_animation->helmets_animation->mithril_HELMET;
            //pr_int(medium_exp_anim.framesSpeed);
            mithril_armor.currentFrame = 0;
            anim_map[object_id] = mithril_armor;
            anim_map[object_id].index = object_id;
            anim_map[object_id].isPlaying = true;
            append_item_anim_to_arr(game_anim,&anim_map[object_id]);
        }
    }
}


void append_to_anim_enemy_list_updater(GAME_DATA* game_data,GAME_ANIM* game_anim,Enemy* enemy)
{
    if (enemy->current_animation != NULL)
    {
        //pr_int(444);   
        Animation*** anim_enemy_list = game_anim->maps->animation_enemies_map->animation_map_queue;
        int* amount = &game_anim->maps->animation_enemies_map->amount_animation_map_queue;
        anim_enemy_list[*amount] = enemy->current_animation;
        
        *amount+=1;
    }
    
}
void play_full_animation(GAME_DATA* game_data,Action* action,float directing_x,float directing_y)
{
    
    if (action->misc->max_fill == 2)
    {
        Animation* current_animation;
        if (action->object->object_type == ENEMY)
        {
            Enemy* enemy = get_enemy_from_enemy_map(game_data,action->object->object_index);
            current_animation = enemy->current_animation[0];
        }
        else if (action->object->object_type == PLAYER)
        {
            
            current_animation = game_data->player->current_anim[0];
        }
        directing_x *=64;
        directing_y *=64;
        if (directing_x<0)
        {
            directing_x *=-1;
        }
        if (directing_y<0)
        {
            directing_y *=-1;
        }
        float full_path = sqrtf(directing_x*directing_x+directing_y*directing_y);
        
        if (full_path == 0)
        {
            float speed = action->misc->speed;
            float amount_frames = current_animation->frameCount* action->misc->amount_full_moves*speed;
            action->misc->max_fill = amount_frames-1;
            current_animation->framesSpeed = speed;
            return;
        }
        float speed = action->misc->speed;
        float full_play_time = full_path /speed;
        float amount_frames = current_animation->frameCount* action->misc->amount_full_moves;
        float per_one_frame_speed = full_play_time/amount_frames;
        current_animation->framesSpeed = per_one_frame_speed;
        
    }
}