#pragma once

#include "types.h"

typedef struct component_t {
	length type;

	void (*start)(struct component_t* self);
	void (*update)(struct component_t* self, float delta);
	void (*shutdown)(struct component_t* self);
} component_t;
