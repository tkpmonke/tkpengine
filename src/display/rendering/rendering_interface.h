#pragma once

/* 
 * rendering api abstraction designed to have easy integration with any api into the engine
 *
 * please note that this api is designed to be able to be used outside of the engine with very little
 * struggle. so do that if you want i guess
 */

#include "display/windowing/window.h"
#include "core/types.h"

typedef u32 rendering_object_id_t;

typedef enum {
	rendering_buffer_data = 0,
	rendering_buffer_vertex = 1,
	rendering_buffer_index = 2,

	rendering_buffer_read = 64,
	rendering_buffer_write = 128,
	rendering_buffer_read_write = rendering_buffer_read | rendering_buffer_write
} rendering_buffer_usage_t;

/* gpu buffer */
typedef struct {
	 length size;
	 void* platform;
	 rendering_buffer_usage_t usage;
} rendering_buffer_t;

/* basically a wrapper for a graphics api */
typedef struct {
	void (*init)(window_t* window);

	rendering_buffer_t (*create_buffer)(length size, rendering_buffer_usage_t usage, void* data);
	void* (*map_buffer)(rendering_buffer_t* buffer);
	void (*unmap_buffer)(rendering_buffer_t* buffer);
	void (*free_buffer)(rendering_buffer_t* buffer);

	void (*free)();
} rendering_interface_t;
