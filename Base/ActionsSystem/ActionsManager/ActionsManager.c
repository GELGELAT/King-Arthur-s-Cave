#include "ActionsManager.h"

CreateActions(* action_factories)[10];

void init_action_factories()
{
    (*action_factories)[ATTACK] = action_attacks;
}
void action_manager(GAME_DATA* game_data,//for alloc
    int object_type,int object_index, //main object
    int* movement_type ,int* action_type ,int during_type, // types and sub types
    int affected_type,int affected_index, //sub object
    Vector2* position_pixels,Vector2 old_tile,Vector2 new_tile, //pos info
    float max_fill,float amount_full_anim,float speed) //during
{
    (*action_factories)[action_type[0]](game_data,//for alloc
    object_type,object_index, //main object
    movement_type ,action_type ,during_type, // types and sub types
    affected_type,affected_index, //sub object
    position_pixels,old_tile,new_tile, //pos info
    max_fill,amount_full_anim,speed);
}
void action_attacks(GAME_DATA* game_data,//for alloc
    int object_type,int object_index, //main object
    int* movement_type ,int* action_type ,int during_type, // types and sub types
    int affected_type,int affected_index, //sub object
    Vector2* position_pixels,Vector2 old_tile,Vector2 new_tile, //pos info
    float max_fill,float amount_full_anim,float speed) //during
{
    
    if (action_type[1]==ATTACK_PUNCH)
    {
        Allocator* alloc =create_alloc(1024);
        int new_tile_x = new_tile.x;
        int new_tile_y = new_tile.y;
        int index = game_data->maps->enemy_map->index_map[new_tile_x][new_tile_y];
        //Enemy* enemy = get_enemy_from_enemy_map(game_data,index); 
        //FORWARD ATTACK PUNCH      
        Action* attack_punch = create_action(alloc,MAIN_MAP,PLAYER,-1,movement_forward_none,(int[]){ATTACK,ATTACK_PUNCH},END,ENEMY,index,
        &game_data->player->player_pos->position_pixels->pos_pixels,old_tile,new_tile,PLAY_FULL_ANIM,1,PLAYER_ATTACK_SPEED_ANIM);
        Action* moving = create_action(alloc,MAIN_MAP,PLAYER,-1,movement_back_none,action_moving_none,END,-1,-1,
        &game_data->player->player_pos->position_pixels->pos_pixels,new_tile ,old_tile,PLAY_FULL_ANIM,2,PLAYER_WALK_SPEED_ANIM);
        attack_punch->queue->ending_action=moving;
        
        //Action* receiving_damage = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,index,RANDOM_MOVING,RECEIVING_DAMAGE,START,-1,-1,
        // &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,ENEMY_RECEIVING_DAMAGE_TIME_ANIM,1,5);
        // moving->queue->beginning_action = receiving_damage;
        append_action_to_actions_map(game_data,attack_punch);
    }
}