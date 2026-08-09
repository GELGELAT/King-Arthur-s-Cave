#ifndef PLAYER_LOGIC_H
#define PLAYER_LOGIC_H

#include "structurs.h"
#include "misc.h"
#include "enemy_logic.h"
#include "items_logic.h"




void player_attaks(GAME_DATA *game_data, GAME_ANIM *game_anim, int enemy_x, int enemy_y);

int player_ground_check(GAME_DATA *game_data, int new_x, int new_y);

int take_item(GAME_DATA *game_data, int index, int pos_x, int pos_y);

void apply_equipment(Player *player, int item_type, int index);

#endif

