#include "ActionsUpdaterLogic.h"

//MOVEMENT
int movement_without_moving_none[2]= {WITHOUT_MOVING,NONE};
int movement_forward_none[2] ={FORWARD,NONE};
int movement_back_none[2] ={BACK,NONE};
int movement_random_moving_none[2] ={RANDOM_MOVING,NONE};

//ACTIONS
//ENEMY DIE
int action_fall_die[2] = {FALL,DIE};
int action_corpse_die[2] ={CORPSE,DIE};
int action_die_die[2] ={DIE,DIE};

//MOVING WALK
int action_moving_none[2] ={MOVING,NONE};

//MINE 
int action_mine_none[2] ={MINE,NONE};
//ATTACK
int action_attack_none[2] ={ATTACK,NONE};
int action_attack_punch[2] ={ATTACK,ATTACK_PUNCH};
//BREATH
int action_breath_none[2] ={BREATH,NONE};
//PREPARATION
int action_preparation_none[2] ={PREPARATION,NONE};


void main_action_map_updater(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    LlistManager * llist_manag = game_data->maps->actins_map->actions_main_queue;
    llist_check_and_delete_or_activate(llist_manag
        ,action_fill_check,action_deleter,action_activation
    ,game_data,game_anim);
}




void effects_action_map_updater(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    LlistManager * llist_manag = game_data->maps->actins_map->actions_effects_queue;
    llist_check_and_delete_or_activate(llist_manag
        ,action_fill_check,action_deleter,action_activation
    ,game_data,game_anim);
}
void append_action_to_actions_map(GAME_DATA* game_data,Action* action)
{
    ActionsMap* action_maps = game_data->maps->actins_map;
    int map_number = action->flow;

    if (map_number == MAIN_MAP)
    {
        llist_append(action_maps->actions_main_queue,action);
        

    }
    else if (map_number == EFFECT_MAP)
    {
        llist_append(action_maps->actions_effects_queue,action);

    }
    

}
void delete_action_from_queue_action_map(Llist* cur_lst)
{
    llist_delete(cur_lst,action_deleter);
}
