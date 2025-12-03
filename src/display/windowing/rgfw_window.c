#include "window.h"
#include "core/utilites/console.h"
#include "core/main_loop.h"

#include <stddef.h>

#if defined(__unix__) || defined(_WIN32) || defined(__APPLE__)

#define RGFW_IMPORT
#define RGFW_OPENGL
#define RGFW_VULKAN
#define RGFW_INT_DEFINED
#include "../../external/rgfw/RGFW.h"

void window_init(window_t* window, string name) {
	int flags = 0;
	flags |= window->flags & window_centered ? RGFW_windowCenter : 0;
	flags |= window->flags & window_no_resize ? RGFW_windowNoResize : 0;
	flags |= window->flags & window_transparent ? RGFW_windowTransparent : 0;

	window->platform = RGFW_createWindow(
		name,
		window->rect.position[0],
		window->rect.position[1],
		window->rect.size[0],
		window->rect.size[1],
		flags
	);
}

void window_opengl_create_context(window_t* window) {
	RGFW_glHints* hints = RGFW_getGlobalHints_OpenGL();
	hints->major = 3;
	hints->minor = 3;
	RGFW_glContext* err = RGFW_window_createContext_OpenGL(window->platform, hints);

	if (err == NULL) {
		console_write_error("Failed to create OpenGL context");
		exit(1);
	}

	RGFW_window_makeCurrentContext_OpenGL(window->platform);
	RGFW_window_show(window->platform);
}

boolean window_ping(window_t* window) {
	RGFW_event e;
	while (RGFW_window_checkEvent(window->platform, &e)) {
		if (e.type == RGFW_quit) {
			return FALSE;
		} else if (e.type == RGFW_windowResized) {
			RGFW_window_getSize(window->platform, &window->rect.size[0], &window->rect.size[1]);

			if (main_loop_get()->render_interface) {
				main_loop_get()->render_interface->resize(window);
			}
		} else if (e.type == RGFW_windowMoved) {
			RGFW_window_getPosition(window->platform, &window->rect.position[0], &window->rect.position[1]);
		}
	}

	return !RGFW_window_shouldClose(window->platform);
}

void window_opengl_swap_buffers(window_t* window) {
	RGFW_window_swapBuffers_OpenGL(window->platform);
}

void window_free(window_t* window) {
	RGFW_window_close(window->platform);
}

void window_set_icon(window_t* window, u8* data, u32 width, u32 height) {
	(void)window;
	(void)data;
	(void)width;
	(void)height;
}

void window_set_size(window_t* window, u32 width, u32 height) {
	RGFW_window_resize(window->platform, width, height);
}

#endif /* platform check */
