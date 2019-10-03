#pragma once

#include <hevadea/rectangle.h>

typedef struct
{
    const char *name;
    rectangle_t rect;
} sprite_t;

void sprites_load(void);
void sprites_unload(void);