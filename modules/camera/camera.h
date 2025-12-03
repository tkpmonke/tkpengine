#pragma once

#include "core/component.h"
#include "math/matrices.h"

typedef struct {
	component_t base;

	struct component_camera_matrices {
		matrix4 projection;
		matrix4 view;
	} matrices;

	struct component_camera_clip_plane {
		float near;
		float far;
	} clip_plane;

	enum component_camera_projection_mode {
		perspective,
		orthographic
	} projection_mode;

	enum component_camera_clear_mode {
		skybox,
		clear_color,
		nothing,
		dont_clear
	} clear_mode;
} component_camera_t;

void component_camera_start(component_t* self);
void component_camera_update(component_t* self, double delta);
void component_camera_post_render(component_t* self);
void component_camera_shutdown(component_t* self);
