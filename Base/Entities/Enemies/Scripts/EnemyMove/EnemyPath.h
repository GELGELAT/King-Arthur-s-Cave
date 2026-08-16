#ifndef ENEMYPATH_H
#define ENEMYPATH_H

#include "EnemyLogic.h"

#define persecution 1
#define search 2

void clear_visited_tiles(GAME_DATA *game_data);

Vector2 *path_finding(Allocator *alloc_path, GAME_DATA *game_data, Enemy *enemy, int mode);

Vector2 *restore_path(Allocator *alloc_path, GAME_DATA *game_data, Enemy *enemy, int player_pos_x, int player_pos_y);
#endif

