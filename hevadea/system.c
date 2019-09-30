#include <stddef.h>
#include <raylib.h>

#include <hevadea/system.h>
#include <hevadea/camera.h>
#include <hevadea/logger.h>

#define PLAYER_MOVE_SPEED 2

static void system_player_input_process(entity_t player, double deltatime)
{
    if (IsKeyDown(KEY_W))
    {
        E(player)->position.Y -= PLAYER_MOVE_SPEED * deltatime;
    }
    if (IsKeyDown(KEY_S))
    {
        E(player)->position.Y += PLAYER_MOVE_SPEED * deltatime;
    }
    if (IsKeyDown(KEY_A))
    {
        E(player)->position.X -= PLAYER_MOVE_SPEED * deltatime;
    }
    if (IsKeyDown(KEY_D))
    {
        E(player)->position.X += PLAYER_MOVE_SPEED * deltatime;
    }

    camera_set_position(E(player)->position);
}

static system_t system_player_input = {
    .name = "player_input",
    .type = SYSTEM_PROCESS,
    .mask = COMPONENT_PLAYER,
    .process = system_player_input_process,
};

static system_t *systems[] = {
    &system_player_input,
    NULL,
};

typedef struct
{
    system_t *sys;
    double deltatime;
} system_process_callback_args_t;

iterate_state_t system_process_callback(entity_t entity, system_process_callback_args_t *args)
{
    bool is_entity_processable = (E(entity)->blueprint->components & args->sys->mask) == args->sys->mask;

    if (is_entity_processable)
    {
        args->sys->process(entity, 1 / 60.0);
    }

    return SEARCH_CONTINUE;
}

void system_process(system_type_t type, double deltatime)
{

    for (int i = 0; systems[i]; i++)
    {
        if (systems[i]->type == type)
        {
            system_process_callback_args_t args;

            args.sys = systems[i];
            args.deltatime = deltatime;

            entity_iterate_all((entity_iterate_callback_t)system_process_callback, &args);
        }
    }
}