#ifndef FOGLOGIC_H
#define FOGLOGIC_H
#include "structurs.h"
#include "texturs.h"
void map_in_fog(GAME_DATA *game_data);

void player_review(GAME_DATA *game_data);

char colid_fog_check(char **col_map, int current_pos_x, int current_pos_y, int relative_pos_x, int relative_pos_y);


#endif

