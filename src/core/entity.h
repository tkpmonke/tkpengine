#pragma once

#include "component.h"
#include "memory/list.h"
#include "types.h"

typedef struct entity_t
{
	object_t base;

	string name;
	length id;

	list_t components;
} entity_t;
