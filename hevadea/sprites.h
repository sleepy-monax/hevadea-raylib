#pragma once

#include <hevadea/rectangle.h>
#include <hevadea/color.h>

typedef struct
{
    double X;
    double Y;
    double Width;
    double Height;
} sprite_t;

void sprites_load(void);

void sprites_unload(void);

sprite_t sprites_by_name(const char *name);

void sprite_draw(sprite_t sprite, position_t position, color_t color);
