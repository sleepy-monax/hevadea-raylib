#include <stddef.h>
#include <string.h>

#include <hevadea/tile.h>
#include <hevadea/utils.h>
#include <hevadea/chunk.h>

tile_blueprint_t TILE_WATER = {
    .name = "water",
    .color = (color_t){0, 0, 255, 255},
    .components = 0,
};

tile_blueprint_t TILE_DEEP_WATER = {
    .name = "deep_water",
    .color = (color_t){0, 0, 175, 255},
    .components = TILE_COMPONENT_SOLID,
};

tile_blueprint_t TILE_SAND = {
    .name = "sand",
    .color = (color_t){255, 175, 0, 255},
    .components = 0,
};

tile_blueprint_t TILE_GRASS = {
    .name = "grass",
    .color = (color_t){0, 175, 0, 255},
    .components = 0,
};

tile_blueprint_t TILE_ROCK = {
    .name = "rock",
    .color = (color_t){100, 100, 100, 255},
    .components = TILE_COMPONENT_SOLID,
};

static tile_blueprint_t *blueprints[] = {&TILE_WATER, &TILE_DEEP_WATER, &TILE_SAND, &TILE_GRASS, &TILE_ROCK, NULL};

tile_instance_t *tile_at(tile_position_t pos)
{
    chunk_position_t chunk_pos = tile_position_to_chunk_position(pos);

    chunk_t *chunk = chunk_at(chunk_pos);

    if (chunk != NULL)
    {
        int in_chunk_x = pos.X % TILE_PER_CHUNK;
        int in_chunk_y = pos.Y % TILE_PER_CHUNK;

        if (in_chunk_x < 0)
            in_chunk_x += 16;

        if (in_chunk_y < 0)
            in_chunk_y += 16;

        return &chunk->tiles[in_chunk_x][in_chunk_y];
    }
    else
    {
        return NULL;
    }
}

bool tile_has_component(tile_instance_t *tile, tile_component_t mask)
{
    if (tile == NULL)
        return false;

    if (tile->blueprint == NULL)
        return false;

    return (tile->blueprint->components & mask) == mask;
}

tile_blueprint_t *tile_blueprint(const char *name)
{
    for (int i = 0; blueprints[i]; i++)
    {
        if (strcmp(blueprints[i]->name, name) == 0)
        {
            return blueprints[i];
        }
    }

    PANIC("Invalid blueprint name!");
}

rectangle_t tile_bound(tile_position_t tile)
{
    position_t tile_pos = tile_position_to_position(tile);
    return (rectangle_t){tile_pos.X, tile_pos.Y, UNIT_PER_TILE, UNIT_PER_TILE};
}