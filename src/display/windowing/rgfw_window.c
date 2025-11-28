#include "core/utilites/console.h"
#include "display/rendering/rendering_interface.h"
#include "window.h"

#include <stddef.h>

#if defined(__unix__) || defined(_WIN32) || defined(__APPLE__)
	#define RGFW_IMPORT

	#if !defined(__EMSCRIPTEN__)
		#define RGFW_VULKAN
	#endif
	#define RGFW_OPENGL
	#define RGFW_INT_DEFINED
	#include "../../external/rgfw/RGFW.h"

void window_on_resize(RGFW_window* win, i32 w, i32 h) {
	window_t* window = (window_t*)RGFW_window_getUserPtr(win);
	window->rect.size[0] = w;
	window->rect.size[1] = h;

	if (rendering_interface_get() != NULL) {
		rendering_interface_get()->resize(window);
	}
}

void window_on_move(RGFW_window* win, i32 x, i32 y) {
	window_t* window = (window_t*)RGFW_window_getUserPtr(win);
	window->rect.position[0] = x;
	window->rect.position[1] = y;
}

void window_init(window_t* window, string name) {
	int flags = 0;
	flags |= window->flags & window_centered ? RGFW_windowCenter : 0;
	flags |= window->flags & window_no_resize ? RGFW_windowNoResize : 0;
	flags |= window->flags & window_transparent ? RGFW_windowTransparent : 0;

	window->platform = RGFW_createWindow(name, window->rect.position[0], window->rect.position[1], window->rect.size[0],
										 window->rect.size[1], flags);
	RGFW_window_setUserPtr(window->platform, window);
	RGFW_setWindowResizedCallback(window_on_resize);
	RGFW_setWindowMovedCallback(window_on_move);
}

void window_set_icon(window_t* window, u8* data, u32 width, u32 height) {
	(void)window;
	(void)data;
	(void)width;
	(void)height;
}

void* window_opengl_load_proc(void) {
	return RGFW_getProcAddress_OpenGL;
}

#if defined (__EMSCRIPTEN__)
static u64 _window_frame_counter = 0;
void window_main_loop(void) {
	_window_frame_counter += 1;
}

void window_wait_for_emscripten(void* arg) {
	while (_window_frame_counter < 1) {}
}
#endif

void window_opengl_create_context(window_t* window) {
	RGFW_window_createContext_OpenGL(window->platform, RGFW_getGlobalHints_OpenGL());
	RGFW_window_makeCurrentContext_OpenGL(window->platform);

#if defined (__EMSCRIPTEN)
	emscripten_set_main_loop(window_main_loop, 0, 1);
	emscripten_async_call(window_wait_for_emscripten, NULL, 500);
#endif
	
	RGFW_window_show(window->platform);
}

boolean window_ping(window_t* window) {
	RGFW_event e;
	while (RGFW_window_checkEvent(window->platform, &e)) {
		if (e.type == RGFW_quit) {
			return FALSE;
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

#endif /* platform check */
