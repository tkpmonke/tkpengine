#include "camera.h"
#include "core/utilites/console.h"

void component_camera_start(component_t* self) {
	(void)self;
	console_write("Camera Start Called\n");
}

void component_camera_update(component_t* self, float delta) {
	(void)self;
	(void)delta;
}

void component_camera_shutdown(component_t* self) {
	(void)self;
}
