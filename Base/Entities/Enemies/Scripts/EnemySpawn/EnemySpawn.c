#include "EnemySpawn.h"


void spawn_enemy(GAME_ANIM *game_anim,GAME_DATA *game_data,int pos_x, int pos_y,int enemy_index, int enemy_type,int skin) //поставить в колизии s и в обьекты имя и в индексы индекс
{
    
    char** colis_map = game_data->maps->collision_map->grid;
    colis_map[pos_x][pos_y] = 's';
    

    int** index_map = game_data->maps->enemy_map->index_map;
    index_map[pos_x][pos_y] = enemy_index;
    

    Enemy* enemy = create_enemy(game_anim,game_data->allocators->alloc_data,enemy_index,enemy_type,pos_x,pos_y,skin); 
    append_to_anim_enemy_list_updater(game_data,game_anim,enemy);
    append_enemy_to_arr(game_data,enemy,1);
    game_data->maps->enemy_map->enemy_map[enemy_indexes] = enemy;
    
    CellsMap* objects_map = game_data->maps->cells_map;
    objects_map->cells[pos_x][pos_y]->objects[2] = enemy->enemy_main->name;
    enemy_indexes +=1;
    //print_int_map(game_data,index_map);
    //correctness_index_map_check(game_data,index_map);
}

int enemy_damage[4][2] = {{5,10},{10,15},{15,20},{20,25}};
int enemy_heal_points[4] = {20,30,40,50};
int enemy_defens[4] = {2,3,4,5};



