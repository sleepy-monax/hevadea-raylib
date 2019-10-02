#include <stdlib.h>
#include <string.h>

#include <hevadea/entity.h>
#include <hevadea/system.h>
#include <hevadea/logger.h>

void construct_player_entity(entity_instance_t *instance)
{
    instance->components = COMPONENT_PLAYER | COMPONENT_MOTION | COMPONENT_COLIDER;
    instance->colider = (rectangle_t){-4, -4, 8, 8};
}

const entity_blueprint_t entity_PLAYER = (entity_blueprint_t){
    .name = "player",
    .construct = construct_player_entity,
};

const entity_blueprint_t *blueprints[] = {&entity_PLAYER, NULL};

static entity_instance_t *entity_instances = NULL;

static size_t entity_instances_allocated = 0;
static size_t entity_instances_used = 0;

void entity_instances_grow(void)
{
    if (entity_instances_allocated == 0)
    {
        entity_instances_allocated = 1024;
        entity_instances = calloc(entity_instances_allocated, sizeof(entity_instance_t));
    }
    else
    {
        size_t new_allocated = entity_instances_allocated * 2;
        entity_instances = realloc(entity_instances, new_allocated * sizeof(entity_instance_t));

        log_info("Expended the entity instance array from %d to %d at %08x", entity_instances_allocated, new_allocated, entity_instances);

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

entity_t entity_alloc(void)
{
    if (entity_instances_allocated == entity_instances_used)
    {
        entity_instances_grow();
    }

    for (size_t i = 0; i < entity_instances_allocated; i++)
    {
        entity_instance_t *instance = &entity_instances[i];

        if (!instance->allocated)
        {
            instance->allocated = true;
            entity_instances_used++;

            return i;
        }
    }

    PANIC("Failled to allocate entity!");
}

void entity_free(entity_t entity)
{
    if (!entity_instances[entity].allocated)
    {
        PANIC("Free'ing unalocated entity!");
    }

    entity_instances_used--;
    entity_instances[entity].allocated = false;
}

entity_t entity_create(const entity_blueprint_t *blueprint, position_t position)
{
    entity_t entity = entity_alloc();

    E(entity)->blueprint = blueprint;
    E(entity)->position = position;

    blueprint->construct(E(entity));

    return entity;
}

void entity_destroy(entity_t entity)
{
    entity_free(entity);
}

entity_instance_t *entity_instance(entity_t entity)
{
    if (entity >= entity_instances_allocated)
        PANIC("Invalid entity handle!");

    entity_instance_t *instance = &entity_instances[entity];

    if (instance->allocated)
    {
        return instance;
    }

    PANIC("Entity is not allocated!");
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

rectangle_t entity_get_bound(entity_t entity)
{
    if (entity_has_component(entity, COMPONENT_COLIDER))
    {
        return (rectangle_t){
            E(entity)->position.X + E(entity)->colider.X,
            E(entity)->position.Y + E(entity)->colider.Y,
            E(entity)->colider.W,
            E(entity)->colider.H,
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

    return a.X < b.X + b.W &&
           a.X + a.W > b.X &&
           a.Y < b.Y + b.H &&
           a.Y + a.H > b.Y;
}