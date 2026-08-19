#include "ZombieLogic.h"
bool zombie_revival_move(GAME_DATA *game_data, Enemy *enemy, Vector2 *path)
{
    if (enemy->enemy_main->live == ALIVE)
    {
        return false;
    }
    else if (enemy->enemy_main->live == NEAR_DIE)
    {
        if (enemy->enemy_main->enemy_stats->current_timer < enemy->enemy_main->enemy_stats->max_timer)
        {
            enemy->enemy_main->enemy_stats->current_timer +=1;
            enemy->enemy_characteristics->heal_points += rand_num_within(5,10);
            if (enemy->enemy_characteristics->heal_points > 40)
            {
                enemy->enemy_characteristics->heal_points = 40;
            }
        }
        else
        {
            Vector2 old_tile = enemy->enemy_position->position_tiles->pos_tiles;
            Vector2 new_tile = enemy->enemy_position->position_tiles->pos_tiles;
            Action* breath = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,WITHOUT_MOVING,BREATH,START,-1,-1,
            &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,1,1,1);
            append_action_to_actions_map(game_data,breath);
            enemy->enemy_main->live = ALIVE;
        }
        return true;
    }
}
bool revival_check(GAME_DATA* game_data,GAME_ANIM* game_anim,Enemy* enemy) 
{
    if (enemy->enemy_main->name == enemy_texturs[2] && enemy->enemy_animations->skin==RESETTER_ZOMBIE && enemy->enemy_misc->activated == false)
    {
        enemy->enemy_characteristics->heal_points = 10;
        enemy->enemy_misc->activated = true;
        enemy->enemy_main->live = NEAR_DIE;

        Vector2 old_tile = enemy->enemy_position->position_tiles->pos_tiles;
        Vector2 new_tile = enemy->enemy_position->position_tiles->pos_tiles;
        //enemy->current_animation[0] = &enemy->enemy_animations->corpse;
        Action* fall = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,WITHOUT_MOVING,FALL,DURING,-1,-1,
        &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,PLAY_FULL_ANIM,1,ENEMY_FALL_DIE_SPEED_ANIM);
        Action* corpse = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,WITHOUT_MOVING,CORPSE,DURING,-1,-1,
        &enemy->enemy_position->position_pixels->pos_pixels,new_tile ,old_tile,1,1,5);
        fall->queue->ending_action=corpse;

        append_action_to_actions_map(game_data,fall);
        return true;
    }
    return false;
}