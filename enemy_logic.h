#ifndef ENEMY_LOGIC_H
#define ENEMY_LOGIC_H
#include <stdlib.h> 
#include "raylib.h"
#include "allocator.h"
#include "structurs.h"
#include "misc.h"
#include "texturs.h"
#include "items_logic.h"


void correctness_index_map_check(GAME_DATA *game_data, int **map);

void clear_visited_tiles(GAME_DATA *game_data);

void append_enemy_to_arr(GAME_DATA *game_data, Enemy *enemy, int map_index);

void spawn_enemy(GAME_DATA *game_data, int pos_x, int pos_y, int enemy_index, int enemy_type);

Enemy *create_enemy(Allocator *alloc, int enemy_indexes, int enemy_type, int start_posX, int start_posY);



Vector2 *path_finding(Allocator *alloc_path, GAME_DATA *game_data, Enemy *enemy, int mode);

Vector2 *restore_path(Allocator *alloc_path, GAME_DATA *game_data, Enemy *enemy, int player_pos_x, int player_pos_y);

void enemies_finding(GAME_DATA *game_data);

char enemy_activation(char **col_map, int current_pos_x, int current_pos_y, int relative_pos_x, int relative_pos_y);

void enemies_moving(GAME_DATA *game_data);

void enemy_moving(GAME_DATA *game_data, Enemy *enemy);

void enemy_attack(GAME_DATA *game_data, Enemy *enemy);

void enemy_life_check(GAME_DATA *game_data, GAME_ANIM *game_anim, Enemy *enemy, int enemy_x, int enemy_y);



void items_drop(GAME_DATA *game_data, GAME_ANIM *game_anim, Enemy *enemy, int enemy_x, int enemy_y);

void delete_from_move_queue(GAME_DATA *game_data, int id);

void enemies_rand_spawn(GAME_DATA *game_data);

#endif

