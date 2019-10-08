#pragma once

#include <hevadea/entity/entity.h>
#include <hevadea/gametime.h>

typedef enum
{
    SYSTEM_PROCESS,
    SYSTEM_RENDER,
    SYSTEM_OVERLAY
} system_type_t;

typedef void (*system_process_callback_t)(entity_t entity, gametime_t gametime);

typedef struct
{
    int mask;
    const char *name;

    system_type_t type;
    system_process_callback_t process;
} system_t;

void system_process(system_type_t type, gametime_t gametime);