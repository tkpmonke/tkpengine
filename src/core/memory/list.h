#pragma once

#include "../types.h"

typedef struct {
	void* data;
	length size;
	length capacity;
	uint32_t item_size;
} list_t;


void list_init(list_t* list, length start_capacity, length item_size);

void* list_get(list_t* list, length index);

/* assumes the size of `data` is the same as list->item_size */
void list_push(list_t* list, void* data);

/*
 * it is recommended to copy the data once you retrieve it.
 * this simply returns the last item in the list, and will get overwritten
 * whenever there is a new element added to the list.
 *
 * it will also become dangling whenever the list is resized
 */
void* list_pop(list_t* list);

void list_resize(list_t* list, length new_capacity);

void list_copy_to(list_t* list, void* data, length start, length count);
void list_copy_from(list_t* list, void* data, length start, length count);

/* list_push but without copying data */
void* list_increment(list_t* list);

void list_free(list_t* list);
