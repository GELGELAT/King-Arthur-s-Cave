#include "ZombieLogic.h"
bool zombie_revival_move(GAME_DATA *game_data, Enemy *enemy, Vector2 *path)
{
    if (enemy->enemy_main->live == ALIVE)
    {
        pr_int(555);
        return false;
    }
    else if (enemy->enemy_main->live == NEAR_DIE)
    {
        pr_int(666);
        if (enemy->enemy_main->enemy_stats->current_timer >= enemy->enemy_main->enemy_stats->max_timer)
        {
            enemy->enemy_main->enemy_stats->current_timer +=1;
        }
        else
        {

        }
        return true;
    }
}
bool revival_check(GAME_DATA* game_data,GAME_ANIM* game_anim,Enemy* enemy) 
{
    if (enemy->enemy_main->name == enemy_texturs[2] && enemy->enemy_animations->skin==RESETTER_ZOMBIE && enemy->enemy_misc->activated == false)
    {
        enemy->enemy_misc->activated = true;
        enemy->enemy_main->live = NEAR_DIE;
        enemy->current_animation[0] = &enemy->enemy_animations->corpse;
        return true;
    }
    return false;
}