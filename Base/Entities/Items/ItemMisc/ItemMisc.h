#ifndef ITEMMISC_H
#define ITEMMISC_H

#include "ItemLogic.h"
#include "ItemSpawn.h"
void item_throw(GAME_DATA *game_data, GAME_ANIM *game_anim, char *item_type, int start_x, int start_y);

int determine_value(char *item_type);

int *get_item_type_textur_type(char *item_type);

void equipments_rand_spawn(GAME_DATA *game_data, GAME_ANIM *game_anim);


#endif

