#include "RendererLogic.h"
void GAME_DRAW(GAME_DATA *game_data,GAME_ANIM* game_anim)
{
    map_draw(game_data,game_anim);
    player_draw(game_data);
    draw_enemy(game_data);
    fog_draw(game_data,game_anim);
}