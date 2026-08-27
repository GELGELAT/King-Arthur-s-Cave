#ifndef ACTIONSUPDATERLOGIC_H
#define ACTIONSUPDATERLOGIC_H
#include "structurs.h"
#include "raylib.h"
#include <stdlib.h> 
#include "MiscScripts.h"
#include "AssetsLogic.h"
#include "EnemyLogic.h"
#include "PlayerLogic.h"

#include "ActionsMisc.h"
#include "ActionForward.h"
#include "ActionBack.h"
#include "ActionRandom.h"
#include "ActionWithout.h"
#include "ActionsManager.h"
#include "ActionsTilesLogic.h"


#define MAIN_MAP 0
#define EFFECT_MAP 1

//ТИП ДВИЖЕНИЯ
#define WITHOUT_MOVING 0
#define FORWARD 1
#define BACK 2
#define RANDOM_MOVING 3

//ТИП СОБЫТИЯ
#define START -1
#define END 0
#define DURING 1

//ТИП ДЕЙСТВИЯ
#define BREATH 8
#define MOVING 0
#define ATTACK 1
#define MINE 2
#define DIE 3
#define PREPARATION 4
#define FALL 5
#define CORPSE 6
#define RECEIVING_DAMAGE 7

#define NONE -1

typedef enum {
    ATTACK_PUNCH,
    ATTACK_JAB,
    ATTACK_SLASH,
    ATTACK_COUNT
} AttackType;

typedef void (*CreateActions)(GAME_DATA* game_data,//for alloc
    int object_type,int object_index, //main object
    int* movement_type ,int* action_type ,int during_type, // types and sub types
    int affected_type,int affected_index, //sub object
    Vector2* position_pixels,Vector2 old_tile,Vector2 new_tile, //pos info
    float max_fill,float amount_full_anim,float speed);
//ТИП АНИМАЦИИ
#define ANIMATION_FULL_PLAY -2
//ТИП ОБЬЕКТА КОТОРЫЙ ДЕЛАЕТ ДЕЙСТВИЕ
//4 enemy

//СТАДИИ
#define ZERO_STAGE 0
#define FIRST_STAGE 1
#define SECOND_STAGE 2
//ТИПЫ ДЕЙСТВИЙ
extern int movement_without_moving_none[2];
extern int movement_forward_none[2];
extern int movement_back_none[2];
extern int movement_random_moving_none[2];






extern int action_fall_die[2];
extern int action_corpse_die[2];
extern int action_die_die[2];
extern int action_moving_none[2];
extern int action_mine_none[2];
extern int action_attack_none[2];
extern int action_breath_none[2];
extern int action_preparation_none[2];



void main_action_map_updater(GAME_DATA *game_data, GAME_ANIM *game_anim);

void append_action_to_actions_map(GAME_DATA *game_data, Action *action);
void delete_action_from_main_action_map(GAME_DATA* game_data,int current_pos_at_map);


#endif