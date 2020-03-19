#pragma once

#include <math.h>
#include <stdlib.h>
#include "hevadea/system/system.h"
#include "hevadea/noise.h"
#include "hevadea/random.h"
#include "hevadea/tile/tile.h"

static void system_wandering_process(entity_instance_t *entity, gametime_t gametime)
{
    entity->wandering_timer -= gametime.deltatime;

    if (entity->wandering_timer < 0)
    {
        entity->wandering_timer = fabs(random_next_double()) * 3;

        vector_t wandering_position = vector_scale(random_next_vector(), 16 * 16);
        position_t destination = position_offset(entity->position, wandering_position);

        if (entity_can_go_here(entity, position_to_tile_position(destination)))
        {
            entity->pathfinding_destination = destination;
            entity->pathfinding_should_move = true;
        }
    }
}

static system_t system_wandering = {
    .name = "wandering",
    .type = SYSTEM_PROCESS,
    .mask = COMPONENT_WANDERING,
    .process = system_wandering_process,
};