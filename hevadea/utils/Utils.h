#pragma once

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    ITERATION_CONTINUE,
    ITERATION_STOP,
} IterationDecision;

#define __create(__type) ((__type *)calloc(1, sizeof(__type)))

typedef IterationDecision (*iterate_callback_t)(int x, int y, void *arg);

void iterate_spiral(int x, int y, int size, iterate_callback_t callback, void *arg);

void iterate_square(int x, int y, int size, iterate_callback_t callback, void *arg);

void __attribute__((noreturn)) PANIC(const char *why);