#include "object_registry.h"
#include "object.h"
#include "component.h"
#include "resource.h"
#include "entity.h"
#include "memory/hashed_string.h"
#include "memory/memory.h"

#include <stddef.h>

object_t* create_component() {
	return TKP_MALLOC(sizeof(component_t));
}

static int _core_object_ids[4] = {0, 0, 0, 0};

void register_core_objects() {
	/* object */
	{
		static object_variable_t* variables = NULL;

		object_variable_t vars[] = {
			{
				.name = hashed_string_generate("type"),
				.type = variant_type_u64,
				.offset = 0
			},
			{0, 0, 0}
		};

		variables = TKP_MALLOC(sizeof(vars));
		memcpy(variables, vars, sizeof(vars));

		object_definition_t def = {
			.name = hashed_string_generate("object"),
			.unhashed_name = "object",
			.type = 0,
			.base_type = 0,
			.variables = variables
		};

		object_registry_add(&def);
	}
	/* component */
	{
		static object_variable_t* variables = NULL;

		object_variable_t vars[] = {
			{
				.name = hashed_string_generate("parent"),
				.type = variant_type_object,
				.offset = offsetof(component_t, parent)
			},
			{0, 0, 0}
		};

		variables = TKP_MALLOC(sizeof(vars));
		memcpy(variables, vars, sizeof(vars));

		object_definition_t def = {
			.name = hashed_string_generate("component"),
			.unhashed_name = "component",
			.type = 0,
			.base_type = 0,
			.variables = variables
		};

		object_registry_add(&def);

		_core_object_ids[1] = def.type;
	}

	/* resource */
	{
		static object_variable_t* variables = NULL;

		object_variable_t vars[] = {
			{
				.name = hashed_string_generate("path"),
				.type = variant_type_string,
				.offset = offsetof(resource_t, path)
			},
			{0, 0, 0}
		};

		variables = TKP_MALLOC(sizeof(vars));
		memcpy(variables, vars, sizeof(vars));

		object_definition_t def = {
			.name = hashed_string_generate("resource"),
			.unhashed_name = "resource",
			.type = 0,
			.base_type = 0,
			.variables = variables
		};

		object_registry_add(&def);
		_core_object_ids[2] = def.type;
	}

	/* entity */
	{
		static object_variable_t* variables = NULL;

		/* 
		 * this does not include components because i'd prefer
		 * for there not to be direct access to the components
		 * if it's not needed
		 */
		object_variable_t vars[] = {
			{
				.name = hashed_string_generate("name"),
				.type = variant_type_string,
				.offset = offsetof(entity_t, name)
			}, {
				.name = hashed_string_generate("id"),
				.type = variant_type_u64,
				.offset = offsetof(entity_t, id)
			},
			{0, 0, 0}
		};

		variables = TKP_MALLOC(sizeof(vars));
		memcpy(variables, vars, sizeof(vars));

		object_definition_t def = {
			.name = hashed_string_generate("entity"),
			.unhashed_name = "entity",
			.type = 0,
			.base_type = 0,
			.variables = variables
		};

		object_registry_add(&def);
		_core_object_ids[3] = def.type;
	}
}

void deregister_core_objects() {
	for (int i = 0; i < 4; ++i) {
		TKP_FREE(object_registry_get_by_id(_core_object_ids[i])->variables);
	}
}

