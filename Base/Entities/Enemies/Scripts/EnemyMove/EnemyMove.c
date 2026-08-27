#include "EnemyMove.h"

void enemies_moving(GAME_DATA* game_data)
{
    Enemy** enemyeis = game_data->maps->enemy_map->move_queue;
    int amount_enemyeis = game_data->maps->enemy_map->move_queue_amount;
    if (amount_enemyeis == 0)
    {

    }
    else
    {
        for (int i =0;i<amount_enemyeis;i++)
        {
            if (enemyeis[i]->current_animation != NULL)
            {
                //enemyeis[i]->current_animation = &enemyeis[i]->enemy_animations->attack;
                
                //enemyeis[i]->current_animation = &enemyeis[i]->enemy_animations->breathe;
            }
            enemy_moving(game_data,enemyeis[i]);
            
            
            
        }
    }
}

void enemy_moving(GAME_DATA* game_data,Enemy* enemy)
{
    Allocator* alloc_path = create_alloc(1024*1024);
    int** id_map = game_data->maps->enemy_map->index_map;
    CellsMap* objecta_map = game_data->maps->cells_map;
    char** col_map = game_data->maps->collision_map->grid;
    Vector2* persecution_path = path_finding(alloc_path,game_data,enemy,persecution);
    Vector2* search_path = path_finding(alloc_path,game_data,enemy,search);
    Vector2* path = persecution_path;

    
    for (int i = 0;i<enemy->enemy_misc->path_len+1;i++)
    {
       
        if ((int)persecution_path[i].x ==-1 || (int)persecution_path[i].y==-1)
        {
            break;
        }
       
        if (game_data->maps->collision_map->grid[(int)persecution_path[i].x][(int)persecution_path[i].y]=='m')
        {
            
            if (vectors_comparison(search_path[0],(Vector2){-1,-1}))
            {
                path = persecution_path;
                break;
            }
            else
            {
                
                path = search_path;
                break;
            }
        }
    }
    if (enemy->enemy_animations->skin == CHICKEN_ZOMBIE && enemy->enemy_main->name == enemy_texturs[0])
    {
        bool move = chicken_zombie_dobble_move(game_data,enemy,path);
        if (move)
        {
            return;
        }
        
    }
    
    else if (enemy->enemy_animations->skin == ARM_ZOMBIE && enemy->enemy_main->name == enemy_texturs[0])
    {
        bool move = arm_zombie_jump_move(game_data,enemy,path);
        if (move)
        {
            return;
        }
        
    }
    else if (enemy->enemy_animations->skin == RESETTER_ZOMBIE && enemy->enemy_main->name == enemy_texturs[2])
    {
        bool move = zombie_revival_move(game_data,enemy,path);
        if (move)
        {
            pr_int(444);
            return;
        }
        
    }
    if (vectors_comparison(path[0],(Vector2){-1,-1}))
    {
    }
    else if (vectors_comparison(path[0],game_data->player->player_pos->position_tiles->pos_tiles) == 1)
    {
        int old_tile_x = enemy->enemy_position->position_tiles->pos_tiles.x;
        int old_tile_y = enemy->enemy_position->position_tiles->pos_tiles.y;
        int new_tile_x = path[0].x;
        int new_tile_y = path[0].y;
        Vector2 new_tile = {new_tile_x,new_tile_y};
        Vector2 old_tile = {old_tile_x,old_tile_y};
        
        if (enemy->enemy_main->name == enemy_texturs[3])
        {
            Action* attack1 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,movement_forward_none,action_attack_none,END,-1,-1,
            &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,PLAY_FULL_ANIM,1,ENEMY_ATTACK_SPEED_ANIM-2);
            
            Action* moving1 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,movement_back_none,action_moving_none,END,-1,-1,
            &enemy->enemy_position->position_pixels->pos_pixels,new_tile ,old_tile,PLAY_FULL_ANIM,2,ENEMY_WALK_SPEED_ANIM);
            attack1->queue->ending_action=moving1;

            append_action_to_actions_map(game_data,attack1);
        }
        else
        {
            Action* attack1 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,movement_forward_none,action_attack_none,END,-1,-1,
            &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,PLAY_FULL_ANIM,1,ENEMY_ATTACK_SPEED_ANIM);
            
            Action* moving1 = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,movement_back_none,action_moving_none,END,-1,-1,
            &enemy->enemy_position->position_pixels->pos_pixels,new_tile ,old_tile,PLAY_FULL_ANIM,2,ENEMY_WALK_SPEED_ANIM);
            attack1->queue->ending_action=moving1;

            append_action_to_actions_map(game_data,attack1);
        }
        
        
        //enemy_attack(game_data,enemy);
        
    }
    else if (game_data->maps->collision_map->grid[(int)path[0].x][(int)path[0].y]=='m')
    {
        
        if (enemy->enemy_animations->skin == CHICKEN_ZOMBIE || enemy->enemy_animations->skin == ARM_ZOMBIE)
        {
            plus_to_stamina(enemy);
        }
    }
    else
    {
        //enemy->current_animation = &enemy->enemy_animations->walk;
        //pr_int(enemy->current_animation->texture.id);
        int old_x = enemy->enemy_position->position_tiles->pos_tiles.x;
        int old_y = enemy->enemy_position->position_tiles->pos_tiles.y;
        int new_x = path[0].x;
        int new_y = path[0].y;

        col_map[old_x][old_y] = 'f';
        col_map[new_x][new_y] = 'm';


        objecta_map->cells[old_x][old_y]->objects[2] = NULL;
        objecta_map->cells[new_x][new_y]->objects[2] = enemy->enemy_main->name;
        enemy->enemy_position->position_tiles->pos_tiles = path[0];
        int cur_id = id_map[old_x][old_y];
        id_map[old_x][old_y] = -1;
        id_map[new_x][new_y] = cur_id;
        Vector2 old_tile = {(float)old_x,(float)old_y};
        Vector2 new_tile = {(float)new_x,(float)new_y};
        //pr_int(enemy->enemy_main->index);
        Action* moving = create_action(game_data->allocators->alloc_data,MAIN_MAP,ENEMY,enemy->enemy_main->index,movement_forward_none,action_moving_none,END,-1,-1,
                &enemy->enemy_position->position_pixels->pos_pixels,old_tile,new_tile,PLAY_FULL_ANIM,2,ENEMY_WALK_SPEED_ANIM);
        append_action_to_actions_map(game_data,moving);

    }
    //destroy_allocator(alloc_path);
    //print_vector_arr(path,game_data->maps->enemy_map->enemy_map[0]->path_len);
    
}

