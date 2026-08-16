#include "ZombieChickenLogic.h"


bool chicken_zombie_dobble_move(GAME_DATA* game_data,Enemy* enemy,Vector2* path)
{

    int rand = rand_num_within(0,9);
    if (rand >=5)
    {
        
        if (vectors_comparison(path[0],(Vector2){-1,-1}))
        {   
            return false;
        }
        
        if(enemy->enemy_characteristics->enemy_stamina->stamina >=4)
        {
            char** col_map = game_data->maps->collision_map->grid;
            Vector2 player_pos = game_data->player->player_pos->position_tiles->pos_tiles;
            if (vectors_comparison(player_pos,path[0]))
            {
                int old_tile_x = enemy->enemy_position->position_tiles->pos_tiles.x;
                int old_tile_y = enemy->enemy_position->position_tiles->pos_tiles.y;
                int new_tile_x = path[0].x;
                int new_tile_y = path[0].y;
                Vector2 new_tile = {new_tile_x,new_tile_y};
                Vector2 old_tile = {old_tile_x,old_tile_y};
                Action* attack1 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,FORWARD,ATTACK,END,-1,-1,
                &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,1,5);
                Action* moving1 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,BACK,MOVING,END,-1,-1,
                &enemy->enemy_position->position_pixels->pos_pixels,new_tile ,old_tile,1,5);
                attack1->queue->ending_action=moving1;

                Action* attack2 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,FORWARD,ATTACK,END,-1,-1,
                &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,1,5);
                moving1->queue->ending_action = attack2;
                Action* moving2 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,BACK,MOVING,END,-1,-1,
                &enemy->enemy_position->position_pixels->pos_pixels,new_tile ,old_tile,1,5);
                attack2->queue->ending_action=moving2;

                append_action_to_actions_map(game_data,attack1);
                enemy->enemy_characteristics->enemy_stamina->stamina-=4;
            }
            else if (vectors_comparison(player_pos,path[1]) && col_map[(int)path[0].x][(int)path[0].y] != 'm')
            {
                
                CellsMap* objecta_map = game_data->maps->cells_map;
                int** id_map = game_data->maps->enemy_map->index_map;
                char** col_map = game_data->maps->collision_map->grid;

                int old_tile_x = enemy->enemy_position->position_tiles->pos_tiles.x;
                int old_tile_y = enemy->enemy_position->position_tiles->pos_tiles.y;
                int new_tile_x = path[0].x;
                int new_tile_y = path[0].y;

                int old_tile_attack_x = new_tile_x;
                int old_tile_attack_y = new_tile_y;
                int new_tile_attack_x = path[1].x;
                int new_tile_attack_y = path[1].y;
                Vector2 new_tile = {new_tile_x,new_tile_y};
                Vector2 old_tile = {old_tile_x,old_tile_y};
                Vector2 new_tile_attack = {new_tile_attack_x,new_tile_attack_y};
                Vector2 old_tile_attack = {old_tile_attack_x,old_tile_attack_y};
                Action* moving = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,FORWARD,MOVING,END,-1,-1,
                &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,1,5);
                
                col_map[old_tile_x][old_tile_y] = 'f';
                col_map[new_tile_x][new_tile_y] = 'm';


                objecta_map->cells[old_tile_x][old_tile_y]->objects[2] = NULL;
                objecta_map->cells[new_tile_x][new_tile_y]->objects[2] = enemy->enemy_main->name;
                enemy->enemy_position->position_tiles->pos_tiles = path[0];
                int cur_id = id_map[old_tile_x][old_tile_y];
                id_map[old_tile_x][old_tile_y] = -1;
                id_map[new_tile_x][new_tile_y] = cur_id;
                Action* attack1 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,FORWARD,ATTACK,END,-1,-1,
                &enemy->enemy_position->position_pixels->pos_pixels,old_tile_attack,new_tile_attack,1,5);
                moving->queue->ending_action = attack1;
                Action* moving1 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,BACK,MOVING,END,-1,-1,
                &enemy->enemy_position->position_pixels->pos_pixels,new_tile_attack ,old_tile_attack,1,5);
                attack1->queue->ending_action=moving1;
                append_action_to_actions_map(game_data,moving);
                enemy->enemy_characteristics->enemy_stamina->stamina-=2;
            }
            
            else
            {
                return false;
            }
            return true;
        }
         return false;
        
    }
    else
    {
        return false;
    }
}