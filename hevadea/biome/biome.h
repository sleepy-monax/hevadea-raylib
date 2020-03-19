#pragma once

#include "hevadea/tile/tile.h"
#include "hevadea/entity/entity.h"

typedef void (*biome_decorate_callback_t)(tile_position_t pos);

typedef struct
{
    const char *name;

    double temperature;
    double elevation;
    double moisture;

    biome_decorate_callback_t decorate;

    tile_blueprint_t *tile;
} biome_t;

biome_t *biome_lookup(double temperature, double elevation, double moisture);
