#ifndef TEXTURS_H
#define TEXTURS_H

#define FLOOR 1
#define WALL 2
#define PLAYER 3
#define ENEMY 4
//#define ARMOR_HELMET 5
#define ARMOR_CHEST 5
#define WEAPON 6
#define HELMET 7

#define COINS 8
#define HEALS 9
#define EXP 10

#define Width 0
#define Height 1

//#define ARMOR_TROUSERS 7
//#define ARMOR_BOOTS 8

#include "misc.h"  
#include "structurs.h"

extern char* floor_texturs[];
extern char* wall_texturs[];
extern char* player_texturs;
extern char* enemy_texturs[];
extern char* fog_texturs;

extern char* armor_chest_texturs[];
extern char* weapon_texturs[];
extern char* HELMET_texturs[];

extern char* coins_texturs[];
extern char* heals_texturs[];
extern char* experience_texturs[];

extern Color color_floor_texturs[];
extern Color color_wall_texturs[];
extern Color color_enemy_texturs[];

extern Color color_armor_chest_texturs[];
extern Color color_weapon_texturs[];
extern Color color_HELMET_texturs[];


#define floor_textur 1
#define wall_textur 2
#define player_textur 3
#define enemy_textur 4
#define small 0
#define medium 1
char *textur(int index, int textur_index);

void texturs_init(GAME_ANIM *game_anim);


void mics_items_textur_init(GAME_ANIM *game_anim);

void equipment_textur_init(GAME_ANIM *game_anim);

void enemies_textur_init(GAME_ANIM *game_anim);

void tiles_textur_init(GAME_ANIM *game_anim);


Texturs *create_texturs_struct(Allocator *alloc);

Animations *create_animations_struct(Allocator *alloc);

Animation create_animation(Texture2D textur, int direction, int frame_count, int frame_width, int frame_height, Rectangle start_frame, int anim_speed, Allocator *alloc);

void update_animations(GAME_ANIM *game_anim);

void draw_animation(Animation *anim, Vector2 pos, int size_x, int size_y, int pos_index, float rotate);

Animation get_item_animation(GAME_ANIM *game_anim, int index);

void append_item_anim_to_arr(GAME_ANIM *game_anim, Animation *anim);


void append_item_anim_to_map(GAME_ANIM *game_anim, Animation anim, int index);

void create_animations(GAME_DATA *game_data, GAME_ANIM *game_anim);

void delete_from_item_anim_queue(GAME_DATA *game_data, GAME_ANIM *game_anim, int id);

void append_animation(GAME_ANIM *game_anim, int object_type, int textur_type, int object_id);


#endif

