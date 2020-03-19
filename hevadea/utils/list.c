#include <stdlib.h>
#include "hevadea/utils/list.h"

#define list_foreach_entry(__item, __list) for (list_item_t *__item = __list->head; __item != NULL; __item = __item->next)

list_t *list_create(void)
{
    list_t *l = malloc(sizeof(list_t));

    l->count = 0;
    l->head = NULL;
    l->tail = NULL;

    return l;
}

void list_delete(list_t *this)
{
    list_clear(this);
    free(this);
}

list_t *list_clone(list_t *this)
{
    list_t *copy = list_create();

    list_foreach_entry(i, this)
    {
        list_pushback(copy, i->value);
    }

    return copy;
}

void list_clear(list_t *this)
{
    list_item_t *current = this->head;

    while (current)
    {
        list_item_t *next = current->next;
        free(current);
        current = next;
    }

    this->count = 0;
    this->head = NULL;
    this->tail = NULL;
}

void list_insert_sorted(list_t *this, void *value, list_comparator_t comparator)
{
    if (this->head == NULL || comparator(value, this->head->value) > 0)
    {
        list_push(this, value);
    }
    else
    {
        list_item_t *current = this->head;

        while (current->next != NULL && comparator(current->next->value, value) > 0)
        {
            current = current->next;
        }

        list_item_t *item = malloc(sizeof(list_item_t));

        item->prev = current;
        item->next = current->next;
        item->value = value;

        if (current->next == NULL)
        {
            this->tail = item;
        }
        else
        {
            current->next->prev = item;
        }

        current->next = item;

        this->count++;
    }
}

bool list_peek(list_t *list, void **value)
{
    if (list->head != NULL)
    {
        *value = list->head->value;
        return true;
    }
    else
    {
        *value = NULL;
        return false;
    }
}

bool list_peek_and_pushback(list_t *l, void **value)
{
    if (list_peek(l, value))
    {
        list_item_t *item = l->head;

        // Pop
        if (l->count == 1)
        {
            l->count = 0;
            l->head = NULL;
            l->tail = NULL;
        }
        else if (l->count > 1)
        {
            item->next->prev = NULL;
            l->head = item->next;

            l->count--;
        }

        // Push back
        item->prev = NULL;
        item->next = NULL;

        l->count++;

        if (l->tail == NULL)
        {
            l->tail = item;
            l->head = item;
        }
        else
        {
            l->tail->next = item;
            item->prev = l->tail;
            l->tail = item;
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool list_peekback(list_t *list, void **value)
{
    if (list->tail != NULL)
    {
        *value = list->tail->value;
        return true;
    }
    else
    {
        return false;
    }
}

bool list_peekat(list_t *list, int index, void **value)
{
    if (index < list->count)
    {
        list_item_t *current = list->head;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        *value = current->value;

        return true;
    }
    else
    {
        return false;
    }
}

void list_push(list_t *l, void *value)
{
    list_item_t *item = malloc(sizeof(list_item_t));

    item->prev = NULL;
    item->next = NULL;
    item->value = value;

    l->count++;

    if (l->head == NULL)
    {
        l->head = item;
        l->tail = item;
    }
    else
    {
        l->head->prev = item;
        item->next = l->head;
        l->head = item;
    }
}

bool list_pop(list_t *l, void **value)
{
    list_item_t *item = l->head;

    if (l->count == 0)
    {
        return false;
    }
    else if (l->count == 1)
    {
        l->count = 0;
        l->head = NULL;
        l->tail = NULL;
    }
    else if (l->count > 1)
    {
        item->next->prev = NULL;
        l->head = item->next;

        l->count--;
    }

    if (value != NULL)
        *(value) = item->value;

    free(item);

    return true;
}

void list_pushback(list_t *l, void *value)
{
    list_item_t *item = malloc(sizeof(list_item_t));

    item->prev = NULL;
    item->next = NULL;
    item->value = value;

    l->count++;

    if (l->tail == NULL)
    {
        l->tail = item;
        l->head = item;
    }
    else
    {
        l->tail->next = item;
        item->prev = l->tail;
        l->tail = item;
    }
}

bool list_popback(list_t *l, void **value)
{
    list_item_t *item = l->tail;

    if (l->count == 0)
    {
        return NULL;
    }
    else if (l->count == 1)
    {
        l->count = 0;
        l->head = NULL;
        l->tail = NULL;
    }
    else if (l->count > 1)
    {
        item->prev->next = NULL;
        l->tail = item->prev;

        l->count--;
    }

    if (value != NULL)
        *(value) = item->value;

    free(item);

    return true;
}

bool list_remove(list_t *l, void *value)
{
    list_foreach_entry(item, l)
    {
        if (item->value == value)
        {
            if (item->prev != NULL)
            {
                item->prev->next = item->next;
            }
            else
            {
                l->head = item->next;
            }

            if (item->next != NULL)
            {
                item->next->prev = item->prev;
            }
            else
            {
                l->tail = item->prev;
            }

            l->count--;
            free(item);

            return true;
        }
    }

    return false;
}

bool list_containe(list_t *l, void *value)
{
    list_foreach_entry(item, l)
    {
        if (item->value == value)
        {
            return true;
        }
    }

    return false;
}

void list_iterate(list_t *this, list_iterate_callback_t callback, void *args)
{
    list_item_t *current = this->head;

    while (current)
    {
        list_item_t *next = current->next;
        if (callback(current->value, args) == ITERATION_STOP)
        {
            return;
        }
        current = next;
    }
}
