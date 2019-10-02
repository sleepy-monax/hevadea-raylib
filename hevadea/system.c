#include <stddef.h>
#include <raylib.h>

#include <hevadea/system.h>
#include <hevadea/camera.h>
#include <hevadea/logger.h>

#include <hevadea/system/debug_entity_colider.h>
#include <hevadea/system/debug_entity_motion.h>
#include <hevadea/system/entity_motion.h>
#include <hevadea/system/player_input.h>

static system_t *systems[] = {
    &system_player_input,

    &system_debug_entity_colider,
    &system_debug_entity_motion,

    &system_entity_motion,

    NULL,
};

typedef struct
{
    system_t *sys;
    double deltatime;
} system_process_callback_args_t;

iterate_state_t system_process_callback(entity_t entity, system_process_callback_args_t *args)
{
    bool is_entity_processable = entity_has_component(entity, args->sys->mask);

    if (is_entity_processable)
    {
        args->sys->process(entity, 1 / 60.0);
    }

    return ITERATION_CONTINUE;
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