void enemy_attack(GAME_DATA* game_data,Enemy* enemy)
{
    //enemy->current_animation[0] = &enemy->enemy_animations->attack;
    //pr_int(enemy->current_animation->currentFrame);
    
    
    pr_int_with_text(game_data->player->player_stats->player_characteristics->heal_points,"player hp");

    int enemy_damage = rand_num_within(enemy->enemy_characteristics->min_physical_damage,enemy->enemy_characteristics->max_physical_damage);
    int player_heals = game_data->player->player_stats->player_characteristics->heal_points;
    int player_def = game_data->player->player_stats->player_characteristics->defense;
    int damage_after_def = enemy_damage - player_def;
    if (damage_after_def < 0)
    {
        damage_after_def =0;
    }
    game_data->player->player_stats->player_characteristics->heal_points = player_heals - damage_after_def;
    pr_int_with_text(game_data->player->player_stats->player_characteristics->heal_points,"player hp");
    //enemy->current_animation[0] = &enemy->enemy_animations->breathe;

}
void enemy_fast_attack(GAME_DATA* game_data,GAME_ANIM* game_anim,Enemy* enemy_attacker,Enemy* enemy_accepting)
{
    //enemy->current_animation[0] = &enemy->enemy_animations->attack;
    //pr_int(enemy->current_animation->currentFrame);
    if (enemy_accepting != NULL)
    {
        
        int enemy_damage = rand_num_within(enemy_attacker->enemy_characteristics->fast_min_physical_damage,enemy_attacker->enemy_characteristics->fast_max_physical_damage);
        
        int enemy_heals = enemy_accepting->enemy_characteristics->heal_points;
        int enemy_def = enemy_accepting->enemy_characteristics->defense;
        int damage_after_def = enemy_damage - enemy_def;
        if (damage_after_def <= 0)
        {
            damage_after_def =1;
        }
        enemy_accepting->enemy_characteristics->heal_points = enemy_heals - damage_after_def;
        //enemy_life_check(game_data,game_anim,enemy_accepting,enemy_accepting->enemy_position->position_tiles->pos_tiles.x,enemy_accepting->enemy_position->position_tiles->pos_tiles.y);
    }
    else
    {
        pr_int_with_text(game_data->player->player_stats->player_characteristics->heal_points,"player hp");

        int enemy_damage = rand_num_within(enemy_attacker->enemy_characteristics->fast_min_physical_damage,enemy_attacker->enemy_characteristics->fast_max_physical_damage);
        int player_heals = game_data->player->player_stats->player_characteristics->heal_points;
        int player_def = game_data->player->player_stats->player_characteristics->defense;
        int damage_after_def = enemy_damage - player_def;
        if (damage_after_def < 0)
        {
            damage_after_def =0;
        }
        game_data->player->player_stats->player_characteristics->heal_points = player_heals - damage_after_def;
        pr_int_with_text(game_data->player->player_stats->player_characteristics->heal_points,"player hp");
    }
    
    

}