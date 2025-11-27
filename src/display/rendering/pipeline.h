#pragma once

#include "math/rects.h"

typedef enum PACKED {
	rendering_shader_vertex,
	rendering_shader_fragment
} rendering_shader_type_t;

typedef struct {
	void* platform;
	rendering_shader_type_t type;
} rendering_shader_t;

/* they equal the same as compute shaders aren't implemented yet */
typedef enum PACKED {
	rendering_pipeline_graphics = 0,
	rendering_pipeline_compute = 0
} rendering_pipeline_type_t;

typedef enum PACKED {
	rendering_pipeline_cull_back,
	rendering_pipeline_cull_front,
} rendering_pipeline_cull_mode_t;

typedef enum PACKED {
	/* clockwise vs counter-clockwise */
	rendering_pipeline_front_cw,
	rendering_pipeline_front_ccw,
} rendering_pipeline_front_face_t;

typedef enum PACKED {
	rendering_pipeline_polygon_triangles,
	rendering_pipeline_polygon_points,
	rendering_pipeline_polygon_lines,
	rendering_pipeline_polygon_triangle_strip,
	rendering_pipeline_polygon_quads
} rendering_pipeline_polygon_mode_t;

typedef struct {
	void* platform;
	rect2i_t scissor;
	rect2i_t viewport;

	union {
		struct {
			rendering_shader_t vertex;
			rendering_shader_t fragment;
		} graphics;
	} shaders;

	rendering_pipeline_type_t type;
	rendering_pipeline_cull_mode_t cull_mode;
	rendering_pipeline_front_face_t front_face;
	rendering_pipeline_polygon_mode_t polygon_mode;
	rendering_pipeline_polygon_mode_t render_polygon_mode;
} rendering_pipeline_t;
