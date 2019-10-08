#pragma once

#include <hevadea/system/system.h>
#include <hevadea/sprites.h>

static void system_entity_sprite_process(entity_t entity, gametime_t gametime)
{
    (void)gametime;

    sprite_draw(E(entity)->sprite, position_offset(E(entity)->position, vector_reverse(E(entity)->sprite_origine)), COLOR_WHITE);
}

static system_t system_entity_sprite = {
    .name = "entity_sprite",
    .type = SYSTEM_RENDER,
    .mask = COMPONENT_SPRITE,
    .process = system_entity_sprite_process,
};