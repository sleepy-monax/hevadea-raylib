#pragma once

#include <hevadea/entity/entity.h>

void player_entity_create(entity_instance_t *instance)
{
    instance->components = COMPONENT_PLAYER | COMPONENT_MOTION | COMPONENT_COLIDER;
    instance->colider = (rectangle_t){-4, -4, 8, 8};
}

const entity_blueprint_t ENTITY_PLAYER = (entity_blueprint_t){
    .name = "player",
    .create = player_entity_create,
};