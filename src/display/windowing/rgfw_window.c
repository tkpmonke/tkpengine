#include "window.h"

#include <stddef.h>

#if defined(__unix__) || defined(_WIN32) || defined(__APPLE__)

#define RGFW_IMPORT
#define RGFW_OPENGL
#include "../../external/rgfw/RGFW.h"

void window_init(window_t* window, string name) {
	int flags = RGFW_windowOpenGL;
	flags |= window->flags & window_centered ? RGFW_windowCenter : 0;
	flags |= window->flags & window_no_resize ? RGFW_windowNoResize : 0;

	window->platform = RGFW_createWindow(name, window->x, window->y, window->width, window->height, flags);
	RGFW_window_makeCurrentContext_OpenGL(window->platform);
}

void window_set_icon(window_t* window, u8* data, u32 width, u32 height) {
	(void)window;
	(void)data;
	(void)width;
	(void)height;
}

boolean window_ping(window_t* window) {
	RGFW_event e;
	while (RGFW_window_checkEvent(window->platform, &e)) {
		if (e.type == RGFW_quit) {
			return FALSE;
		}
	}

	RGFW_window_swapBuffers_OpenGL(window->platform);

	return !RGFW_window_shouldClose(window->platform);
}

void window_free(window_t* window) {
	RGFW_window_close(window->platform);
}

#endif /* platform check */
