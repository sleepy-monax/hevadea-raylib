#pragma once

#include <hevadea/entity/entity.h>

void flower_entity_create(entity_instance_t *instance)
{
    instance->components = COMPONENT_SPRITE;
    instance->colider = (rectangle_t){-2, -2, 4, 4};
    instance->sprite = sprites_by_name("entity/flower0");
    instance->sprite_origine = (vector_t){8, 8};
}

const entity_blueprint_t ENTITY_FLOWER = (entity_blueprint_t){
    .name = "flower",
    .create = flower_entity_create,
};
