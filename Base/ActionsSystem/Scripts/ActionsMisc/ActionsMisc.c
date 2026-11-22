#include "ActionsMisc.h"
int current_direction = 0;
void player_animation_direction(int directing_x,int directing_y,Player* player)
{
    int width = player->player_anim->player_action_animation->player_breathe_animation.frameWidth;
    if (directing_x>0)
    {
        player->player_anim->player_action_animation->player_attack_animation.cur_frameRec.width = -width;
        player->player_anim->player_action_animation ->player_breathe_animation.cur_frameRec.width= -width;
        player->player_anim->player_action_animation->player_walk_animation.cur_frameRec.width = -width;
        player->player_anim->player_action_animation->player_mine_animation.cur_frameRec.width = -width;
        head_list[0]->cur_frameRec.width = 16;
        head_list[1]->cur_frameRec.width =16;
        head_list[2]->cur_frameRec.width = 16;
        for (int i=0;i<4;i++)
        {
            armor_list[i]->cur_frameRec.width = 17;
            sword_list[i]->cur_frameRec.width = 17;
            helmet_list[i]->cur_frameRec.width = 17;
        }
        current_direction = RIGHT;
        //player->player_anim. = -width;
       // player->player_anim = -width;
    }
    if (directing_x<0)
    {
        
        player->player_anim->player_action_animation->player_attack_animation.cur_frameRec.width = width;
        player->player_anim->player_action_animation ->player_breathe_animation.cur_frameRec.width= width;
        player->player_anim->player_action_animation->player_walk_animation.cur_frameRec.width = width;
        player->player_anim->player_action_animation->player_mine_animation.cur_frameRec.width = width;
        head_list[0]->cur_frameRec.width = -16;
        head_list[1]->cur_frameRec.width = -16;
        head_list[2]->cur_frameRec.width = -16;
        for (int i=0;i<4;i++)
        {
            armor_list[i]->cur_frameRec.width = -17;
            sword_list[i]->cur_frameRec.width = -17;
            helmet_list[i]->cur_frameRec.width = -17;
        }
        current_direction = LEFT;
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
        enemy->enemy_animations->fall.cur_frameRec.width = -width;
        enemy->enemy_animations->corpse.cur_frameRec.width = -width;
        enemy->enemy_animations->preparation.cur_frameRec.width = -width;
        enemy->enemy_animations->receiving_damage.cur_frameRec.width = -width;
        enemy->enemy_animations_effects->effect_attack->anim.cur_frameRec.width=24;
    }
    if (directing_x<0)
    {
        enemy->enemy_animations->walk.cur_frameRec.width = width;
        enemy->enemy_animations->attack.cur_frameRec.width = width;
        enemy->enemy_animations->breathe.cur_frameRec.width = width;
        enemy->enemy_animations->fall.cur_frameRec.width = width;
        enemy->enemy_animations->corpse.cur_frameRec.width = width;
        enemy->enemy_animations->preparation.cur_frameRec.width = width;
        enemy->enemy_animations->receiving_damage.cur_frameRec.width = width;
        enemy->enemy_animations_effects->effect_attack->anim.cur_frameRec.width=-24;
    }
    
}
void action_deleter(void* action)
{
    Action* ac = (Action*)action;
    Allocator* alloc = ac->alloc;
    destroy_allocator(alloc);
}
bool action_fill_check(void* data_)
{
    Action*current_action=(Action*) data_;
    float current_fill = current_action->misc->current_fill;
    float max_fill = current_action->misc->max_fill;
    if (current_fill >=max_fill)
    {
        return false;
    }
    return true;
}
void action_activation(void* action_,void* game_data_,void* game_anim_)
{

    Action* current_action = (Action*)action_;
    GAME_DATA* game_data = (GAME_DATA*)game_data_;
    GAME_ANIM* game_anim =(GAME_ANIM*)game_anim_;
    
    int* movement_type = current_action->main->movement_type;
    if (movement_type[0] == WITHOUT_MOVING)
    {
        without_movement_action_update(game_data,game_anim,current_action);
        
    }
    else if (movement_type[0] == FORWARD)
    {
        forward_movement_action_update(game_data,game_anim,current_action);
        
    }
    else if (movement_type[0] == BACK)
    {
        back_movement_action_update(game_data,game_anim,current_action);
        
    }
    else if (movement_type[0] == RANDOM_MOVING)
    {
        random_movement_action_update(game_data,game_anim,current_action);
        
    }
    
}
