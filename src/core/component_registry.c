#include "component_registry.h"
#include "memory/memory.h"
#include "memory/hashed_string.h"

#include <string.h>
#include <stdlib.h>

static component_registry_t registry = {
	.components = NULL,
	.count = 0,
	.capacity = 0
};

component_registry_t* component_registry_get() { return &registry; }

component_definition_t* component_registry_get_component(char* name) {
	/* 
	 * basic binary string search implementation
	 * THIS IS BROKEN AND NEEDS WORK 
	 *
	 * Future me:
	 * write better code
	 *
	 * you forgot to sort the components by name dumbass
	 */
	/* ... */

	/* slower version but it actually works properly */
	/* ... */

	/* 
	 * okay so now i'm using a hashed string comparison which is faster than either
	 * of the versions that these comments were for, but i'm keeping them here
	 * because my comments were funny lol
	 */

	hashed_string hash = hashed_string_generate(name);
	for (length i = 0; i < registry.count; ++i) {
		if (registry.components[i].hash == hash) {
			return &registry.components[i];
		}
	}

	return NULL;
}


static const u8 component_registry_default_size_c = 4;
static const float component_registry_step_c = 2.f;
void component_registry_add(component_definition_t* def) {
	if (registry.count + 1 > registry.capacity) {
		registry.capacity *= component_registry_step_c;
		if (registry.capacity == 0 || registry.components == NULL) {
			registry.capacity = component_registry_default_size_c;
			registry.components = TKP_MALLOC(component_registry_default_size_c * sizeof(component_definition_t));
		} else {
			registry.components = TKP_REALLOC(registry.components, registry.capacity * sizeof(component_definition_t));
		}
	}
	def->hash = hashed_string_generate(def->name);
	registry.components[registry.count] = *def;
	registry.count += 1;
}

void component_registry_free() {
	TKP_FREE(registry.components);
	registry.count = 0;
	registry.capacity = 0;
}
