#pragma once

#include <hevadea/system/system.h>
#include <hevadea/sprite.h>

static const int FRAMES[] = {0, 2, 1, 2};

static void system_entity_sprite_animated_process(entity_instance_t *entity, gametime_t gametime)
{
    (void)gametime;

    int frame = 2;

    if (entity_is_moving(entity))
    {
        frame = FRAMES[(int)(4 * gametime.totaltime) % 4];
    }
    sprite_t current_sprite = sprite_subsprite(entity->sprite, 3, 4, frame, entity->facing);

    graphic_draw_sprite(
        current_sprite,
        vector_add(position_to_vector(entity->position), vector_reverse(entity->sprite_origine)),
        COLOR_WHITE);
}

static system_t system_entity_sprite_animated = {
    .name = "entity_sprite_animated",
    .type = SYSTEM_RENDER,
    .mask = COMPONENT_SPRITE_ANIMATED,
    .process = system_entity_sprite_animated_process,
};