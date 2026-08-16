#ifndef ENEMYSPAWN_H
#define ENEMYSPAWN_H

#include "EnemyLogic.h"

void spawn_enemy(GAME_ANIM *game_anim, GAME_DATA *game_data, int pos_x, int pos_y, int enemy_index, int enemy_type, int skin);

Enemy *create_enemy(GAME_ANIM *game_anim, Allocator *alloc, int enemy_indexes, int enemy_type, int start_posX, int start_posY, int skin);

void append_enemy_to_arr(GAME_DATA *game_data, Enemy *enemy, int map_index);

void delete_from_move_queue(GAME_DATA *game_data, int id);

#endif


