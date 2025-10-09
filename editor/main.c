#include "core/component_registry.h"
#include "core/utilites/os.h"

#include "modules.h"
#include "camera/camera.h"

#include <stdio.h>

int main() {
	os_write("Initilizing Modules And Testing os_write!\n", 42, stdout->_fileno);
	printf("Home Path > %s\n", os_get_home());
	printf("Log Path > %s\n\n", os_get_log_path());

	modules_register();
	component_registry_t* registry = component_registry_get();

	component_camera_t* camera = (component_camera_t*)component_registry_get_component("camera")->create();
	camera->base.start((component_t*)camera);

	for (u8 i = 0; i < registry->count; ++i) {
		printf("Component > %s\n", registry->components[i].name);

		component_variable_t* variable;
		u8 j = 0;
		while ((variable = &registry->components[i].variables[j])->name != NULL) {
			printf("\tVariable > %s\n", variable->name);
			printf("\t\tOffset > %d\n", variable->offset);
			printf("\t\tType > %d\n", variable->type);
			printf("\t\tFlags > %d\n", variable->flags);
			j++;
		}
	}

	getchar();

	component_registry_free();
	free(camera);
}
