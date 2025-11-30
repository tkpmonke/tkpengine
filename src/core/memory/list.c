#include "list.h"
#include "memory.h"
#include "../utilites/console.h"

#include <string.h>

void list_init(list_t* list, length start_capacity, length item_size) {
	list->item_size = item_size;
	list->capacity = start_capacity;
	list->data = TKP_MALLOC(start_capacity*item_size);
	list->size = 0;
}

void* list_get(list_t* list, length index) {
	return list->data+index*list->item_size;
}

void list_push(list_t* list, void* data) {
	if (list->capacity < list->size+1) {
		list_resize(list, list->capacity*2);
	}

	memcpy(list->data+list->size*list->item_size, data, list->item_size);
	list->size += 1;
}

void* list_pop(list_t* list) {
	list->size -= 1;
	return list->data+list->size*list->item_size;
}

void list_resize(list_t* list, length new_capacity) {
	list->capacity = new_capacity;

	/* probably not worth the reallocation if its smaller */
	if (new_capacity < list->capacity) {
		return;
	}

	list->data = realloc(list->data, list->item_size*new_capacity);
}

void list_copy_to(list_t* list, void* data, length start, length count) {
	if (count == 0) {
		console_write_error("List > Cannot copy with length of 0\n");
		return;
	}

	if (start+count > list->capacity) {
		console_write_error_va("List > Cannot execute list_copy_to, %d > %d\n", start+count, list->capacity);
		return;
	}

	memcpy(data, list->data+start*list->item_size, count*list->item_size);
}

void list_copy_from(list_t* list, void* data, length start, length count) {
	if (count == 0) {
		console_write_error("List > Cannot copy with length of 0\n");
		return;
	}
	
	if (start+count > list->capacity) {
		list_resize(list, start+count);
	}

	memcpy(list->data+start*list->item_size, data, count*list->item_size);
}

void list_increment(list_t* list) {
	if (list->capacity < list->size+1) {
		list_resize(list, list->capacity*2);
	}

	list->size += 1;
}

void list_free(list_t* list) {
	TKP_FREE(list->data);
	list->capacity = 0;
	list->size = 0;
	list->item_size = 0;
}
