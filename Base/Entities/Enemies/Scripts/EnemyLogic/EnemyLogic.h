#ifndef ENEMYLOGIC_H
#define ENEMYLOGIC_H
#include <stdlib.h> 
#include "raylib.h"
#include "Allocator.h"
#include "structurs.h"
#include "MiscScripts.h"
#include "AssetsLogic.h"
#include "ItemLogic.h"
#include "UpdaterLogic.h"
#include "ActionsUpdaterLogic.h"

#include "EnemyMisc.h"
#include "EnemyMove.h"
#include "EnemyPath.h"
#include "EnemySpawn.h"

#include "ZombieArmLogic.h"
#include "ZombieChickenLogic.h"


#define CHICKEN_ZOMBIE 0
#define ARM_ZOMBIE 1


void enemies_finding(GAME_DATA *game_data);

char enemy_activation(char **col_map, int current_pos_x, int current_pos_y, int relative_pos_x, int relative_pos_y);


#endif
