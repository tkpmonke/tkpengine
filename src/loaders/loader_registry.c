#include "loader_registry.h"

#include <string.h>
#include <stddef.h>

#define COUNTOF_ARRAY(x) sizeof(x)/sizeof(*x)

static loader_registry_t _loader_registry;

void loader_registry_init(void) {
	loader_t default_loaders[] = {
		{
			.output_type = 2,
			.load = NULL,
			.extensions = (string[]){ (string)"txt", (string)"md" },
			.extension_count = 2
		},
	};
	list_init(&_loader_registry, COUNTOF_ARRAY(default_loaders), sizeof(loader_t));
	list_copy_to(&_loader_registry, default_loaders, 0, COUNTOF_ARRAY(default_loaders));
}

void loader_registry_add(loader_t* loader) {
	list_push(&_loader_registry, loader);
}

loader_t* loader_registry_get(string ext) {
	for (length i = 0; i < _loader_registry.size; ++i) {
		loader_t* loader = list_get(&_loader_registry, i);
		for (length j = 0; j < loader->extension_count; ++j) {
			if (strcmp(loader->extensions[j], ext) == 0) {
				return loader;
			}
		}
	}

	return NULL;
}

void* loader_registry_load(loader_t* loader, string data) {
	if (loader->load == NULL) {
		return data;
	}

	return loader->load(data);
}

void loader_registry_free(void) {
	list_free(&_loader_registry);
}
