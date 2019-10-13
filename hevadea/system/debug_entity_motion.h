#pragma once

#include <raylib.h>

#include <hevadea/system/system.h>
#include <hevadea/graphic.h>

static void system_debug_entity_motion_process(entity_instance_t *entity, gametime_t gametime)
{
    (void)gametime;

    if (entity_is_moving(entity))
    {
        vector_t from = position_to_vector(entity->position);
        vector_t to = vector_add(from, entity->motion);

        graphic_draw_line(from, to, COLOR_MAGENTA);
    }
}

static system_t system_debug_entity_motion = {
    .name = "debug_entity_motion",
    .type = SYSTEM_OVERLAY,
    .mask = COMPONENT_MOTION,
    .process = system_debug_entity_motion_process,
};