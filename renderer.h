#ifndef RENDERER_H
#define RENDERER_H
#include "structurs.h"
#include "texturs.h"



void GAME_DRAW(GAME_DATA *game_data, GAME_ANIM *game_anim);


void map_draw(GAME_DATA *game_data, GAME_ANIM *game_anim);

void drawing_objects(GAME_DATA *game_data, GAME_ANIM *game_anim, char **objects, int tile_x, int tile_y, Vector2 pos_1, Vector2 pos_2);

void draw_floor_wall(GAME_ANIM *game_anim, char **objects, Vector2 pos_1, Vector2 pos_2);



void draw_enemy(char **objects, Vector2 pos_1, Vector2 pos_2);

void draw_fog(char **objects, Vector2 pos_1, Vector2 pos_2);

void draw_item(GAME_DATA *game_data, GAME_ANIM *game_anim, char **objects, int x, int y, Vector2 pos_1, Vector2 pos_2);




void player_draw(GAME_DATA *game_data);

void floor_tile_draw(GAME_ANIM *game_anim, Vector2 pos, int frame_index);

void wall_tile_draw(GAME_ANIM *game_anim, Vector2 pos, int frame_index);

void any_coins_draw(GAME_ANIM *game_anim, Vector2 pos, int coins_type, int frame_index, int pos_index);



#endif

