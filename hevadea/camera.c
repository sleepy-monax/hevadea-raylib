#include <math.h>
#include <stdlib.h>
#include <raylib.h>

#include <hevadea/logger.h>
#include <hevadea/camera.h>
#include <hevadea/graphic.h>

static position_t camera_position_animated = {0};
static position_t camera_position_focused = {0};

static double camera_zoom_animated = 4.0;
static double camera_zoom = 4.0;

position_t camera_get_position(void)
{
    return camera_position_animated;
}

void camera_set_focus(position_t position)
{
    camera_position_focused = position;
}

position_t camera_get_focus(void)
{
    return camera_position_focused;
}

void camera_render_begin(void)
{
    Camera2D raylib_cam = {0};

    if (IsKeyDown(KEY_SPACE))
    {
        raylib_cam.zoom = 1.0 / UNIT_PER_TILE;
    }
    else
    {
        raylib_cam.zoom = camera_zoom_animated;
    }
    raylib_cam.target.x = camera_position_animated.X;
    raylib_cam.target.y = camera_position_animated.Y;
    raylib_cam.offset.x = GetScreenWidth() / 2;
    raylib_cam.offset.y = GetScreenHeight() / 2;

    BeginMode2D(raylib_cam);
}

void camera_render_end(void)
{
    EndMode2D();
}

void camera_debug_draw(void)
{
    graphic_draw_rectangle(camera_load_bound(), COLOR_WHITE);
    graphic_draw_rectangle(camera_unload_bound(), COLOR_RED);
    graphic_draw_rectangle(camera_screen_bound(), COLOR_CYAN);

    graphic_draw_line((vector_t){-1000000, 0}, (vector_t){1000000, 0}, COLOR_RED);
    graphic_draw_line((vector_t){0, -1000000}, (vector_t){0, 1000000}, COLOR_GREEN);
}

void camera_update(double deltatime)
{
    if (IsKeyPressed(KEY_UP))
    {
        camera_zoom *= 2;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        camera_zoom /= 2;
    }

    camera_zoom = fmax(camera_zoom, 1.0);
    camera_zoom = fmin(camera_zoom, 1.0 * UNIT_PER_TILE);

    camera_position_animated = position_offset(camera_position_animated, vector_scale(position_sub(camera_position_focused, camera_position_animated), deltatime * camera_zoom_animated));

    camera_zoom_animated += 4 * (camera_zoom - camera_zoom_animated) * deltatime;
}

rectangle_t camera_load_bound(void)
{
    rectangle_t bound;

    bound.X = camera_position_focused.X - (CHUNK_LOAD_DISTANCE * UNIT_PER_CHUNK);
    bound.Y = camera_position_focused.Y - (CHUNK_LOAD_DISTANCE * UNIT_PER_CHUNK);

    bound.Width = 2 * (CHUNK_LOAD_DISTANCE * UNIT_PER_CHUNK);
    bound.Height = 2 * (CHUNK_LOAD_DISTANCE * UNIT_PER_CHUNK);

    return bound;
}

rectangle_t camera_unload_bound(void)
{
    rectangle_t bound;

    bound.X = camera_position_focused.X - (CHUNK_UNLOAD_DISTANCE * UNIT_PER_CHUNK);
    bound.Y = camera_position_focused.Y - (CHUNK_UNLOAD_DISTANCE * UNIT_PER_CHUNK);

    bound.Width = 2 * (CHUNK_UNLOAD_DISTANCE * UNIT_PER_CHUNK);
    bound.Height = 2 * (CHUNK_UNLOAD_DISTANCE * UNIT_PER_CHUNK);

    return bound;
}

rectangle_t camera_screen_bound(void)
{
    rectangle_t bound;

    bound.X = camera_position_animated.X - ((GetScreenWidth() / 2) / camera_zoom_animated);
    bound.Y = camera_position_animated.Y - ((GetScreenHeight() / 2) / camera_zoom_animated);

    bound.Width = GetScreenWidth() / camera_zoom_animated;
    bound.Height = GetScreenHeight() / camera_zoom_animated;

    return bound;
}

void camera_interate_on_screen_chunk(chunk_iterate_callback_t callback, void *arg)
{
    chunk_position_t start_pos = rectangle_topleft_chunk(camera_screen_bound());
    chunk_position_t end_pos = rectangle_bottomright_chunk(camera_screen_bound());

    for (int cx = start_pos.X; cx <= end_pos.X; cx++)
    {
        for (int cy = start_pos.Y; cy <= end_pos.Y; cy++)
        {
            chunk_position_t pos = (chunk_position_t){cx, cy};

            chunk_t *chunk = chunk_at(pos);

            if (chunk != NULL)
            {
                if (callback(chunk, arg) == ITERATION_STOP)
                {
                    return;
                }
            }
        }
    }
}