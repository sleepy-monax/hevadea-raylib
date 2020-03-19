#pragma once

#include "hevadea/utils.h"

typedef struct list_node
{
    void *value;

    struct list_node *prev;
    struct list_node *next;
} list_item_t;

typedef struct list
{
    int count;

    list_item_t *head;
    list_item_t *tail;
} list_t;

// Return true if the two value are ordered
typedef int (*list_comparator_t)(void *left, void *right);

typedef iterate_state_t (*list_iterate_callback_t)(void *element, void *args);

/* --- List object constructor and destructor ------------------------------- */

list_t *list_create(void);

void list_destroy(list_t *this);

list_t *list_clone(list_t *this);

/* --- List operation ------------------------------------------------------- */

// Clear all the item in the list.
void list_clear(list_t *this);

// Insert a list item sorted.
void list_insert_sorted(list_t *this, void *value, list_comparator_t comparator);

// Take a look at the **first item** of the list.
bool list_peek(list_t *this, void **value);

// Take a look at the **first item** of the list, and push it to the **tail** of the list
bool list_peek_and_pushback(list_t *this, void **value);

// Take a look at the **last item** of the list.
bool list_peekback(list_t *this, void **value);

// Take a look at the **last item** of the list, and push it to the **head** of the list
bool list_peekback_and_push(list_t *this, void **value);

// Take a look at the item at the **position specified by index** in the list.
bool list_peekat(list_t *this, int index, void **value);

// Push an item to the **head** of the list.
void list_push(list_t *this, void *value);

// Push an item to the **tail** of the list
void list_pushback(list_t *this, void *value);

// Pop the head item of the list.
bool list_pop(list_t *this, void **value);

// Pop the tail item of the list.
bool list_popback(list_t *this, void **value);

// Check if the list conatain a given item.
bool list_containe(list_t *this, void *value);

// Remove the first occurence of an item in the list.
bool list_remove(list_t *this, void *value);

// Is the list empty?
#define list_empty(__list) ((__list)->count == 0)

// Is the list has any item in it?
#define list_any(__list) ((__list)->count != 0)

// Get item count
#define list_count(__list) ((__list)->count)

// Iterate all list items
void list_iterate(list_t *this, list_iterate_callback_t callback, void *args);
