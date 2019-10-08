#include <raylib.h>

#include <hevadea/graphic.h>

void graphic_draw_line(vector_t from, vector_t to, color_t color)
{
    DrawLineV(
        (Vector2){from.X, from.Y},
        (Vector2){to.X, to.Y},
        (Color){color.R, color.G, color.B, color.A});
}

void graphic_draw_rectangle(rectangle_t rect, color_t color)
{
    graphic_draw_line(rectangle_topleft(rect), rectangle_topright(rect), color);
    graphic_draw_line(rectangle_bottomleft(rect), rectangle_bottomright(rect), color);
    graphic_draw_line(rectangle_topleft(rect), rectangle_bottomleft(rect), color);
    graphic_draw_line(rectangle_topright(rect), rectangle_bottomright(rect), color);
}

void graphic_fill_rectangle(rectangle_t rect, color_t color)
{
    DrawRectangleV(
        (Vector2){rect.X, rect.Y},
        (Vector2){rect.Width, rect.Height},
        (Color){color.R, color.G, color.B, color.A});
}