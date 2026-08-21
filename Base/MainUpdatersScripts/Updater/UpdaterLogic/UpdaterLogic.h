#ifndef UPDATERLOGIC_H
#define UPDATERLOGIC_H
#include "structurs.h"
#include "raylib.h"
#include <stdlib.h> 
#include "MiscScripts.h"
#include "AssetsLogic.h"
#include "FogLogic.h"
#include "EnemyLogic.h"
#include "PlayerLogic.h"
#include "ActionsUpdaterLogic.h"


#include "UpdaterCamera.h"
#include "UpdaterStep.h"
//#define 

#define time_between_actions 15
#define first_state 1
#define second_state 2
#define third_state 2
#define DIE_TIME 35

void GAME_UPDATE(GAME_DATA *game_data, GAME_ANIM *game_anim);

void update_animations(GAME_ANIM *game_anim);

#endif

