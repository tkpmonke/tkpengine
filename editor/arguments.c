#include "arguments.h"
#include "core/memory/memory.h"

#include <string.h>

arguments_t* arguments_parse(int argc, string* argv) {
	arguments_t* arguments = TKP_MALLOC(sizeof(arguments_t));
	memset(arguments, 0, sizeof(arguments_t));
	arguments->print_header = TRUE;

	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], "--help") == 0
			   || strcmp(argv[i], "-h") == 0) {
			arguments->print_help_message = TRUE;
		} else if (strcmp(argv[i], "--no-header") == 0) {
			arguments->print_header = FALSE;
		} else if (strcmp(argv[i], "--width") == 0) {
			arguments->window_width = atoi(argv[++i]);
		} else if (strcmp(argv[i], "--height") == 0) {
			arguments->window_height = atoi(argv[++i]);
		} else if (strcmp(argv[i], "--log-path") == 0) {
			arguments->log_path = argv[++i];
		}
	}

	return arguments;
}
