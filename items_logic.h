#ifndef ITEM_LOGIC_H
#define ITEM_LOGIC_H
#include "structurs.h"
#include "misc.h"
#include "texturs.h"
#include "player_logic.h"

extern int armor_stats[];
extern int weapon_stats[];
extern int HELMET_stats[];
extern int items_indices;



Item *create_item(Allocator *alloc, int index, int pos_x, int pos_y, char *item_type);
void item_throw(GAME_DATA *game_data, GAME_ANIM *game_anim, char *item_type, int start_x, int start_y);
int determine_value(char *item_type);
void append_to_items_map(GAME_DATA *game_data, Item *item);
void spawn_item(GAME_DATA *game_data, GAME_ANIM *game_anim, int pos_x, int pos_y, char *item_type);

int* get_item_type_textur_type(char *item_type);

void equipments_rand_spawn(GAME_DATA *game_data, GAME_ANIM *game_anim);



#endif

