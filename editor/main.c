#include "core/utilites/console.h"
#include "core/memory/memory.h"
#include "arguments.h"

#include "core/main_loop.h"

int main(int argc, string* argv) {
	arguments_t* args = arguments_parse(argc, argv);

	console_init_log_file(args->log_path);
	console_init(args->print_header, args->print_help_message);

	{
		main_loop_t loop;
		main_loop_init(&loop, "TKPEngine Editor");
		main_loop_start(&loop);
	}

	console_free();
	TKP_FREE(args);
}
