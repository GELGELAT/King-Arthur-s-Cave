#ifndef UPDATERSTEP_H
#define UPDATERSTEP_H

#include "UpdaterLogic.h"
void pos_player_updater(GAME_DATA *game_data, GAME_ANIM *game_anim);

void after_step(GAME_DATA *game_data, GAME_ANIM *game_anim);

void enemies_actions_logic(GAME_DATA *game_data, GAME_ANIM *game_anim);

void player_actions_logic(GAME_DATA *game_data, GAME_ANIM *game_anim);
void card_actions_logic(GAME_DATA *game_data);
void moves_actions_logic(GAME_DATA *game_data, GAME_ANIM *game_anim, int *player_step_direction);
#endif
