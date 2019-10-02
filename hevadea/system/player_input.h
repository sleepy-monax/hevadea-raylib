#pragma once

#include <raylib.h>
#include <hevadea/camera.h>
#include <hevadea/system.h>

#define PLAYER_MOVE_SPEED 2
#define PLAYER_RUN_SPEED 8

static void system_player_input_process(entity_t player, double deltatime)
{
    (void)deltatime;

    E(player)->motion = (vector_t){0, 0};

    double speed = PLAYER_MOVE_SPEED;

    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        speed = PLAYER_RUN_SPEED;
    }

    if (IsKeyDown(KEY_W))
    {
        E(player)->motion.Y -= speed;
    }
    if (IsKeyDown(KEY_S))
    {
        E(player)->motion.Y += speed;
    }
    if (IsKeyDown(KEY_A))
    {
        E(player)->motion.X -= speed;
    }
    if (IsKeyDown(KEY_D))
    {
        E(player)->motion.X += speed;
    }
}

static system_t system_player_input = {
    .name = "player_input",
    .type = SYSTEM_PROCESS,
    .mask = COMPONENT_PLAYER,
    .process = system_player_input_process,
};