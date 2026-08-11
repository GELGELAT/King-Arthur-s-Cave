#include "items_logic.h"
int items_indices;

int armor_stats[] = {4,7,10,12};
int weapon_stats[] = {5,10,15,20};
int HELMET_stats[] = {4,7,10,12};

int coins_value[3][2]={{1,3},{4,10},{3,4}};
int heals_value[3][2] = {{10,20},{40,50},{3,4}};
int experience_value[3][2]={{10,20},{40,50},{3,4}};

char** thing[3] = {coins_texturs,heals_texturs,experience_texturs};
int (*thing_value[3])[2] ={coins_value,heals_value,experience_value};
Item* create_item(Allocator* alloc,int index,int pos_x,int pos_y,char* item_type)
{
    Item* item = alloc_alloc(alloc,sizeof(Item));
    ItemMain* item_main = alloc_alloc(alloc,sizeof(ItemMain));
    ItemPos* item_position = alloc_alloc(alloc,sizeof(ItemPos));
    ItemPixelsPos* position_pixels = alloc_alloc(alloc,sizeof(ItemPixelsPos));
    ItemTilesPos* position_tiles = alloc_alloc(alloc,sizeof(ItemTilesPos));

    item->item_main =item_main;
    item->item_position = item_position;
    item->item_position->position_pixels =position_pixels;
    item->item_position->position_tiles = position_tiles;
    item->item_main->name = item_type;
    item->item_main->index = index; 
    
    items_indices+=1;
    item->item_position->position_tiles->pos_tiles = (Vector2){pos_x,pos_y};
    item->item_main->value = determine_value(item_type);
    item->item_main->textur_index = rand_num_within(0,3);
    item->item_main->pos_index = rand_num_within(0,3);
    return item;
}
void item_throw(GAME_DATA* game_data,GAME_ANIM* game_anim,char* item_type,int start_x,int start_y)
{

    char** col_map = game_data->maps->collision_map->grid;
    int** items_map = game_data->maps->items_map->index_map;
    Vector2 info[8] ={0};
    int tail=0; 
    int dx[] = {0,1,1,1,0,-1,-1,-1};
    int dy[] = {-1,-1,0,1,1,1,0,-1};
    for (int i = 0;i<8;i++)
    {
        int new_x = start_x +dx[i];
        int new_y = start_y +dy[i];
        if (col_map[new_x][new_y] != 'w'&& items_map[new_x][new_y]==-1)
        {
            info[tail] = (Vector2){new_x,new_y};
            tail+=1;
        }
    }
    if (tail==0)
    {
        return;
    }
    Vector2 finded_pos = info[rand_num_within(0,tail-1)];

    if (vectors_comparison(finded_pos,game_data->player->player_pos->position_tiles->pos_tiles))
    {
        spawn_item(game_data,game_anim,finded_pos.x,finded_pos.y,item_type);
        delete_from_item_anim_queue(game_data,game_anim,player_ground_check(game_data,finded_pos.x,finded_pos.y));
    }
    else
    {
        spawn_item(game_data,game_anim,finded_pos.x,finded_pos.y,item_type);
    }
    
}
int determine_value(char* item_type)
{
    for (int i = 0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if (item_type == thing[i][j])
            {
                return rand_num_within(thing_value[i][j][0],thing_value[i][j][1]);
            }
        }
    }
    return -1;
}
void append_to_items_map(GAME_DATA* game_data,Item* item)
{
    int pos_x = item->item_position->position_tiles->pos_tiles.x;
    int pos_y = item->item_position->position_tiles->pos_tiles.y;
    int index = item->item_main->index;
    ItemsMap* map = game_data->maps->items_map;
    map->index_map[pos_x][pos_y] = index;
    map->items_map[index] = item;
    map->items_map_amount +=1;
}