Enemy* create_enemy(GAME_ANIM* game_anim,Allocator* alloc,int enemy_indexes,int enemy_type,int start_posX,int start_posY,int skin)
{
    Enemy* enemy = alloc_alloc(alloc,sizeof(Enemy));
    EnemyMisc* enemy_misc = alloc_alloc(alloc,sizeof(EnemyMisc));
    
    EnemyMain* enemy_main = alloc_alloc(alloc,sizeof(EnemyMain));
    EnemyStats* enemy_stats = alloc_alloc(alloc,sizeof(EnemyStats));
    EnemyCharacteristics* enemy_characteristics = alloc_alloc(alloc,sizeof(EnemyCharacteristics));
    EnemyPos* enemy_position = alloc_alloc(alloc,sizeof(EnemyPos));
    EnemyTilesPos* position_tiles = alloc_alloc(alloc,sizeof(EnemyTilesPos));
    EnemyPixelsPos* position_pixels = alloc_alloc(alloc,sizeof(EnemyPixelsPos));
    EnemyAnimations* enemy_animations = alloc_alloc(alloc,sizeof(EnemyAnimations));
    Animation** current_animations = alloc_alloc(alloc,sizeof(Animation*));
    EnemyStamina* enemy_stamina = alloc_alloc(alloc,sizeof(EnemyStamina));
    
    enemy->enemy_characteristics = enemy_characteristics;
    enemy->enemy_main =enemy_main;
    enemy->enemy_main->enemy_stats = enemy_stats;
    
    enemy->enemy_misc =enemy_misc;
    enemy->enemy_misc->activated = false;
    enemy->enemy_position = enemy_position;
    enemy->enemy_position->position_tiles = position_tiles;
    enemy->enemy_position->position_pixels = position_pixels;
    enemy->enemy_misc->activated = false; 
    enemy->enemy_main->index = enemy_indexes;
    enemy->enemy_animations = enemy_animations;
    enemy->current_animation = current_animations;
    enemy->enemy_characteristics->enemy_stamina = enemy_stamina;
    enemy->enemy_main->live = 1;
    if (enemy_type == 1)
    {
        enemy->enemy_animations->breathe = game_anim->animations->enemies_animation->skeleton_enemies_animations->skeleton_breathe_animation;
        enemy->enemy_animations->breathe.currentFrame = rand_num_within(0,3);
        enemy->enemy_animations->walk = game_anim->animations->enemies_animation->skeleton_enemies_animations->skeleton_walk_animation;
        enemy->enemy_animations->attack = game_anim->animations->enemies_animation->skeleton_enemies_animations->skeleton_attack_animation;
        enemy->enemy_animations->die = game_anim->animations->enemies_animation->skeleton_enemies_animations->skeleton_die_animation;
       // enemy->current_animation = &enemy->enemy_animations->die;
        //enemy->current_animation = &enemy->enemy_animations->walk;
        enemy->current_animation[0] = &enemy->enemy_animations->breathe;
        enemy->enemy_animations->size_x = rand_num_within(114,132);
        enemy->enemy_animations->size_y = rand_num_within(114,132);
         enemy->enemy_animations->alignment_x =64;
          enemy->enemy_animations->alignment_y =96;
    }
    else if (enemy_type == 0)
    {
        
        if (skin == CHICKEN_ZOMBIE)
        {
            enemy->enemy_animations->breathe = game_anim->animations->enemies_animation->arm_enemies_animations->arm_0_breathe_animation;
            enemy->enemy_animations->breathe.currentFrame = rand_num_within(0,3);
            enemy->enemy_animations->walk = game_anim->animations->enemies_animation->arm_enemies_animations->arm_0_walk_animation;
            enemy->enemy_animations->attack = game_anim->animations->enemies_animation->arm_enemies_animations->arm_0_attack_animation;
            enemy->enemy_animations->die =game_anim->animations->enemies_animation->arm_enemies_animations->arm_0_die_animation;
            enemy->current_animation[0] = &enemy->enemy_animations->breathe;
            enemy->enemy_animations->size_x = rand_num_within(48,64);
            enemy->enemy_animations->size_y = rand_num_within(48,64);
            enemy->enemy_animations->alignment_x =32;
          enemy->enemy_animations->alignment_y =32;
          enemy->enemy_animations->skin = CHICKEN_ZOMBIE;
          enemy->enemy_characteristics->enemy_stamina->max_stamina = rand_num_within(4,8);
          enemy->enemy_characteristics->enemy_stamina->stamina=rand_num_within(0,8);
          enemy->enemy_characteristics->enemy_stamina->stamina_regeneration = rand_num_within(0,2);
        }
        else if( skin ==ARM_ZOMBIE)
        {
            enemy->enemy_animations->breathe = game_anim->animations->enemies_animation->arm_enemies_animations->arm_1_breathe_animation;
            enemy->enemy_animations->breathe.currentFrame = rand_num_within(0,3);
            enemy->enemy_animations->walk = game_anim->animations->enemies_animation->arm_enemies_animations->arm_1_walk_animation;
            enemy->enemy_animations->attack = game_anim->animations->enemies_animation->arm_enemies_animations->arm_1_attack_animation;
            enemy->enemy_animations->die =game_anim->animations->enemies_animation->arm_enemies_animations->arm_1_die_animation;
            enemy->current_animation[0] = &enemy->enemy_animations->breathe;
            enemy->enemy_animations->size_x = rand_num_within(48,64);
            enemy->enemy_animations->size_y = rand_num_within(48,64);
            enemy->enemy_animations->alignment_x =32;
          enemy->enemy_animations->alignment_y =32;
          enemy->enemy_animations->skin = ARM_ZOMBIE;
          enemy->enemy_characteristics->enemy_stamina->max_stamina = rand_num_within(60,80);
          enemy->enemy_characteristics->enemy_stamina->stamina=rand_num_within(60,80);
          enemy->enemy_characteristics->enemy_stamina->stamina_regeneration = rand_num_within(0,2);
          enemy->enemy_characteristics->fast_max_physical_damage = 10;
          enemy->enemy_characteristics->fast_min_physical_damage =30;
        }
    }
    else if (enemy_type == 2)
    {
        enemy->enemy_animations->breathe = game_anim->animations->enemies_animation->zombie_enemies_animations->zombie_breathe_animation;
        enemy->enemy_animations->breathe.currentFrame = rand_num_within(0,3);
        enemy->enemy_animations->walk = game_anim->animations->enemies_animation->zombie_enemies_animations->zombie_walk_animation;
        enemy->enemy_animations->attack = game_anim->animations->enemies_animation->zombie_enemies_animations->zombie_attack_animation;
        enemy->enemy_animations->die = game_anim->animations->enemies_animation->zombie_enemies_animations->zombie_die_animation;
       // enemy->current_animation = &enemy->enemy_animations->die;
        //enemy->current_animation = &enemy->enemy_animations->walk;
        enemy->current_animation[0] = &enemy->enemy_animations->breathe;
        enemy->enemy_animations->size_x = rand_num_within(84,92);
        enemy->enemy_animations->size_y = rand_num_within(84,92);
         enemy->enemy_animations->alignment_x =48;
          enemy->enemy_animations->alignment_y =64;
        if (skin = RESETTER_ZOMBIE)
        {
            enemy->enemy_animations->dying = game_anim->animations->enemies_animation->zombie_enemies_animations->zombie_dying_animation;
            enemy->enemy_animations->corpse = game_anim->animations->enemies_animation->zombie_enemies_animations->zombie_corpse_animation;
            enemy->enemy_main->enemy_stats->max_timer = 4;
            enemy->enemy_main->enemy_stats->current_timer = 0;
            enemy->enemy_animations->skin =  RESETTER_ZOMBIE;
        }
        
    }
    else if (enemy_type == 3)
    {
        enemy->enemy_animations->breathe = game_anim->animations->enemies_animation->knight_zombie_enemies_animations->knight_zombie_breathe_animation;
        enemy->enemy_animations->breathe.currentFrame = rand_num_within(0,3);
        enemy->enemy_animations->walk = game_anim->animations->enemies_animation->knight_zombie_enemies_animations->knight_zombie_walk_animation;
        enemy->enemy_animations->attack = game_anim->animations->enemies_animation->knight_zombie_enemies_animations->knight_zombie_attack_animation;
        enemy->enemy_animations->die = game_anim->animations->enemies_animation->knight_zombie_enemies_animations->knight_zombie_die_animation;


       // enemy->current_animation = &enemy->enemy_animations->die;
        //enemy->current_animation = &enemy->enemy_animations->walk;
        enemy->current_animation[0] = &enemy->enemy_animations->breathe;
        enemy->enemy_animations->size_x = rand_num_within(114,132);
        enemy->enemy_animations->size_y = rand_num_within(114,132);
         enemy->enemy_animations->alignment_x =64;
          enemy->enemy_animations->alignment_y =96;
    }
    
    else
    {
        enemy->current_animation = NULL;
    }
    //enemy_indexes +=1;
    enemy->enemy_main->name = textur(enemy_textur,enemy_type);
    Vector2 s_p =  {start_posX,start_posY};
    Vector2 start_pixels_pos =  {start_posX*64+32,start_posY*64+32};
    enemy->enemy_position->position_tiles->pos_tiles =s_p;
    enemy->enemy_position->position_pixels->pos_pixels =start_pixels_pos;
    //enemy->path_to_player = alloc_alloc(alloc,sizeof(Vector2*));
     enemy->enemy_characteristics->heal_points =enemy_heal_points[enemy_type];
    enemy->enemy_characteristics->min_physical_damage = enemy_damage[enemy_type][0]; 
    enemy->enemy_characteristics->max_physical_damage = enemy_damage[enemy_type][1];
    enemy->enemy_characteristics->defense = enemy_defens[enemy_type];
    

    return enemy;
}

