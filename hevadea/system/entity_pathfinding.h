#pragma once

#include <hevadea/system/system.h>

static void system_pathfinding_process(entity_t entity, gametime_t gametime)
{
    (void)gametime;

    if (E(entity)->pathfinding_should_move)
    {
        vector_t motion_vector = position_vector_to(E(entity)->position, E(entity)->pathfinding_destination);
        E(entity)->motion = vector_scale(motion_vector, E(entity)->pathfinding_move_speed);
        E(entity)->facing = vector_to_direction(E(entity)->motion);
    }
}

static system_t system_pathfinding = {
    .name = "pathfinding",
    .type = SYSTEM_PROCESS,
    .mask = COMPONENT_PATHFINDING,
    .process = system_pathfinding_process,
};