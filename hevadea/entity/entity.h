#pragma once

#include <limits.h>

#include "hevadea/direction.h"
#include "hevadea/position.h"
#include "hevadea/rectangle.h"
#include "hevadea/sprite.h"
#include "hevadea/utils/Utils.h"
#include "hevadea/vector.h"

#define COMPONENT_PLAYER (1 << 0)
#define COMPONENT_MOTION (1 << 1)
#define COMPONENT_COLIDER (1 << 2)
#define COMPONENT_SPRITE (1 << 3)
#define COMPONENT_SPRITE_ANIMATED (1 << 4)
#define COMPONENT_PATHFINDING (1 << 5)
#define COMPONENT_WANDERING (1 << 6)
#define COMPONENT_SWIMMING (1 << 7)

typedef unsigned int entity_component_t;

struct entity_blueprint_t;

typedef struct
{
    int components;
    const struct entity_blueprint_t *blueprint;

    position_t position;
    vector_t motion;
    direction_t facing;
    rectangle_t colider;
    double lifetime;

    sprite_t sprite;
    vector_t sprite_origine;

    double wandering_timer;

    bool pathfinding_should_move;
    double pathfinding_move_speed;
    position_t pathfinding_destination;
} entity_instance_t;

typedef void (*entity_blueprint_create_callback_t)(entity_instance_t *instance);
typedef void (*entity_blueprint_destroy_callback_t)(entity_instance_t *instance);

typedef struct entity_blueprint_t
{
    const char *name;

    entity_blueprint_create_callback_t create;
    entity_blueprint_destroy_callback_t destroy;
} entity_blueprint_t;

/* --- Entity logistic ------------------------------------------------------ */

entity_instance_t *entity_create(const entity_blueprint_t *blueprint, position_t position);

void entity_destroy(entity_instance_t *entity);

const entity_blueprint_t *entity_blueprint(const char *name);

/* --- Entity iterators ----------------------------------------------------- */

typedef IterationDecision (*EntityIterateCallback)(entity_instance_t *entity, void *arg);

void entity_iterate_all(void *target, EntityIterateCallback callback);

/* --- Entity state --------------------------------------------------------- */

bool entity_has_component(entity_instance_t *entity, entity_component_t mask);

bool entity_is_moving(entity_instance_t *entity);

rectangle_t entity_get_bound(entity_instance_t *entity);

bool entity_colide_with(entity_instance_t *entity, rectangle_t bound);

chunk_position_t entity_get_chunk(entity_instance_t *entity);

bool entity_can_go_here(entity_instance_t *entity, tile_position_t pos);
