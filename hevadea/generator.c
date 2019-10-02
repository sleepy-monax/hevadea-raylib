#include <hevadea/generator.h>
#include <hevadea/noise.h>

double generator_terrain_altitude(tile_position_t pos)
{
    return noise_octave(pos.X, pos.Y, 1 / 128.0, 32);
}

// double generator_terrain_temperature(tile_position_t pos)
// {
// }

void generator_terain(chunk_t *chunk)
{
    tile_position_t chunk_pos = chunk_position_to_tile_position(chunk->position);

    for (int x = 0; x < TILE_PER_CHUNK; x++)
    {
        for (int y = 0; y < TILE_PER_CHUNK; y++)
        {
            tile_position_t pos = (tile_position_t){x, y};
            double value = generator_terrain_altitude(POS_ADD(tile_position_t, chunk_pos, pos));

            if (value > 0)
            {
                if (value > 0.95)
                {
                    chunk->tiles[x][y].blueprint = &TILE_ROCK;
                }
                else if (value > 0.3)
                {
                    chunk->tiles[x][y].blueprint = &TILE_GRASS;
                }
                else
                {
                    chunk->tiles[x][y].blueprint = &TILE_SAND;
                }
            }
            else
            {
                if (value > -0.5)
                {
                    chunk->tiles[x][y].blueprint = &TILE_WATER;
                }
                else
                {
                    chunk->tiles[x][y].blueprint = &TILE_DEEP_WATER;
                }
            }
        }
    }
}