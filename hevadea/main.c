#include <raylib.h>

#include <hevadea/camera.h>
#include <hevadea/chunk.h>
#include <hevadea/chunkloader.h>

static const char *WINDOW_TITLE = "Hevadea";
static const int WINDOW_HEIGHT = 600;
static const int WINDOW_WIDTH = 800;
static const int WINDOW_FPS = 60;

static int tick = 0;

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    SetTargetFPS(WINDOW_FPS);

    while (!WindowShouldClose())
    {
        tick++;

        // Update

        camera_move();

        chunkloader_shedule();

        for (int i = 0; i < CHUNK_UPDATE; i++)
        {
            chunkloader_load_chunks();
            chunkloader_unload_chunks();
        }

        // Draw

        BeginDrawing();
        ClearBackground(BLACK);

        camera_render_begin();
        {
            chunk_render_terrain();

            chunks_debug_draw();

            camera_debug_draw();
        }
        camera_render_end();

        DrawFPS(16, 16);

        EndDrawing();
    }

    CloseWindow();
}