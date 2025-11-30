#pragma once

#include "display/windowing/window.h"
#include "display/rendering/rendering_interface.h"
#include "entity.h"

typedef struct {
	window_t window;
	rendering_interface_t* render_interface;
	entity_t* root;
} main_loop_t;

void main_loop_init(main_loop_t* loop, string title);
main_loop_t* main_loop_get(void);

void main_loop_start(main_loop_t* loop);
