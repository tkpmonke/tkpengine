#pragma once

#include "../types.h"

typedef struct
{
	char* log_path;

	u32 window_width;
	u32 window_height;

	boolean print_header: 1;
	boolean print_help_message: 1;
} arguments_t;

arguments_t* arguments_parse(int argc, string* argv);
