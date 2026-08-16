#include "ActionsMisc.h"

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