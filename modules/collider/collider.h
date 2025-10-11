#pragma once

/* honestly this is just here to test stuff for the time being */

#include "core/component.h"
#include "core/utilites/math/vectors.h"

typedef struct {
	component_t base;

	vector3 offset;	
	vector3 size;	
} component_collider_t;

void component_collider_start(component_t* self);
void component_collider_update(component_t* self, float delta);
void component_collider_post_render(component_t* self);
void component_collider_shutdown(component_t* self);
