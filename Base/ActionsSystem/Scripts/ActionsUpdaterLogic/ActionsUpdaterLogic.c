#include "ActionsUpdaterLogic.h"
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
            delete_action_from_main_action_map(game_data,i);
            continue;
        }
        int movement_type = current_action->main->movement_type;
        
        if (movement_type == WITHOUT_MOVING)
        {
            without_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type == FORWARD)
        {
            forward_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type == BACK)
        {
            back_movement_action_update(game_data,game_anim,current_action);
            
        }
        else if (movement_type == RANDOM_MOVING)
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
void delete_action_from_main_action_map(GAME_DATA* game_data,int current_pos_at_map)
{
    int* amount = &game_data->maps->actins_map->amount_actions_main_queue;
    Action** map = game_data->maps->actins_map->actions_main_queue;
    for (int i=current_pos_at_map;i<*amount-1;i++)
    {
        map[i] =map[i+1];
    }
    *amount-=1;
    
}