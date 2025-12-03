#pragma once

#include "../../core/types.h"
#include "../../math/rects.h"

typedef enum {
	window_default,
	window_centered,
	window_no_resize,
	window_transparent,
} window_flags_t;

typedef struct {
	rect2i_t rect;
	void* platform;

	window_flags_t flags;
} window_t;

void window_init(window_t* window, string name);

void window_opengl_create_context(window_t* window);

boolean window_ping(window_t* window);

void window_opengl_swap_buffers(window_t* window);

void window_free(window_t* window);

void window_set_icon(window_t* window, u8* data, u32 width, u32 height);
void window_set_size(window_t* window, u32 width, u32 height);
