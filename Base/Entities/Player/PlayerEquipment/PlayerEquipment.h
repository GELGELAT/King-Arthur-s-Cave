#ifndef PLAYEREQUIPMENT_H
#define PLAYEREQUIPMENT_H

#include "PlayerLogic.h"
extern Vector2* equipment_pos_list[10];
extern Animation* armor_list[4];
extern Animation* sword_list[5];
extern Animation* helmet_list[4];
extern float sword_rotate[2];
void init_equipment_animations(GAME_DATA *game_data, GAME_ANIM *game_anim);

void apply_equipment(GAME_DATA *game_data, GAME_ANIM *game_anim, Player *player, int item_type, int index);

void update_equipment_pos(GAME_DATA *game_data);

#endif

