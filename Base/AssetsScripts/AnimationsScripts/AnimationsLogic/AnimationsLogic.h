#ifndef ANIMATIONSLOGIC_H
#define ANIMATIONSLOGIC_H

#include "AssetsLogic.h"
#include "AnimationsUpdater.h"
#include "AnimationsInit.h"
#include "EnemyMisc.h"

void append_player_anim_to_arr(GAME_ANIM *game_anim, Animation **anim);

void draw_animation(Animation *anim, Vector2 pos, int size_x, int size_y, int pos_index, float rotate);

Animation get_item_animation(GAME_ANIM *game_anim, int index);

void append_item_anim_to_arr(GAME_ANIM *game_anim, Animation *anim);

void append_item_anim_to_map(GAME_ANIM *game_anim, Animation anim, int index);

void delete_from_item_anim_queue(GAME_DATA *game_data, GAME_ANIM *game_anim, int id);

void append_item_animation(GAME_ANIM *game_anim, int object_type, int textur_type, int object_id);

void append_to_anim_enemy_list_updater(GAME_DATA *game_data, GAME_ANIM *game_anim, Enemy *enemy);

void play_full_animation(GAME_DATA *game_data, Action *action, float directing_x, float directing_y);



#endif

