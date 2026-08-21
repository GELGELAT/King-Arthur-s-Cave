#include "PlayerHead.h"

Animation* head_list[3];
//int head_breath_alignment_y[4] = {0,-1,0,1};
Vector2 reletiv_cur_head_pos;
Vector2 player_head_alignment[10][10] = {0};
Vector2 player_head_offsets[10][2];

Animation* head_action_anim_list[10];
void init_head_offsets_and_alignment_animations(GAME_DATA* game_data,GAME_ANIM* game_anim) 
{
    //OFFSET
    int center_x = 24;
    player_head_offsets[BREATH][0] = (Vector2){center_x,32};
    player_head_offsets[BREATH][1] = (Vector2){center_x,32};
    player_head_offsets[MOVING][0] = (Vector2){center_x+6,32};
    player_head_offsets[MOVING][1] = (Vector2){center_x-6,32};
    player_head_offsets[ATTACK][0] = (Vector2){center_x+6,32};
    player_head_offsets[ATTACK][1] = (Vector2){center_x-6,32};
    player_head_offsets[MINE][0] = (Vector2){center_x+6,32};
    player_head_offsets[MINE][1] = (Vector2){center_x-6,32};

    //ALIGNMENT
    player_head_alignment[BREATH][0] = (Vector2){0,0};
    player_head_alignment[BREATH][1] = (Vector2){0,-1};
    player_head_alignment[BREATH][2] = (Vector2){0,0};
    player_head_alignment[BREATH][3] = (Vector2){0,1};
}
void init_head_animations(GAME_DATA* game_data,GAME_ANIM* game_anim) 
{
    
    game_data->player->player_anim->player_head_animation->ordinary_head_animation=game_anim->animations->player_animation->human_head_animations->human_head_0_animations->ordinary;
    game_data->player->player_anim->player_head_animation->angry_head_animation=game_anim->animations->player_animation->human_head_animations->human_head_0_animations->angry;
    game_data->player->player_anim->player_head_animation->weak_head_animation=game_anim->animations->player_animation->human_head_animations->human_head_0_animations->weak;
    
    head_list[0] = &game_data->player->player_anim->player_head_animation->ordinary_head_animation;
    head_list[1] = &game_data->player->player_anim->player_head_animation->angry_head_animation;
    head_list[2] = &game_data->player->player_anim->player_head_animation->weak_head_animation;

    head_list[0]->cur_frameRec.width = -16;
    head_list[1]->cur_frameRec.width =-16;
    head_list[2]->cur_frameRec.width = -16;

    head_action_anim_list[BREATH] = head_list[0];
    head_action_anim_list[ATTACK] = head_list[1];
    head_action_anim_list[MINE] = head_list[1];
    head_action_anim_list[MOVING] = head_list[0];

    game_data->player->current_animations->current_head_anim[0] = head_list[0];
    game_data->player->player_anim->player_head_animation->size_x=48;
    game_data->player->player_anim->player_head_animation->size_y=48;
}
void update_current_head(GAME_DATA* game_data)
{
    Player* player = game_data->player;
    int current_anim_index = get_current_animation(player->current_animations->current_anim[0]);
    game_data->player->current_animations->current_head_anim[0] = head_action_anim_list[current_anim_index]; //CURR_ANIM
    Vector2 current_player_pos=game_data->player->player_pos->position_pixels->pos_pixels;
    Vector2 current_head_offset = player_head_offsets[current_anim_index][current_direction];
    Vector2 reletiv_head_pos = (Vector2){current_player_pos.x-current_head_offset.x,current_player_pos.y-current_head_offset.y};
    reletiv_cur_head_pos = reletiv_head_pos;
    Vector2 current_head_alignment = player_head_alignment[current_anim_index][player->current_animations->current_anim[0]->currentFrame];
    Vector2 current_pos = (Vector2){reletiv_cur_head_pos.x+current_head_alignment.x,reletiv_cur_head_pos.y+current_head_alignment.y}; //CUR_POS
    game_data->player->player_pos->head_pos->current_pos = current_pos;
    
}