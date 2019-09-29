#pragma once

#include <hevadea/position.h>

typedef struct
{
    double X;
    double Y;
    double W;
    double H;
} rectangle_t;

bool rectangle_contain_position(rectangle_t rect, position_t pos);

bool rectangle_contain_tile_position(rectangle_t rect, tile_position_t pos);

bool rectangle_contain_chunk_position(rectangle_t rect, chunk_position_t pos);