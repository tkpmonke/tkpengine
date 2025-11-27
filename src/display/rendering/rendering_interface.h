#pragma once

/* 
 * rendering api abstraction designed to have easy integration with any api into the engine
 */

#include "display/windowing/window.h"
#include "core/types.h"

#include "pipeline.h"
#include "buffer.h"
#include "vertex_attributes.h"

typedef void* rendering_command_buffer;

/* basically a wrapper for a graphics api */
typedef struct {
	void (*init)(window_t* window);

	boolean (*query_compute_support)(void);

	rendering_buffer_t (*create_buffer)(length size, rendering_buffer_usage_t usage, void* data);
	void* (*map_buffer)(rendering_buffer_t* buffer);
	void (*unmap_buffer)(rendering_buffer_t* buffer);
	void (*free_buffer)(rendering_buffer_t* buffer);

	/* index buffer should be NULL if there isn't one */
	vertex_attribute_object (*create_vertex_attribute_object)(
		vertex_attribute_t* attributes,
		length count,
		rendering_buffer_t* vertex_buffer,
		rendering_buffer_t* index_buffer
	);
	void (*free_vertex_attribute_object)(vertex_attribute_object vao);

	rendering_shader_t (*compile_shader)(string contents, rendering_shader_type_t type);
	rendering_pipeline_t (*create_graphics_pipeline)(rendering_shader_t vertex, rendering_shader_t fragment);
	void (*bind_pipeline)(rendering_command_buffer cmd, rendering_pipeline_t* pipeline);
	/* destroys attached shaders as well */
	void (*free_pipeline)(rendering_pipeline_t* pipeline);

	void (*draw_buffer)(rendering_command_buffer cmd, vertex_attribute_object vao, length draw_count);
	void (*draw_indexed_buffer)(rendering_command_buffer cmd, vertex_attribute_object vao, length draw_count);

	rendering_command_buffer (*create_command_buffer)(void);
	void (*execute_command_buffer)(rendering_command_buffer cmd, window_t* window);
	void (*clear_command_buffer)(rendering_command_buffer cmd);
	void (*free_command_buffer)(rendering_command_buffer cmd);

	void (*clear)(f32 r, f32 g, f32 b, f32 a);
	void (*swap_buffers)(window_t* window);

	/* called by the windowing system to notify when viewport needs resized */
	void (*resize)(window_t* window);

	void (*free)(void);
} rendering_interface_t;

void rendering_interface_set(rendering_interface_t* interface);
rendering_interface_t* rendering_interface_get(void);
