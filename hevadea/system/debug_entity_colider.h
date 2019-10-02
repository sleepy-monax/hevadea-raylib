#pragma once

#include <hevadea/camera.h>
#include <hevadea/system.h>
#include <hevadea/graphic.h>
#include <hevadea/tile.h>

static void system_debug_entity_colider_process(entity_t entity, double deltatime)
{
    (void)deltatime;

    tile_position_t entity_pos = position_to_tile_position(E(entity)->position);

    for (int x = entity_pos.X - 1; x <= entity_pos.X + 1; x++)
    {
        for (int y = entity_pos.Y - 1; y <= entity_pos.Y + 1; y++)
        {
            if (tile_has_component(tile_at((tile_position_t){x, y}), TILE_COMPONENT_SOLID))
            {
                graphic_draw_rectangle(tile_bound((tile_position_t){x, y}), COLOR_BLACK);
            }
        }
    }

    rectangle_t entity_bound = entity_get_bound(entity);
    graphic_draw_rectangle(entity_bound, COLOR_YELLOW);
}

static system_t system_debug_entity_colider = {
    .name = "debug_entity_colider",
    .type = SYSTEM_RENDER,
    .mask = COMPONENT_COLIDER,
    .process = system_debug_entity_colider_process,
};