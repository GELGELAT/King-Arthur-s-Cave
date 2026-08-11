#include "renderer.h"
void GAME_DRAW(GAME_DATA *game_data,GAME_ANIM* game_anim)
{
    map_draw(game_data,game_anim);
    player_draw(game_data);
    draw_enemy(game_data);
    fog_draw(game_data,game_anim);
}

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
void draw_enemy(GAME_DATA* game_data)
{
    EnemyMap* enemy_map = game_data->maps->enemy_map;
    Enemy** enemy_arr = enemy_map->move_queue;
    int* amount = &enemy_map->move_queue_amount;
    for (int i =0;i<*amount;i++)
    {
        Enemy* cur_enemy = enemy_arr[i];
        /*
        for (int i = 0;i<4;i++)
        {
            if (cur_enemy->enemy_main->name==enemy_texturs[i])
            {
                //draw_animation(&cur_anim,pos_1,64,64,4,0);
                DrawCircle(cur_enemy->enemy_position->position_pixels->pos_pixels.x,cur_enemy->enemy_position->position_pixels->pos_pixels.y, 32.0f, color_enemy_texturs[i]);
            }
        }
            */
        if (cur_enemy->current_animation != NULL)
        {
            //cur_enemy->current_animation = &cur_enemy->enemy_animations->breathe;
            //pr_int(cur_enemy->current_animation->framesCounter);
            int pos_x = cur_enemy->enemy_position->position_pixels->pos_pixels.x -cur_enemy->enemy_animations->alignment_x;
            int pos_y =cur_enemy->enemy_position->position_pixels->pos_pixels.y -cur_enemy->enemy_animations->alignment_y;
            //pr_int(cur_enemy->current_animation->texture.id);
            draw_animation(cur_enemy->current_animation[0],(Vector2){pos_x,pos_y},cur_enemy->enemy_animations->size_x,cur_enemy->enemy_animations->size_y,4,0);
        }
        
        
    }
        
        
    
}

/*
void draw_enemy(char** objects,Vector2 pos_1,Vector2 pos_2)
{
    for (int i = 0;i<4;i++)
    {
        if (objects[2]==enemy_texturs[i])
        {
            DrawCircle(pos_1.x+32,pos_1.y+32, 32.0f, color_enemy_texturs[i]);
        }
    }
}
*/
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

void draw_item(GAME_DATA* game_data,GAME_ANIM* game_anim,char** objects,int x,int y,Vector2 pos_1,Vector2 pos_2)
{
    
    int** item_index_map = game_data->maps->items_map->index_map;
    int index_item = item_index_map[(int)y][(int)x];
    //print_int_map(game_data,item_index_map);
    if(index_item <=-1)
    {
        return;
    }
    Item* item = game_data->maps->items_map->items_map[index_item];
    int textur_id = item->item_main->textur_index;
    int pos_index = item->item_main->pos_index;
    
    for (int i = 0;i<4;i++)
    {
        if (objects[1]==armor_chest_texturs[i])
        {
            Animation cur_anim = get_item_animation(game_anim,index_item);
            draw_animation(&cur_anim,pos_1,64,64,4,0);
            //DrawCircle(pos_1.x+32,pos_1.y+32, 20.0f, color_armor_chest_texturs[i]);        
        }
        else if (objects[1]==weapon_texturs[i])
        {
            Animation cur_anim = get_item_animation(game_anim,index_item);
            draw_animation(&cur_anim,pos_1,64,64,4,0);
            //DrawCircle(pos_1.x+32,pos_1.y+32, 10.0f, color_weapon_texturs[i]);
                

        }
        else if (objects[1]==HELMET_texturs[i])
        {
            Animation cur_anim = get_item_animation(game_anim,index_item);
            draw_animation(&cur_anim,pos_1,64,64,4,0);
            //DrawCircle(pos_1.x+32,pos_1.y+32, 5.0f, color_HELMET_texturs[i]);
                

        }
    }
    
    for (int i = 0;i<3;i++)
    {
        if (objects[1]==coins_texturs[i])
        {
            
            any_coins_draw(game_anim, pos_1,i,textur_id,pos_index);
        }
        else if (objects[1]==heals_texturs[i])
        {
            Animation cur_anim = get_item_animation(game_anim,index_item);
            draw_animation(&cur_anim,pos_1,32,32,pos_index,0);
            //DrawCircle(pos_1.x+32,pos_1.y+32, 5.0f, RED);
                

        }
        else if (objects[1]==experience_texturs[i])
        {
            Animation cur_anim = get_item_animation(game_anim,index_item);
            draw_animation(&cur_anim,pos_1,32,32,pos_index,0);
            //DrawCircle(pos_1.x+32,pos_1.y+32, 5.0f, BLUE);
                

        }
    }

}
#define small 0
#define medium 1
void player_draw(GAME_DATA *game_data)
{
    DrawCircle(game_data->player->player_pos->position_pixels->pos_pixels.x,game_data->player->player_pos->position_pixels->pos_pixels.y, 32.0f, GOLD); 
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
int rand_pos[4][2] = {{0,0},{0,32},{32,0},{32,32}};
void any_coins_draw(GAME_ANIM* game_anim, Vector2 pos,int coins_type, int frame_index,int pos_index)
{

    
    Texture2D coins_list = game_anim->texturs->items_texturs->misc_texturs->coins_texturs->coins;
    if (coins_type == small)
    {
        Rectangle source = game_anim->texturs->items_texturs->misc_texturs->coins_texturs->small_frames[frame_index];
        Rectangle dest = {pos.x+rand_pos[pos_index][0],pos.y+rand_pos[pos_index][1],48,48};
        DrawTexturePro(coins_list,source,dest,(Vector2){0,0}, 0, WHITE);
    }
    else if (coins_type == medium)
    {
        Rectangle source = game_anim->texturs->items_texturs->misc_texturs->coins_texturs->medium_frames[frame_index];
        Rectangle dest = {pos.x+rand_pos[pos_index][0],pos.y+rand_pos[pos_index][1],48,48};
        DrawTexturePro(coins_list,source,dest,(Vector2){0,0}, 0, WHITE);
    }
    
}