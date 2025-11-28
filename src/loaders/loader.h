#pragma once

#include "../core/types.h"

typedef struct
{
	length output_type;
	void* (*load)(string data);

	string* extensions;
	u8 extension_count;
} loader_t;
