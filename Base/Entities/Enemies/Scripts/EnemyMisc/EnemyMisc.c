#include "EnemyMisc.h"
void plus_to_stamina(Enemy* enemy)
{
    int* cur_stam = &enemy->enemy_characteristics->enemy_stamina->stamina;
    int max_stam = enemy->enemy_characteristics->enemy_stamina->max_stamina;
    int plus_stum = enemy->enemy_characteristics->enemy_stamina->stamina_regeneration;
    *cur_stam +=plus_stum;
    if (*cur_stam > max_stam)
    {
        *cur_stam = max_stam;
    }

}

void enemy_life_check(GAME_DATA* game_data,GAME_ANIM* game_anim,Enemy* enemy) 
{
    if ( enemy == NULL || enemy->enemy_main->live == 0)
    {
        return;
    }
    if ( enemy->enemy_characteristics->heal_points<=0)
    {
        enemy->enemy_main->live = 0;
        int enemy_x = enemy->enemy_position->position_tiles->pos_tiles.x;
        int enemy_y = enemy->enemy_position->position_tiles->pos_tiles.y;
        /*
        Vector2 new_tile = {enemy->enemy_position->position_tiles->pos_tiles.x,enemy->enemy_position->position_tiles->pos_tiles.y};
        Vector2 old_tile = {enemy->enemy_position->position_tiles->pos_tiles.x,enemy->enemy_position->position_tiles->pos_tiles.y};
        Action* die = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,RANDOM_MOVING,DIE,END,-1,-1,
        &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,30,5);
        append_action_to_actions_map(game_data,die);
        */
        pr_int(enemy->enemy_main->index);
        game_data->maps->cells_map->cells[enemy_x][enemy_y]->objects[2] = NULL;
        game_data->maps->collision_map->grid[enemy_x][enemy_y] = 'f';
        game_data->maps->enemy_map->index_map[enemy_x][enemy_y] = -1;
        items_drop(game_data,game_anim,enemy,(int)enemy_x,(int)enemy_y);
        delete_from_move_queue(game_data,enemy->enemy_main->index);
        

    }
}
int list_drop[4][2] ={{1,0},{1,0},{2,0},{0,1}};
void items_drop(GAME_DATA* game_data,GAME_ANIM* game_anim,Enemy* enemy,int enemy_x,int enemy_y)
{
    for (int i = 0;i<4;i++)
    {
        if (enemy->enemy_main->name == textur(ENEMY,i))
        {
            for (int j = 0;j<2;j++)
            {
                for (int k = 0;k<list_drop[i][j];k++)
                {
                    item_throw(game_data,game_anim,textur(EXP,j), enemy_x, enemy_y);
                }
            }
            
        }
    }
    

}

void enemies_rand_spawn(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    bool pos_find = false;
    int pos_x,pos_y;
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    Vector2 rand_pos;
    char** col_map = game_data->maps->collision_map->grid;
    //int enemies_amount[4][4] = {{3,2,1,0},{2,3,1,0},{0,2,3,1},{0,0,2,3}};
    int enemies_amount[4][4] = {{10,2,5,10},{0,2,10,5},{0,10,5,2},{5,2,0,0}};
    float enemies_spawn_zones[4][2] = {{0,0.15},{0.15,0.1},{0.25,0.1},{0.35}};
    int mode[] = {0,0,0,1};
    for (int i =0;i<4;i++)
    {
        for (int j =0;j<4;j++)
        {
            for (int k =0;k <enemies_amount[i][j];k++)
            {
                while (!pos_find)
                {
                    rand_pos = rand_pos_within(tilesX,tilesY,enemies_spawn_zones[i][1],enemies_spawn_zones[i][0],mode[i]);
                    pos_x = rand_pos.x;
                    pos_y = rand_pos.y;
                    if (col_map[pos_x][pos_y] != 'w' && col_map[pos_x][pos_y] != 's' && col_map[pos_x][pos_y] != 'p'&& col_map[pos_x][pos_y] != 'b')
                    {
                        pos_find = true;
                    }
                    
                    
                }
                int skin = -1;
                if (j == 0)
                {
                    skin = rand_num_within(0,1);
                }
                spawn_enemy(game_anim,game_data,pos_x,pos_y,enemy_indexes,j,skin);
                pos_find = false;
            }
            
            
            
        }
    }
}
Enemy* get_enemy_from_enemy_map(GAME_DATA* game_data, int enemy_index)
{
    if (enemy_index == -1)
    {
        return NULL;
    }
    return game_data->maps->enemy_map->enemy_map[enemy_index];
}