#pragma once

#include "core/types.h"

typedef enum {
	rendering_buffer_data = 0,
	rendering_buffer_vertex = 1,
	rendering_buffer_index = 2,

	/* use if you plan on writing to the buffer often */
	rendering_buffer_dynamic = 32,
	rendering_buffer_read = 64,
	rendering_buffer_write = 128,
	rendering_buffer_read_write = rendering_buffer_read | rendering_buffer_write
} rendering_buffer_usage_t;

/* gpu buffer */
typedef struct {
	 length size;
	 void* platform;
	 rendering_buffer_usage_t usage;
	 boolean is_mapped;
} rendering_buffer_t;
