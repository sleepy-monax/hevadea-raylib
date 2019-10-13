#include <hevadea/entity/entity.h>
#include <hevadea/biome/biome.h>
#include <hevadea/generator.h>
#include <hevadea/noise.h>
#include <hevadea/logger.h>

/* --- Elevation/Moisture/Temperature --------------------------------------- */

double generator_terrain_elevation(tile_position_t pos)
{
    return noise_octave(pos.X, pos.Y, 1 / 128.0, 32);
}

double generator_terrain_moisture(tile_position_t pos)
{
    return noise_octave(pos.X + 10000, pos.Y, 1 / 256.0, 8);
}

double generator_terrain_temperature(tile_position_t pos)
{
    return noise_octave(pos.X, pos.Y + 10000, 1 / 256.0, 8);
}

/* --- Biome generator ------------------------------------------------------ */

biome_t *generator_generate_biome(tile_position_t pos)
{
    double elevation = generator_terrain_elevation(pos);
    double moisture = generator_terrain_moisture(pos);
    double temperature = generator_terrain_temperature(pos);

    return biome_lookup(temperature, elevation, moisture);
}

/* --- Chunk generator ------------------------------------------------------ */

void generator_terain(chunk_t *chunk)
{
    tile_position_t chunk_pos = chunk_position_to_tile_position(chunk->position);

    for (int x = 0; x < TILE_PER_CHUNK; x++)
    {
        for (int y = 0; y < TILE_PER_CHUNK; y++)
        {
            tile_position_t pos = (tile_position_t){x + chunk_pos.X, y + chunk_pos.Y};

            biome_t *biome = generator_generate_biome(pos);

            chunk->tiles[x][y].blueprint = biome->tile;

            tile_position_t decor_pos = (tile_position_t){x + chunk->position.X * TILE_PER_CHUNK, y + chunk->position.Y * TILE_PER_CHUNK};

            if (biome->decorate)
            {
                biome->decorate(decor_pos);
            }
        }
    }
}