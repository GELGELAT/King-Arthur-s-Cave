#include "ZombieArmLogic.h"


bool arm_zombie_jump_move(GAME_DATA* game_data,Enemy* enemy,Vector2* path)
{


        
    if (vectors_comparison(path[0],(Vector2){-1,-1}))
    {   
        return false;
    }
    

    if(enemy->enemy_characteristics->enemy_stamina->stamina >=4)
    {
        Vector2 next_move = enemy->enemy_misc->next_move;
        Vector2 player_pos = game_data->player->player_pos->position_tiles->pos_tiles;
        if (vectors_comparison(player_pos,path[1]) && enemy->enemy_misc->activated == false)
        {
            
            enemy->enemy_misc->next_move = path[1];
            Action* preparation = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,WITHOUT_MOVING,PREPARATION,END,-1,-1,
                    &enemy->enemy_position->position_pixels->pos_pixels,path[1],path[1],48,5);
            append_action_to_actions_map(game_data,preparation);
            return true;
            
            
        }
        else if (vectors_comparison(player_pos,path[1]) && enemy->enemy_misc->activated == true)
        {
            int old_tile_x = enemy->enemy_position->position_tiles->pos_tiles.x;
            int old_tile_y = enemy->enemy_position->position_tiles->pos_tiles.y;
            int new_tile_x = path[0].x;
            int new_tile_y = path[0].y;
            
            Vector2 new_tile = path[1];
            Vector2 old_tile = {old_tile_x,old_tile_y};
            
            Action* moving1 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,FORWARD,MOVING,END,-1,-1,
            &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,1,5);
            Action* attack = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,RANDOM_MOVING,ATTACK,DURING,-1,-1,
                    &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,48,5);
            Action* moving2 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,BACK,MOVING,END,-1,-1,
            &enemy->enemy_position->position_pixels->pos_pixels,new_tile ,old_tile,1,5);
            moving1->queue->ending_action = attack;
            attack->queue->ending_action =moving2;
            append_action_to_actions_map(game_data,moving1);
            enemy->enemy_misc->activated = false;
            enemy->enemy_characteristics->enemy_stamina->stamina-=4;
            return true;
        }
        else if (game_data->maps->collision_map->grid[(int)next_move.x][(int)next_move.y] == 'f' && enemy->enemy_misc->activated == true)
        {

            int old_tile_x = enemy->enemy_position->position_tiles->pos_tiles.x;
            int old_tile_y = enemy->enemy_position->position_tiles->pos_tiles.y;

            
            Vector2 new_tile = next_move;
            Vector2 old_tile = {old_tile_x,old_tile_y};
            

            int old_x = enemy->enemy_position->position_tiles->pos_tiles.x;
            int old_y = enemy->enemy_position->position_tiles->pos_tiles.y;
            int new_x = next_move.x;
            int new_y = next_move.y;
            int** id_map = game_data->maps->enemy_map->index_map;
            CellsMap* objecta_map = game_data->maps->cells_map;
            char** col_map = game_data->maps->collision_map->grid;
            col_map[old_x][old_y] = 'f';
            col_map[new_x][new_y] = 'm';


            objecta_map->cells[old_x][old_y]->objects[2] = NULL;
            objecta_map->cells[new_x][new_y]->objects[2] = enemy->enemy_main->name;
            enemy->enemy_position->position_tiles->pos_tiles = next_move;
            int cur_id = id_map[old_x][old_y];
            id_map[old_x][old_y] = -1;
            id_map[new_x][new_y] = cur_id;

            Action* moving1 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,FORWARD,MOVING,END,-1,-1,
            &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,1,5);
            append_action_to_actions_map(game_data,moving1);
            enemy->enemy_misc->activated = false;
            enemy->enemy_characteristics->enemy_stamina->stamina-=4;
            return true;
        }
        else if (game_data->maps->collision_map->grid[(int)next_move.x][(int)next_move.y] == 'm' && enemy->enemy_misc->activated == true)
        {
            
            
            int** id_map = game_data->maps->enemy_map->index_map;
            
            int old_tile_x = enemy->enemy_position->position_tiles->pos_tiles.x;
            int old_tile_y = enemy->enemy_position->position_tiles->pos_tiles.y;
            
            Vector2 new_tile = next_move;
            Vector2 old_tile = {old_tile_x,old_tile_y};
            int m_id = id_map[(int)next_move.x][(int)next_move.y];
            
            Action* moving1 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,FORWARD,MOVING,END,-1,-1,
            &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,1,5);
            Action* attack = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,RANDOM_MOVING,ATTACK,DURING,-1,m_id,
                    &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,48,5);
            Action* moving2 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,BACK,MOVING,END,-1,-1,
            &enemy->enemy_position->position_pixels->pos_pixels,new_tile ,old_tile,1,5);
            moving1->queue->ending_action = attack;
            attack->queue->ending_action =moving2;
            append_action_to_actions_map(game_data,moving1);
            enemy->enemy_misc->activated = false;
            enemy->enemy_characteristics->enemy_stamina->stamina-=4;
            return true;
        }
    }
    return false;
    
        
        
}