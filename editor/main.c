#include "core/object_registry.h"
#include "core/utilites/console.h"
#include "core/memory/memory.h"
#include "core/memory/hashed_string.h"
#include "loaders/loader_registry.h"

#include "camera/camera.h"
#include "texture/texture.h"

int main() {
	console_init_log_file(NULL);
	console_init();

	console_write("Initilizing Modules And Testing Console!\n\n");
	console_write("This is a standard print!\n");
	console_write_warning("Here is a warning!\n");
	console_write_error("Here is an error!\n\n");
	
	console_write_va("Does write va work? %s %s\n", "yeah it does!!", "nuh uh");
	console_write_va("Perhaps floats work? %f, %f, %f\n", 15.0f, -74.52f, 213.546f);
	console_write_va("Ints? %d, %d, %d\n", 64, 12-16, -532);
	console_write_warning_va("What about warning va? %s\n", "it does too!!");
	console_write_error_va("ok ok, theres no way error va works too... %s\n\n", "it also works!!");

	loader_registry_init();
	object_registry_init();
	object_definition_t* camera_def = object_registry_get_by_name(hashed_string_generate("camera"));
	component_camera_t* camera = (component_camera_t*)object_registry_create(camera_def);
	camera->base.start((component_t*)camera);

	object_definition_t* texture_def = object_registry_get_by_name(hashed_string_generate("texture"));
	texture_t* texture = (texture_t*)object_registry_create(texture_def);

	/*
#if defined(DEBUG)
	object_registry_print_debug_info();
#endif
	*/

	TKP_FREE(camera);
	TKP_FREE(texture);
	
	object_registry_free();
	loader_registry_free();
	console_free();
}
