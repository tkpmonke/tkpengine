#include "core/memory/list.h"
#include "core/memory/memory.h"
#include "opengl_es2_rendering_interface.h"

#include <string.h>

#if defined(__EMSCRIPTEN__)
#include "../../external/glad/include/glad/gles2.h"

typedef list_t opengl_es2_command_buffer;

typedef struct
{
	rendering_pipeline_t* pipeline;
	vertex_attribute_object vao;
	length draw_count;

	boolean indexed: 1;
} opengl_es2_draw_command_t;

typedef struct {
	vertex_attribute_t* attributes;
	rendering_buffer_t* vertex_buffer;
	length count;
} opengl_es2_vao_t;

static GLenum _buffer_usage_to_GLenum[] = {
	0,						 /* data */
	GL_ARRAY_BUFFER,		 /* vertex */
	GL_ELEMENT_ARRAY_BUFFER, /* index */
};

static GLenum _shader_type_to_GLenum[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };

static GLenum _pipeline_polygon_mode_to_GLenum[] = { GL_TRIANGLES, GL_POINTS, GL_LINES, GL_TRIANGLE_STRIP, GL_QUADS };

static list_t _opengl_es2_objects;

static GLenum variant_type_to_GLenum(variant_type_t type) {
	switch (type) {
	case (variant_type_f32):
	{
		return GL_FLOAT;
	}
	case (variant_type_u16):
	{
		return GL_UNSIGNED_SHORT;
	}
	case (variant_type_u32):
	{
		return GL_UNSIGNED_INT;
	}
	case (variant_type_i8):
	{
		return GL_BYTE;
	}
	case (variant_type_i16):
	{
		return GL_SHORT;
	}
	case (variant_type_i32):
	{
		return GL_INT;
	}
	default:
	{
		return GL_UNSIGNED_BYTE;
	}
	}
}

void opengl_es2_init(window_t* window) {
	window_opengl_create_context(window);
	gladLoadGLES2(window_opengl_load_proc());

	list_init(&_opengl_es2_objects, 32, sizeof(u32));
}

boolean opengl_es2_query_compute_support(void) {
	return FALSE;
}

rendering_buffer_t opengl_es2_create_buffer(length size, rendering_buffer_usage_t usage, void* data) {

	GLenum buffer_flags;
	if (usage & rendering_buffer_dynamic) {
		buffer_flags = GL_DYNAMIC_DRAW;
	} else {
		buffer_flags = GL_STATIC_DRAW;
	}

	u32 b;
	glGenBuffers(1, &b);
	glBindBuffer(_buffer_usage_to_GLenum[usage & 0b00001111], b);
	glBufferData(_buffer_usage_to_GLenum[usage & 0b00001111], size, data, buffer_flags);

	list_push(&_opengl_es2_objects, &b);

	rendering_buffer_t buffer = { .size = size,
								  .usage = usage,
								  .platform = list_get(&_opengl_es2_objects, _opengl_es2_objects.size - 1) };
	return buffer;
}

void* opengl_es2_map_buffer(rendering_buffer_t* buffer) {
	(void)buffer;
	return NULL;
}

void opengl_es2_unmap_buffer(rendering_buffer_t* buffer) {
	(void)buffer;
}

void opengl_es2_free_buffer(rendering_buffer_t* buffer) {
	if (buffer->is_mapped) {
		opengl_es2_unmap_buffer(buffer);
	}

	glDeleteBuffers(1, (u32*)buffer->platform);
}

vertex_attribute_object opengl_es2_create_vertex_attribute_object(vertex_attribute_t* attributes, length count,
															  rendering_buffer_t* vertex_buffer,
															  rendering_buffer_t* index_buffer) {
	/* gles2 sucks and doesn't have vaos */
	opengl_es2_vao_t* vao = TKP_MALLOC(sizeof(opengl_es2_vao_t));

	vao->attributes = TKP_MALLOC(sizeof(vertex_attribute_t)*count);
	memcpy(vao->attributes, attributes, sizeof(vertex_attribute_t)*count);
	vao->vertex_buffer = vertex_buffer;
	vao->count = count;

	return vao;
}

