#pragma once

#include "object.h"

typedef struct component_t {
	object_t base;
	struct entity_t* parent;

	void (*start)(struct component_t* self);

	/* called every 0.05 second interval */
	void (*fixed_update)(struct component_t* self);

	/* update called before render */
	void (*update)(struct component_t* self, double delta);
	void (*render)(struct component_t* self);
	void (*post_render)(struct component_t* self);
	
	void (*shutdown)(struct component_t* self);
} component_t;
