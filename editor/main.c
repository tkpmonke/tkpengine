#include "core/object_registry.h"
#include "core/utilites/console.h"
#include "loaders/loader_registry.h"
#include "core/utilites/arguments.h"
#include "display/windowing/window.h"
#include "core/memory/memory.h"
#include "display/rendering/backends/opengl/opengl_rendering_interface.h"

/* 
 * yes these are copied from learnopengl
 *
 * no i don't feel bad
 */
static const string vertex_shader_source = 
"#version 330 core\n"
"layout (location = 0) in vec3 a_pos;\n"
"void main() {\n"
"   gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);\n"
"}\0";

static const string fragment_shader_source = 
"#version 330 core\n"
"out vec4 o_color;\n"
"void main() {\n"
"   o_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

static const float vertices[] = {
	0.5f,  0.5f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};

static const u32 indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main(int argc, string* argv) {
	arguments_t* args = arguments_parse(argc, argv);

	console_init_log_file(args->log_path);
	console_init(args);

	window_t root_window = {
		.rect.position[0] = 0,
		.rect.position[1] = 0,
		.rect.size[0] = args->window_width != 0 ? args->window_width : 1280,
		.rect.size[1] = args->window_height != 0 ? args->window_height : 720,
		.flags = window_centered
	};

	window_init(&root_window, "TKPEngine Editor");
	loader_registry_init();
	object_registry_init();

	rendering_interface_t* rendering_interface = opengl_create_rendering_interface();
	rendering_interface_set(rendering_interface);
	rendering_interface->init(&root_window);

	rendering_shader_t vertex = rendering_interface->compile_shader((string)vertex_shader_source, rendering_shader_vertex);
	rendering_shader_t fragment = rendering_interface->compile_shader((string)fragment_shader_source, rendering_shader_fragment);
	rendering_pipeline_t pipeline = rendering_interface->create_graphics_pipeline(vertex, fragment);

	rendering_buffer_t vertex_buffer = rendering_interface->create_buffer(sizeof(vertices), rendering_buffer_vertex | rendering_buffer_write, (void*)vertices);
	rendering_buffer_t index_buffer = rendering_interface->create_buffer(sizeof(indices), rendering_buffer_index | rendering_buffer_write, (void*)indices);

	vertex_attribute_object vao = rendering_interface->create_vertex_attribute_object((vertex_attribute_t[]){
		(vertex_attribute_t){
			.offset = 0,
			.size = 3,
			.stride = 3*sizeof(f32),
			.type = variant_type_f32
		}
	}, 1, &vertex_buffer, &index_buffer);

	rendering_command_buffer cmd = rendering_interface->create_command_buffer();

	while (window_ping(&root_window)) {
		rendering_interface->clear();
		rendering_interface->bind_pipeline(cmd, &pipeline);
		rendering_interface->draw_indexed_buffer(cmd, vao, 6);
		rendering_interface->execute_command_buffer(cmd, &root_window);
		rendering_interface->swap_buffers(&root_window);
		rendering_interface->clear_command_buffer(cmd);
	}
	
	rendering_interface->free_command_buffer(cmd);
	rendering_interface->free_buffer(&index_buffer);
	rendering_interface->free_buffer(&vertex_buffer);
	rendering_interface->free_pipeline(&pipeline);

	rendering_interface->free();
	TKP_FREE(rendering_interface);
	object_registry_free();
	loader_registry_free();
	window_free(&root_window);
	console_free();

	TKP_FREE(args);
}
