#pragma once

#include <hevadea/utils.h>

typedef enum
{
    FILESYSTEM_FILE,
    FILESYSTEM_DIRECTORY,
    FILESYSTEM_LINK,
    FILESYSTEM_OTHER,
} filesystem_file_type_t;

typedef iterate_state_t(filesystem_iterate_callback_t)(const char *path, filesystem_file_type_t type, void *arg);

void filesystem_iterate(const char *path, filesystem_iterate_callback_t *callback, void *args);