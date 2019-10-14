#pragma once

#include <stdbool.h>

#include <hevadea/constants.h>
#include <hevadea/vector.h>

typedef struct
{
    double X;
    double Y;
} position_t;

typedef struct
{
    int X;
    int Y;
} tile_position_t;

typedef struct
{
    int X;
    int Y;
} chunk_position_t;

#define DECL_POSITION_CONVERT_FUNCTION(__from, __to) \
    __to##_t __from##_to_##__to(__from##_t pos);

/* --- Position ------------------------------------------------------------- */

DECL_POSITION_CONVERT_FUNCTION(position, tile_position)

DECL_POSITION_CONVERT_FUNCTION(position, chunk_position)

vector_t position_sub(position_t left, position_t right);

vector_t position_to_vector(position_t pos);

position_t position_offset(position_t pos, vector_t vec);

vector_t position_vector_to(position_t from, position_t to);

double position_distance(position_t from, position_t to);

/* --- Tile Position -------------------------------------------------------- */

DECL_POSITION_CONVERT_FUNCTION(tile_position, position)

position_t tile_position_to_position_centered(tile_position_t pos);

DECL_POSITION_CONVERT_FUNCTION(tile_position, chunk_position)

/* --- Chunk Position ------------------------------------------------------- */

DECL_POSITION_CONVERT_FUNCTION(chunk_position, position)

DECL_POSITION_CONVERT_FUNCTION(chunk_position, tile_position)

bool chunk_position_equal(chunk_position_t a, chunk_position_t b);