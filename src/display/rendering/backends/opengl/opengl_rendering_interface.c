#include "../../external/glew/include/GL/glew.h"

#include "opengl_rendering_interface.h"
#include "core/memory/list.h"
#include "core/memory/memory.h"

#include <string.h>

typedef list_t opengl_command_buffer;

typedef struct {
	rendering_pipeline_t* pipeline;
	vertex_attribute_object vao;
	length draw_count;

	boolean indexed: 1;
} opengl_draw_command_t;

static GLenum _buffer_usage_to_GLenum[] = {
	0, /* data */
	GL_ARRAY_BUFFER, /* vertex */
	GL_ELEMENT_ARRAY_BUFFER, /* index */
};

static GLenum _shader_type_to_GLenum[] = {
	GL_VERTEX_SHADER,
	GL_FRAGMENT_SHADER
};

static GLenum _pipeline_polygon_mode_to_GLenum[] ={
	GL_TRIANGLES,
	GL_POINTS,
	GL_LINES,
	GL_TRIANGLE_STRIP,
	GL_QUADS
};

static list_t _opengl_objects;

GLenum variant_type_to_GLenum(variant_type_t type) {
	switch (type) {
		case (variant_type_f32): {
			return GL_FLOAT;
		} case (variant_type_f64): {
			return GL_DOUBLE;
		} case (variant_type_u16): {
			return GL_UNSIGNED_SHORT;
		} case (variant_type_u32): {
			return GL_UNSIGNED_INT;
		} case (variant_type_i8): {
			return GL_BYTE;
		} case (variant_type_i16): {
			return GL_SHORT;
		} case (variant_type_i32): {
			return GL_INT;
		} default: {
			return GL_UNSIGNED_BYTE;
		}
	}
}

void opengl_init(window_t* window) {
	window_opengl_create_context(window);
	glewInit();

	list_init(&_opengl_objects, 32, sizeof(u32));
}

