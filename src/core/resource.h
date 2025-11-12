#pragma once

#include "types.h"
#include "object.h"

typedef struct {
	object_t base;
	string path;
} resource_t;
