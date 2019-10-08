#pragma once

#include <hevadea/system/system.h>
#include <hevadea/sprites.h>

static void system_entity_sprite_animated_process(entity_t entity, double deltatime)
{
    (void)deltatime;

    sprite_t current_sprite = sprite_subsprite(E(entity)->sprite, 3, 4, 2, E(entity)->facing);

    sprite_draw(current_sprite, position_offset(E(entity)->position, vector_reverse(E(entity)->sprite_origine)), COLOR_WHITE);
}

static system_t system_entity_sprite_animated = {
    .name = "entity_sprite_animated",
    .type = SYSTEM_RENDER,
    .mask = COMPONENT_SPRITE_ANIMATED,
    .process = system_entity_sprite_animated_process,
};