#pragma once

#include "types.h"
#include "component.h"
#include "memory/list.h"

typedef struct entity_t {
	object_t base;

	string name;
	length id;

	list_t components;
} entity_t;

