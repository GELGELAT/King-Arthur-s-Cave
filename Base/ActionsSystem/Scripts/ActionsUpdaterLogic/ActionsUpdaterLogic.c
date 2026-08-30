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
    Action** action_maps = game_data->maps->actins_map->actions_main_queue;
    int* amount = &game_data->maps->actins_map->amount_actions_main_queue;
    for (int i =0;i<*amount;i++)
    {
        //pr_int(*amount);
        Action* current_action = action_maps[i];
        float current_fill = current_action->misc->current_fill;
        float max_fill = current_action->misc->max_fill;
        if (current_fill >=max_fill)
        {
            delete_action_from_queue_action_map(game_data,current_action->flow,i);
            //destroy_allocator(current_action->alloc);
            continue;
        }
        int* movement_type = current_action->main->movement_type;
        if (movement_type[0] == WITHOUT_MOVING)
        {
            without_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type[0] == FORWARD)
        {
            forward_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type[0] == BACK)
        {
            back_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type[0] == RANDOM_MOVING)
        {
            random_movement_action_update(game_data,game_anim,current_action);
            
        }
    }
}
void effects_action_map_updater(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    Action** action_maps = game_data->maps->actins_map->actions_effects_queue;
    int* amount = &game_data->maps->actins_map->amount_actions_effects_queue;
    for (int i =0;i<*amount;i++)
    {
        //pr_int(*amount);
        Action* current_action = action_maps[i];
        float current_fill = current_action->misc->current_fill;
        float max_fill = current_action->misc->max_fill;
        if (current_fill >=max_fill)
        {
            delete_action_from_queue_action_map(game_data,current_action->flow,i);
            //destroy_allocator(current_action->alloc);
            continue;
        }
        int* movement_type = current_action->main->movement_type;
        if (movement_type[0] == WITHOUT_MOVING)
        {
            without_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type[0] == FORWARD)
        {
            forward_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type[0] == BACK)
        {
            back_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type[0] == RANDOM_MOVING)
        {
            random_movement_action_update(game_data,game_anim,current_action);
            
        }
    }
}
void append_action_to_actions_map(GAME_DATA* game_data,Action* action)
{
    ActionsMap* action_maps = game_data->maps->actins_map;
    int map_number = action->flow;

    int* main_amount = &action_maps->amount_actions_main_queue;
    int* effect_amount = &action_maps->amount_actions_effects_queue;
    if (map_number == MAIN_MAP)
    {
        action_maps->actions_main_queue[*main_amount]=action;
        *main_amount +=1;
    }
    else if (map_number == EFFECT_MAP)
    {
        action_maps->actions_effects_queue[*effect_amount] = action;
        *effect_amount+=1;
    }
    

}
void delete_action_from_queue_action_map(GAME_DATA* game_data,int queue,int current_pos_at_map)
{
    int* amount;
    Action** map;
    if (queue == MAIN_MAP)
    {
        amount = &game_data->maps->actins_map->amount_actions_main_queue;
        map = game_data->maps->actins_map->actions_main_queue;
    }
    else
    {
        amount = &game_data->maps->actins_map->amount_actions_effects_queue;
        map = game_data->maps->actins_map->actions_effects_queue;
    }
    //Action* current_action = map[current_pos_at_map];
    for (int i=current_pos_at_map;i<*amount-1;i++)
    {
        map[i] =map[i+1];
    }
    *amount-=1;
    //destroy_allocator(current_action->alloc);
}
