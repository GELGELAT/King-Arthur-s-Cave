#ifndef ANIMATION_MAPS_STRUCT_H
#define ANIMATION_MAPS_STRUCT_H
typedef struct Animation Animation;

typedef struct AnimationItemsMap
{
    Animation* animation_map;
    Animation** animation_map_queue;
    int amount_animation_map_queue;

}AnimationItemsMap;
typedef struct AnimationEnemyMap
{
    Animation*** animation_map_queue;
    int amount_animation_map_queue;

}AnimationEnemyMap;
typedef struct AnimationPlayerMap
{
    Animation*** animation_map_queue;
    int amount_animation_map_queue;

}AnimationPlayerMap;
typedef struct AnimationActionTilesMap
{
    Animation** animation_action_tiles_map_queue;
    int amount_animation_action_tiles_map_queue;

}AnimationActionTilesMap;
typedef struct AnimationWorldMaps
{
    AnimationActionTilesMap* animation_action_tiles_map;


}AnimationWorldMaps;
typedef struct AnimationMaps
{
    AnimationItemsMap* animation_items_map;
    AnimationEnemyMap* animation_enemies_map;
    AnimationPlayerMap* animation_player_map;
    AnimationWorldMaps* animation_world_maps;
}AnimationMaps;

#endif