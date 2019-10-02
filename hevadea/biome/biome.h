#pragma once

#include <hevadea/tile/tile.h>

typedef struct
{
    const char *name;

    double temperature;
    double elevation;
    double moisture;

    tile_blueprint_t *tile;
} biome_t;

biome_t *biome_lookup(double temperature, double elevation, double moisture);
