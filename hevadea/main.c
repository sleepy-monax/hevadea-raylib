#include <raylib.h>
#include <math.h>

#include <hevadea/camera.h>
#include <hevadea/atlas.h>
#include <hevadea/chunk.h>
#include <hevadea/chunkloader.h>
#include <hevadea/system/system.h>
#include <hevadea/logger.h>

// #include <hevadea/biome/biome.h>

static const char *WINDOW_TITLE = "Hevadea";
static const int WINDOW_HEIGHT = 600;
static const int WINDOW_WIDTH = 800;
static const int WINDOW_FPS = 60;

void game_update(gametime_t gametime)
{
    camera_update(gametime);

    chunkloader_shedule();

    for (int i = 0; i < CHUNK_UPDATE; i++)
    {
        chunkloader_load_chunks();
        chunkloader_unload_chunks();
    }

    system_process(SYSTEM_PROCESS, gametime);
}

void game_draw(gametime_t gametime)
{
    BeginDrawing();
    ClearBackground(BLUE);

    camera_render_begin();
    {
        chunk_render_terrain();

        system_process(SYSTEM_RENDER, gametime);

        if (IsKeyDown(KEY_F3))
        {
            system_process(SYSTEM_OVERLAY, gametime);
            chunks_debug_draw();
            camera_debug_draw();
        }
    }
    camera_render_end();

    // for (int x = -100; x <= 100; x++)
    // {
    //     for (int y = -100; y <= 100; y++)
    //     {
    //         color_t c = biome_lookup(x / 100.0, y / 100.0, sin(GetTime()))->tile->color;
    //         DrawRectangle(GetScreenWidth() / 2 + x, GetScreenHeight() / 2 + y, 1, 1, (Color){c.R, c.G, c.B, 255});
    //     }
    // }

    DrawFPS(16, 16);

    EndDrawing();
}

void game_loop(void)
{
    entity_create(entity_blueprint("player"), (position_t){16, 16});

    while (!WindowShouldClose())
    {
        gametime_t gametime = {
            .totaltime = GetTime(),
            .deltatime = GetFrameTime(),
        };

        game_update(gametime);
        game_draw(gametime);
    }
}

int main(void)
{
    log_info("Intializing raylib...");
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    atlas_load();

    SetTargetFPS(WINDOW_FPS);

    log_info("Entering gameloop...");
    game_loop();

    atlas_unload();
    
    log_info("Closing window...");
    CloseWindow();


    log_info("Goodbye");
}