#include "PlayerEquipment.h"
int equipment_list[10] = {0};
Vector2* equipment_pos_list[10] = {0};
//ANIM ARRS

Animation* armor_list[4];
Animation* sword_list[4];
Animation* helmet_list[4];
//POS ARRS
Vector2 reletiv_cur_equipment_pos[10]={0};
Vector2 player_equipment_alignment[10][10][10] = {0};
Vector2 player_equipment_offsets[10][10][2];


void init_equipment_animations(GAME_DATA* game_data,GAME_ANIM* game_anim) 
{
    armor_list[0] = &game_anim->animations->items_animation->equipment_animation->armors_animation->wooden_armor_no_line;
    armor_list[1] = &game_anim->animations->items_animation->equipment_animation->armors_animation->leather_armor_no_line;
    armor_list[2] = &game_anim->animations->items_animation->equipment_animation->armors_animation->iron_armor_no_line;
    armor_list[3] = &game_anim->animations->items_animation->equipment_animation->armors_animation->mithril_armor_no_line;

    sword_list[0] = &game_anim->animations->items_animation->equipment_animation->swords_animation->wooden_weapon_no_line;
    sword_list[1] = &game_anim->animations->items_animation->equipment_animation->swords_animation->stone_weapon_no_line;
    sword_list[2] = &game_anim->animations->items_animation->equipment_animation->swords_animation->iron_weapon_no_line;
    sword_list[3] = &game_anim->animations->items_animation->equipment_animation->swords_animation->mithril_weapon_no_line;

    helmet_list[0] = &game_anim->animations->items_animation->equipment_animation->helmets_animation->wooden_HELMET_no_line;
    helmet_list[1] = &game_anim->animations->items_animation->equipment_animation->helmets_animation->leather_HELMET_no_line;
    helmet_list[2] = &game_anim->animations->items_animation->equipment_animation->helmets_animation->iron_HELMET_no_line;
    helmet_list[3] = &game_anim->animations->items_animation->equipment_animation->helmets_animation->mithril_HELMET_no_line;
    //OFFSET
    int center_x = 24;
    int armor_center_y = 18;
    player_equipment_offsets[BREATH][ARMOR_CHEST][0] = (Vector2){center_x-4,armor_center_y};
    player_equipment_offsets[BREATH][ARMOR_CHEST][1] = (Vector2){center_x+4,armor_center_y};
    player_equipment_offsets[MOVING][ARMOR_CHEST][0] = (Vector2){center_x+5,armor_center_y};
    player_equipment_offsets[MOVING][ARMOR_CHEST][1] = (Vector2){center_x-5,armor_center_y};
    player_equipment_offsets[ATTACK][ARMOR_CHEST][0] = (Vector2){center_x+6,armor_center_y};
    player_equipment_offsets[ATTACK][ARMOR_CHEST][1] = (Vector2){center_x-6,armor_center_y};
    player_equipment_offsets[MINE][ARMOR_CHEST][0] = (Vector2){center_x+6,armor_center_y};
    player_equipment_offsets[MINE][ARMOR_CHEST][1] = (Vector2){center_x-6,armor_center_y};
    
    player_equipment_offsets[BREATH][WEAPON][0] = (Vector2){center_x,32};
    player_equipment_offsets[BREATH][WEAPON][1] = (Vector2){center_x,32};
    player_equipment_offsets[MOVING][WEAPON][0] = (Vector2){center_x+6,32};
    player_equipment_offsets[MOVING][WEAPON][1] = (Vector2){center_x-6,32};
    player_equipment_offsets[ATTACK][WEAPON][0] = (Vector2){center_x+6,32};
    player_equipment_offsets[ATTACK][WEAPON][1] = (Vector2){center_x-6,32};
    player_equipment_offsets[MINE][WEAPON][0] = (Vector2){center_x+6,32};
    player_equipment_offsets[MINE][WEAPON][1] = (Vector2){center_x-6,32};
    int helmet_center_y = 36;
    player_equipment_offsets[BREATH][HELMET][0] = (Vector2){center_x,helmet_center_y};
    player_equipment_offsets[BREATH][HELMET][1] = (Vector2){center_x,helmet_center_y};
    player_equipment_offsets[MOVING][HELMET][0] = (Vector2){center_x+6,helmet_center_y};
    player_equipment_offsets[MOVING][HELMET][1] = (Vector2){center_x-6,helmet_center_y};
    player_equipment_offsets[ATTACK][HELMET][0] = (Vector2){center_x+6,helmet_center_y};
    player_equipment_offsets[ATTACK][HELMET][1] = (Vector2){center_x-6,helmet_center_y};
    player_equipment_offsets[MINE][HELMET][0] = (Vector2){center_x+6,helmet_center_y};
    player_equipment_offsets[MINE][HELMET][1] = (Vector2){center_x-6,helmet_center_y};

    //ALIGNMENT
    player_equipment_alignment[BREATH][ARMOR_CHEST][0] = (Vector2){0,0};
    player_equipment_alignment[BREATH][ARMOR_CHEST][1] = (Vector2){0,-1};
    player_equipment_alignment[BREATH][ARMOR_CHEST][2] = (Vector2){0,0};
    player_equipment_alignment[BREATH][ARMOR_CHEST][3] = (Vector2){0,1};

    player_equipment_alignment[BREATH][WEAPON][0] = (Vector2){0,0};
    player_equipment_alignment[BREATH][WEAPON][1] = (Vector2){0,-1};
    player_equipment_alignment[BREATH][WEAPON][2] = (Vector2){0,0};
    player_equipment_alignment[BREATH][WEAPON][3] = (Vector2){0,1};

    player_equipment_alignment[BREATH][HELMET][0] = (Vector2){0,0};
    player_equipment_alignment[BREATH][HELMET][1] = (Vector2){0,-1};
    player_equipment_alignment[BREATH][HELMET][2] = (Vector2){0,0};
    player_equipment_alignment[BREATH][HELMET][3] = (Vector2){0,1};

    equipment_list[0] = ARMOR_CHEST;
    equipment_list[1] =WEAPON;
    equipment_list[2] =HELMET;

    equipment_pos_list[ARMOR_CHEST]= &game_data->player->player_pos->equipment_pos->armor_pos->current_pos;
    equipment_pos_list[WEAPON]= &game_data->player->player_pos->equipment_pos->sword_pos->current_pos;
    equipment_pos_list[HELMET]= &game_data->player->player_pos->equipment_pos->helmet_pos->current_pos;
}

