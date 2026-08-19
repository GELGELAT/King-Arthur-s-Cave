#include "PlayerMove.h"

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
    
}