#include <stddef.h>
#include <string.h>

#include "hevadea/chunk.h"
#include "hevadea/tile/tile.h"
#include "hevadea/utils/Utils.h"

tile_blueprint_t TILE_WATER = {
    .name = "water",
    .color = (color_t){0, 0, 255, 255},
    .components = TILE_COMPONENT_LIQUID,
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

tile_blueprint_t TILE_SNOW = {
    .name = "snow",
    .color = (color_t){225, 225, 255, 255},
    .components = 0,
};

tile_blueprint_t TILE_DIRT = {
    .name = "dirt",
    .color = (color_t){125, 125, 50, 255},
    .components = 0,
};

tile_blueprint_t TILE_GRAVEL = {
    .name = "gravel",
    .color = (color_t){125, 100, 125, 255},
    .components = 0,
};

tile_blueprint_t TILE_ROCK = {
    .name = "rock",
    .color = (color_t){100, 100, 100, 255},
    .components = TILE_COMPONENT_SOLID,
};

static tile_blueprint_t *blueprints[] = {
    &TILE_WATER,
    &TILE_SAND,
    &TILE_GRASS,
    &TILE_SNOW,
    &TILE_DIRT,
    &TILE_ROCK,
    &TILE_GRAVEL,
    NULL,
};

void tile_load(void)
{
    TILE_GRASS.components |= TILE_COMPONENT_SPRITE;
    TILE_GRASS.sprite = atlas_sprite_by_name("tile/grass");

    TILE_WATER.components |= TILE_COMPONENT_SPRITE;
    TILE_WATER.sprite = atlas_sprite_by_name("tile/water");

    TILE_SAND.components |= TILE_COMPONENT_SPRITE;
    TILE_SAND.sprite = atlas_sprite_by_name("tile/sand");

    TILE_ROCK.components |= TILE_COMPONENT_SPRITE;
    TILE_ROCK.sprite = atlas_sprite_by_name("tile/rock");

    TILE_SNOW.components |= TILE_COMPONENT_SPRITE;
    TILE_SNOW.sprite = atlas_sprite_by_name("tile/snow");

    TILE_DIRT.components |= TILE_COMPONENT_SPRITE;
    TILE_DIRT.sprite = atlas_sprite_by_name("tile/dirt");

    TILE_GRAVEL.components |= TILE_COMPONENT_SPRITE;
    TILE_GRAVEL.sprite = atlas_sprite_by_name("tile/gravel");
}

tile_instance_t *tile_at(tile_position_t pos)
{
    chunk_position_t chunk_pos = tile_position_to_chunk_position(pos);

    chunk_t *chunk = chunk_at(chunk_pos);

    if (chunk != NULL && chunk->state == CHUNK_STATE_LOADED)
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

tile_connection_t tile_get_connection(tile_position_t pos)
{
    tile_connection_t connection;
    tile_instance_t *other_tile;
    tile_instance_t *tile = tile_at(pos);

    other_tile = tile_at((tile_position_t){pos.X, pos.Y - 1});
    connection.up = other_tile && other_tile->blueprint == tile->blueprint;

    other_tile = tile_at((tile_position_t){pos.X, pos.Y + 1});
    connection.down = other_tile && other_tile->blueprint == tile->blueprint;

    other_tile = tile_at((tile_position_t){pos.X - 1, pos.Y});
    connection.left = other_tile && other_tile->blueprint == tile->blueprint;

    other_tile = tile_at((tile_position_t){pos.X + 1, pos.Y});
    connection.right = other_tile && other_tile->blueprint == tile->blueprint;

    other_tile = tile_at((tile_position_t){pos.X - 1, pos.Y - 1});
    connection.up_left = other_tile && other_tile->blueprint == tile->blueprint;

    other_tile = tile_at((tile_position_t){pos.X + 1, pos.Y - 1});
    connection.up_right = other_tile && other_tile->blueprint == tile->blueprint;

    other_tile = tile_at((tile_position_t){pos.X - 1, pos.Y + 1});
    connection.down_left = other_tile && other_tile->blueprint == tile->blueprint;

    other_tile = tile_at((tile_position_t){pos.X + 1, pos.Y + 1});
    connection.down_right = other_tile && other_tile->blueprint == tile->blueprint;

    return connection;
}

bool tile_has_component(tile_position_t pos, tile_component_t mask)
{
    tile_instance_t *tile = tile_at(pos);

    if (tile == NULL || tile->blueprint == NULL)
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

rectangle_t tile_get_bound(tile_position_t tile)
{
    position_t tile_pos = tile_position_to_position(tile);

    return (rectangle_t){tile_pos.X, tile_pos.Y, UNIT_PER_TILE, UNIT_PER_TILE};
}

color_t tile_get_color(tile_position_t pos)
{
    tile_instance_t *tile = tile_at(pos);

    if (tile == NULL || tile->blueprint == NULL)
        return COLOR_BLACK;

    return tile->blueprint->color;
}

sprite_t tile_get_sprite(tile_position_t pos)
{
    tile_instance_t *tile = tile_at(pos);

    if (tile == NULL || tile->blueprint == NULL)
        return atlas_sprite_by_name("none");

    return tile->blueprint->sprite;
}
