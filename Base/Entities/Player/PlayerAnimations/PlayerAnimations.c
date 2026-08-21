#include "PlayerAnimations.h"

Animation* player_animations[10];

void player_anim_init(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    Player* player = game_data->player;
    player->player_anim->player_action_animation->player_breathe_animation = game_anim->animations->player_animation->human_animations->player_breathe_animation;
    player->player_anim->player_action_animation->player_walk_animation = game_anim->animations->player_animation->human_animations->player_walk_animation;
    player->player_anim->player_action_animation->player_attack_animation =game_anim->animations->player_animation->human_animations->player_attack_animation;
    player->player_anim->player_action_animation->player_mine_animation = game_anim->animations->player_animation->human_animations->player_mine_animation;
    init_head_animations(game_data,game_anim);
    init_player_animations(game_data);
    init_head_offsets_and_alignment_animations(game_data,game_anim);
    append_player_anim_to_arr(game_anim,game_data->player->current_animations->current_anim);
}
void init_player_animations(GAME_DATA* game_data)
{
    Player* player = game_data->player;
    player_animations[BREATH] = &player->player_anim->player_action_animation->player_breathe_animation;
    player_animations[MOVING] = &player->player_anim->player_action_animation->player_walk_animation;
    player_animations[ATTACK] = &player->player_anim->player_action_animation->player_attack_animation;
    player_animations[MINE] = &player->player_anim->player_action_animation->player_mine_animation;
    //player_animations[RECEIVING_DAMAGE] = player->player_anim->player_action_animation->;
}
int get_current_animation(Animation* current_animation)
{
    if (current_animation == player_animations[BREATH])
    {
        return BREATH;
    }
    else if (current_animation == player_animations[MOVING])
    {
        return MOVING;
    }
    else if (current_animation == player_animations[ATTACK])
    {
        return ATTACK;
    }
    else if (current_animation == player_animations[MINE])
    {
        return MINE;
    }
}