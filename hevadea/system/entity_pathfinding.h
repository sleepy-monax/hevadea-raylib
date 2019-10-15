#pragma once

#include <hevadea/system/system.h>

static void system_pathfinding_process(entity_instance_t *entity, gametime_t gametime)
{
    (void)gametime;
    if (entity->pathfinding_should_move)
    {
        if (position_distance(entity->position, entity->pathfinding_destination) < UNIT_PER_TILE / 4)
        {
            entity->motion = (vector_t){0, 0};
            entity->pathfinding_should_move = false;
        }
        else
        {
            tile_position_t entity_pos = position_to_tile_position(entity->position);
            tile_position_t best_pos = entity_pos;
            double best_dist = position_distance(tile_position_to_position_centered(entity_pos), entity->pathfinding_destination);

            for (int x = entity_pos.X - 1; x <= entity_pos.X + 1; x++)
            {
                for (int y = entity_pos.Y - 1; y <= entity_pos.Y + 1; y++)
                {
                    tile_position_t current_pos = (tile_position_t){x, y};

                    if (entity_can_go_here(entity, current_pos))
                    {
                        double current_dist = position_distance(tile_position_to_position_centered(current_pos), entity->pathfinding_destination);

                        if (current_dist < best_dist)
                        {
                            best_dist = current_dist;
                            best_pos = current_pos;
                        }
                    }
                }
            }

            if (!any_position_equal(entity_pos, best_pos))
            {
                vector_t motion_vector = position_vector_to(entity->position, tile_position_to_position_centered(best_pos));

                entity->motion = vector_scale(motion_vector, entity->pathfinding_move_speed);
                entity->facing = vector_to_direction(entity->motion);
            }
            else
            {
                entity->motion = (vector_t){0, 0};
                entity->pathfinding_should_move = false;
            }
        }
    }
}

static system_t system_pathfinding = {
    .name = "pathfinding",
    .type = SYSTEM_PROCESS,
    .mask = COMPONENT_PATHFINDING,
    .process = system_pathfinding_process,
};