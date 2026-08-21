#ifndef PLAYEREQUIPMENT_H
#define PLAYEREQUIPMENT_H

#include "PlayerLogic.h"

void init_equipment_animations(GAME_ANIM *game_anim);

void apply_equipment(GAME_DATA *game_data, GAME_ANIM *game_anim, Player *player, int item_type, int index);

#endif

