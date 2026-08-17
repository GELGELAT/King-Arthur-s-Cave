#ifndef ACTIONSUPDATERLOGIC_H
#define ACTIONSUPDATERLOGIC_H
#include "structurs.h"
#include "raylib.h"
#include <stdlib.h> 
#include "MiscScripts.h"
#include "texturs.h"
#include "EnemyLogic.h"
#include "PlayerLogic.h"

#include "ActionsMisc.h"
#include "ActionForward.h"
#include "ActionBack.h"
#include "ActionRandom.h"
#include "ActionWithout.h"


#define MAIN_MAP 0
#define EFFECT_MAP 1

//ТИП ДВИЖЕНИЯ
#define WITHOUT_MOVING 0
#define FORWARD 1
#define BACK 2
#define RANDOM_MOVING 3

//ТИП СОБЫТИЯ
#define END 0
#define DURING 1

//ТИП ДЕЙСТВИЯ
#define MOVING 0
#define ATTACK 1
#define MINE 2
#define DIE 3
#define PREPARATION 4

//ТИП ОБЬЕКТА КОТОРЫЙ ДЕЛАЕТ ДЕЙСТВИЕ
//4 enemy

//СТАДИИ
#define ZERO_STAGE 0
#define FIRST_STAGE 1
#define SECOND_STAGE 2

void main_action_map_updater(GAME_DATA *game_data, GAME_ANIM *game_anim);

void append_action_to_actions_map(GAME_DATA *game_data, Action *action);
void delete_action_from_main_action_map(GAME_DATA* game_data,int current_pos_at_map);


#endif