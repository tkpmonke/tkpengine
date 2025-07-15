#pragma once

#include "types.h"

typedef struct {
	const char* name;
	u32 offset;
} component_variable;

typedef struct {
	const char* name;
	component_variable* variables;
} component_definition;

typedef struct {
	component_definition* components;
	length count;
	length capacity;
} component_registry;

component_registry* component_registry_get();
component_definition* component_registry_get_component(char* name);

void component_registry_add(component_definition*);
