#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <hevadea/entity/entity.h>
#include <hevadea/system/system.h>
#include <hevadea/logger.h>

#include <hevadea/entity/player.h>
#include <hevadea/entity/rabbit.h>
#include <hevadea/entity/tree.h>
#include <hevadea/entity/grass_small.h>
#include <hevadea/entity/grass_medium.h>
#include <hevadea/entity/grass_tall.h>
#include <hevadea/entity/flower.h>

const entity_blueprint_t *blueprints[] = {
    &ENTITY_PLAYER,
    &ENTITY_TREE,
    &ENTITY_RABBIT,
    &ENTITY_FLOWER,
    &ENTITY_GRASS_SMALL,
    &ENTITY_GRASS_MEDIUM,
    &ENTITY_GRASS_TALL,

    NULL,
};

static entity_instance_t *entity_instances = NULL;

static size_t entity_instances_allocated = 0;
static size_t entity_instances_used = 0;

void entity_instances_grow(void)
{
    if (entity_instances_allocated == 0)
    {
        entity_instances_allocated = 128;
        entity_instances = calloc(entity_instances_allocated, sizeof(entity_instance_t));
    }
    else
    {
        size_t new_allocated = entity_instances_allocated * 2;
        entity_instances = realloc(entity_instances, new_allocated * sizeof(entity_instance_t));

        log_info("Expended the entity instance array from %d to %d at %08x", entity_instances_allocated, new_allocated, entity_instances);

        for (size_t i = entity_instances_allocated + 1; i < new_allocated; i++)
        {
            entity_instances[i].allocated = false;
        }

        entity_instances_allocated = new_allocated;
    }
}

const entity_blueprint_t *entity_blueprint(const char *name)
{
    for (int i = 0; blueprints[i]; i++)
    {
        if (strcmp(blueprints[i]->name, name) == 0)
        {
            return blueprints[i];
        }
    }

    PANIC("Invalid blueprint name!");
}

entity_t entity_create(const entity_blueprint_t *blueprint, position_t position)
{
    if (entity_instances_used + 1 == entity_instances_allocated ||
        entity_instances_allocated == 0)
    {
        entity_instances_grow();
    }

    for (size_t i = 0; i < entity_instances_allocated; i++)
    {
        entity_instance_t *instance = &entity_instances[i];

        if (!instance->allocated)
        {
            entity_instances_used++;
            memset(instance, 0, sizeof(entity_iterate_callback_t));

            instance->allocated = true;
            instance->blueprint = blueprint;
            instance->position = position;
            instance->facing = DIRECTION_SOUTH;

            if (blueprint->create)
            {
                blueprint->create(instance);
            }
            else
            {
                log_warn("No construct for entity %s", blueprint->name);
            }

            return i;
        }
    }

    log_fatal("Failled to allocated entity %d/%d", entity_instances_allocated, entity_instances_allocated);
    PANIC("Failled to allocate entity!");
}

void entity_destroy(entity_t entity)
{
    assert(entity_instances[entity].allocated);

    const entity_blueprint_t *blueprint = entity_instances[entity].blueprint;

    if (blueprint->destroy)
    {
        blueprint->destroy(&entity_instances[entity]);
    }

    entity_instances[entity].allocated = false;
    entity_instances_used--;
}

entity_instance_t *entity_instance(entity_t entity)
{
    if (entity >= entity_instances_allocated)
        PANIC("Invalid entity handle!");

    entity_instance_t *instance = &entity_instances[entity];

    assert(instance->allocated);

    return instance;
}

/* --- Entity iterator ----------------------------------------------------- */

void entity_iterate_all(entity_iterate_callback_t callback, void *arg)
{
    for (unsigned int i = 0; i < entity_instances_allocated; i++)
    {
        if (entity_instances[i].allocated == true)
        {
            if (callback(i, arg) == ITERATION_STOP)
            {
                return;
            }
        }
    }
}

/* --- Entity state --------------------------------------------------------- */

bool entity_has_component(entity_t entity, entity_component_t mask)
{
    return (E(entity)->components & mask) == mask;
}

bool entity_is_moving(entity_t entity)
{
    return E(entity)->motion.X != 0 || E(entity)->motion.Y != 0;
}

rectangle_t entity_get_bound(entity_t entity)
{
    if (entity_has_component(entity, COMPONENT_COLIDER))
    {
        return (rectangle_t){
            E(entity)->position.X + E(entity)->colider.X,
            E(entity)->position.Y + E(entity)->colider.Y,
            E(entity)->colider.Width,
            E(entity)->colider.Height,
        };
    }
    else
    {
        return (rectangle_t){E(entity)->position.X, E(entity)->position.Y, 1, 1};
    }
}

bool entity_colide_with(entity_t entity, rectangle_t bound)
{
    rectangle_t a = entity_get_bound(entity);
    rectangle_t b = bound;

    return a.X < b.X + b.Width &&
           a.X + a.Width > b.X &&
           a.Y < b.Y + b.Height &&
           a.Y + a.Height > b.Y;
}

chunk_position_t entity_get_chunk(entity_t entity)
{
    return position_to_chunk_position(E(entity)->position);
}
