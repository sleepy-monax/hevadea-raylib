#include <raylib.h>

#include <hevadea/graphic.h>
#include <hevadea/atlas.h>

// void graphic_context_create(int width, int height, int fps)
// {
// }
//
// void graphic_context_destroy(void)
// {
// }

static Color color_to_raylib(color_t color)
{
    return (Color){color.red, color.green, color.blue, color.alpha};
}

static Vector2 vector_to_raylib(vector_t vec)
{
    return (Vector2){vec.X, vec.Y};
}

static Rectangle rect_to_raylib(rectangle_t rect)
{
    return (Rectangle){rect.X, rect.Y, rect.Width, rect.Height};
}

static Texture2D texture_to_raylib(texture2d_t tex)
{
    return (Texture2D){tex.id, tex.width, tex.height, tex.mipmaps, tex.format};
}

void graphic_draw_line(vector_t from, vector_t to, color_t color)
{
    DrawLineV(vector_to_raylib(from), vector_to_raylib(to), color_to_raylib(color));
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
        color_to_raylib(color));
}

void graphic_draw_sprite(sprite_t sprite, vector_t position, color_t color)
{
    graphic_draw_texture(
        atlas_get_texture(),
        (rectangle_t){sprite.X, sprite.Y, sprite.Width, sprite.Height},
        (rectangle_t){position.X, position.Y, sprite.Width, sprite.Height},
        (vector_t){0, 0},
        0,
        color);
}

void graphic_draw_texture(texture2d_t texture, rectangle_t source_rect, rectangle_t dest_rect, vector_t origin, double rotation, color_t color)
{
    DrawTexturePro(
        texture_to_raylib(texture),
        rect_to_raylib(source_rect),
        rect_to_raylib(dest_rect),
        vector_to_raylib(origin),
        rotation,
        color_to_raylib(color));
}
