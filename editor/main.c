#include "core/object_registry.h"
#include "core/utilites/console.h"
#include "loaders/loader_registry.h"
#include "core/utilites/arguments.h"
#include "display/windowing/window.h"
#include "core/memory/memory.h"

int main(int argc, string* argv) {
	arguments_t* args = arguments_parse(argc, argv);

	console_init_log_file(args->log_path);
	console_init(args);

	window_t root_window = {
		.x = 0,
		.y = 0,
		.width = args->window_width != 0 ? args->window_width : 1280,
		.height = args->window_height != 0 ? args->window_height : 720,
		.flags = window_centered
	};

	window_init(&root_window, "TKPEngine Editor");
	loader_registry_init();
	object_registry_init();

	while (window_ping(&root_window)) {}
	
	object_registry_free();
	loader_registry_free();
	window_free(&root_window);
	console_free();

	TKP_FREE(args);
}
