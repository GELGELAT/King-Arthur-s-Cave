

#ifndef ENEMYMOVE_H
#define ENEMYMOVE_H

#include "EnemyLogic.h"
#include "EnemyPath.h"

void enemies_moving(GAME_DATA *game_data);

void enemy_moving(GAME_DATA *game_data, Enemy *enemy);

void enemy_attack(GAME_DATA *game_data, Enemy *enemy);

void enemy_fast_attack(GAME_DATA *game_data, GAME_ANIM *game_anim, Enemy *enemy_attacker, Enemy *enemy_accepting);


#endif

