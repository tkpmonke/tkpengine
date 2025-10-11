#pragma once

#include "core/types.h"

#if !defined(WINDOWING_BACKEND)
#define WINDOWING_BACKEND RGFW
#endif

typedef struct {
	u32 width, height, x, y;

	/* 
	 * used for platform dependent info
	 *
	 * for example, for the RGFW backend, this
	 * is used for the RGFW_window pointer
	 */
	void* platform_data;
} window_t;

window_t* system_windowing_init();
void system_windowing_update(boolean* is_running);
void system_windowing_shutdown();

void system_windowing_swap_buffers();
