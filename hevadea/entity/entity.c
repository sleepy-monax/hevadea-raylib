#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <hevadea/utils/list.h>
#include <hevadea/system/system.h>
#include <hevadea/logger.h>

#include <hevadea/entity/entity.h>
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

static list_t *entities = NULL;

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

entity_instance_t *entity_create(const entity_blueprint_t *blueprint, position_t position)
{
    if (entities == NULL)
    {
        entities = list_create();
    }

    entity_instance_t *entity = malloc(sizeof(entity_instance_t));

    memset(entity, 0, sizeof(entity_instance_t));

    entity->blueprint = blueprint;
    entity->position = position;
    entity->facing = DIRECTION_SOUTH;

    if (blueprint->create)
    {
        blueprint->create(entity);
    }
    else
    {
        log_warn("No construct for entity %s", blueprint->name);
    }

    list_pushback(entities, entity);

    return entity;
}

void entity_destroy(entity_instance_t *this)
{
    const entity_blueprint_t *blueprint = this->blueprint;

    if (blueprint->destroy)
    {
        blueprint->destroy(this);
    }

    list_remove(entities, this);
    free(this);
}

/* --- Entity iterator ----------------------------------------------------- */

void entity_iterate_all(entity_iterate_callback_t callback, void *args)
{
    list_iterate(entities, (list_iterate_callback_t)callback, args);
}

/* --- Entity state --------------------------------------------------------- */

bool entity_has_component(entity_instance_t *this, entity_component_t mask)
{
    return (this->components & mask) == mask;
}

bool entity_is_moving(entity_instance_t *this)
{
    return this->motion.X != 0 || this->motion.Y != 0;
}

rectangle_t entity_get_bound(entity_instance_t *this)
{
    if (entity_has_component(this, COMPONENT_COLIDER))
    {
        return (rectangle_t){
            this->position.X + this->colider.X,
            this->position.Y + this->colider.Y,
            this->colider.Width,
            this->colider.Height,
        };
    }
    else
    {
        return (rectangle_t){this->position.X - 0.5, this->position.Y - 0.5, 1, 1};
    }
}

bool entity_colide_with(entity_instance_t *this, rectangle_t bound)
{
    return rectangle_coliding(entity_get_bound(this), bound);
}

chunk_position_t entity_get_chunk(entity_instance_t *this)
{
    return position_to_chunk_position(this->position);
}
