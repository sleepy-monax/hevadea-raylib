#include <stddef.h>

#include <hevadea/camera.h>
#include <hevadea/chunk.h>
#include <hevadea/chunkloader.h>
#include <hevadea/generator.h>
#include <hevadea/utils.h>
#include <hevadea/entity/entity.h>

/* --- Chunk sheduler ------------------------------------------------------- */

static iterate_state_t chunk_load_shedule_callback(int x, int y, void *args)
{
    (void)args;

    chunk_position_t pos = (chunk_position_t){x, y};

    chunk_t *chunk = chunk_at(pos);

    if (!chunk)
    {
        chunk = chunk_alloc(pos);

        if (chunk != NULL)
        {
            chunk->state = CHUNK_STATE_LOADING_SHEDULED;
        }
    }
    else if (chunk->state == CHUNK_STATE_UNLOADING_SHEDULED)
    {
        chunk->state = CHUNK_STATE_LOADED;
    }

    return ITERATION_CONTINUE;
}

static iterate_state_t chunk_unload_shedule_callback(chunk_t *chunk, void *arg)
{
    (void)arg;

    if (!rectangle_contain_chunk_position(camera_unload_bound(), chunk->position))
    {
        if (chunk->state == CHUNK_STATE_LOADED)
        {
            chunk->state = CHUNK_STATE_UNLOADING_SHEDULED;
        }
        else if (chunk->state == CHUNK_STATE_LOADING_SHEDULED)
        {
            chunk->state = CHUNK_STATE_UNLOADED;
        }
    }

    return ITERATION_CONTINUE;
}

void chunkloader_shedule(void)
{
    // Shedule chunk loading
    chunk_position_t camera_pos = position_to_chunk_position(camera_get_focus());
    iterate_square(camera_pos.X, camera_pos.Y, CHUNK_LOAD_DISTANCE, chunk_load_shedule_callback, NULL);

    // Shedule chunk unloading
    chunk_iterate_all(chunk_unload_shedule_callback, NULL);
}

/* --- Chunk loading -------------------------------------------------------- */

static iterate_state_t chunk_load_callback(int x, int y, void *args)
{
    (void)args;

    chunk_t *chunk = chunk_at((chunk_position_t){x, y});

    if (chunk != NULL && chunk->state == CHUNK_STATE_LOADING_SHEDULED)
    {
        chunk->state = CHUNK_STATE_LOADED;

        generator_terain(chunk);

        return ITERATION_STOP;
    }

    return ITERATION_CONTINUE;
}

void chunkloader_load_chunks(void)
{
    chunk_position_t camera_pos = position_to_chunk_position(camera_get_focus());
    iterate_spiral(camera_pos.X, camera_pos.Y, CHUNK_LOAD_DISTANCE, chunk_load_callback, NULL);
}

/* --- Chunk unloading ------------------------------------------------------ */

static iterate_state_t entity_unload_callback(entity_instance_t *entity, chunk_t *chunk)
{
    chunk_position_t entity_pos = entity_get_chunk(entity);

    if (chunk_position_equal(entity_pos, chunk->position))
    {
        entity_destroy(entity);
    }

    return ITERATION_CONTINUE;
}

static iterate_state_t chunk_unload_callback(chunk_t *chunk, void *args)
{
    (void)args;

    if (chunk->state == CHUNK_STATE_UNLOADING_SHEDULED)
    {
        entity_iterate_all((entity_iterate_callback_t)entity_unload_callback, chunk);

        chunk->state = CHUNK_STATE_UNLOADED;

        return ITERATION_STOP;
    }

    return ITERATION_CONTINUE;
}

void chunkloader_unload_chunks(void)
{
    chunk_iterate_all(chunk_unload_callback, NULL);
}