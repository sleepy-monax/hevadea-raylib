#include <hevadea/entity/entity.h>
#include <hevadea/biome/biome.h>
#include <hevadea/generator.h>
#include <hevadea/noise.h>

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

void generator_terain(chunk_t *chunk)
{
    tile_position_t chunk_pos = chunk_position_to_tile_position(chunk->position);

    for (int x = 0; x < TILE_PER_CHUNK; x++)
    {
        for (int y = 0; y < TILE_PER_CHUNK; y++)
        {
            tile_position_t pos = (tile_position_t){x, y};

            double elevation = generator_terrain_elevation(POS_ADD(tile_position_t, chunk_pos, pos));
            double moisture = generator_terrain_moisture(POS_ADD(tile_position_t, chunk_pos, pos));
            double temperature = generator_terrain_temperature(POS_ADD(tile_position_t, chunk_pos, pos));

            biome_t *biome = biome_lookup(temperature, elevation, moisture);

            chunk->tiles[x][y].blueprint = biome->tile;

            chunk->tiles[x][y].elevation = elevation;
            chunk->tiles[x][y].moisture = moisture;
            chunk->tiles[x][y].temperature = temperature;
        }
    }
}