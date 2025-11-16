#include "object_registry.h"
#include "modules.h"
#include "core_objects.h"

static object_registry_t _object_registry;

void object_registry_init() {
	list_init(&_object_registry, 4, sizeof(object_definition_t));
	register_core_objects();
	modules_register();
}

object_definition_t* object_registry_get_by_id(length id) {
	return (object_definition_t*)list_get(&_object_registry, id);
}

object_definition_t* object_registry_get_by_name(hashed_string name) {
	for (length i = 0; i < _object_registry.size; ++i) {
		object_definition_t* o = object_registry_get_by_id(i);
		if (o->name == name) {
			return o;
		}
	}

	return (void*)0;
}

object_t* object_registry_create(object_definition_t* def) {
	object_t* o = def->create_func();
	o->type = def->type;
	return o;
}

void object_registry_add(object_definition_t* def) {
	def->type = _object_registry.size;
	list_push(&_object_registry, def);
}

void object_registry_free() {
	modules_deregister();
	deregister_core_objects();
	list_free(&_object_registry);
}

#if defined(DEBUG)
#include "utilites/console.h"

void object_registry_print_debug_info() {
	for (u8 i = 0; i < _object_registry.size; ++i) {
		object_definition_t* def = (object_definition_t*)list_get(&_object_registry, i);
		console_write_va("Object > %s\n", def->unhashed_name);
		console_write_va("\tBase Type > %s\n", object_registry_get_by_id(def->base_type)->unhashed_name);

		for (int i = 0; TRUE; ++i) {
			object_variable_t* variable = &def->variables[i];

			if (variable->name == 0) {
				break;
			}

			console_write_va("\tVariable > %d\n", variable->name);
			console_write_va("\t\tType > %d\n", variable->type);
			console_write_va("\t\tOffset > %d\n", variable->offset);
		}
	}

}
#endif
