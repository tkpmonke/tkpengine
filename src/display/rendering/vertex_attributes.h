#pragma once

#include "core/types.h"
#include "core/variant.h"

typedef struct
{
	length size;
	length stride;
	length offset;
	variant_type_t type;
} vertex_attribute_t;

typedef void* vertex_attribute_object;
