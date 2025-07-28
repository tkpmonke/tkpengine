#include "component_registry.h"

#include <string.h>
#include <stdlib.h>

static component_registry_t registry = {
	.components = NULL,
	.count = 0,
	.capacity = 0
};

component_registry_t* component_registry_get() { return &registry; }

component_definition_t* component_registry_get_component(char* name) {
	/* basic binary string search implementation
	 * THIS IS BROKEN AND NEEDS WORK 
	 *
	 * Future me:
	 * write better code
	 *
	 * you forgot to sort the components by name dumbass

	int start = 0, end = registry.count;
	while (start <= end) {
		int mid = start + (end-1)/2;

		int direction = strcmp(name, registry.components[mid].name);

		if (direction == 0) {
			return &registry.components[mid];
		} else if (direction < 0) {
			start = mid + 1;
		} else {
			end = mid - 1;
		}
	}
	*/

	/* slower version but it actually works properly */
	for (length i = 0; i < registry.count; ++i) {
		if (strcmp(registry.components[i].name, name) == 0) {
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
		if (registry.capacity == 0) {
			registry.capacity = component_registry_default_size_c;
			registry.components = malloc(component_registry_default_size_c * sizeof(component_definition_t));
		} else {
			registry.components =
				realloc(registry.components,
						registry.capacity * sizeof(component_definition_t));
		}
	}
	registry.components[registry.count] = *def;
	registry.count += 1;
}

void component_registry_free() {
	free(registry.components);
	registry.count = 0;
	registry.capacity = 0;
}
