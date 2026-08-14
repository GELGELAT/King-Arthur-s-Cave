#include "player_logic.h"
void player_attaks(GAME_DATA* game_data, GAME_ANIM* game_anim,int enemy_x, int enemy_y)
{
    Vector2 old_tile = {game_data->player->player_pos->position_tiles->pos_tiles.x,game_data->player->player_pos->position_tiles->pos_tiles.y};
    Vector2 new_tile = {(float)enemy_x,(float)enemy_y};
    
    EnemyMap* enemy_map = game_data->maps->enemy_map;
    int** id_map = enemy_map->index_map;
    int current_enemy_id = id_map[enemy_x][enemy_y];
    Enemy* current_enemy = enemy_map->enemy_map[current_enemy_id];
    
    Player* player = game_data->player;
    int player_damage = rand_num_within(player->player_stats->player_characteristics->min_physical_damage,player->player_stats->player_characteristics->max_physical_damage);
    
    int enemy_heals = current_enemy->enemy_characteristics->heal_points;
    pr_int_with_text(current_enemy->enemy_characteristics->heal_points,"enemy hp");
    int enemy_def = current_enemy->enemy_characteristics->defense;
    int damage_after_def = player_damage - enemy_def;
    if (damage_after_def < 0)
    {
        damage_after_def =0;
    }
    current_enemy->enemy_characteristics->heal_points = enemy_heals - damage_after_def;
    pr_int_with_text(current_enemy->enemy_characteristics->heal_points,"enemy hp");
    enemy_life_check(game_data,game_anim,current_enemy);
}

int player_ground_check(GAME_DATA* game_data,int new_x,int new_y)
{
    int taken=-2;
    CellsMap* objects_map =game_data->maps->cells_map;
    int** items_indices = game_data->maps->items_map->index_map;
    
    if (items_indices[new_x][new_y] != -1)
    {
         taken = take_item(game_data,items_indices[new_x][new_y],new_x,new_y);
    }
    if (taken != -1)
    {
        objects_map->cells[new_x][new_y]->objects[1] = NULL;
        items_indices[new_x][new_y] = -1;
        return taken;
    }
}

int take_item(GAME_DATA* game_data,int index,int pos_x,int pos_y)
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
                apply_equipment(player,ARMOR_CHEST,i);
                return index;
            }
            return -1;
        }
        else if(item_type == textur(WEAPON,i))
        {
            if (player->player_stats->player_equipment_tier->sword_tier < i+1)
            {
                player->player_stats->player_equipment_tier->sword_tier = i+1;
                apply_equipment(player,WEAPON,i);
                return index;
            }
            return -1;
        }
        else if(item_type == textur(HELMET,i))
        {
            if (player->player_stats->player_equipment_tier->HELMET_tier < i+1)
            {
                player->player_stats->player_equipment_tier->HELMET_tier = i+1;
                apply_equipment(player,HELMET,i);
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