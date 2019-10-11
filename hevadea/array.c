#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <hevadea/array.h>

#define ARRAY_DEFAULT_ALLOCATED 512

array_t *array_create(size_t element_size)
{
    array_t *this = malloc(sizeof(array_t));

    this->elements_allocated = ARRAY_DEFAULT_ALLOCATED;
    this->elements_size = element_size;
    this->elements_count = 0;
    this->elments = malloc(element_size * ARRAY_DEFAULT_ALLOCATED);

    return this;
}

void array_destroy(array_t *this, array_element_destroy_callback_t callback, void *args)
{
    if (callback)
    {
        for (size_t i = 0; i < this->elements_count; i++)
        {
            callback(array_index(this, i), args);
        }
    }

    free(this->elments);
    free(this);
}

void *array_index(array_t *this, size_t index)
{
    assert(index < this->elements_count);

    return (void *)(((size_t)this->elments) + index * this->elements_size);
}

static void array_grow(array_t *this)
{
    if (this->elements_count == this->elements_allocated)
    {
        size_t new_allocated = this->elements_allocated * 2;

        this->elments = realloc(this->elments, new_allocated * this->elements_allocated);

        memset((void *)((size_t)(this->elments) + this->elements_count * this->elements_size), 0, (new_allocated - this->elements_count) * this->elements_size);

        this->elements_allocated = new_allocated;
    }
}

void array_pushback(array_t *this, void *element, size_t size)
{
    assert(this->elements_size >= size);

    array_grow(this);

    this->elements_count++;
    void *ptr = array_index(this, this->elements_count - 1);

    memcpy(ptr, element, size);
}

// FIXME: srink array when not enought elements
// static void array_shrink(array_t *this)
// {
// }

void array_popback(array_t *this, void *element, size_t size)
{
    assert(this->elements_size >= size);

    void *ptr = array_index(this, this->elements_count - 1);
    memcpy(element, ptr, size);
    memset(ptr, 0, this->elements_size);
    this->elements_count--;
}

void array_iterate(array_t *this, array_iterate_callback_t callback, void *args)
{
    for (size_t i = 0; i < this->elements_count; i++)
    {
        if (callback(array_index(this, i), args) == ITERATION_STOP)
        {
            return;
        }
    }
}

void array_sort(array_t *this, array_sorting_callback_t callback)
{
    qsort(this->elments, this->elements_count, this->elements_size, callback);
}

size_t array_count(array_t *this)
{
    return this->elements_count;
}
