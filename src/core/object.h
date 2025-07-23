#pragma once

#include "types.h"
#include "utils/math/vectors.h"
#include "component.h"

typedef struct object {
	string name;
	length id;

	vector3 position;
	vector3 rotation;
	vector3 scale;
	vector3 forward;
	vector3 right;
	vector3 up;

	component_t* components;
} object_t;

