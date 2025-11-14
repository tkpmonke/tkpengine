#pragma once

#include "core/resource.h"

typedef enum {
	format_undefined,

	/* rgba */
	format_r8g8b8,
	format_r8g8b8a8,
	format_b8g8r8,
	format_b8g8r8a8,
	
	/* depth/stencil */
	format_d24s8,
	format_d32,
	format_d32s8,
} texture_format_t;

typedef struct {
	resource_t resource;
	
	length width;
	length height;
} texture_t;
