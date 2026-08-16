#include "ItemSpawn.h"


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