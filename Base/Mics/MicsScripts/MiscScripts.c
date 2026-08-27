#include "MiscScripts.h"

Vector2 parents_visen_map[9][9][2] = {
    // x = 0 (бывший y = 0)
    {
        {{1, 1}, {0, 0}}, {{1, 1}, {0, 0}}, {{1, 1}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, -1}, {0, 0}}
    },
    // x = 1 (бывший y = 1)
    {
        {{1, 1}, {0, 0}}, {{1, 1}, {0, 0}}, {{1, 1}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, -1}, {0, 0}}, {{1, -1}, {0, 0}}
    },
    // x = 2 (бывший y = 2)
    {
        {{1, 1}, {0, 0}}, {{1, 1}, {0, 0}}, {{1, 1}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, -1}, {0, 0}}, {{1, -1}, {0, 0}}, {{1, -1}, {0, 0}}
    },
    // x = 3 (бывший y = 3)
    {
        {{1, 1}, {0, 1}}, {{1, 1}, {0, 1}}, {{1, 1}, {0, 1}}, {{1, 1}, {0, 0}}, {{1, 0}, {0, 0}}, {{1, -1}, {0, 0}}, {{1, -1}, {0, -1}}, {{1, -1}, {0, -1}}, {{1, -1}, {0, -1}}
    },
    // x = 4 (центр)
    {
        {{0, 1}, {0, 0}}, {{0, 1}, {0, 0}}, {{0, 1}, {0, 0}}, {{0, 1}, {0, 0}}, {{0, 0}, {0, 0}}, {{0, -1}, {0, 0}}, {{0, -1}, {0, 0}}, {{0, -1}, {0, 0}}, {{0, -1}, {0, 0}}
    },
    // x = 5 (бывший y = 5)
    {
        {{-1, 1}, {0, 1}}, {{-1, 1}, {0, 1}}, {{-1, 1}, {0, 1}}, {{-1, 1}, {0, 0}}, {{-1, 0}, {0, 0}}, {{-1, -1}, {0, 0}}, {{-1, -1}, {0, -1}}, {{-1, -1}, {0, -1}}, {{-1, -1}, {0, -1}}
    },
    // x = 6 (бывший y = 6)
    {
        {{-1, 1}, {0, 0}}, {{-1, 1}, {0, 0}}, {{-1, 1}, {0, 0}}, {{-1, 0}, {-1, 1}}, {{-1, 0}, {0, 0}}, {{-1, 0}, {-1, -1}}, {{-1, -1}, {0, 0}}, {{-1, -1}, {0, 0}}, {{-1, -1}, {0, 0}}
    },
    // x = 7 (бывший y = 7)
    {
        {{-1, 1}, {0, 0}}, {{-1, 1}, {0, 0}}, {{-1, 1}, {0, 0}}, {{-1, 0}, {-1, 1}}, {{-1, 0}, {0, 0}}, {{-1, 0}, {-1, -1}}, {{-1, -1}, {0, 0}}, {{-1, -1}, {0, 0}}, {{-1, -1}, {0, 0}}
    },
    // x = 8 (бывший y = 8)
    {
        {{-1, 1}, {0, 0}}, {{-1, 1}, {0, 0}}, {{-1, 1}, {0, 0}}, {{-1, 0}, {-1, 1}}, {{-1, 0}, {0, 0}}, {{-1, 0}, {-1, -1}}, {{-1, -1}, {0, 0}}, {{-1, -1}, {0, 0}}, {{-1, -1}, {0, 0}}
    }
};


int rand_num_within(int min, int max)
{
    int num = min + rand() % (max - min + 1);
    return num;
}

void print_collision_map(GAME_DATA* game_data)
{
    char **map = game_data->maps->collision_map->grid;
    
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    for (int x = 0;x<tilesX;x++)
    {
        for (int y = 0;y<tilesY;y++)
        {
            printf("%c",map[y][x]);
        }
        printf("\n");
    }
}

