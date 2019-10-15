#pragma once

#include <hevadea/system/system.h>
#include <hevadea/camera.h>

static vector_t entity_motion_check(entity_instance_t *entity, vector_t motion, rectangle_t colide_bound)
{
    rectangle_t entity_bound = entity_get_bound(entity);
    entity_bound = rectangle_offset(entity_bound, vector_X(motion));

    if (rectangle_coliding(entity_bound, colide_bound))
    {
        motion.X = 0;
    }

    entity_bound = entity_get_bound(entity);
    entity_bound = rectangle_offset(entity_bound, vector_Y(motion));

    if (rectangle_coliding(entity_bound, colide_bound))
    {
        motion.Y = 0;
    }

    entity_bound = entity_get_bound(entity);
    entity_bound = rectangle_offset(entity_bound, motion);

    if (rectangle_coliding(entity_bound, colide_bound))
    {
        motion.X = 0;
        motion.Y = 0;
    }

    return motion;
}

static vector_t system_entity_motion_check_with_tile(entity_instance_t *entity, vector_t motion, tile_position_t pos)
{
    if (tile_has_component(pos, TILE_COMPONENT_SOLID))
    {
        motion = entity_motion_check(entity, motion, tile_get_bound(pos));
    }

    return motion;
}

static vector_t system_entity_motion_check_with_chunk(entity_instance_t *entity, vector_t motion, chunk_position_t pos)
{
    chunk_t *chunk = chunk_at(pos);

    if (chunk == NULL || chunk->state != CHUNK_STATE_LOADED)
    {
        motion = entity_motion_check(entity, motion, chunk_bound(pos));
    }

    return motion;
}

// static vector_t system_entity_motion_check_with_entity(entity_instance_t *entity, vector_t motion, entity_instance_t *other_entity)
// {
//     if (entity_has_component(other_entity, COMPONENT_COLIDER))
//     {
//         motion = entity_motion_check(entity, motion, entity_get_bound(other_entity));
//     }
//
//     return motion;
// }

static void system_entity_motion_process(entity_instance_t *entity, gametime_t gametime)
{
    vector_t motion = vector_scale(entity->motion, gametime.deltatime * UNIT_PER_TILE);

    if (vector_lenght(motion) > 0.01 && entity_has_component(entity, COMPONENT_COLIDER))
    {
        // check colision with unloaded chunks
        chunk_position_t chunk_pos = position_to_chunk_position(entity->position);
        for (int x = chunk_pos.X - 1; x <= chunk_pos.X + 1; x++)
        {
            for (int y = chunk_pos.Y - 1; y <= chunk_pos.Y + 1; y++)
            {
                motion = system_entity_motion_check_with_chunk(entity, motion, (chunk_position_t){x, y});
            }
        }

        // Check colision with tiles
        tile_position_t tile_pos = position_to_tile_position(entity->position);

        for (int x = tile_pos.X - 1; x <= tile_pos.X + 1; x++)
        {
            for (int y = tile_pos.Y - 1; y <= tile_pos.Y + 1; y++)
            {
                motion = system_entity_motion_check_with_tile(entity, motion, (tile_position_t){x, y});
            }
        }

        // Check colision with entities
    }

    entity->position.X += motion.X;
    entity->position.Y += motion.Y;

    if (entity_has_component(entity, COMPONENT_PLAYER))
    {
        camera_set_focus(entity->position);
    }
}

static system_t system_entity_motion = {
    .name = "entity_motion",
    .type = SYSTEM_PROCESS,
    .mask = COMPONENT_MOTION,
    .process = system_entity_motion_process,
};