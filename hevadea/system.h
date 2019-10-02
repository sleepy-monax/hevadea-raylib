#pragma once

#include <hevadea/entity.h>

typedef enum
{
    SYSTEM_PROCESS,
    SYSTEM_RENDER
} system_type_t;

typedef void (*system_process_callback_t)(entity_t entity, double deltatime);

typedef struct
{
    const char *name;
    system_type_t type;
    int mask;
    system_process_callback_t process;
} system_t;

void system_process(system_type_t type, double deltatime);