#pragma once

#include <stdbool.h>

typedef enum
{
    SEARCH_CONTINUE,
    SEARCH_STOP,
} iterate_state_t;

typedef iterate_state_t (*iterate_callback_t)(int x, int y, void *arg);

void iterate_spiral(int x, int y, int size, iterate_callback_t callback, void *arg);

void iterate_square(int x, int y, int size, iterate_callback_t callback, void *arg);
