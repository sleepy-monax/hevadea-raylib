#pragma once

#include <hevadea/entity/entity.h>
#include <hevadea/atlas.h>

void grass_medium_entity_create(entity_instance_t *instance)
{
    instance->components = COMPONENT_SPRITE;
    instance->colider = (rectangle_t){-2, -2, 4, 4};
    instance->sprite = atlas_sprite_by_name("entity/weath1");
    instance->sprite_origine = (vector_t){8, 10};
}

const entity_blueprint_t ENTITY_GRASS_MEDIUM = (entity_blueprint_t){
    .name = "grass_medium",
    .create = grass_medium_entity_create,
};
