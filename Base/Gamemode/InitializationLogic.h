#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include "structurs.h"
#include "Allocator.h"
#include "Generators.h"     
#include "MiscScripts.h"     
#include "AssetsLogic.h"     
#include "EnemyLogic.h"     
#include "FogLogic.h"
#include "ItemLogic.h"





void GAME_INIT(GAME_DATA *game_data, int tilesX, int tilesY, int tileSize, GAME_ANIM *game_anim);

void window_init(GAME_DATA *game_data);


void structurs_init(GAME_DATA *game_data, GAME_ANIM *game_anim, int tilesX, int tilesY, int tileSize);

void anim_init(GAME_ANIM *game_anim);

void path_init(GAME_DATA *game_data);

void items_map_init(GAME_DATA *game_data);

void allcator_init(GAME_DATA *game_data);

void player_init(GAME_DATA *game_data);

void cells_map_init(GAME_DATA *game_data, int tilesX, int tilesY, int tileSize);

void camera_init(GAME_DATA *game_data);

void spawn_pos_init(GAME_DATA *game_data);


void collision_map_init(GAME_DATA *game_data);

void action_map_init(GAME_DATA *game_data);

void fog_init(GAME_DATA *game_data);

void cave_init(GAME_DATA *game_data);

void map_objects_init(GAME_DATA *game_data);

void enemy_map_init(GAME_DATA *game_data);


void enemy_init(GAME_DATA *game_data, GAME_ANIM *game_anim);

void items_init(GAME_DATA *game_data, GAME_ANIM *game_anim);

#endif
