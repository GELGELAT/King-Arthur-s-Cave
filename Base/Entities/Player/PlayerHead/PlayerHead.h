#ifndef PLAYERHEAD_H
#define PLAYERHEAD_H

#include "PlayerLogic.h"

extern Animation* head_list[3];

void init_head_offsets_and_alignment_animations(GAME_DATA *game_data, GAME_ANIM *game_anim);

void init_head_animations(GAME_DATA *game_data, GAME_ANIM *game_anim);

void update_current_head(GAME_DATA *game_data);



#endif


