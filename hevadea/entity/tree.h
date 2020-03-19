#pragma once

#include "hevadea/entity/entity.h"
#include "hevadea/atlas.h"

void tree_entity_create(entity_instance_t *instance)
{
    instance->components = COMPONENT_COLIDER | COMPONENT_SPRITE;
    instance->colider = (rectangle_t){-2, -2, 4, 4};
    instance->sprite = atlas_sprite_by_name("entity/tree3");
    instance->sprite_origine = (vector_t){16, 70};
}

const entity_blueprint_t ENTITY_TREE = (entity_blueprint_t){
    .name = "tree",
    .create = tree_entity_create,
};
