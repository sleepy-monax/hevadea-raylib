#pragma once

#include <hevadea/entity/entity.h>
#include <hevadea/atlas.h>

void grass_small_entity_create(entity_instance_t *instance)
{
    instance->components = COMPONENT_SPRITE;
    instance->colider = (rectangle_t){-2, -2, 4, 4};
    instance->sprite = atlas_sprite_by_name("entity/weath0");
    instance->sprite_origine = (vector_t){8, 8};
}

const entity_blueprint_t ENTITY_GRASS_SMALL = (entity_blueprint_t){
    .name = "grass_small",
    .create = grass_small_entity_create,
};
