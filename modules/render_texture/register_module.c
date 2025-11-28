#include "register_module.h"
#include "core/memory/hashed_string.h"
#include "core/memory/memory.h"
#include "core/object_registry.h"
#include "render_texture.h"

#include <stddef.h>

static object_variable_t* variables = NULL;

object_t* create_render_texture_resource() {
	resource_t* c = TKP_MALLOC(sizeof(render_texture_t));
	return (object_t*)c;
}

void register_module_render_texture() {
	object_variable_t vars[] = { { 0, 0, 0 } };

	variables = TKP_MALLOC(sizeof(vars));
	memcpy(variables, vars, sizeof(vars));

	object_definition_t definition = { .name = hashed_string_generate("render_texture"),
									   .unhashed_name = "render_texture",
									   .base_type =
										   object_registry_get_by_name(hashed_string_generate("texture"))->type,
									   .create_func = create_render_texture_resource,
									   .variables = variables };

	object_registry_add(&definition);
}

void deregister_module_render_texture() {
	TKP_FREE(variables);
}
