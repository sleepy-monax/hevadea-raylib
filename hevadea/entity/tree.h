#pragma once

#include <hevadea/entity/entity.h>

void construct_tree_entity(entity_instance_t *instance)
{
    instance->components = COMPONENT_COLIDER;
    instance->colider = (rectangle_t){-2, -2, 4, 4};
}

const entity_blueprint_t entity_TREE = (entity_blueprint_t){
    .name = "tree",
    .construct = construct_tree_entity,
};
