#pragma once

#include <hevadea/position.h>
#include <hevadea/vector.h>

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

bool rectangle_coliding(rectangle_t a, rectangle_t b);

rectangle_t rectangle_offset(rectangle_t rect, vector_t vec);

vector_t rectangle_topleft(rectangle_t rect);

vector_t rectangle_topright(rectangle_t rect);

vector_t rectangle_bottomleft(rectangle_t rect);

vector_t rectangle_bottomright(rectangle_t rect);

position_t rectangle_topleft_position(rectangle_t rect);

position_t rectangle_topright_position(rectangle_t rect);

position_t rectangle_bottomleft_position(rectangle_t rect);

position_t rectangle_bottomright_position(rectangle_t rect);

tile_position_t rectangle_topleft_tile(rectangle_t rect);

tile_position_t rectangle_topright_tile(rectangle_t rect);

tile_position_t rectangle_bottomleft_tile(rectangle_t rect);

tile_position_t rectangle_bottomright_tile(rectangle_t rect);

chunk_position_t rectangle_topleft_chunk(rectangle_t rect);

chunk_position_t rectangle_topright_chunk(rectangle_t rect);

chunk_position_t rectangle_bottomleft_chunk(rectangle_t rect);

chunk_position_t rectangle_bottomright_chunk(rectangle_t rect);
