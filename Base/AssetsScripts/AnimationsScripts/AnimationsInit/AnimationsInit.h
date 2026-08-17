#ifndef ANIMATIONSINIT_H
#define ANIMATIONSINIT_H

#include "AnimationsLogic.h"
void create_animations(GAME_DATA *game_data, GAME_ANIM *game_anim);

Animation create_animation(Texture2D textur, int direction, int frame_count, int frame_width, int frame_height, Rectangle start_frame, int anim_speed, Allocator *alloc);

Animations *create_animations_struct(Allocator *alloc);

void player_anim_init(GAME_DATA *game_data, GAME_ANIM *game_anim);

#endif