void append_enemy_to_arr(GAME_DATA *game_data, Enemy *enemy, int map_index)
{
    int** index_map = game_data->maps->enemy_map->index_map;
    EnemyMap *enemy_map = game_data->maps->enemy_map;
    Enemy **current_map;
    int amount;
    if (map_index == 1)
    {
        current_map = enemy_map->enemy_map;
        
        amount = enemy_map->enemy_map_amount;
        current_map[amount] = enemy;
        amount +=1;
        enemy_map->enemy_map_amount =amount;

    }
    else if (map_index == 2)
    {
        current_map = enemy_map->move_queue;
        amount = enemy_map->move_queue_amount;
        current_map[amount] = enemy;
        amount +=1;
        enemy_map->move_queue_amount =amount;
    }
}


void delete_from_move_queue(GAME_DATA* game_data,int id)
{
    bool find_flag = false;
    Enemy** move_queue = game_data->maps->enemy_map->move_queue;
    for (int i = 0;i<game_data->maps->enemy_map->move_queue_amount;i++)
    {
        if (!find_flag )
        {
            if(move_queue[i]->enemy_main->index == id)
            {
                find_flag = true;
            }
        }
        else
        {
            move_queue[i-1] = move_queue[i];
        }
    }
    game_data->maps->enemy_map->move_queue_amount -=1;
}