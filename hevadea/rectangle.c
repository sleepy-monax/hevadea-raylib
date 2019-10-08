#include <hevadea/rectangle.h>

bool rectangle_contain_position(rectangle_t rect, position_t pos)
{
    return (rect.X <= pos.X) &&
           (rect.X + rect.Width > pos.X) &&
           (rect.Y <= pos.Y) &&
           (rect.Y + rect.Height > pos.Y);
}

bool rectangle_contain_tile_position(rectangle_t rect, tile_position_t pos)
{
    return rectangle_contain_position(rect, tile_position_to_position(pos));
}

bool rectangle_contain_chunk_position(rectangle_t rect, chunk_position_t pos)
{
    return rectangle_contain_position(rect, chunk_position_to_position(pos));
}

rectangle_t rectangle_offset(rectangle_t rect, vector_t vec)
{
    return (rectangle_t){
        rect.X + vec.X,
        rect.Y + vec.Y,
        rect.Width,
        rect.Height,
    };
}

bool rectangle_coliding(rectangle_t a, rectangle_t b)
{
    return a.X < b.X + b.Width &&
           a.X + a.Width > b.X &&
           a.Y < b.Y + b.Height &&
           a.Y + a.Height > b.Y;
}
/* ---  --- */

vector_t rectangle_topleft(rectangle_t rect)
{
    return (vector_t){rect.X, rect.Y};
}

vector_t rectangle_topright(rectangle_t rect)
{
    return (vector_t){rect.X + rect.Width, rect.Y};
}

vector_t rectangle_bottomleft(rectangle_t rect)
{
    return (vector_t){rect.X, rect.Y + rect.Height};
}

vector_t rectangle_bottomright(rectangle_t rect)
{
    return (vector_t){rect.X + rect.Width, rect.Y + rect.Height};
}

/* --- Position corners ----------------------------------------------------- */

position_t rectangle_topleft_position(rectangle_t rect)
{
    return (position_t){rect.X, rect.Y};
}

position_t rectangle_topright_position(rectangle_t rect)
{
    return (position_t){rect.X + rect.Width, rect.Y};
}

position_t rectangle_bottomleft_position(rectangle_t rect)
{
    return (position_t){rect.X, rect.Y + rect.Height};
}

position_t rectangle_bottomright_position(rectangle_t rect)
{
    return (position_t){rect.X + rect.Width, rect.Y + rect.Height};
}

/* --- Tile cornes ---------------------------------------------------------- */

tile_position_t rectangle_topleft_tile(rectangle_t rect)
{
    return position_to_tile_position(rectangle_topleft_position(rect));
}

tile_position_t rectangle_topright_tile(rectangle_t rect)
{
    return position_to_tile_position(rectangle_topright_position(rect));
}

tile_position_t rectangle_bottomleft_tile(rectangle_t rect)
{
    return position_to_tile_position(rectangle_bottomleft_position(rect));
}

tile_position_t rectangle_bottomright_tile(rectangle_t rect)
{
    return position_to_tile_position(rectangle_bottomleft_position(rect));
}

/* --- Chunk cornes ---------------------------------------------------------- */

chunk_position_t rectangle_topleft_chunk(rectangle_t rect)
{
    return position_to_chunk_position(rectangle_topleft_position(rect));
}

chunk_position_t rectangle_topright_chunk(rectangle_t rect)
{
    return position_to_chunk_position(rectangle_topright_position(rect));
}

chunk_position_t rectangle_bottomleft_chunk(rectangle_t rect)
{
    return position_to_chunk_position(rectangle_bottomleft_position(rect));
}

chunk_position_t rectangle_bottomright_chunk(rectangle_t rect)
{
    return position_to_chunk_position(rectangle_bottomright_position(rect));
}
