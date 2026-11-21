#ifndef ITEMSPAWN_H
#define ITEMSPAWN_H

#include "ItemLogic.h"
#include "ItemMisc.h"
void spawn_item(GAME_DATA *game_data, GAME_ANIM *game_anim, int pos_x, int pos_y, char *item_type);

Item *create_item(int index, int pos_x, int pos_y, char *item_type);


void append_to_items_map(GAME_DATA *game_data, Item *item);

void delete_from_items_map(GAME_DATA *game_data, int index);

#endif

