#include "module_loading.h"
#include "../core/types.h"

#include <stdio.h>

#if defined(__unix__)
#include <dlfcn.h>
#elif defined(_WIN32)
/* todo */
#endif

module_t* load_module(const char* m) {
	module_t* module = malloc(sizeof(module_t));

#if defined(__unix__)
	module->so = dlopen(m, RTLD_NOW);

	if (!module->so) {
		goto load_module_failed;
	}

	module->register_module = dlsym(module->so, "register_module");
	string result = dlerror();
	if (result) {
		printf("Failed to load register_module from %s module\n", m);
		goto load_module_failed;
	}

	module->register_module();

	module->close_module = dlsym(module->so, "close_module");
	result = dlerror();
	if (result) {
		printf("Failed to load close_module from %s module\n", m);
		goto load_module_failed;
	}

#elif defined(_WIN32)
/* todo */
#endif

	return module;

load_module_failed:
	free(module);
	return NULL;
}

void free_module(module_t* module) {
	module->close_module();
	free(module);
}
