#ifndef RENDERERMAP_H
#define RENDERERMAP_H

#include "RendererLogic.h"
#include "RendererEntities.h"


void map_draw(GAME_DATA *game_data, GAME_ANIM *game_anim);

void fog_draw(GAME_DATA *game_data, GAME_ANIM *game_anim);

void drawing_objects(GAME_DATA *game_data, GAME_ANIM *game_anim, char **objects, int tile_x, int tile_y, Vector2 pos_1, Vector2 pos_2);

void draw_floor_wall(GAME_ANIM *game_anim, char **objects, Vector2 pos_1, Vector2 pos_2);

void draw_fog(char **objects, Vector2 pos_1, Vector2 pos_2);

void floor_tile_draw(GAME_ANIM *game_anim, Vector2 pos, int frame_index);

void wall_tile_draw(GAME_ANIM *game_anim, Vector2 pos, int frame_index);


#endif


