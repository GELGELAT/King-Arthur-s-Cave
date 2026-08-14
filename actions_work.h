#ifndef ACTIONS_WORK_H
#define ACTIONS_WORK_H
#include "structurs.h"
#include "raylib.h"
#include <stdlib.h> 
#include "misc.h"
#include "texturs.h"
#include "fog.h"
#include "enemy_logic.h"
#include "player_logic.h"

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

#endif

void append_action_to_actions_map(GAME_DATA *game_data, Action *action);

void main_action_map_updater(GAME_DATA *game_data, GAME_ANIM *game_anim);

void delete_action_from_main_action_map(GAME_DATA *game_data, int current_pos_at_map);

void without_movement_action_update(GAME_DATA *game_data, GAME_ANIM *game_anim, Action *action);

void forward_movement_action_update(GAME_DATA *game_data, GAME_ANIM *game_anim, Action *action);

void back_movement_action_update(GAME_DATA *game_data, GAME_ANIM *game_anim, Action *action);

void random_movement_action_update(GAME_DATA *game_data, GAME_ANIM *game_anim, Action *action);

void player_animation_direction(int directing_x, int directing_y, Player *player);

void enemy_animation_direction(int directing_x, int directing_y, Enemy *enemy);
