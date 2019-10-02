#include <raylib.h>

#include <hevadea/camera.h>
#include <hevadea/chunk.h>
#include <hevadea/chunkloader.h>
#include <hevadea/system.h>
#include <hevadea/logger.h>
#include <hevadea/gui.h>

static const char *WINDOW_TITLE = "Hevadea";
static const int WINDOW_HEIGHT = 600;
static const int WINDOW_WIDTH = 800;
static const int WINDOW_FPS = 60;

void game_update(double deltatime)
{
    camera_update(deltatime);

    chunkloader_shedule();

    for (int i = 0; i < CHUNK_UPDATE; i++)
    {
        chunkloader_load_chunks();
        chunkloader_unload_chunks();
    }

    system_process(SYSTEM_PROCESS, deltatime);
}

void game_draw(double deltatime)
{
    BeginDrawing();
    ClearBackground(BLUE);

    camera_render_begin();
    {
        chunk_render_terrain();

        system_process(SYSTEM_RENDER, deltatime);

        chunks_debug_draw();

        camera_debug_draw();
    }
    camera_render_end();

    DrawFPS(16, 16);

    EndDrawing();
}

void game_loop(void)
{
    entity_create(entity_blueprint("player"), (position_t){16, 16});

    while (!WindowShouldClose())
    {
        double deltatime = GetFrameTime();

        game_update(deltatime);
        game_draw(deltatime);
    }
}

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    SetTargetFPS(WINDOW_FPS);

    game_loop();

    CloseWindow();
}