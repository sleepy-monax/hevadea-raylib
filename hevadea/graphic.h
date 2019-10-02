#pragma once

#include <hevadea/color.h>
#include <hevadea/rectangle.h>

void graphic_draw_line(vector_t from, vector_t to, color_t color);

void graphic_draw_rectangle(rectangle_t rect, color_t color);

void graphic_fill_rectangle(rectangle_t rect, color_t color);