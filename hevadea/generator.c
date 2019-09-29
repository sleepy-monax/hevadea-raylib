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

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            tile_position_t pos = (tile_position_t){x, y};
            double value = generator_terrain_altitude(POS_ADD(tile_position_t, chunk_pos, pos));

            if (value > 0)
            {
                chunk->tiles[x][y].color = (color_t){0, 255, 0, 255};
            }
            else
            {
                chunk->tiles[x][y].color = (color_t){0, 0, 255, 255};
            }
        }
    }
}