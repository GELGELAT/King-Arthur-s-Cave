#ifndef STRUCTURS_H
#define STRUCTURS_H
#include <stdlib.h>
#include "raylib.h"
#include "Allocator.h"
#include "void_linked_list.h"

#include "game_anim_struct.h"
#include "game_data_struct.h"
#include "miscellanea_struct.h"

extern int enemy_indexes;
typedef struct Enemy Enemy;
typedef struct Animation Animation;
typedef struct Action Action;

typedef struct GAME_DATA
{
    Player *player;
    Maps *maps;
    Allocators *allocators;
    Misc *misc;

} GAME_DATA;

typedef struct GAME_ANIM
{
    Animations *animations;
    Texturs *texturs;
    Allocator *anim_alloc;
    AnimationMaps *maps;

} GAME_ANIM;

Player *create_player(Allocator *alloc, int start_posX, int start_posY);

ActionsMap *create_action_map(Allocator *alloc, int tilesX, int tilesY);

Action *create_action(int flow, int object_type, int object_index, int *movement_type, int *action_type, int during_type, int affected_type, int affected_index, Vector2 *position_pixels, Vector2 old_tile, Vector2 new_tile, float max_fill, float amount_full_anim, float speed);


GAME_DATA *create_game_data();

AnimationEnemyMap *create_anim_enemies_map(GAME_ANIM *game_anim);

AnimationActionTilesMap *create_anim_action_tiles_map(GAME_ANIM *game_anim);

AnimationPlayerMap *create_anim_player_map(GAME_ANIM *game_anim);

AnimationItemsMap *create_anim_items_map(GAME_ANIM *game_anim);

GAME_ANIM *create_game_anim();

ItemsMap *create_items_map(Allocator *alloc, int tilesX, int tilesY);

Cell *create_cell(Allocator *alloc);

FogMap *create_fog_map(Allocator *alloc, int tilesX, int tilesY);

CellsMap *create_cells_map(Allocator *alloc, int tilesX, int tilesY, int tileSize);

CollisionMap *create_collision_map(Allocator *alloc, int tilesX, int tilesY);

EnemyMap *create_enemy_map(Allocator *alloc, int enemy_indexes, int tilesX, int tilesY);

void raw_initialization_cells(Allocator *alloc, CellsMap *cells_map);

Path *create_path_structur(Allocator *alloc, int tilesX, int tilesY);

#endif
