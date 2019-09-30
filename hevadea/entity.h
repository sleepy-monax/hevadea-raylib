#pragma once

#include <hevadea/component.h>
#include <hevadea/position.h>
#include <hevadea/utils.h>

typedef struct
{
    const char *name;
    component_t components;
} entity_blueprint_t;

typedef struct
{
    bool allocated;

    position_t position;

    const entity_blueprint_t *blueprint;
} entity_instance_t;

typedef unsigned int entity_t;

entity_t entity_create(const entity_blueprint_t *blueprint, position_t position);

void entity_destroy(entity_t entity);

#define E(__entity) entity_instance(__entity)

entity_instance_t *entity_instance(entity_t entity);

typedef iterate_state_t (*entity_iterate_callback_t)(entity_t entity, void *arg);

void entity_iterate_all(entity_iterate_callback_t callback, void *arg);

const entity_blueprint_t *entity_blueprint(const char *name);
