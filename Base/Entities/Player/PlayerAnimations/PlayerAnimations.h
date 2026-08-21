#ifndef PLAYERANIMATIONS_H
#define PLAYERANIMATIONS_H




#include "PlayerLogic.h"
extern Animation* player_animations[10];
void player_anim_init(GAME_DATA *game_data, GAME_ANIM *game_anim);

void init_player_animations(GAME_DATA *game_data);

int get_current_animation(Animation *current_animation);

#endif


