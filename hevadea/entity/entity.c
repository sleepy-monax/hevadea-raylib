#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "hevadea/logger.h"
#include "hevadea/system/system.h"
#include "hevadea/utils/List.h"

#include "hevadea/entity/chicken.h"
#include "hevadea/entity/entity.h"
#include "hevadea/entity/fish.h"
#include "hevadea/entity/flower.h"
#include "hevadea/entity/player.h"
#include "hevadea/entity/rabbit.h"
#include "hevadea/entity/tree.h"
#include "hevadea/tile/tile.h"
#include <hevadea/entity/grass_medium.h>
#include <hevadea/entity/grass_small.h>
#include <hevadea/entity/grass_tall.h>

const entity_blueprint_t *blueprints[] = {
    &ENTITY_PLAYER,
    &ENTITY_TREE,
    &ENTITY_RABBIT,
    &ENTITY_FLOWER,
    &ENTITY_GRASS_SMALL,
    &ENTITY_GRASS_MEDIUM,
    &ENTITY_GRASS_TALL,
    &ENTITY_CHICKEN,
    &ENTITY_FISH,

    NULL,
};

static List *entities = NULL;

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

    entity_instance_t *entity = __create(entity_instance_t);

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

void entity_destroy(entity_instance_t *entity)
{
    const entity_blueprint_t *blueprint = entity->blueprint;

    if (blueprint->destroy)
    {
        blueprint->destroy(entity);
    }

    list_remove(entities, entity);
    free(entity);
}

/* --- Entity iterator ----------------------------------------------------- */

void entity_iterate_all(void *target, EntityIterateCallback callback)
{
    list_iterate(entities, target, (ListIterationCallback)callback);
}

/* --- Entity state --------------------------------------------------------- */

bool entity_has_component(entity_instance_t *entity, entity_component_t mask)
{
    return (entity->components & mask) == mask;
}

bool entity_is_moving(entity_instance_t *entity)
{
    return entity->motion.X != 0 || entity->motion.Y != 0;
}

rectangle_t entity_get_bound(entity_instance_t *entity)
{
    if (entity_has_component(entity, COMPONENT_COLIDER))
    {
        return (rectangle_t){
            entity->position.X + entity->colider.X,
            entity->position.Y + entity->colider.Y,
            entity->colider.Width,
            entity->colider.Height,
        };
    }
    else
    {
        return (rectangle_t){entity->position.X - 0.5, entity->position.Y - 0.5, 1, 1};
    }
}

bool entity_colide_with(entity_instance_t *entity, rectangle_t bound)
{
    return rectangle_coliding(entity_get_bound(entity), bound);
}

chunk_position_t entity_get_chunk(entity_instance_t *entity)
{
    return position_to_chunk_position(entity->position);
}

bool entity_can_go_here(entity_instance_t *entity, tile_position_t pos)
{
    if (tile_has_component(pos, TILE_COMPONENT_LIQUID) ^ entity_has_component(entity, COMPONENT_SWIMMING))
        return false;

    if (tile_has_component(pos, TILE_COMPONENT_SOLID) && entity_has_component(entity, COMPONENT_COLIDER))
        return false;

    return true;
}