#include "main_loop.h"

#include "loaders/loader_registry.h"
#include "core/object_registry.h"
#include "display/windowing/window.h"
#include "display/rendering/backends/opengl/opengl_rendering_interface.h"
#include "core/memory/memory.h"

static main_loop_t* _main_loop = NULL;

void main_loop_init(main_loop_t* loop, string title) {
	loop->window = (window_t) {
		.rect.position[0] = 0,
		.rect.position[1] = 0,
		.rect.size[0] = 1280,
		.rect.size[1] = 720,
		.flags = window_centered
	};

	window_init(&loop->window, title);
	loader_registry_init();
	object_registry_init();
	loop->render_interface = opengl_create_rendering_interface();
	rendering_interface_set(loop->render_interface);
	loop->render_interface->init(&loop->window);

	_main_loop = loop;
}

main_loop_t* main_loop_get(void) {
	return _main_loop;
}

void main_loop_start(main_loop_t* loop) {
	while (window_ping(&loop->window)) {
		loop->render_interface->clear(0.2f, 0.2f, 0.2f, 1.0f);
		loop->render_interface->swap_buffers(&loop->window);
	}

	loop->render_interface->free();
	TKP_FREE(loop->render_interface);
	object_registry_free();
	loader_registry_free();
	window_free(&loop->window);
}
