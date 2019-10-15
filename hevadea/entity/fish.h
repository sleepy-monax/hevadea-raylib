#pragma once

#include <hevadea/entity/entity.h>
#include <hevadea/atlas.h>

void fish_entity_create(entity_instance_t *instance)
{
    instance->components = COMPONENT_COLIDER | COMPONENT_MOTION | COMPONENT_COLIDER | COMPONENT_WANDERING | COMPONENT_PATHFINDING | COMPONENT_SPRITE | COMPONENT_SWIMMING;

    instance->colider = (rectangle_t){-4, -4, 8, 8};

    instance->sprite = atlas_sprite_by_name("entity/fish");
    instance->sprite_origine = (vector_t){8, 12};
    instance->pathfinding_move_speed = 1;
}

const entity_blueprint_t ENTITY_FISH = (entity_blueprint_t){
    .name = "fish",
    .create = fish_entity_create,
};