#ifndef TEXTURSINIT_H
#define TEXTURSINIT_H

#include "TextursLogic.h"

Texturs *create_texturs_struct(Allocator *alloc);

void texturs_init(GAME_ANIM *game_anim);

void mics_items_textur_init(GAME_ANIM *game_anim);

void equipment_textur_init(GAME_ANIM *game_anim);

void enemies_textur_init(GAME_ANIM *game_anim);

void player_textur_init(GAME_ANIM *game_anim);

void tiles_textur_init(GAME_ANIM *game_anim);
void effects_textur_init(GAME_ANIM *game_anim);
#endif