void apply_equipment(GAME_DATA* game_data,GAME_ANIM* game_anim,Player* player,int item_type,int index)
{
    
    if (item_type == ARMOR_CHEST)
    {
        player->player_stats->player_characteristics->defense = armor_stats[index]; 
        player->current_animations->current_equipment_anim->current_armor_anim[0] = armor_list[index];
        
        
    }
    else if (item_type == WEAPON)
    {
        player->player_stats->player_characteristics->min_physical_damage = weapon_stats[index];
        player->player_stats->player_characteristics->max_physical_damage = weapon_stats[index];
        player->current_animations->current_equipment_anim->current_sword_anim[0] = sword_list[index];
    }
    else if (item_type == HELMET)
    {
        player->player_stats->player_characteristics->defense = HELMET_stats[index];
        player->current_animations->current_equipment_anim->current_helmet_anim[0] = helmet_list[index];
    }
    
}



void update_equipment_pos(GAME_DATA* game_data)
{
    Player* player = game_data->player;
    int current_anim_index = get_current_animation(player->current_animations->current_anim[0]);
    Vector2 current_player_pos=game_data->player->player_pos->position_pixels->pos_pixels;
    for (int i = 0;i <3;i++)
    {
        int current_equipment = equipment_list[i];
        Vector2 current_equipment_offset = player_equipment_offsets[current_anim_index][current_equipment][current_direction];
        Vector2 reletiv_equipmen_pos = (Vector2){current_player_pos.x-current_equipment_offset.x,current_player_pos.y-current_equipment_offset.y};
        reletiv_cur_equipment_pos[current_equipment] = reletiv_equipmen_pos;
        Vector2 current_equipment_alignment = player_equipment_alignment[current_anim_index][current_equipment][player->current_animations->current_anim[0]->currentFrame];
        Vector2 current_pos = (Vector2){reletiv_cur_equipment_pos[current_equipment].x+current_equipment_alignment.x,reletiv_cur_equipment_pos[current_equipment].y+current_equipment_alignment.y}; //CUR_POS
        *equipment_pos_list[current_equipment] = current_pos;
    }
    
    
}