#pragma once

#include "hevadea/constants.h"
#include "hevadea/position.h"
#include "hevadea/rectangle.h"
#include "hevadea/tile/tile.h"
#include "hevadea/utils/Utils.h"

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

typedef IterationDecision (*ChunkIterateCallback)(void *target, chunk_t *chunk);

void chunk_iterate_all(void *target, ChunkIterateCallback callback);

rectangle_t chunk_bound(chunk_position_t at);

void chunks_debug_draw(void);

void chunk_render_terrain(void);
