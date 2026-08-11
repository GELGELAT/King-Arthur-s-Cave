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

#define PLAYER_BREATHE -1
#define WALK 0
#define ATTACK 1
#define PLAYER_MINE 2
#define DIE 3


void GAME_UPDATE(GAME_DATA *game_data, GAME_ANIM *game_anim);

void camera_updater(GAME_DATA *game_data);


bool pos_player_updater(GAME_DATA *game_data, GAME_ANIM *game_anim);

void after_step(GAME_DATA *game_data);



void append_to_action_map(GAME_DATA *game_data, Vector2 old_tile, Vector2 new_tile, Vector2 *pos_pixels, int cur_action, float speed, int enemy_index);

void delete_action_from_action_map(GAME_DATA *game_data, int cur_pos_at_map);

void action_q_updater(GAME_DATA *game_data, GAME_ANIM *game_anim);


void die_action_update(GAME_DATA *game_data, GAME_ANIM *game_anim, Action *action, int cur_pos_at_map);


void attack_action_update(GAME_DATA *game_data, Action *action, int cur_pos_at_map);

void walk_action_update(GAME_DATA *game_data, Action *action, int cur_pos_at_map);

void animation_direction(int directing_x, int directing_y, Enemy *enemy);

#endif

