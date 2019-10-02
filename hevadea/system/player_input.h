#pragma once

#include <raylib.h>
#include <hevadea/camera.h>
#include <hevadea/system/system.h>

#define PLAYER_MOVE_SPEED 3
#define PLAYER_RUN_SPEED 128

static void system_player_input_process(entity_t player, double deltatime)
{
    (void)deltatime;

    vector_t motion = (vector_t){0, 0};

    if (IsKeyDown(KEY_W))
        motion.Y -= 1;

    if (IsKeyDown(KEY_S))
        motion.Y += 1;

    if (IsKeyDown(KEY_A))
        motion.X -= 1;

    if (IsKeyDown(KEY_D))
        motion.X += 1;

    if (vector_lenght(motion) > 0.1)
    {
        motion = vector_normalized(motion);

        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            motion = vector_scale(motion, PLAYER_RUN_SPEED);
        }
        else
        {
            motion = vector_scale(motion, PLAYER_MOVE_SPEED);
        }
    }

    E(player)->motion = motion;
}

static system_t system_player_input = {
    .name = "player_input",
    .type = SYSTEM_PROCESS,
    .mask = COMPONENT_PLAYER,
    .process = system_player_input_process,
};