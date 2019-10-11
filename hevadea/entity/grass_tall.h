#pragma once

#include <hevadea/entity/entity.h>
#include <hevadea/atlas.h>

void grass_tall_entity_create(entity_instance_t *instance)
{
    instance->components = COMPONENT_SPRITE;
    instance->colider = (rectangle_t){-2, -2, 4, 4};
    instance->sprite = atlas_sprite_by_name("entity/weath2");
    instance->sprite_origine = (vector_t){8, 8};
}

const entity_blueprint_t ENTITY_GRASS_TALL = (entity_blueprint_t){
    .name = "grass_tall",
    .create = grass_tall_entity_create,
};
