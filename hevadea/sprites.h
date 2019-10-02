#pragma once

#include <hevadea/rectangle.h>

typedef struct
{
    int atlas;
    rectangle_t rect;
} sprite_t;

void sprites_load(void);