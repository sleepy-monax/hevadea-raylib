#pragma once

#include <hevadea/position.h>
#include <hevadea/tile.h>
#include <hevadea/constants.h>
#include <hevadea/rectangle.h>

#include <hevadea/utils.h>

typedef enum
{
    CHUNK_STATE_UNLOADED,
    CHUNK_STATE_UNLOADING_SHEDULED,
    CHUNK_STATE_LOADED,
    CHUNK_STATE_LOADING_SHEDULED,
} chunk_state_t;

typedef struct
{
    chunk_state_t state;
    chunk_position_t position;
    tile_instance_t tiles[TILE_PER_CHUNK][TILE_PER_CHUNK];
} chunk_t;

chunk_t *chunk_at(chunk_position_t at);

chunk_t *chunk_alloc(chunk_position_t at);

typedef iterate_state_t (*chunk_iterate_callback_t)(chunk_t *chunk, void *arg);

void chunk_iterate_all(chunk_iterate_callback_t callback, void *arg);

rectangle_t chunk_bound(chunk_position_t at);

void chunks_debug_draw(void);

void chunk_render_terrain(void);
