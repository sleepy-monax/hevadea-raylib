#pragma once

#include <hevadea/entity/entity.h>

void construct_rabbit_entity(entity_instance_t *instance)
{
    instance->components = COMPONENT_COLIDER | COMPONENT_MOTION;
    instance->colider = (rectangle_t){-4, -4, 8, 8};
}

const entity_blueprint_t entity_RABBIT = (entity_blueprint_t){
    .name = "rabbit",
    .construct = construct_rabbit_entity,
};