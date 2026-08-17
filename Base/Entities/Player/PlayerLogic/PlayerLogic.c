#include "PlayerLogic.h"

void apply_equipment(Player* player,int item_type,int index)
{
    if (item_type == ARMOR_CHEST)
    {
        player->player_stats->player_characteristics->defense += armor_stats[index]; 
    }
    else if (item_type == WEAPON)
    {
        player->player_stats->player_characteristics->min_physical_damage += weapon_stats[index];
        player->player_stats->player_characteristics->max_physical_damage += weapon_stats[index];
    }
    else if (item_type == HELMET)
    {
        player->player_stats->player_characteristics->defense += HELMET_stats[index];
    }
    
}