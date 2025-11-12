#include "register_module.h"
#include "collider.h"
#include "core/object_registry.h"
#include "core/memory/memory.h"
#include "core/memory/hashed_string.h"

object_t* create_collider_component() {
	component_t* c = TKP_MALLOC(sizeof(component_collider_t));
	c->start = component_collider_start;
	c->fixed_update = NULL;
	c->update = component_collider_update;
	c->render = NULL;
	c->post_render = NULL;
	c->shutdown = component_collider_shutdown;
	return (object_t*)c;
}

static object_variable_t* variables;
void register_module_collider() {
	object_variable_t vars[] = {
		{
			.name = hashed_string_generate("offset"),
			.offset = offsetof(component_collider_t, offset),
			.type = variant_type_vector3,
		}, {
			.name = hashed_string_generate("size"),
			.offset = offsetof(component_collider_t, size),
			.type = variant_type_vector3,
		},
		{ 0, 0, 0 }
	};
	
	variables = TKP_MALLOC(sizeof(vars));
	memcpy(variables, vars, sizeof(vars));

	object_definition_t definition = {
		.name = hashed_string_generate("collider"),
		.unhashed_name = "collider",
		.create_func = create_collider_component,
		.variables = variables
	};

	object_registry_add(&definition);
}

void deregister_module_collider() {
	TKP_FREE(variables);
}
