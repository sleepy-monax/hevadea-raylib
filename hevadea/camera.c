#include <raylib.h>
#include <math.h>
#include <hevadea/camera.h>

static position_t camera_position = {0};
static double camera_zoom = 1.0;

position_t camera_get_position(void)
{
    return camera_position;
}

void camera_set_position(position_t position)
{
    camera_position = position;
}

void camera_render_begin(void)
{
    Camera2D raylib_cam = {0};

    raylib_cam.zoom = camera_zoom;
    raylib_cam.target.x = camera_position.X;
    raylib_cam.target.y = camera_position.Y;
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
    DrawCircleV((Vector2){camera_position.X, camera_position.Y}, 1 / camera_zoom, WHITE);

    DrawRectangleLines(camera_load_bound().X, camera_load_bound().Y, camera_load_bound().W, camera_load_bound().H, WHITE);
    DrawRectangleLines(camera_unload_bound().X, camera_unload_bound().Y, camera_unload_bound().W, camera_unload_bound().H, RED);
}

void camera_move(void)
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
    camera_zoom = fmin(camera_zoom, 64.0);
}

rectangle_t camera_load_bound(void)
{
    rectangle_t bound;

    bound.X = camera_position.X - (CHUNK_LOAD_DISTANCE * CHUNK_SIZE);
    bound.Y = camera_position.Y - (CHUNK_LOAD_DISTANCE * CHUNK_SIZE);

    bound.W = 2 * (CHUNK_LOAD_DISTANCE * CHUNK_SIZE);
    bound.H = 2 * (CHUNK_LOAD_DISTANCE * CHUNK_SIZE);

    return bound;
}

rectangle_t camera_unload_bound(void)
{
    rectangle_t bound;

    bound.X = camera_position.X - (CHUNK_UNLOAD_DISTANCE * CHUNK_SIZE);
    bound.Y = camera_position.Y - (CHUNK_UNLOAD_DISTANCE * CHUNK_SIZE);

    bound.W = 2 * (CHUNK_UNLOAD_DISTANCE * CHUNK_SIZE);
    bound.H = 2 * (CHUNK_UNLOAD_DISTANCE * CHUNK_SIZE);

    return bound;
}