void spawn_item(GAME_DATA* game_data,GAME_ANIM* game_anim,int pos_x,int pos_y,char* item_type)
{
    Item* item = create_item(game_data->allocators->alloc_data,items_indices,pos_x,pos_y,item_type);
    int* item_info = get_item_type_textur_type(item_type);
    if (item_info !=NULL)
    {
        append_item_animation(game_anim,item_info[0],item_info[1],item->item_main->index);
        free(item_info);
    }
    
    append_to_items_map(game_data,item);
    CellsMap* objects_map = game_data->maps->cells_map;
    if (objects_map->cells[pos_x][pos_y]->objects[1] == NULL)
    {
        objects_map->cells[pos_x][pos_y]->objects[1] = item_type;
    }
}
int* get_item_type_textur_type(char* item_type)
{
    for(int i =0;i<4;i++)
    {
        if (item_type==experience_texturs[i])
        {
            int* item_info = malloc(sizeof(int)*2);
            item_info[0] = EXP;
            item_info[1] = i;
            return item_info;
        }
        else if (item_type==heals_texturs[i])
        {
            int* item_info = malloc(sizeof(int)*2);
            item_info[0] = HEALS;
            item_info[1] = i;
            return item_info;
        }
        else if (item_type==armor_chest_texturs[i])
        {
            int* item_info = malloc(sizeof(int)*2);
            item_info[0] = ARMOR_CHEST;
            item_info[1] = i;
            return item_info;
        }
        else if (item_type==weapon_texturs[i])
        {
            int* item_info = malloc(sizeof(int)*2);
            item_info[0] = WEAPON;
            item_info[1] = i;
            return item_info;
        }
        else if (item_type==HELMET_texturs[i])
        {
            int* item_info = malloc(sizeof(int)*2);
            item_info[0] = HELMET;
            item_info[1] = i;
            return item_info;
        }
    }
    return NULL;
}
void equipments_rand_spawn(GAME_DATA* game_data,GAME_ANIM* game_anim)
{
    CellsMap* map =game_data->maps->cells_map;
    bool pos_find = false;
    int pos_x,pos_y;
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    Vector2 rand_pos;
    char** col_map = game_data->maps->collision_map->grid;
    int items_amount[4][3][4] = {{{2,2,1,2},{2,2,1,2},{2,2,1,2}},{{1,1,2,0},{1,1,2,0},{1,1,2,0}},{{2,2,0,0},{2,2,0,0},{2,2,0,0}},{{2,0,0,0},{2,0,0,0},{2,0,0,0}}};
    char** items_type[3] ={armor_chest_texturs,weapon_texturs,HELMET_texturs};
    float items_spawn_zones[4][2] = {{0,0.15},{0.15,0.1},{0.25,0.1},{0.35}};
    int mode[] = {0,0,0,1};
    for (int i =0;i<4;i++)
    {
        for (int j =0;j<3;j++)
        {
            for (int k =0;k <4;k++)
            {
                
                for (int p = 0; p<items_amount[i][j][k];p++)
                {
                    while (!pos_find)
                    {
                        rand_pos = rand_pos_within(tilesX,tilesY,items_spawn_zones[i][1],items_spawn_zones[i][0],mode[i]);
                        pos_x = rand_pos.x;
                        pos_y = rand_pos.y;
                        if (col_map[pos_x][pos_y] != 'w' &&col_map[pos_x][pos_y] != 'p'&& col_map[pos_x][pos_y] != 'b')
                        {
                            if (col_map[pos_x][pos_y] == 'w')
                            {
                                col_map[pos_x][pos_y] = 'f';
                                map->cells[pos_x][pos_y]->objects[0] = textur(FLOOR,-1);
                            }
                            pos_find = true;
                        }
                        
                        
                    }
                    char** item_type = items_type[j];
                    spawn_item(game_data,game_anim,pos_x,pos_y,item_type[k]);
                    
                    pos_find = false;
                }
                
            }
            
            
            
        }
    }
}