#pragma once

#include <hevadea/entity/entity.h>

void rabbit_entity_create(entity_instance_t *instance)
{
    instance->components = COMPONENT_COLIDER | COMPONENT_MOTION;
    instance->colider = (rectangle_t){-4, -4, 8, 8};
}

const entity_blueprint_t ENTITY_RABBIT = (entity_blueprint_t){
    .name = "rabbit",
    .create = rabbit_entity_create,
};