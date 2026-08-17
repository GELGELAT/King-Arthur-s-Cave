#include "RendererMap.h"

void map_draw(GAME_DATA *game_data,GAME_ANIM* game_anim)
{
    CellsMap* o_map = game_data->maps->cells_map;
    Vector2 pos_2 = {game_data->maps->cells_map->tileSize,game_data->maps->cells_map->tileSize};
    for (int x = 0;x<game_data->maps->cells_map->tilesX;x++)
    {
        
        for(int y = 0;y<game_data->maps->cells_map->tilesY;y++)
        {
            Vector2 pos_1 = game_data->maps->cells_map->cells[y][x]->positin;
            drawing_objects(game_data,game_anim,o_map->cells[y][x]->objects,x,y,pos_1,pos_2);
             
        }
    }
}
void fog_draw(GAME_DATA *game_data,GAME_ANIM* game_anim)
{
    CellsMap* o_map = game_data->maps->cells_map;
    Vector2 pos_2 = {game_data->maps->cells_map->tileSize,game_data->maps->cells_map->tileSize};
    for (int x = 0;x<game_data->maps->cells_map->tilesX;x++)
    {
        
        for(int y = 0;y<game_data->maps->cells_map->tilesY;y++)
        {
            Vector2 pos_1 = game_data->maps->cells_map->cells[y][x]->positin;
            draw_fog(o_map->cells[y][x]->objects,pos_1,pos_2);
        }
    }
}
void drawing_objects(GAME_DATA *game_data,GAME_ANIM *game_anim,char** objects,int tile_x,int tile_y,Vector2 pos_1,Vector2 pos_2)
{
    draw_floor_wall(game_anim,objects,pos_1,pos_2);
    
    draw_item(game_data,game_anim,objects,tile_x,tile_y,pos_1,pos_2);
    //draw_fog(objects,pos_1,pos_2);
    
    
}

void draw_floor_wall(GAME_ANIM *game_anim,char** objects,Vector2 pos_1,Vector2 pos_2)
{
    for (int i = 0;i<4;i++)
    {
        if (objects[0]==floor_texturs[i])
        {
            floor_tile_draw(game_anim,pos_1,i);
        }
        else if (objects[0]==wall_texturs[i])
        {
            wall_tile_draw(game_anim,pos_1,i);
                

        }
    }
}
void draw_fog(char** objects,Vector2 pos_1,Vector2 pos_2)
{
    if (objects[3]==fog_texturs)
    {
        //pos_1.x -=16;
        //pos_1.y-=16;
        //pos_2.x-=16;
        //pos_2.y-=16;
        DrawRectangleV(pos_1,pos_2,BLACK);
    }
}

void floor_tile_draw(GAME_ANIM* game_anim, Vector2 pos, int frame_index)
{
    Texture2D tiles_list = game_anim->texturs->world_texturs->tiles_texturs->floor_texturs->ground_floor;
    Rectangle source = game_anim->texturs->world_texturs->tiles_texturs->floor_texturs->frames[frame_index];
    Rectangle dest = {pos.x,pos.y,64,64};
    DrawTexturePro(tiles_list,source,dest,(Vector2){0,0}, 0, WHITE);
}
void wall_tile_draw(GAME_ANIM* game_anim, Vector2 pos, int frame_index)
{
    Texture2D tiles_list = game_anim->texturs->world_texturs->tiles_texturs->wall_texturs->ground_wall;
    Rectangle source = game_anim->texturs->world_texturs->tiles_texturs->wall_texturs->frames[frame_index];
    Rectangle dest = {pos.x,pos.y,64,64};
    DrawTexturePro(tiles_list,source,dest,(Vector2){0,0}, 0, WHITE);
}