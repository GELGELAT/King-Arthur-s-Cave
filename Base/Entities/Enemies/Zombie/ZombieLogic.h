#ifndef ZOMBIELOGIC_H
#define ZOMBIELOGIC_H
#include <stdlib.h> 
#include "raylib.h"
#include "Allocator.h"
#include "structurs.h"
#include "MiscScripts.h"
#include "AssetsLogic.h"
#include "ItemLogic.h"
#include "UpdaterLogic.h"
#include "ActionsUpdaterLogic.h"


bool zombie_revival_move(GAME_DATA *game_data, Enemy *enemy, Vector2 *path);

bool revival_check(GAME_DATA *game_data, GAME_ANIM *game_anim, Enemy *enemy);

#endif

