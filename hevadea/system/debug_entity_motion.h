#pragma once

#include <raylib.h>
#include <hevadea/graphic.h>
#include <hevadea/system.h>

static void system_debug_entity_motion_process(entity_t entity, double deltatime)
{
    (void)deltatime;

    if (E(entity)->motion.X == 0 && E(entity)->motion.Y == 0)
    {
        return;
    }

    vector_t from = (vector_t){
        E(entity)->position.X,
        E(entity)->position.Y,
    };

    vector_t to = (vector_t){
        E(entity)->position.X + (E(entity)->motion.X),
        E(entity)->position.Y + (E(entity)->motion.Y),
    };

    graphic_draw_line(from, to, COLOR_MAGENTA);
}

static system_t system_debug_entity_motion = {
    .name = "debug_entity_motion",
    .type = SYSTEM_RENDER,
    .mask = COMPONENT_MOTION,
    .process = system_debug_entity_motion_process,
};