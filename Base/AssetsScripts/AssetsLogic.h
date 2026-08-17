#ifndef ASSETSLOGIC_H
#define ASSETSLOGIC_H

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

#include "MiscScripts.h"  
#include "structurs.h"

#include "TextursLogic.h"
#include "AnimationsLogic.h"

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

#endif
