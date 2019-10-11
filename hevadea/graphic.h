#pragma once

#include <hevadea/color.h>
#include <hevadea/rectangle.h>
#include <hevadea/sprite.h>
#include <hevadea/texture2d.h>
#include <hevadea/vector.h>

void graphic_draw_line(vector_t from, vector_t to, color_t color);

void graphic_draw_rectangle(rectangle_t rect, color_t color);

void graphic_fill_rectangle(rectangle_t rect, color_t color);

void graphic_draw_sprite(sprite_t sprite, vector_t position, color_t color);

void graphic_draw_texture(
    texture2d_t texture,
    rectangle_t source_rect,
    rectangle_t dest_rect,
    vector_t origin,
    double rotation,
    color_t tint);
