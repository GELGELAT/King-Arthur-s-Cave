#include "AnimationsUpdater.h"


void update_ememies_animations(GAME_ANIM* game_anim)
{
    Animation*** anim_enemy_list = game_anim->maps->animation_enemies_map->animation_map_queue;
    int* amount = &game_anim->maps->animation_enemies_map->amount_animation_map_queue;
    for (int i =0;i<*amount;i++)
    {
    
        //pr_int(*amount);
        //pr_int(anim_enemy_list[i]->frameCount);
        //pr_int(anim_enemy_list[i]->framesCounter);
        if (anim_enemy_list[i][0] != NULL)
        {
            update_animation(anim_enemy_list[i][0]);
        }
        
        //pr_int(anim_enemy_list[i]->texture.id);
        //pr_int(anim_enemy_list[i]->cur_frameRec.x);
    }
}

void update_items_animations(GAME_ANIM* game_anim)
{
    
    for (int i=0;i< game_anim->maps->animation_items_map->amount_animation_map_queue;i++)
    {
        //pr_int(game_anim->maps->animation_items_map->animation_map_queue[i]->framesCounter);
        //Animation anim = ;
        update_animation(game_anim->maps->animation_items_map->animation_map_queue[i]);
    }
}
void update_player_animations(GAME_ANIM* game_anim)
{
    
    for (int i=0;i< game_anim->maps->animation_player_map->amount_animation_map_queue;i++)
    {
        update_animation(game_anim->maps->animation_player_map->animation_map_queue[i][0]);
    }
}
void update_action_tiles_animations(GAME_ANIM* game_anim)
{
    
    for (int i=0;i< game_anim->maps->animation_world_maps->animation_action_tiles_map->amount_animation_action_tiles_map_queue;i++)
    {
        update_animation(game_anim->maps->animation_world_maps->animation_action_tiles_map->animation_action_tiles_map_queue[i]);
    }
}
void update_animation(Animation* anim)
{
    
    if (!anim->isPlaying)
    {
        return;
    }
    int direction = anim->direction;
    if (anim->frameCount == 1)
    {
        return;
    }
    //pr_int(anim->texture.id);
    anim->framesCounter+=1;
    if (anim->framesCounter >= (anim->framesSpeed)) 
    {
        anim->framesCounter = 0;
        anim->currentFrame++;
        
        if (anim->currentFrame >= anim->frameCount) 
        {
            anim->currentFrame = 0;
        }
        if (direction == Width)
        {
            anim->cur_frameRec.x = anim->start_frameRec.x+ (anim->currentFrame * anim->frameWidth);
        }
        else
        {
            anim->cur_frameRec.y = anim->start_frameRec.y+ (anim->currentFrame * anim->frameHeight);
        }
    
    }
}