void opengl_es2_free_vertex_attribute_object(vertex_attribute_object vao) {
	opengl_es2_vao_t* v = vao;
	TKP_FREE(v->attributes);
	TKP_FREE(v);
}

rendering_shader_t opengl_es2_compile_shader(string contents, rendering_shader_type_t type) {
	GLenum target = _shader_type_to_GLenum[type];

	u32 s = glCreateShader(target);
	glShaderSource(s, 1, (const GLchar**)&contents, NULL);
	glCompileShader(s);

	list_push(&_opengl_es2_objects, &s);

	rendering_shader_t shader = { .type = type, .platform = list_get(&_opengl_es2_objects, _opengl_es2_objects.size - 1) };
	return shader;
}

rendering_pipeline_t opengl_es2_create_graphics_pipeline(rendering_shader_t vertex, rendering_shader_t fragment) {
	u32 p = glCreateProgram();
	glAttachShader(p, *(u32*)vertex.platform);
	glAttachShader(p, *(u32*)fragment.platform);
	glLinkProgram(p);

	list_push(&_opengl_es2_objects, &p);
	rendering_pipeline_t pipeline = {
		.platform = list_get(&_opengl_es2_objects, _opengl_es2_objects.size - 1),
		.scissor = {
			.position = {0, 0},
			.size = {0, 0},
		},
		.shaders = {.graphics = {.vertex = vertex, .fragment = fragment}					},
		.type = rendering_pipeline_graphics,
		.cull_mode = rendering_pipeline_cull_back,
		.front_face = rendering_pipeline_front_cw,
		.polygon_mode = rendering_pipeline_polygon_triangles,
		.render_polygon_mode = rendering_pipeline_polygon_triangles
	   };
	return pipeline;
}

void opengl_es2_bind_pipeline(rendering_command_buffer cmd, rendering_pipeline_t* pipeline) {
	opengl_es2_draw_command_t* draw_cmd = list_get((opengl_es2_command_buffer*)cmd, ((opengl_es2_command_buffer*)cmd)->size);
	draw_cmd->pipeline = pipeline;
}

void opengl_es2_free_pipeline(rendering_pipeline_t* pipeline) {
	glDeleteProgram(*(u32*)pipeline->platform);
	glDeleteShader(*(u32*)pipeline->shaders.graphics.vertex.platform);
	glDeleteShader(*(u32*)pipeline->shaders.graphics.fragment.platform);
}

void opengl_es2_draw_buffer(rendering_command_buffer cmd, vertex_attribute_object vao, length draw_count) {
	opengl_es2_draw_command_t* draw_cmd = list_get((opengl_es2_command_buffer*)cmd, ((opengl_es2_command_buffer*)cmd)->size);
	draw_cmd->vao = vao;
	draw_cmd->draw_count = draw_count;
	draw_cmd->indexed = FALSE;
	list_increment(cmd);
}

void opengl_es2_draw_indexed_buffer(rendering_command_buffer cmd, vertex_attribute_object vao, length draw_count) {
	opengl_es2_draw_command_t* draw_cmd = list_get((opengl_es2_command_buffer*)cmd, ((opengl_es2_command_buffer*)cmd)->size);
	draw_cmd->vao = vao;
	draw_cmd->draw_count = draw_count;
	draw_cmd->indexed = TRUE;
	list_increment(cmd);
}

rendering_command_buffer opengl_es2_create_command_buffer(void) {
	opengl_es2_command_buffer* cmd = TKP_MALLOC(sizeof(opengl_es2_command_buffer));
	list_init(cmd, 32, sizeof(opengl_es2_draw_command_t));
	return (rendering_command_buffer)cmd;
}

