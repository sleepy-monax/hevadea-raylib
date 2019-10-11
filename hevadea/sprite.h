#pragma once

typedef struct
{
    const char *name;

    double X;
    double Y;
    double Width;
    double Height;
} sprite_t;

sprite_t sprite_subsprite(sprite_t sprite, int split_x, int split_y, int x, int y);