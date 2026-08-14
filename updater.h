#ifndef UPDATER_H
#define UPDATER_H
#include "structurs.h"
#include "raylib.h"
#include <stdlib.h> 
#include "misc.h"
#include "texturs.h"
#include "fog.h"
#include "enemy_logic.h"
#include "player_logic.h"
#include "actions_work.h"

//#define 

void GAME_UPDATE(GAME_DATA *game_data, GAME_ANIM *game_anim);

void camera_updater(GAME_DATA *game_data);


bool pos_player_updater(GAME_DATA *game_data, GAME_ANIM *game_anim);

void after_step(GAME_DATA *game_data);



#endif

