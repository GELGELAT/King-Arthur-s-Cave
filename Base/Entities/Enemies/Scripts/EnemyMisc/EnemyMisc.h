#ifndef ENEMYMISC_H
#define ENEMYMISC_H

#include "EnemyLogic.h"

void plus_to_stamina(Enemy *enemy);

void enemy_life_check(GAME_DATA *game_data, GAME_ANIM *game_anim, Enemy *enemy);

void items_drop(GAME_DATA *game_data, GAME_ANIM *game_anim, Enemy *enemy, int enemy_x, int enemy_y);

void enemies_rand_spawn(GAME_DATA *game_data, GAME_ANIM *game_anim);

Enemy *get_enemy_from_enemy_map(GAME_DATA *game_data, int enemy_index);

#endif


