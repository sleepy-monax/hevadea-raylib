#pragma once

#include <math.h>
#include <stdlib.h>
#include <hevadea/system/system.h>
#include <hevadea/noise.h>
#include <hevadea/random.h>

static void system_wandering_process(entity_t entity, gametime_t gametime)
{
    E(entity)->wandering_timer -= gametime.deltatime;

    if (E(entity)->wandering_timer < 0)
    {
        E(entity)->wandering_timer = fabs(random_next_double()) * 3;

        vector_t wandering_position = vector_scale(random_next_vector(), 16 * 16);

        E(entity)->pathfinding_destination = position_offset(E(entity)->position, wandering_position);
        E(entity)->pathfinding_should_move = true;
    }
}

static system_t system_wandering = {
    .name = "wandering",
    .type = SYSTEM_PROCESS,
    .mask = COMPONENT_WANDERING,
    .process = system_wandering_process,
};