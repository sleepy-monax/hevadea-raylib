#pragma once

#include <hevadea/color.h>
#include <hevadea/position.h>
#include <hevadea/rectangle.h>

typedef enum
{
    TILE_COMPONENT_SOLID = 1 << 0,

    __TILE_COMPONENT_COUNT,
} tile_component_t;
typedef struct
{
    const char *name;
    color_t color;
    tile_component_t components;
} tile_blueprint_t;

typedef struct
{
    double temperature;
    double elevation;
    double moisture;

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

tile_instance_t *
tile_at(tile_position_t pos);

bool tile_has_component(tile_instance_t *tile, tile_component_t mask);

rectangle_t tile_bound(tile_position_t tile);
