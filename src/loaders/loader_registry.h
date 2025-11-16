#pragma once

#include "../core/memory/list.h"
#include "loader.h"

typedef list_t loader_registry_t;

void loader_registry_init(void);
void loader_registry_add(loader_t* loader);
loader_t* loader_registry_get(string ext);
void* loader_registry_load(loader_t* loader, string data);
void loader_registry_free(void);
