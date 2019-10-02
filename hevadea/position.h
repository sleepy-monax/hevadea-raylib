#pragma once

#include <stdbool.h>

#include <hevadea/constants.h>

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

#define POS_ADD(__type, __a, __b)            \
    (__type)                                 \
    {                                        \
        (__a).X + (__b).X, (__a).Y + (__b).Y \
    }

#define POS_SUB(__type, __a, __b)            \
    (__type)                                 \
    {                                        \
        (__a).X - (__b).X, (__a).Y - (__b).Y \
    }

#define DECL_POSITION_CONVERT_FUNCTION(__from, __to) \
    __to##_t __from##_to_##__to(__from##_t pos);

/* --- Position ------------------------------------------------------------- */

DECL_POSITION_CONVERT_FUNCTION(position, tile_position)

DECL_POSITION_CONVERT_FUNCTION(position, chunk_position)

/* --- Tile Position -------------------------------------------------------- */

DECL_POSITION_CONVERT_FUNCTION(tile_position, position)

DECL_POSITION_CONVERT_FUNCTION(tile_position, chunk_position)

/* --- Chunk Position ------------------------------------------------------- */

DECL_POSITION_CONVERT_FUNCTION(chunk_position, position)

DECL_POSITION_CONVERT_FUNCTION(chunk_position, tile_position)

bool chunk_position_equal(chunk_position_t a, chunk_position_t b);