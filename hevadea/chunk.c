#include <stddef.h>
#include <raylib.h>

#include <hevadea/chunk.h>
#include <hevadea/camera.h>
#include <hevadea/logger.h>
#include <hevadea/utils.h>

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
        at.X * CHUNK_SIZE,
        at.Y * CHUNK_SIZE,
        CHUNK_SIZE,
        CHUNK_SIZE,
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
            if (callback(chunk, arg) == SEARCH_STOP)
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
            Color color = GRAY;

            if (chunk != NULL)
            {
                if (chunk->state == CHUNK_STATE_LOADING_SHEDULED)
                {
                    color = BLUE;
                }
                else if (chunk->state == CHUNK_STATE_LOADED)
                {
                    color = WHITE;
                    color.a = 0;
                }
                else if (chunk->state == CHUNK_STATE_UNLOADING_SHEDULED)
                {
                    color = RED;
                }
            }

            DrawRectangleLines(chunk->position.X * CHUNK_SIZE, chunk->position.Y * CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE, color);
        }
    }
}

iterate_state_t chunk_render_terrain_callback(chunk_t *chunk, void *arg)
{
    (void)arg;

    if (chunk->state != CHUNK_STATE_LOADED)
        return SEARCH_CONTINUE;

    tile_position_t chunk_pos = chunk_position_to_tile_position(chunk->position);

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            tile_position_t pos = (tile_position_t){x + chunk_pos.X, y + chunk_pos.Y};

            tile_t t = chunk->tiles[x][y];

            Color c = {t.color.R, t.color.G, t.color.B, t.color.A};

            DrawRectangle(pos.X, pos.Y, 1, 1, c);
        }
    }

    return SEARCH_CONTINUE;
}

void chunk_render_terrain(void)
{
    chunk_iterate_all(chunk_render_terrain_callback, NULL);
}