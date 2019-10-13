#include <math.h>

#include <hevadea/position.h>
#include <hevadea/vector.h>

#define DEFN_POSITION_CONVERT_FUNCTION(__from, __to, __how)              \
    __to##_t __from##_to_##__to(__from##_t pos)                          \
    {                                                                    \
        return (__to##_t){.X = (__how((pos.X))), .Y = (__how((pos.Y)))}; \
    }

/* --- Position ------------------------------------------------------------- */

#define POS_TO_TILE(__v) (int)floor(__v / UNIT_PER_TILE)
DEFN_POSITION_CONVERT_FUNCTION(position, tile_position, POS_TO_TILE)

#define POS_TO_CHUNK(__v) (int)floor(__v / UNIT_PER_CHUNK)
DEFN_POSITION_CONVERT_FUNCTION(position, chunk_position, POS_TO_CHUNK)

vector_t position_sub(position_t left, position_t right)
{
    return (vector_t){left.X - right.X, left.Y - right.Y};
}

vector_t position_to_vector(position_t pos)
{
    return (vector_t){pos.X, pos.Y};
}

position_t position_offset(position_t pos, vector_t vec)
{
    return (position_t){pos.X + vec.X, pos.Y + vec.Y};
}

vector_t position_vector_to(position_t from, position_t to)
{
    return vector_normalized((vector_t){to.X - from.X, to.Y - from.Y});
}

/* --- Tile Position -------------------------------------------------------- */

#define TILE_TO_POS(__v) (__v * UNIT_PER_TILE)
DEFN_POSITION_CONVERT_FUNCTION(tile_position, position, TILE_TO_POS)

position_t tile_position_to_position_centered(tile_position_t pos)
{
    return (position_t){(pos.X + 0.5) * UNIT_PER_TILE, (pos.Y + 0.5) * UNIT_PER_TILE};
}

#define TILE_TO_CHUNK(__v) floor(__v / (double)TILE_PER_CHUNK)
DEFN_POSITION_CONVERT_FUNCTION(tile_position, chunk_position, TILE_TO_CHUNK)

/* --- Chunk Position ------------------------------------------------------- */

#define CHUNK_TO_POS(__v) (__v * UNIT_PER_CHUNK)
DEFN_POSITION_CONVERT_FUNCTION(chunk_position, position, CHUNK_TO_POS)

#define CHUNK_TO_TILE(__v) __v *TILE_PER_CHUNK
DEFN_POSITION_CONVERT_FUNCTION(chunk_position, tile_position, CHUNK_TO_TILE)

bool chunk_position_equal(chunk_position_t a, chunk_position_t b)
{
    return a.X == b.X && a.Y == b.Y;
}