#pragma once

#include "core/component.h"
#include "utils/math/matrices.h"

typedef struct {
	component_t base;

	struct component_camera_matrices {
		matrix4 projection;
		matrix4 view;
	} matrices;

	struct component_camera_clip_plane {
		float near, far;
	} clip_plane;

	enum component_camera_projection_mode {
		perspective,
		orthographic,
	} projection_mode;
} component_camera_t;
