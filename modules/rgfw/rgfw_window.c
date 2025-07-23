#include <stddef.h>
#include "systems/windowing/windowing.h"

#if WINDOWING_BACKEND == RGFW

window_t* system_windowing_init() {
	return NULL;
}

void system_windowing_update(boolean* is_running) {
	*is_running = TRUE;
}

void system_windowing_shutdown() {}

void system_windowing_swap_buffers() {}

#endif
