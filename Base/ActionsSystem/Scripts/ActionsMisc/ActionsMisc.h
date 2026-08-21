#ifndef ACTIONSMISC_H
#define ACTIONSMISC_H
#define LEFT 0
#define RIGHT 1
extern int current_direction;
#include "ActionsUpdaterLogic.h"


void player_animation_direction(int directing_x, int directing_y, Player *player);

void enemy_animation_direction(int directing_x, int directing_y, Enemy *enemy);

#endif

