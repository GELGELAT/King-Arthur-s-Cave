#ifndef ACTIONSTILESLOGIC_H
#define ACTIONSTILESLOGIC_H

#include "ActionsUpdaterLogic.h"

extern Vector2 actions_tiles_glow_plus_one[4];
extern int actions_tiles_glow_plus_one_amount;

void actions_mark_tiles(GAME_DATA *game_data, Vector2 current_pos, Vector2 *mark_increments, int amount_increments);

void actions_clear_mark_tiles(GAME_DATA *game_data);

bool actions_mouse_click_check(GAME_DATA *game_data, Vector2 mouse_click);

#endif

