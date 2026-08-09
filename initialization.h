#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include "structurs.h"
#include "allocator.h"
#include "generators.h"     
#include "misc.h"     
#include "texturs.h"     
#include "enemy_logic.h"     
#include "fog.h"
#include "items_logic.h"





bool GAME_INIT(GAME_DATA *game_data, int tilesX, int tilesY, int tileSize, GAME_ANIM *game_anim);

bool window_init(GAME_DATA *game_data);


bool structurs_init(GAME_DATA *game_data, GAME_ANIM *game_anim, int tilesX, int tilesY, int tileSize);

void anim_init(GAME_ANIM *game_anim);

bool path_init(GAME_DATA *game_data);

bool items_map_init(GAME_DATA *game_data);

bool allcator_init(GAME_DATA *game_data);

bool player_init(GAME_DATA *game_data);

bool cells_map_init(GAME_DATA *game_data, int tilesX, int tilesY, int tileSize);

bool camera_init(GAME_DATA *game_data);

bool spawn_pos_init(GAME_DATA *game_data);


bool collision_map_init(GAME_DATA *game_data);

bool fog_init(GAME_DATA *game_data);

bool cave_init(GAME_DATA *game_data);

bool map_objects_init(GAME_DATA *game_data);

bool enemy_map_init(GAME_DATA *game_data);

bool enemy_init(GAME_DATA *game_data);

bool items_init(GAME_DATA *game_data, GAME_ANIM *game_anim);


#endif
