#include "rendering_interface.h"

static rendering_interface_t* _global_render_interface = NULL;

void rendering_interface_set(rendering_interface_t* interface) {
	_global_render_interface = interface;
}

rendering_interface_t* rendering_interface_get(void) {
	return _global_render_interface;
}
