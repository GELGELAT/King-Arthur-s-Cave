#include "enemy_logic.h"

void correctness_index_map_check(GAME_DATA *game_data,int** map)
{
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    for (int x =0;x<tilesX;x++)
    {
        for (int y =0;y<tilesY;y++)
        {
            if (map[x][y]> enemy_indexes || map[x][y]< -1)
            {
                map[x][y] = 0;
            }
        }


    }
}


void clear_visited_tiles(GAME_DATA *game_data)
{
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    char** visited_map = game_data->misc->path->visited_tiles;
    for (int x =0;x<tilesX;x++)
    {
        for (int y =0;y<tilesY;y++)
        {
            visited_map[x][y] = '0';
        }


    }
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

void spawn_enemy(GAME_ANIM *game_anim,GAME_DATA *game_data,int pos_x, int pos_y,int enemy_index, int enemy_type) //поставить в колизии s и в обьекты имя и в индексы индекс
{
    
    char** colis_map = game_data->maps->collision_map->grid;
    colis_map[pos_x][pos_y] = 's';
    

    int** index_map = game_data->maps->enemy_map->index_map;
    index_map[pos_x][pos_y] = enemy_index;
    

    Enemy* enemy = create_enemy(game_anim,game_data->allocators->alloc_data,enemy_index,enemy_type,pos_x,pos_y); 
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
int enemy_heal_points[4] = {{20},{30},{40},{50}};
int enemy_defens[4] = {{2},{3},{4},{5}};



Enemy* create_enemy(GAME_ANIM* game_anim,Allocator* alloc,int enemy_indexes,int enemy_type,int start_posX,int start_posY)
{
    Enemy* enemy = alloc_alloc(alloc,sizeof(Enemy));
    EnemyMisc* enemy_misc = alloc_alloc(alloc,sizeof(EnemyMisc));
    EnemyMain* enemy_main = alloc_alloc(alloc,sizeof(EnemyMain));
    EnemyCharacteristics* enemy_characteristics = alloc_alloc(alloc,sizeof(EnemyCharacteristics));
    EnemyPos* enemy_position = alloc_alloc(alloc,sizeof(EnemyPos));
    EnemyTilesPos* position_tiles = alloc_alloc(alloc,sizeof(EnemyTilesPos));
    EnemyPixelsPos* position_pixels = alloc_alloc(alloc,sizeof(EnemyPixelsPos));
    EnemyAnimations* enemy_animations = alloc_alloc(alloc,sizeof(EnemyAnimations));
    Animation** current_animations = alloc_alloc(alloc,sizeof(Animation*));
    enemy->enemy_characteristics = enemy_characteristics;
    enemy->enemy_main =enemy_main;
    enemy->enemy_misc =enemy_misc;
    enemy->enemy_position = enemy_position;
    enemy->enemy_position->position_tiles = position_tiles;
    enemy->enemy_position->position_pixels = position_pixels;
    enemy->enemy_misc->activated = false; 
    enemy->enemy_main->index = enemy_indexes;
    enemy->enemy_animations = enemy_animations;
    enemy->current_animation = current_animations;

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
        int skin = rand_num_within(0,1);
        if (skin == 0)
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
        }
        else if( skin ==1)
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
#define persecution 1
#define search 2

Vector2* path_finding(Allocator* alloc_path,GAME_DATA *game_data,Enemy* enemy,int mode)
{

    clear_visited_tiles(game_data);
    int start_posX = enemy->enemy_position->position_tiles->pos_tiles.x;
    int start_posY = enemy->enemy_position->position_tiles->pos_tiles.y;
    bool find_flag = false;
    
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;

    int new_x,new_y;
    int size = tilesX * tilesY;
    
    int dx[] = {0,1,0,-1};
    int dy[] = {-1,0,1,0};
    
    int head = 0, tail = 0;

    Vector2 **parent_map = game_data->misc->path->parents_position_tiles;
    char** visited_map = game_data->misc->path->visited_tiles;
    char** colid_map = game_data->maps->collision_map->grid;
    Vector2 queue[size];

    queue[0] = (Vector2){start_posX,start_posY};
    visited_map[start_posX][start_posY] = '1';
    tail+=1;
    parent_map[start_posX][start_posY] = (Vector2){-1,-1};

    while(head<tail && !find_flag)
    {
        Vector2 current_tile = queue[head];
        head+=1;
        int current_x = current_tile.x;
        int current_y = current_tile.y;

        visited_map[current_x][current_y] = '1';

        
        for (int i = 0; i<4;i++)
        {
            new_x = current_x + dx[i];
            new_y = current_y + dy[i];
            if (new_x < 0)
            {
                new_x = 0;
            }
            if (new_y < 0)
            {
                new_y = 0;
            }
            if (new_x >= game_data->maps->cells_map->tilesX)
            {
                new_x = game_data->maps->cells_map->tilesX-1;
            }
            if (new_y >= game_data->maps->cells_map->tilesY)
            {
                new_y  = game_data->maps->cells_map->tilesY-1;
            }

            if (colid_map[new_x][new_y] == 'p')
            {
                parent_map[new_x][new_y] = (Vector2){current_x,current_y};
                return restore_path(alloc_path,game_data,enemy,new_x,new_y);
                find_flag = true;
            }
            else if ( mode == 1 &&colid_map[new_x][new_y] != 'w' && visited_map[new_x][new_y] != '1')
            {
                queue[tail] = (Vector2){new_x,new_y};
                tail+=1;
                parent_map[new_x][new_y] = (Vector2){current_x,current_y};
                visited_map[new_x][new_y] = '1';
            }
            else if (mode == 2 && colid_map[new_x][new_y] != 'w' && visited_map[new_x][new_y] != '1' && colid_map[new_x][new_y] != 'm')
            {
                queue[tail] = (Vector2){new_x,new_y};
                tail+=1;
                parent_map[new_x][new_y] = (Vector2){current_x,current_y};
                visited_map[new_x][new_y] = '1';
            }
        }
    }
    return restore_path(alloc_path,game_data,enemy,-1,-1);

}

int amount;
Vector2* restore_path(Allocator* alloc_path,GAME_DATA* game_data,Enemy* enemy,int player_pos_x,int player_pos_y)
{
    
    Vector2 **parent_map = game_data->misc->path->parents_position_tiles;

    if (player_pos_x == -1 && player_pos_y ==-1)
    {
        Vector2* path_to_player = alloc_alloc(alloc_path,sizeof(Vector2));
        path_to_player[0] = (Vector2){-1,-1};
        enemy->enemy_misc->path_len = 1; 
        return path_to_player;
    }
    else
    {

        int current_x,current_y,next_x,next_y;
        amount=-3;
        current_x = player_pos_x;
        current_y = player_pos_y;
        next_x = parent_map[current_x][current_y].x;
        next_y = parent_map[current_x][current_y].y;
        amount +=1;
        while (next_x != -1&& next_y != -1)
        {
            next_x = parent_map[current_x][current_y].x;
            next_y = parent_map[current_x][current_y].y;
            current_x = next_x;
            current_y = next_y;
            amount +=1;
        }
        enemy->enemy_misc->path_len = amount;

        Vector2* path_to_player = alloc_alloc(alloc_path,sizeof(Vector2)*(amount+1));
        next_x = 0;
        next_y = 0;
        current_x = player_pos_x;
        current_y = player_pos_y;
        path_to_player[amount] = (Vector2){current_x,current_y};
        amount-=1;
        while (next_x != -1&& next_y != -1)
        {
            if (next_x == enemy->enemy_position->position_tiles->pos_tiles.x && next_y == enemy->enemy_position->position_tiles->pos_tiles.y)
            {
                break;
            }
            next_x = parent_map[current_x][current_y].x;
            next_y = parent_map[current_x][current_y].y;
            current_x = next_x;
            current_y = next_y;
            path_to_player[amount] = (Vector2){current_x,current_y};
            amount -=1;
        }
        return path_to_player;

        
    }
}

void enemies_finding(GAME_DATA* game_data)
{
    char** col_map = game_data->maps->collision_map->grid;
    int** id_map = game_data->maps->enemy_map->index_map;
    Enemy** enemy_map = game_data->maps->enemy_map->enemy_map;

    Enemy** move_map = game_data->maps->enemy_map->move_queue;


    CellsMap* obj_map = game_data->maps->cells_map;
    CellsMap *map = game_data->maps->cells_map;

    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;

    Vector2 player_pos = game_data->player->player_pos->position_tiles->pos_tiles;

    int player_pos_x = player_pos.x;
    int player_pos_y = player_pos.y;


    int start_pos_x = player_pos.x -4;
    int start_pos_y = player_pos.y -4;

    for (int dx =0;dx<9;dx++)
    {
        for (int dy =0;dy<9;dy++)
        {
            int current_pos_x = start_pos_x+dx;
            int current_pos_y = start_pos_y+dy;
            if ( dx == 4 && dy == 4)
            {
            }
            else
            {
                if (col_map[current_pos_x][current_pos_y]=='s')
                {
                    col_map[current_pos_x][current_pos_y] = enemy_activation(col_map,current_pos_x,current_pos_y,dx,dy);
                    if (col_map[current_pos_x][current_pos_y]=='m')
                    {
                        int current_id = id_map[current_pos_x][current_pos_y];

                        append_enemy_to_arr(game_data,enemy_map[current_id],2);

                    }
                }
                
                
            }

        }
    }
}
char enemy_activation(char** col_map,int current_pos_x,int current_pos_y,int relative_pos_x,int relative_pos_y)
{
    Vector2 first_increment = parents_visen_map[relative_pos_x][relative_pos_y][0];
    int first_increment_x = first_increment.x;
    int first_increment_y = first_increment.y;

    Vector2 second_increment = parents_visen_map[relative_pos_x][relative_pos_y][1];
    int second_increment_x = second_increment.x;
    int second_increment_y = second_increment.y;

    Vector2 queue[10000][2];
    int head = 0;
    int tail = 0;

    Vector2 first_absolut_pos = {current_pos_x+first_increment_x,current_pos_y+first_increment_y};
    Vector2 first_relative_pos = {relative_pos_x +first_increment_x,relative_pos_y+first_increment_y};

    queue[0][0] = first_absolut_pos;
    queue[0][1] = first_relative_pos;
    tail+=1;
    if (second_increment_x == 0&&second_increment_y==0)
    {

    }
    else
    {
        Vector2 second_absolut_pos = {current_pos_x+second_increment_x,current_pos_y+second_increment_y};
        Vector2 second_relative_pos = {relative_pos_x +second_increment_x,relative_pos_y+second_increment_y};
        queue[1][0] = second_absolut_pos;
        queue[1][1] = second_relative_pos;
        tail+=1;
    }
    while (head<tail)
    {
        Vector2 current_absolut_pos = queue[head][0];
        Vector2 current_relative_pos = queue[head][1];
        head+=1;
        if (col_map[(int)current_absolut_pos.x][(int)current_absolut_pos.y]=='w' )
        {

            return 's';
        }
        Vector2 current_first_increment = parents_visen_map[(int)current_relative_pos.x][(int)current_relative_pos.y][0];
        int current_first_increment_x = current_first_increment.x;
        int current_first_increment_y = current_first_increment.y;
        if (current_first_increment_x == 0 && current_first_increment_y ==0)
        {
            break;
        }
        else
        {
            Vector2 new_absolut_pos = {(int)current_absolut_pos.x+current_first_increment_x,(int)current_absolut_pos.y+current_first_increment_y};
            Vector2 new_relative_pos = {(int)current_relative_pos.x +current_first_increment_x,(int)current_relative_pos.y+current_first_increment_y};
            queue[tail][0] = new_absolut_pos;
            queue[tail][1] = new_relative_pos;
            tail+=1;
        }

        Vector2 current_second_increment = parents_visen_map[(int)current_relative_pos.x][(int)current_relative_pos.y][1];
        int current_second_increment_x = current_second_increment.x;
        int current_second_increment_y = current_second_increment.y;
        if (current_second_increment_x == 0 && current_second_increment_y ==0)
        {
        }
        else
        { 
            
            Vector2 new_absolut_pos = {(int)current_absolut_pos.x+current_second_increment_x,(int)current_absolut_pos.y+current_second_increment_y};
            Vector2 new_relative_pos = {(int)current_relative_pos.x +current_second_increment_x,(int)current_relative_pos.y+current_second_increment_y};
            queue[tail][0] = new_absolut_pos;
            queue[tail][1] = new_relative_pos;
            tail+=1;
        }
    }
    return 'm';
}
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
    if (vectors_comparison(path[0],(Vector2){-1,-1}))
    {

    }
    else if (vectors_comparison(path[0],game_data->player->player_pos->position_tiles->pos_tiles) == 1)
    {
        enemy_attack(game_data,enemy);
    }
    else if (game_data->maps->collision_map->grid[(int)path[0].x][(int)path[0].y]=='m')
    {

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
        append_to_action_map(game_data,old_tile,new_tile,&enemy->enemy_position->position_pixels->pos_pixels,WALK,3,enemy->enemy_main->index);

    }
    //destroy_allocator(alloc_path);
    //print_vector_arr(path,game_data->maps->enemy_map->enemy_map[0]->path_len);
    
}
void enemy_attack(GAME_DATA* game_data,Enemy* enemy)
{
    //enemy->current_animation[0] = &enemy->enemy_animations->attack;
    //pr_int(enemy->current_animation->currentFrame);
    Vector2 new_tile = {game_data->player->player_pos->position_tiles->pos_tiles.x,game_data->player->player_pos->position_tiles->pos_tiles.y};
    Vector2 old_tile = {(float)enemy->enemy_position->position_tiles->pos_tiles.x,(float)enemy->enemy_position->position_tiles->pos_tiles.y};
    append_to_action_map(game_data,old_tile,new_tile,&enemy->enemy_position->position_pixels->pos_pixels,ATTACK,5,enemy->enemy_main->index);
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
void enemy_life_check(GAME_DATA* game_data,GAME_ANIM* game_anim,Enemy* enemy,int enemy_x,int enemy_y) 
{
    if ( enemy->enemy_characteristics->heal_points<=0)
    {
        
        
        
        append_to_action_map(game_data,(Vector2){enemy_x,enemy_y},(Vector2){0,0},&enemy->enemy_position->position_pixels->pos_pixels,DIE,3,enemy->enemy_main->index);

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
                spawn_enemy(game_anim,game_data,pos_x,pos_y,enemy_indexes,j);
                pos_find = false;
            }
            
            
            
        }
    }
}