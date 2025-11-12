#pragma once

#include "memory/list.h"
#include "object.h"
#include "variant.h"

#include <string.h>

typedef struct {
	hashed_string name;
	variant_type_t type;
	length offset;
} object_variable_t;

typedef struct {
	hashed_string name;
	const char* const unhashed_name;
	length type;
	length base_type;
	object_variable_t* variables;
	object_t* (*create_func)();
} object_definition_t;

/* list of object_definition_t */
typedef list_t object_registry_t;

void object_registry_init(void);

object_definition_t* object_registry_get_by_id(length id);
object_definition_t* object_registry_get_by_name(hashed_string name);

object_t* object_registry_create(object_definition_t* def);
void object_registry_add(object_definition_t* def);

void object_registry_free(void);

#if defined(DEBUG)
void object_registry_print_debug_info();
#endif
