#pragma once

#include <limits.h>

#include "hevadea/position.h"
#include "hevadea/utils.h"
#include "hevadea/vector.h"
#include "hevadea/rectangle.h"
#include "hevadea/sprite.h"
#include "hevadea/direction.h"

typedef enum
{
    COMPONENT_PLAYER = 1 << 0,
    COMPONENT_MOTION = 1 << 1,
    COMPONENT_COLIDER = 1 << 2,
    COMPONENT_SPRITE = 1 << 3,
    COMPONENT_SPRITE_ANIMATED = 1 << 4,
    COMPONENT_PATHFINDING = 1 << 5,
    COMPONENT_WANDERING = 1 << 6,
    COMPONENT_SWIMMING = 1 << 7,

    __COMPONENT_COUNT,
} entity_component_t;

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

void entity_destroy(entity_instance_t *this);

const entity_blueprint_t *entity_blueprint(const char *name);

/* --- Entity iterators ----------------------------------------------------- */

typedef iterate_state_t (*entity_iterate_callback_t)(entity_instance_t *entity, void *arg);

void entity_iterate_all(entity_iterate_callback_t callback, void *args);

/* --- Entity state --------------------------------------------------------- */

bool entity_has_component(entity_instance_t *this, entity_component_t mask);

bool entity_is_moving(entity_instance_t *this);

rectangle_t entity_get_bound(entity_instance_t *this);

bool entity_colide_with(entity_instance_t *this, rectangle_t bound);

chunk_position_t entity_get_chunk(entity_instance_t *this);

bool entity_can_go_here(entity_instance_t *entity, tile_position_t pos);
