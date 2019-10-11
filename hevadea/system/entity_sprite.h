#pragma once

#include <hevadea/system/system.h>
#include <hevadea/graphic.h>
#include <hevadea/sprite.h>

static void system_entity_sprite_process(entity_t entity, gametime_t gametime)
{
    (void)gametime;

    graphic_draw_sprite(E(entity)->sprite, vector_add(position_to_vector(E(entity)->position), vector_reverse(E(entity)->sprite_origine)), COLOR_WHITE);
}

static system_t system_entity_sprite = {
    .name = "entity_sprite",
    .type = SYSTEM_RENDER,
    .mask = COMPONENT_SPRITE,
    .process = system_entity_sprite_process,
};