#include "core/component_registry.h"
#include "core/utilites/os.h"
#include "core/utilites/console.h"
#include "core/memory/memory.h"

#include "modules.h"
#include "camera/camera.h"
#include "collider/collider.h"

#include <stdio.h>

int main() {
	console_init();
	console_init_log_file(NULL);

	console_write("Initilizing Modules And Testing Console!\n\n");
	console_write("This is a standard print!\n");
	console_write_warning("Here is a warning!\n");
	console_write_error("Here is an error!\n\n");
	
	console_write_va("Does write va work? %s %s\n", "yeah it does!!", "nuh uh");
	console_write_va("Perhaps floats work? %f, %f, %f\n", 15.0f, -74.52f, 213.546f);
	console_write_va("Ints? %d, %d, %d\n", 64, 12-16, -532);
	console_write_warning_va("What about warning va? %s\n", "it does too!!");
	console_write_error_va("ok ok, theres no way error va works too... %s\n\n", "it also works!!");

	printf("Home Path > %s\n", os_get_home());
	printf("Log Path > %s\n\n", os_get_log_path());

	modules_register();
	component_registry_t* registry = component_registry_get();
	component_camera_t* camera = (component_camera_t*)component_registry_get_component("camera")->create();
	camera->base.start((component_t*)camera);

	component_collider_t* collider = (component_collider_t*)component_registry_get_component("collider")->create();
	collider->base.start((component_t*)collider);

	for (u8 i = 0; i < registry->count; ++i) {
		console_write_va("Component > %s\n", registry->components[i].name);

		component_variable_t* variable;
		u8 j = 0;
		while ((variable = &registry->components[i].variables[j])->name != NULL) {
			console_write_va("\tVariable > %s\n", variable->name);
			console_write_va("\t\tHash > %d\n", variable->hash);
			console_write_va("\t\tOffset > %d\n", variable->offset);
			console_write_va("\t\tType > %d\n", variable->type);
			console_write_va("\t\tFlags > %d\n", variable->flags);
			j++;
		}
	}

	TKP_FREE(camera);
	
	component_registry_free();
	console_free();
}
