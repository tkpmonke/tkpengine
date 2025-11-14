#include "register_module.h"
#include "texture.h"
#include "core/object_registry.h"
#include "core/memory/hashed_string.h"
#include "core/memory/memory.h"

#include <stddef.h>

static object_variable_t* variables = NULL;

object_t* create_texture_resource() {
	resource_t* c = TKP_MALLOC(sizeof(texture_t));
	return (object_t*)c;
}

void register_module_texture() {
	object_variable_t vars[] = {
		{
			.name = hashed_string_generate("width"),
			.offset = offsetof(texture_t, width),
			.type = variant_type_u64,
		}, {
			.name = hashed_string_generate("height"),
			.offset = offsetof(texture_t, height),
			.type = variant_type_u64,
		},
		{ 0, 0, 0 }
	};

	variables = TKP_MALLOC(sizeof(vars));
	memcpy(variables, vars, sizeof(vars));

	object_definition_t definition = {
		.name = hashed_string_generate("texture"),
		.unhashed_name = "texture",
		.base_type = object_registry_get_by_name(hashed_string_generate("resource"))->type,
		.create_func = create_texture_resource,
		.variables = variables
	};

	object_registry_add(&definition);
}

void deregister_module_texture() {
	TKP_FREE(variables);
}
