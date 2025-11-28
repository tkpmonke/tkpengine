#pragma once

#include "object.h"

typedef struct component
{
	object_t base;
	struct entity_t* parent;

	void (*start)(struct component* self);

	/* called every 0.05 second interval */
	void (*fixed_update)(struct component* self);

	/* update called before render */
	void (*update)(struct component* self, float delta);
	void (*render)(struct component* self);
	void (*post_render)(struct component* self);

	void (*shutdown)(struct component* self);
} component_t;
