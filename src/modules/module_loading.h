#pragma once

/* load module files */

/*
 * unix - module-X.so
 * windows - ModuleX.dll
 * macos - sucks xD
 */

typedef struct {
	void (*register_module)();
	void (*close_module)();

	void* so; /* shared object */
} module_t;

module_t* load_module(const char* module);

void free_module(module_t*);
