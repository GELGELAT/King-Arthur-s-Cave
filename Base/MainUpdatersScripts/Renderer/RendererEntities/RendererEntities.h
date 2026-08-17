#ifndef RENDERERENTITIES_H
#define RENDERERENTITIES_H

#include "RendererLogic.h"


void draw_enemy(GAME_DATA *game_data);

void draw_item(GAME_DATA *game_data, GAME_ANIM *game_anim, char **objects, int x, int y, Vector2 pos_1, Vector2 pos_2);

void player_draw(GAME_DATA *game_data);

void any_coins_draw(GAME_ANIM *game_anim, Vector2 pos, int coins_type, int frame_index, int pos_index);



#endif

