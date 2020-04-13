#include "hevadea/array.h"

#define ARRAY_DEFAULT_ALLOCATED 512

array_t *array_create(size_t element_size)
{
    array_t *array = __create(array_t);

    array->elements_allocated = ARRAY_DEFAULT_ALLOCATED;
    array->elements_size = element_size;
    array->elements_count = 0;
    array->elments = malloc(element_size * ARRAY_DEFAULT_ALLOCATED);

    return array;
}

void array_destroy(array_t *array, array_element_destroy_callback_t callback, void *args)
{
    if (callback)
    {
        for (size_t i = 0; i < array->elements_count; i++)
        {
            callback(array_index(array, i), args);
        }
    }

    free(array->elments);
    free(array);
}

void *array_index(array_t *array, size_t index)
{
    assert(index < array->elements_count);

    return (void *)(((size_t)array->elments) + index * array->elements_size);
}

static void array_grow(array_t *array)
{
    if (array->elements_count == array->elements_allocated)
    {
        size_t new_allocated = array->elements_allocated * 2;

        array->elments = realloc(array->elments, new_allocated * array->elements_allocated);

        memset((void *)((size_t)(array->elments) + array->elements_count * array->elements_size), 0, (new_allocated - array->elements_count) * array->elements_size);

        array->elements_allocated = new_allocated;
    }
}

void array_pushback(array_t *array, void *element, size_t size)
{
    assert(array->elements_size >= size);

    array_grow(array);

    array->elements_count++;
    void *ptr = array_index(array, array->elements_count - 1);

    memcpy(ptr, element, size);
}

// FIXME: srink array when not enought elements
// static void array_shrink(array_t *array)
// {
// }

void array_popback(array_t *array, void *element, size_t size)
{
    assert(array->elements_size >= size);

    void *ptr = array_index(array, array->elements_count - 1);
    memcpy(element, ptr, size);
    memset(ptr, 0, array->elements_size);
    array->elements_count--;
}

void array_iterate(array_t *array, array_iterate_callback_t callback, void *args)
{
    assert(callback);

    for (size_t i = 0; i < array->elements_count; i++)
    {
        if (callback(array_index(array, i), args) == ITERATION_STOP)
        {
            return;
        }
    }
}

void array_sort(array_t *array, array_sorting_callback_t callback)
{
    qsort(array->elments, array->elements_count, array->elements_size, callback);
}

size_t array_count(array_t *array)
{
    return array->elements_count;
}
