#include "component_registry.h"

#include <string.h>

static component_registry registry;

component_registry* component_registry_get() { return &registry; }

component_definition* component_registry_get_component(char* name) {
	for (length i = 0; i < registry.count; ++i) {
		if (strcmp(registry.components[i].name, name) == 0) {
			return &registry.components[i];
		}
	}

	return NULL;
}

void component_registry_add(component_definition* def) {
	if (registry.count + 1 > registry.capacity) {
		registry.capacity <<= 1;
		if (registry.capacity == 0) {
			registry.capacity = 4;
			registry.components = malloc(4 * sizeof(component_definition));
		} else {
			registry.components =
				realloc(registry.components,
						registry.capacity * sizeof(component_definition));
		}
	}
	registry.components[registry.count] = *def;
	registry.count += 1;
}
