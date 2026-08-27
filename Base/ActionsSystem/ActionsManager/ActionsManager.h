#ifndef ACTIONSMANAGER_H
#define ACTIONSMANAGER_H

#include "ActionsUpdaterLogic.h"



void action_manager(GAME_DATA *game_data, int object_type, int object_index, int* movement_type, int* action_type, int during_type, int affected_type, int affected_index, Vector2 *position_pixels, Vector2 old_tile, Vector2 new_tile, float max_fill, float amount_full_anim, float speed);

void action_attacks(GAME_DATA *game_data, int object_type, int object_index, int* movement_type, int* action_type, int during_type, int affected_type, int affected_index, Vector2 *position_pixels, Vector2 old_tile, Vector2 new_tile, float max_fill, float amount_full_anim, float speed);

#endif

