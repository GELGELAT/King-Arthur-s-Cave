#include "PlayerItem.h"

int player_ground_check(GAME_DATA* game_data,GAME_ANIM* game_anim,int new_x,int new_y)
{
    int taken=-2;
    CellsMap* objects_map =game_data->maps->cells_map;
    int** items_indices = game_data->maps->items_map->index_map;
    
    if (items_indices[new_x][new_y] != -1)
    {
         taken = take_item(game_data,game_anim,items_indices[new_x][new_y],new_x,new_y);
    }
    if (taken != -1)
    {
        objects_map->cells[new_x][new_y]->objects[1] = NULL;
        items_indices[new_x][new_y] = -1;
        return taken;
    }
}

int take_item(GAME_DATA* game_data,GAME_ANIM* game_anim,int index,int pos_x,int pos_y)
{
    Player* player = game_data->player;
    Item** items_map = game_data->maps->items_map->items_map;
    Item* item = items_map[index];
    char* item_type = item->item_main->name;
    for (int i = 0; i<4;i++)
    {
        if(item_type == textur(ARMOR_CHEST,i))
        {
            if (player->player_stats->player_equipment_tier->armor_tier < i+1) 
            {
                player->player_stats->player_equipment_tier->armor_tier = i+1;
                apply_equipment(game_data,game_anim,player,ARMOR_CHEST,i);
                return index;
            }
            return -1;
        }
        else if(item_type == textur(WEAPON,i))
        {
            if (player->player_stats->player_equipment_tier->sword_tier < i+1)
            {
                player->player_stats->player_equipment_tier->sword_tier = i+1;
                apply_equipment(game_data,game_anim,player,WEAPON,i);
                return index;
            }
            return -1;
        }
        else if(item_type == textur(HELMET,i))
        {
            if (player->player_stats->player_equipment_tier->HELMET_tier < i+1)
            {
                player->player_stats->player_equipment_tier->HELMET_tier = i+1;
                apply_equipment(game_data,game_anim,player,HELMET,i);
                return index;
            }
            return -1;
        }
    }
    for (int i = 0; i<2;i++)
    {
        if(item_type == textur(COINS,i))
        {
            game_data->player->player_stats->player_coins->coins +=item->item_main->value;
            pr_int(game_data->player->player_stats->player_coins->coins);
            return index;

        }
        else if(item_type == textur(HEALS,i))
        {
            game_data->player->player_stats->player_characteristics->heal_points +=item->item_main->value;
            pr_int(game_data->player->player_stats->player_characteristics->heal_points);
            return index;

        }
        else if(item_type == textur(EXP,i))
        {
            game_data->player->player_stats->player_exp->experience_points +=item->item_main->value;
            pr_int_with_text(game_data->player->player_stats->player_exp->experience_points,"cur_exp");
            
            return index;

        }

    }
    return -1;
}
