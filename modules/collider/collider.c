#include "collider.h"
#include "core/utilites/console.h"

void component_collider_start(component_t* self) {
	(void)self;
	console_write("Collider Start Called\n");
}

void component_collider_update(component_t* self, float delta) {
	(void)self;
	(void)delta;
}

void component_collider_shutdown(component_t* self) {
	(void)self;
}
