#ifndef MISC_H
#define MISC_H


#include "structurs.h"

#include <stdlib.h> 
#define CUTOUT 0
#define FULL 1

extern Vector2 parents_visen_map[9][9][2]; 

int rand_num_within(int min, int max);
void print_collision_map(GAME_DATA *game_data);

void print_objects_map(GAME_DATA *game_data);

void print_char_map(GAME_DATA *game_data, char **map);

void print_vectors_map(GAME_DATA *game_data);

void print_vector_arr(Vector2 *path, int amount);

bool vectors_comparison(Vector2 first_vector, Vector2 second_vector);

void print_int_map(GAME_DATA *game_data, int **map);

void pr_int(int x);

void pr_float(float x);

void pr_int_with_text(int x, char *s);

Vector2 rand_pos_within(int tilesX, int tilesY, float size_zone_coefficient, float start_coefficient, int mode);



#endif

