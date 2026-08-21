#include "PlayerEquipment.h"

Animation* armor_list[4];
Animation* sword_list[4];
Animation* helmet_list[4];


void init_equipment_animations(GAME_ANIM* game_anim) 
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