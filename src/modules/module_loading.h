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

module_t* module_load(const char* module);
void* module_get(module_t* module, const char* function);
void module_free(module_t*);
