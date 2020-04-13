#pragma once

#include "hevadea/utils/Utils.h"

typedef struct
{
    void *elments;
    size_t elements_size;
    size_t elements_count;
    size_t elements_allocated;
} array_t;

array_t *array_create(size_t element_size);

typedef void (*array_element_destroy_callback_t)(void *element, void *args);

void array_destroy(array_t *array, array_element_destroy_callback_t callback, void *args);

void array_pushback(array_t *array, void *element, size_t size);

void array_popback(array_t *array, void *element, size_t size);

void *array_index(array_t *array, size_t index);

typedef IterationDecision (*array_iterate_callback_t)(void *element, void *args);

void array_iterate(array_t *array, array_iterate_callback_t callback, void *args);

typedef int (*array_sorting_callback_t)(const void *a, const void *b);

void array_sort(array_t *array, array_sorting_callback_t callback);

size_t array_count(array_t *array);
