#pragma once

#include <hevadea/system/system.h>
#include <hevadea/camera.h>

static vector_t system_entity_motion_check_with_tile(entity_t entity, vector_t motion, tile_position_t pos)
{
    tile_instance_t *tile = tile_at(pos);

    if (tile != NULL && tile_has_component(tile, TILE_COMPONENT_SOLID))
    {
        position_t tile_pos = tile_position_to_position(pos);

        rectangle_t tile_bound = (rectangle_t){tile_pos.X, tile_pos.Y, UNIT_PER_TILE, UNIT_PER_TILE};

        // Test x offset
        rectangle_t entity_bound = entity_get_bound(entity);
        entity_bound = rectangle_offset(entity_bound, vector_X(motion));

        if (rectangle_coliding(entity_bound, tile_bound))
        {
            motion.X = 0;
        }

        // Test y offset
        entity_bound = entity_get_bound(entity);
        entity_bound = rectangle_offset(entity_bound, vector_Y(motion));

        if (rectangle_coliding(entity_bound, tile_bound))
        {
            motion.Y = 0;
        }

        // Test x, y offset
        entity_bound = entity_get_bound(entity);
        entity_bound = rectangle_offset(entity_bound, motion);

        if (rectangle_coliding(entity_bound, tile_bound))
        {
            motion.X = 0;
            motion.Y = 0;
        }
    }

    return motion;
}

static void system_entity_motion_process(entity_t entity, double deltatime)
{
    vector_t motion = vector_scale(E(entity)->motion, deltatime * UNIT_PER_TILE);

    if (entity_has_component(entity, COMPONENT_COLIDER))
    {
        tile_position_t entity_pos = position_to_tile_position(E(entity)->position);

        for (int x = entity_pos.X - 1; x <= entity_pos.X + 1; x++)
        {
            for (int y = entity_pos.Y - 1; y <= entity_pos.Y + 1; y++)
            {
                motion = system_entity_motion_check_with_tile(entity, motion, (tile_position_t){x, y});
            }
        }
    }

    E(entity)->position.X += motion.X;
    E(entity)->position.Y += motion.Y;

    if (entity_has_component(entity, COMPONENT_PLAYER))
    {
        camera_set_focus(E(entity)->position);
    }
}

static system_t system_entity_motion = {
    .name = "entity_motion",
    .type = SYSTEM_PROCESS,
    .mask = COMPONENT_MOTION,
    .process = system_entity_motion_process,
};