void opengl_es2_execute_command_buffer(rendering_command_buffer cmd, window_t* window) {
	opengl_es2_command_buffer* glcmd = (opengl_es2_command_buffer*)cmd;
	for (length i = 0; i < glcmd->size; ++i) {
		opengl_es2_draw_command_t* draw_cmd = list_get(glcmd, i);

		if (draw_cmd->pipeline->viewport.size[0] != 0 && draw_cmd->pipeline->viewport.size[1] != 0) {
			glViewport(draw_cmd->pipeline->viewport.position[0], draw_cmd->pipeline->viewport.position[1],
					   draw_cmd->pipeline->viewport.size[0], draw_cmd->pipeline->viewport.size[1]);
		}

		if (draw_cmd->pipeline->scissor.size[0] != 0 && draw_cmd->pipeline->scissor.size[1] != 0) {
			glEnable(GL_SCISSOR_TEST);
			glScissor(draw_cmd->pipeline->scissor.position[0], draw_cmd->pipeline->scissor.position[1],
					  draw_cmd->pipeline->scissor.size[0], draw_cmd->pipeline->scissor.size[1]);
		} else {
			glDisable(GL_SCISSOR_TEST);
		}

		glUseProgram(*(u32*)draw_cmd->pipeline->platform);

		opengl_es2_vao_t* vao = (opengl_es2_vao_t*)draw_cmd->vao;
		for (length i = 0; i < vao->count; ++i) {
			glVertexAttribPointer(i, vao->attributes[i].size, variant_type_to_GLenum(vao->attributes[i].type), GL_FALSE,
								  vao->attributes[i].stride, (void*)(vao->attributes->offset));
			glEnableVertexAttribArray(i);
		}

		if (draw_cmd->indexed) {
			glDrawElements(_pipeline_polygon_mode_to_GLenum[draw_cmd->pipeline->polygon_mode], draw_cmd->draw_count,
						   GL_UNSIGNED_INT, 0);
		} else {
			glDrawArrays(_pipeline_polygon_mode_to_GLenum[draw_cmd->pipeline->polygon_mode], 0, draw_cmd->draw_count);
		}

		if (draw_cmd->pipeline->viewport.size[0] != 0 && draw_cmd->pipeline->viewport.size[1] != 0) {
			glViewport(0, 0, window->rect.size[0], window->rect.size[1]);
		}
	}
}

void opengl_es2_clear_command_buffer(rendering_command_buffer cmd) {
	((opengl_es2_command_buffer*)cmd)->size = 0;
}

void opengl_es2_free_command_buffer(rendering_command_buffer cmd) {
	list_free(cmd);
	TKP_FREE(cmd);
}

void opengl_es2_clear(f32 r, f32 g, f32 b, f32 a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void opengl_es2_swap_buffers(window_t* window) {
	window_opengl_swap_buffers(window);
}

void opengl_es2_resize(window_t* window) {
	glViewport(0, 0, window->rect.size[0], window->rect.size[1]);
}

void opengl_es2_free(void) {
	list_free(&_opengl_es2_objects);
}

rendering_interface_t* opengl_es2_create_rendering_interface(void) {
	rendering_interface_t* interface = malloc(sizeof(rendering_interface_t));
	if (interface == NULL) {
		return NULL;
	}

	interface->init = opengl_es2_init;

	interface->query_compute_support = opengl_es2_query_compute_support;

	interface->create_buffer = opengl_es2_create_buffer;
	interface->map_buffer = opengl_es2_map_buffer;
	interface->unmap_buffer = opengl_es2_unmap_buffer;
	interface->free_buffer = opengl_es2_free_buffer;

	interface->create_vertex_attribute_object = opengl_es2_create_vertex_attribute_object;
	interface->free_vertex_attribute_object = opengl_es2_free_vertex_attribute_object;

	interface->compile_shader = opengl_es2_compile_shader;
	interface->create_graphics_pipeline = opengl_es2_create_graphics_pipeline;
	interface->bind_pipeline = opengl_es2_bind_pipeline;
	interface->free_pipeline = opengl_es2_free_pipeline;

	interface->draw_buffer = opengl_es2_draw_buffer;
	interface->draw_indexed_buffer = opengl_es2_draw_indexed_buffer;

	interface->create_command_buffer = opengl_es2_create_command_buffer;
	interface->execute_command_buffer = opengl_es2_execute_command_buffer;
	interface->clear_command_buffer = opengl_es2_clear_command_buffer;
	interface->free_command_buffer = opengl_es2_free_command_buffer;

	interface->clear = opengl_es2_clear;
	interface->swap_buffers = opengl_es2_swap_buffers;

	interface->resize = opengl_es2_resize;

	interface->free = opengl_es2_free;

	return interface;
}

#endif /* __EMSCRIPTEN__ */
