#include "core/utilites/console.h"
#include "core/memory/memory.h"
#include "core/memory/hashed_string.h"
#include "core/object_registry.h"
#include "core/main_loop.h"

#include "arguments.h"

int main(int argc, string* argv) {
	arguments_t* args = arguments_parse(argc, argv);

	console_init_log_file(args->log_path);
	console_init(args->print_header, args->print_help_message);

	{
		main_loop_t loop;
		main_loop_init(&loop, "TKPEngine Editor");

		entity_t* camera = entity_create_child(&loop.root);
		entity_init(camera, "Camera");

		component_t* c = (component_t*)object_registry_create(object_registry_get_by_name(hashed_string_generate("camera")));
		entity_add_component(camera, c);

		if (args->window_width != 0 && args->window_height != 0) {
			window_set_size(&loop.window, args->window_width, args->window_height);
		}

		main_loop_start(&loop);
	}

	console_free();
	TKP_FREE(args);
}
