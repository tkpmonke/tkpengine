#include "register_module.h"
#include "collider.h"
#include "core/component_registry.h"
#include "core/memory/memory.h"

component_t* create_collider_component() {
	component_t* c = TKP_MALLOC(sizeof(component_collider_t));
	c->start = component_collider_start;
	c->update = component_collider_update;
	c->shutdown = component_collider_shutdown;
	c->type = component_registry_get_component("collider")->id;
	return c;
}

static component_variable_t variables[] = {
	{
		.name = "offset",
		.offset = offsetof(component_collider_t, offset),
		.type = component_variable_type_vector3,
		.flags = 0,
		.enum_values = NULL
	}, {
		.name = "size",
		.offset = offsetof(component_collider_t, size),
		.type = component_variable_type_vector3,
		.flags = 0,
		.enum_values = NULL
	},
	COMPONENT_VARIABLE_NULL_INITILIZER
};

void register_module_collider() {
	component_definition_t definition = {
		.name = "collider",
		.create = create_collider_component,
		.variables = variables
	};

	component_registry_add(&definition);
}
