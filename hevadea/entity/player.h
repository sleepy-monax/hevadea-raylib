#pragma once

#include <hevadea/entity/entity.h>

void construct_player_entity(entity_instance_t *instance)
{
    instance->components = COMPONENT_PLAYER | COMPONENT_MOTION;
    //| COMPONENT_COLIDER;
    instance->colider = (rectangle_t){-4, -4, 8, 8};
}

const entity_blueprint_t entity_PLAYER = (entity_blueprint_t){
    .name = "player",
    .construct = construct_player_entity,
};