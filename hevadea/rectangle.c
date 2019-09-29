#include <hevadea/rectangle.h>

bool rectangle_contain_position(rectangle_t rect, position_t pos)
{
    return (rect.X <= pos.X) &&
           (rect.X + rect.W > pos.X) &&
           (rect.Y <= pos.Y) &&
           (rect.Y + rect.H > pos.Y);
}

bool rectangle_contain_tile_position(rectangle_t rect, tile_position_t pos)
{
    return rectangle_contain_position(rect, tile_position_to_position(pos));
}

bool rectangle_contain_chunk_position(rectangle_t rect, chunk_position_t pos)
{
    return rectangle_contain_position(rect, chunk_position_to_position(pos));
}