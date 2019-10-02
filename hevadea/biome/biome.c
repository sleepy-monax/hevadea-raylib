#include <math.h>
#include <stddef.h>
#include <assert.h>

#include <hevadea/biome/biome.h>

// static biome_t BIOME_MONTAIN = {
//     .name = "montain",
//
//     .tile = &TILE_ROCK,
//
//     .temperature = -0.1,
//     .elevation = 0.75,
//     .moisture = 0,
// };

static biome_t BIOME_TAIGA = {
    .name = "taiga",

    .tile = &TILE_DIRT,

    .temperature = -0.5,
    .elevation = 0,
    .moisture = 0.5,
};

static biome_t BIOME_FOREST = {
    .name = "forest",

    .tile = &TILE_FOREST_GRASS,

    .temperature = 0,
    .elevation = 0.5,
    .moisture = 0.5,
};

static biome_t BIOME_JUNGLE = {
    .name = "jungle",

    .tile = &TILE_GRASS,

    .temperature = 0.5,
    .elevation = 0.5,
    .moisture = 0.5,
};

static biome_t BIOME_TUNDRA = {
    .name = "tundra",

    .tile = &TILE_SNOW,

    .temperature = -0.5,
    .elevation = 0,
    .moisture = 0,
};

static biome_t BIOME_PLAIN = {
    .name = "plain",

    .tile = &TILE_GRASS,

    .temperature = 0,
    .elevation = 0.01,
    .moisture = 0,
};

static biome_t BIOME_DESERT = {
    .name = "desert",

    .tile = &TILE_SAND,

    .temperature = 0.5,
    .elevation = 0,
    .moisture = -0.5,
};

static biome_t BIOME_SWAMP = {
    .name = "swamp",

    .tile = &TILE_SWAMP_GRASS,

    .temperature = 0,
    .elevation = 0.1,
    .moisture = 1,
};

static biome_t BIOME_BEACH = {
    .name = "beach",

    .tile = &TILE_BEACH_SAND,

    .temperature = 0,
    .elevation = -0.1,
    .moisture = 0,
};

static biome_t BIOME_STONE_BEACH = {
    .name = "stone_beach",

    .tile = &TILE_ROCK,

    .temperature = -0.5,
    .elevation = -0.15,
    .moisture = 0,
};

static biome_t BIOME_COLD_SEA = {
    .name = "cold_sea",

    .tile = &TILE_WATER,

    .temperature = -0.5,
    .elevation = -0.2,
    .moisture = 0,
};

static biome_t BIOME_COLD_DEEP_SEA = {
    .name = "cold_deep_sea",

    .tile = &TILE_DEEP_WATER,

    .temperature = 0,
    .elevation = -0.5,
    .moisture = 0,
};

static biome_t BIOME_SEA = {
    .name = "sea",

    .tile = &TILE_WATER,

    .temperature = 0,
    .elevation = -0.2,
    .moisture = 0,
};

static biome_t BIOME_DEEP_SEA = {
    .name = "deep_sea",

    .tile = &TILE_DEEP_WATER,

    .temperature = 0,
    .elevation = -0.5,
    .moisture = 0,
};

static biome_t *biomes[] = {
    //&BIOME_MONTAIN,

    &BIOME_TAIGA,
    &BIOME_FOREST,
    &BIOME_JUNGLE,

    &BIOME_TUNDRA,
    &BIOME_PLAIN,
    &BIOME_DESERT,

    &BIOME_SWAMP,
    &BIOME_BEACH,
    &BIOME_STONE_BEACH,

    &BIOME_SEA,
    &BIOME_DEEP_SEA,

    &BIOME_COLD_SEA,
    &BIOME_COLD_DEEP_SEA,
    NULL,
};

biome_t *biome_lookup(double temperature, double elevation, double moisture)
{
    biome_t *best_biome = NULL;
    double best_distance = 10000000;

    for (int i = 0; biomes[i]; i++)
    {
        biome_t *biome = biomes[i];

        double distance = sqrt((biome->temperature - temperature) * (biome->temperature - temperature) +
                               (biome->elevation - elevation) * (biome->elevation - elevation) +
                               (biome->moisture - moisture) * (biome->moisture - moisture));

        if (distance < best_distance)
        {
            best_distance = distance;
            best_biome = biome;
        }
    }

    assert(best_biome != NULL);

    return best_biome;
}