#pragma once

#include <hevadea/color.h>
#include <hevadea/position.h>
#include <hevadea/rectangle.h>
#include <hevadea/atlas.h>

typedef enum
{
    TILE_COMPONENT_SOLID = 1 << 0,
    TILE_COMPONENT_LIQUID = 1 << 1,
    TILE_COMPONENT_SPRITE = 1 << 2,

    __TILE_COMPONENT_COUNT,
} tile_component_t;
typedef struct
{
    const char *name;
    color_t color;
    sprite_t sprite;
    tile_component_t components;
} tile_blueprint_t;

typedef struct
{
    bool up;
    bool down;
    bool left;
    bool right;
    bool up_left;
    bool up_right;
    bool down_left;
    bool down_right;
} tile_connection_t;

typedef struct
{
    tile_blueprint_t *blueprint;
} tile_instance_t;

extern tile_blueprint_t TILE_WATER;
extern tile_blueprint_t TILE_DEEP_WATER;
extern tile_blueprint_t TILE_SAND;
extern tile_blueprint_t TILE_BEACH_SAND;
extern tile_blueprint_t TILE_GRASS;
extern tile_blueprint_t TILE_SWAMP_GRASS;
extern tile_blueprint_t TILE_FOREST_GRASS;
extern tile_blueprint_t TILE_SNOW;
extern tile_blueprint_t TILE_DIRT;
extern tile_blueprint_t TILE_ROCK;
extern tile_blueprint_t TILE_GRAVEL;

void tile_load(void);

tile_instance_t *tile_at(tile_position_t pos);

bool tile_has_component(tile_position_t pos, tile_component_t mask);

tile_connection_t tile_get_connection(tile_position_t pos);

rectangle_t tile_get_bound(tile_position_t tile);

color_t tile_get_color(tile_position_t pos);

sprite_t tile_get_sprite(tile_position_t pos);