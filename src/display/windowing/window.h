#pragma once

#include "../../core/types.h"

typedef enum {
	window_default,
	window_centered,
	window_no_resize,
} window_flags_t;

typedef struct {
	u32 x;
	u32 y;
	u32 width;
	u32 height;
	window_flags_t flags;
	
	void* platform;
} window_t;

void window_init(window_t* window, string name);
void window_set_icon(window_t* window, u8* data, u32 width, u32 height);

boolean window_ping(window_t* window);

void window_free(window_t* window);
