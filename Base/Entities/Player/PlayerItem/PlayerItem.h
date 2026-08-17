#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include "PlayerLogic.h"



int player_ground_check(GAME_DATA *game_data, int new_x, int new_y);

int take_item(GAME_DATA *game_data, int index, int pos_x, int pos_y);


#endif
