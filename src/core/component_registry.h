#pragma once

#include "component.h"
#include "types.h"

#define COMPONENT_VARIABLE_NULL_INITILIZER                                     \
	(component_variable_t) {                                                   \
		.name = NULL, .offset = 0, .type = 0, .flags = 0, .enum_values = NULL  \
	}

typedef struct {
	const string name;
	hashed_string hash;
	u32 offset;

	/*
	 * hidden should be a boolean, but is an enum
	 * for the potential of more flags later on
	 */
	enum component_variable_flags {
		/* is hidden from inspector */
		component_variable_flags_hidden = 1,
	} flags;

	/* only used when type == component_variable_type_enum */
	const string* enum_values;
} component_variable_t;

typedef struct {
	string name;
	hashed_string hash;
	component_t* (*create)();
	component_variable_t* variables;
	length id;
} component_definition_t;

typedef struct {
	component_definition_t* components;
	length count;
	length capacity;
} component_registry_t;

component_registry_t* component_registry_get();
component_definition_t* component_registry_get_component(string name);

void component_registry_free();

void component_registry_add(component_definition_t*);