void print_objects_map(GAME_DATA* game_data)
{
    CellsMap* map = game_data->maps->cells_map;
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            char** objects = map->cells[y][x]->objects;
            for (int i = 0; i<4;i++)
            {
                printf("%s ",objects[i]);
            }
            printf("|");
        }
        printf("\n");
    }
}
void print_char_map(GAME_DATA* game_data,char** map)
{
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            printf("%c",map[y][x]);
        }
        printf("\n");
    }
}

void print_vectors_map(GAME_DATA* game_data)
{
    Vector2** map = game_data->misc->path->parents_position_tiles;
        int tilesX = game_data->maps->cells_map->tilesX;
        int tilesY = game_data->maps->cells_map->tilesY;
        for (int x = 0; x < tilesX; x++)
        {
            for (int y = 0; y < tilesY; y++) 
            {
                int dx = map[y][x].x;
                 int dy = map[y][x].y;
                 printf("%d,%d",dx,dy);
                printf("|");
            }
            printf("\n");
        }
}

void print_vector_arr(Vector2* path,int amount)
{
    for (int i = 0;i<amount;i++)
    {
        printf("%d,%d ",(int)path[i].x,(int)path[i].y);
    }
    printf("\n");
}

bool vectors_comparison(Vector2 first_vector,Vector2 second_vector)
{
    int first_x = first_vector.x;
    int first_y = first_vector.y;
    int second_x = second_vector.x;
    int second_y = second_vector.y;

    if (first_x == second_x && first_y==second_y)
    {
        return 1;
    }
    return 0;
}

void print_int_map(GAME_DATA* game_data,int** map)
{
    int tilesX = game_data->maps->cells_map->tilesX;
    int tilesY = game_data->maps->cells_map->tilesY;
    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            printf("%d",map[y][x]);
        }
        printf("\n");
    }
}

void pr_int(int x)
{
    printf("%d\n",x);
}
void pr_float(float x)
{
    printf("%f\n",x);
}
void pr_int_with_text(int x,char* s)
{
    printf("%s: %d\n",s,x);
}

Vector2 rand_pos_within(int tilesX,int tilesY, float size_zone_coefficient,float start_coefficient,int mode)
{


    tilesX = tilesX-1;
    tilesY = tilesY-1;
    int rand_pox_x_within,rand_pox_y_within;


    int start_pos_x = (int)(tilesX * start_coefficient);
    int start_pos_y = (int)(tilesY * start_coefficient);

    if (!mode)
    {
        int size_x = (int)(tilesX * size_zone_coefficient);
        int size_y = (int)(tilesY * size_zone_coefficient);

        int final_pos_x = tilesX - start_pos_x -size_x;
        int final_pos_y = tilesY - start_pos_y - size_y;
        if (rand_num_within(0,1))
        {
            if (rand_num_within(0,1))
            {
                rand_pox_x_within = rand_num_within(start_pos_x,start_pos_x+size_x);
            }   
            else
            {
                rand_pox_x_within = rand_num_within(final_pos_x,final_pos_x+size_x);
            }
            rand_pox_y_within = rand_num_within(start_pos_y,final_pos_y+size_x);
        } 
        else
        {
            if (rand_num_within(0,1))
            {
                rand_pox_y_within = rand_num_within(start_pos_y,start_pos_y+size_x);
            }   
            else
            {
                rand_pox_y_within = rand_num_within(final_pos_y,final_pos_y+size_x);
                
            }
            rand_pox_x_within = rand_num_within(start_pos_x,final_pos_x+size_x);
        }
        return (Vector2){rand_pox_x_within,rand_pox_y_within};

    }
    else
    {
        rand_pox_x_within = rand_num_within(start_pos_x,tilesX-start_pos_x);
        rand_pox_y_within = rand_num_within(start_pos_y,tilesY-start_pos_y);
        return (Vector2){rand_pox_x_within,rand_pox_y_within};

    }

    
}
Vector2 vector_sum(Vector2 v1,Vector2 v2)
{
    return (Vector2){v1.x+v2.x,v1.y+v2.y};
}
