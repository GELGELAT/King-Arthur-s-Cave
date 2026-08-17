#ifndef UPDATER_H
#define UPDATER_H
#include "structurs.h"
#include "raylib.h"
#include <stdlib.h> 
#include "MiscScripts.h"
#include "texturs.h"
#include "FogLogic.h"
#include "EnemyLogic.h"
#include "PlayerLogic.h"
#include "ActionsUpdaterLogic.h"

//#define 

void GAME_UPDATE(GAME_DATA *game_data, GAME_ANIM *game_anim);

void camera_updater(GAME_DATA *game_data);


bool pos_player_updater(GAME_DATA *game_data, GAME_ANIM *game_anim);

void after_step(GAME_DATA *game_data);



#endif