boolean opengl_query_compute_support(void) {
	i32 major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	if (major < 4 || minor < 3) {
		return 0;
	}

	i32 work_group_count[3];
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_group_count[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_group_count[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_group_count[2]);
	
	return work_group_count[0] > 0 && work_group_count[1] > 0 && work_group_count[2] > 0;
}

rendering_buffer_t opengl_create_buffer(length size, rendering_buffer_usage_t usage, void* data) {

	GLenum buffer_flags;
	if (usage & rendering_buffer_dynamic) {
		if (usage & rendering_buffer_read) {
			if (usage & rendering_buffer_write) {
				buffer_flags = GL_DYNAMIC_COPY;
			} else {
				buffer_flags = GL_DYNAMIC_READ;
			}
		} else {
			buffer_flags = GL_DYNAMIC_DRAW;
		}
	} else {
		if (usage & rendering_buffer_read) {
			if (usage & rendering_buffer_write) {
				buffer_flags = GL_STATIC_COPY;
			} else {
				buffer_flags = GL_STATIC_READ;
			}
		} else {
			buffer_flags = GL_STATIC_DRAW;
		}
	}

	u32 b;
	glGenBuffers(1, &b);
	glBindBuffer(_buffer_usage_to_GLenum[usage & 0b00001111], b);
	glBufferData(_buffer_usage_to_GLenum[usage & 0b00001111], size, data, buffer_flags);

	list_push(&_opengl_objects, &b);

	rendering_buffer_t buffer = {
		.size = size,
		.usage = usage,
		.platform = list_get(&_opengl_objects, _opengl_objects.size-1)
	};
	return buffer;
}

void* opengl_map_buffer(rendering_buffer_t* buffer) {
	buffer->is_mapped = TRUE;
	glBindBuffer(_buffer_usage_to_GLenum[buffer->usage & 0b00001111], *(u32*)buffer->platform);
	return glMapBuffer(_buffer_usage_to_GLenum[buffer->usage & 0b00001111], GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
}

void opengl_unmap_buffer(rendering_buffer_t* buffer) {
	buffer->is_mapped = FALSE;
	glBindBuffer(_buffer_usage_to_GLenum[buffer->usage & 0b00001111], *(u32*)buffer->platform);
	glUnmapBuffer(_buffer_usage_to_GLenum[buffer->usage & 0b00001111]);
}

void opengl_free_buffer(rendering_buffer_t* buffer) {
	if (buffer->is_mapped) {
		opengl_unmap_buffer(buffer);
	}

	glDeleteBuffers(1, (u32*)buffer->platform);
}

vertex_attribute_object opengl_create_vertex_attribute_object(
	vertex_attribute_t* attributes,
	length count,
	rendering_buffer_t* vertex_buffer,
	rendering_buffer_t* index_buffer) {

	u32 vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(_buffer_usage_to_GLenum[vertex_buffer->usage & 0b00001111], *(u32*)vertex_buffer->platform);

	if (index_buffer != NULL) {
		glBindBuffer(_buffer_usage_to_GLenum[index_buffer->usage & 0b00001111], *(u32*)index_buffer->platform);
	}

	for (length i = 0; i < count; ++i) {
		glVertexAttribPointer(i, attributes[i].size, variant_type_to_GLenum(attributes[i].type), GL_FALSE, attributes[i].stride, (void*)(attributes->offset));
		glEnableVertexAttribArray(i);
	}

	list_push(&_opengl_objects, &vao);
	return list_get(&_opengl_objects, _opengl_objects.size-1);
}

void opengl_free_vertex_attribute_object(vertex_attribute_object vao) {
	glDeleteVertexArrays(1, (u32*)vao);
}

rendering_shader_t opengl_compile_shader(string contents, rendering_shader_type_t type) {
	GLenum target = _shader_type_to_GLenum[type];

	u32 s = glCreateShader(target);
	glShaderSource(s, 1, (const GLchar**)&contents, NULL);
	glCompileShader(s);

	list_push(&_opengl_objects, &s);

	rendering_shader_t shader = {
		.type = type,
		.platform = list_get(&_opengl_objects, _opengl_objects.size-1)
	};
	return shader;
}

rendering_pipeline_t opengl_create_graphics_pipeline(rendering_shader_t vertex, rendering_shader_t fragment) {
	u32 p = glCreateProgram();
	glAttachShader(p, *(u32*)vertex.platform);
	glAttachShader(p, *(u32*)fragment.platform);
	glLinkProgram(p);

	list_push(&_opengl_objects, &p);
	rendering_pipeline_t pipeline = {
		.platform = list_get(&_opengl_objects, _opengl_objects.size-1),
		.scissor = {
			.position = { 0, 0 },
			.size = { 0, 0 },
		},
		.shaders = {
			.graphics = {
				.vertex = vertex,
				.fragment = fragment
			}
		},
		.type = rendering_pipeline_graphics,
		.cull_mode = rendering_pipeline_cull_back,
		.front_face = rendering_pipeline_front_cw,
		.polygon_mode = rendering_pipeline_polygon_triangles,
		.render_polygon_mode = rendering_pipeline_polygon_triangles
	};
	return pipeline;
}

void opengl_bind_pipeline(rendering_command_buffer cmd, rendering_pipeline_t* pipeline) {
	opengl_draw_command_t* draw_cmd = list_get((opengl_command_buffer*)cmd, ((opengl_command_buffer*)cmd)->size);
	draw_cmd->pipeline = pipeline;
}

void opengl_free_pipeline(rendering_pipeline_t* pipeline) {
	glDeleteProgram(*(u32*)pipeline->platform);
	glDeleteShader(*(u32*)pipeline->shaders.graphics.vertex.platform);
	glDeleteShader(*(u32*)pipeline->shaders.graphics.fragment.platform);
}

void opengl_draw_buffer(rendering_command_buffer cmd,  vertex_attribute_object vao, length draw_count) {
	opengl_draw_command_t* draw_cmd = list_get((opengl_command_buffer*)cmd, ((opengl_command_buffer*)cmd)->size);
	draw_cmd->vao = vao;
	draw_cmd->draw_count = draw_count;
	draw_cmd->indexed = FALSE;
	list_increment(cmd);
}

void opengl_draw_indexed_buffer(rendering_command_buffer cmd, vertex_attribute_object vao, length draw_count) {
	opengl_draw_command_t* draw_cmd = list_get((opengl_command_buffer*)cmd, ((opengl_command_buffer*)cmd)->size);
	draw_cmd->vao = vao;
	draw_cmd->draw_count = draw_count;
	draw_cmd->indexed = TRUE;
	list_increment(cmd);
}

rendering_command_buffer opengl_create_command_buffer(void) {
	opengl_command_buffer* cmd = TKP_MALLOC(sizeof(opengl_command_buffer));
	list_init(cmd, 32, sizeof(opengl_draw_command_t));
	return (rendering_command_buffer)cmd;
}

void opengl_execute_command_buffer(rendering_command_buffer cmd, window_t* window) {
	opengl_command_buffer* glcmd = (opengl_command_buffer*)cmd;
	for (length i = 0; i < glcmd->size; ++i) {
		opengl_draw_command_t* draw_cmd = list_get(glcmd, i);

		if (draw_cmd->pipeline->scissor.size[0] != 0
		 && draw_cmd->pipeline->scissor.size[1] != 0) {
			glViewport(
				draw_cmd->pipeline->viewport.position[0],
				draw_cmd->pipeline->viewport.position[1],
				draw_cmd->pipeline->viewport.size[0],
				draw_cmd->pipeline->viewport.size[1]
			);
		}

		if (draw_cmd->pipeline->scissor.size[0] != 0
		 && draw_cmd->pipeline->scissor.size[1] != 0) {
			glEnable(GL_SCISSOR_TEST);
			glScissor(
				draw_cmd->pipeline->scissor.position[0],
				draw_cmd->pipeline->scissor.position[1],
				draw_cmd->pipeline->scissor.size[0],
				draw_cmd->pipeline->scissor.size[1]
			);
		} else {
			glDisable(GL_SCISSOR_TEST);
		}
		
		glUseProgram(*(u32*)draw_cmd->pipeline->platform);
		glBindVertexArray(*(u32*)draw_cmd->vao);

		if (draw_cmd->indexed) {
			glDrawElements(_pipeline_polygon_mode_to_GLenum[draw_cmd->pipeline->polygon_mode], draw_cmd->draw_count, GL_UNSIGNED_INT, 0);
		} else {
			glDrawArrays(_pipeline_polygon_mode_to_GLenum[draw_cmd->pipeline->polygon_mode], 0, draw_cmd->draw_count);
		}


		if (draw_cmd->pipeline->scissor.size[0] != 0
		 && draw_cmd->pipeline->scissor.size[1] != 0) {
			glViewport(
				0,
				0,
				window->rect.size[0],
				window->rect.size[1]
			);
		}
	}
}

void opengl_clear_command_buffer(rendering_command_buffer cmd) {
	((opengl_command_buffer*)cmd)->size = 0;
}

void opengl_free_command_buffer(rendering_command_buffer cmd) {
	list_free(cmd);
	TKP_FREE(cmd);
}

void opengl_clear(f32 r, f32 g, f32 b, f32 a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void opengl_swap_buffers(window_t* window) {
	window_opengl_swap_buffers(window);
}

void opengl_resize(window_t* window) {
	glViewport(
		0,
		0,
		window->rect.size[0],
		window->rect.size[1]
	);
}

void opengl_free(void) {
	list_free(&_opengl_objects);
}

rendering_interface_t* opengl_create_rendering_interface(void) {
	rendering_interface_t* interface = malloc(sizeof(rendering_interface_t));
	if (interface == NULL) {
		return NULL;
	}

	interface->init = opengl_init;

	interface->query_compute_support = opengl_query_compute_support;

	interface->create_buffer = opengl_create_buffer;
	interface->map_buffer = opengl_map_buffer;
	interface->unmap_buffer = opengl_unmap_buffer;
	interface->free_buffer = opengl_free_buffer;

	interface->create_vertex_attribute_object = opengl_create_vertex_attribute_object;
	interface->free_vertex_attribute_object = opengl_free_vertex_attribute_object;

	interface->compile_shader = opengl_compile_shader;
	interface->create_graphics_pipeline = opengl_create_graphics_pipeline;
	interface->bind_pipeline = opengl_bind_pipeline;
	interface->free_pipeline = opengl_free_pipeline;

	interface->draw_buffer = opengl_draw_buffer;
	interface->draw_indexed_buffer = opengl_draw_indexed_buffer;

	interface->create_command_buffer = opengl_create_command_buffer;
	interface->execute_command_buffer = opengl_execute_command_buffer;
	interface->clear_command_buffer = opengl_clear_command_buffer;
	interface->free_command_buffer = opengl_free_command_buffer;

	interface->clear = opengl_clear;
	interface->swap_buffers = opengl_swap_buffers;

	interface->resize = opengl_resize;

	interface->free = opengl_free;

	return interface;
}
