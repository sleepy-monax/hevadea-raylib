#pragma once

#include <hevadea/system/system.h>

static void system_pathfinding_process(entity_instance_t *entity, gametime_t gametime)
{
    (void)gametime;

    if (entity->pathfinding_should_move)
    {
        vector_t motion_vector = position_vector_to(entity->position, entity->pathfinding_destination);
        entity->motion = vector_scale(motion_vector, entity->pathfinding_move_speed);
        entity->facing = vector_to_direction(entity->motion);
    }
}

static system_t system_pathfinding = {
    .name = "pathfinding",
    .type = SYSTEM_PROCESS,
    .mask = COMPONENT_PATHFINDING,
    .process = system_pathfinding_process,
};