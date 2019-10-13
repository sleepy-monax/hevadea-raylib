#pragma once

#include <hevadea/entity/entity.h>
#include <hevadea/atlas.h>

void player_entity_create(entity_instance_t *instance)
{
    instance->components = COMPONENT_PLAYER | COMPONENT_COLIDER | COMPONENT_MOTION | COMPONENT_SPRITE_ANIMATED;
    instance->colider = (rectangle_t){-4, -4, 8, 8};

    instance->sprite = atlas_sprite_by_name("entity/player");
    instance->sprite_origine = (vector_t){8, 24};
}

const entity_blueprint_t ENTITY_PLAYER = (entity_blueprint_t){
    .name = "player",
    .create = player_entity_create,
};
