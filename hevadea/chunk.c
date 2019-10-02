#include <raylib.h>
#include <stddef.h>

#include <hevadea/chunk.h>
#include <hevadea/camera.h>
#include <hevadea/logger.h>
#include <hevadea/utils.h>
#include <hevadea/graphic.h>

static chunk_t chunks[MAX_LOADED_CHUNK] = {0};

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

void chunk_iterate_all(chunk_iterate_callback_t callback, void *arg)
{
    for (int i = 0; i < MAX_LOADED_CHUNK; i++)
    {
        chunk_t *chunk = &chunks[i];

        if (chunk->state != CHUNK_STATE_UNLOADED)
        {
            if (callback(chunk, arg) == ITERATION_STOP)
            {
                return;
            }
        }
    }
}

void chunks_debug_draw(void)
{
    //chunk_position_t camera_pos = position_to_chunk_position(camera_get_position());

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

iterate_state_t chunk_render_terrain_callback(chunk_t *chunk, void *arg)
{
    (void)arg;

    if (chunk->state != CHUNK_STATE_LOADED)
        return ITERATION_CONTINUE;

    tile_position_t chunk_pos = chunk_position_to_tile_position(chunk->position);

    for (int x = 0; x < TILE_PER_CHUNK; x++)
    {
        for (int y = 0; y < TILE_PER_CHUNK; y++)
        {
            tile_position_t pos = (tile_position_t){x + chunk_pos.X, y + chunk_pos.Y};

            tile_blueprint_t *t = chunk->tiles[x][y].blueprint;

            Color c = {t->color.R, t->color.G, t->color.B, t->color.A};

            DrawRectangle(pos.X * UNIT_PER_TILE, pos.Y * UNIT_PER_TILE, UNIT_PER_TILE, UNIT_PER_TILE, c);
        }
    }

    return ITERATION_CONTINUE;
}

void chunk_render_terrain(void)
{
    camera_interate_on_screen_chunk(chunk_render_terrain_callback, NULL);
}
