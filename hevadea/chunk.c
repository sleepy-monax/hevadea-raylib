#include <raylib.h>

#include "hevadea/camera.h"
#include "hevadea/chunk.h"
#include "hevadea/graphic.h"
#include "hevadea/logger.h"
#include "hevadea/utils/Utils.h"

static chunk_t chunks[MAX_LOADED_CHUNK] = {};

chunk_t *chunk_at(chunk_position_t at)
{
    for (int i = 0; i < MAX_LOADED_CHUNK; i++)
    {
        chunk_t *chunk = &chunks[i];

        if (chunk->state != CHUNK_STATE_UNLOADED)
        {
            if (chunk_position_equal(chunk->position, at))
            {
                return chunk;
            }
        }
    }

    return NULL;
}

rectangle_t chunk_bound(chunk_position_t at)
{
    return (rectangle_t){
        at.X * UNIT_PER_CHUNK,
        at.Y * UNIT_PER_CHUNK,
        UNIT_PER_CHUNK,
        UNIT_PER_CHUNK,
    };
}

chunk_t *chunk_alloc(chunk_position_t at)
{
    for (int i = 0; i < MAX_LOADED_CHUNK; i++)
    {
        chunk_t *chunk = &chunks[i];

        if (chunk->state == CHUNK_STATE_UNLOADED)
        {
            chunk->position = at;

            return chunk;
        }
    }

    return NULL;
}

void chunk_iterate_all(void *target, ChunkIterateCallback callback)
{
    assert(callback);

    for (int i = 0; i < MAX_LOADED_CHUNK; i++)
    {
        chunk_t *chunk = &chunks[i];

        if (chunk->state != CHUNK_STATE_UNLOADED)
        {
            if (callback(target, chunk) == ITERATION_STOP)
            {
                return;
            }
        }
    }
}

void chunks_debug_draw(void)
{
    for (int i = 0; i < MAX_LOADED_CHUNK; i++)
    {
        chunk_t *chunk = &chunks[i];

        if (chunk->state != CHUNK_STATE_UNLOADED)
        {
            color_t color = COLOR_GRAY;

            if (chunk != NULL)
            {
                if (chunk->state == CHUNK_STATE_LOADING_SHEDULED)
                {
                    color = COLOR_GREEN;
                }
                else if (chunk->state == CHUNK_STATE_LOADED)
                {
                    color = COLOR_BLACK;
                }
                else if (chunk->state == CHUNK_STATE_UNLOADING_SHEDULED)
                {
                    color = COLOR_RED;
                }
            }

            graphic_draw_rectangle(chunk_bound(chunk->position), color);
        }
    }
}

void chunk_render_terrain_corner(sprite_t sprite, vector_t pos, bool a, bool b, bool c, vector_t case1, vector_t case2, vector_t case3, vector_t case4, vector_t case5)
{
    if (!a & !c)
        sprite = sprite_subsprite(sprite, 4, 4, case1.X, case1.Y);
    else if (a & !c)
        sprite = sprite_subsprite(sprite, 4, 4, case2.X, case2.Y);
    else if (!a & c)
        sprite = sprite_subsprite(sprite, 4, 4, case3.X, case3.Y);
    else if (!b)
        sprite = sprite_subsprite(sprite, 4, 4, case4.X, case4.Y);
    else
        sprite = sprite_subsprite(sprite, 4, 4, case5.X, case5.Y);

    graphic_draw_sprite(sprite, pos, COLOR_WHITE);
}

IterationDecision chunk_render_terrain_callback(void *arg, chunk_t *chunk)
{
    (void)arg;

    if (chunk->state != CHUNK_STATE_LOADED)
        return ITERATION_CONTINUE;

    tile_position_t chunk_pos = chunk_position_to_tile_position(chunk->position);

    for (int x = 0; x < TILE_PER_CHUNK; x++)
    {
        for (int y = 0; y < TILE_PER_CHUNK; y++)
        {
            tile_position_t tile_pos = (tile_position_t){x + chunk_pos.X, y + chunk_pos.Y};

            if (tile_has_component(tile_pos, TILE_COMPONENT_SPRITE))
            {
                tile_connection_t connection = tile_get_connection(tile_pos);
                sprite_t sprite = tile_get_sprite(tile_pos);
                vector_t vec = position_to_vector(tile_position_to_position(tile_pos));

                graphic_fill_rectangle(tile_get_bound(tile_pos), (color_t){148, 120, 92, 255});

                chunk_render_terrain_corner(sprite, vector_add(vec, (vector_t){0, 0}), connection.left, connection.up_left, connection.up,
                                            (vector_t){0, 0}, (vector_t){0, 2}, (vector_t){0, 3}, (vector_t){2, 0}, (vector_t){2, 2});

                chunk_render_terrain_corner(sprite, vector_add(vec, (vector_t){0, UNIT_PER_TILE / 2}), connection.down, connection.down_left, connection.left,
                                            (vector_t){0, 1}, (vector_t){0, 3}, (vector_t){1, 3}, (vector_t){2, 1}, (vector_t){2, 3});

                chunk_render_terrain_corner(sprite, vector_add(vec, (vector_t){UNIT_PER_TILE / 2, 0}), connection.up, connection.up_right, connection.right,
                                            (vector_t){1, 0}, (vector_t){1, 2}, (vector_t){0, 2}, (vector_t){3, 0}, (vector_t){3, 2});

                chunk_render_terrain_corner(sprite, vector_add(vec, (vector_t){UNIT_PER_TILE / 2, UNIT_PER_TILE / 2}), connection.right, connection.down_right, connection.down,
                                            (vector_t){1, 1}, (vector_t){1, 3}, (vector_t){1, 2}, (vector_t){3, 1}, (vector_t){3, 3});
            }
            else
            {
                graphic_fill_rectangle(tile_get_bound(tile_pos), tile_get_color(tile_pos));
            }
        }
    }

    return ITERATION_CONTINUE;
}

void chunk_render_terrain(void)
{
    camera_interate_on_screen_chunk(NULL, (ChunkIterateCallback)chunk_render_terrain_callback);
}
