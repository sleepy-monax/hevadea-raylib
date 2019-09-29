#include <hevadea/position.h>

#define DEFN_POSITION_CONVERT_FUNCTION(__from, __to, __how)              \
    __to##_t __from##_to_##__to(__from##_t pos)                          \
    {                                                                    \
        return (__to##_t){.X = (__how((pos.X))), .Y = (__how((pos.Y)))}; \
    }

/* --- Position ------------------------------------------------------------- */

#define POS_TO_TILE(__v) (int)__v
DEFN_POSITION_CONVERT_FUNCTION(position, tile_position, POS_TO_TILE)

#define POS_TO_CHUNK(__v) (int)__v / CHUNK_SIZE
DEFN_POSITION_CONVERT_FUNCTION(position, chunk_position, POS_TO_CHUNK)

/* --- Tile Position -------------------------------------------------------- */

#define TILE_TO_POS(__v) __v + 0.5
DEFN_POSITION_CONVERT_FUNCTION(tile_position, position, TILE_TO_POS)

#define TILE_TO_CHUNK(__v) __v / CHUNK_SIZE
DEFN_POSITION_CONVERT_FUNCTION(tile_position, chunk_position, TILE_TO_CHUNK)

/* --- Chunk Position ------------------------------------------------------- */

#define CHUNK_TO_POS(__v) __v *(double)CHUNK_SIZE
DEFN_POSITION_CONVERT_FUNCTION(chunk_position, position, CHUNK_TO_POS)

#define CHUNK_TO_TILE(__v) __v *CHUNK_SIZE
DEFN_POSITION_CONVERT_FUNCTION(chunk_position, tile_position, CHUNK_TO_TILE)

bool chunk_position_equal(chunk_position_t a, chunk_position_t b)
{
    return a.X == b.X && a.Y == b.Y;
}