#pragma once

#include "component.h"
#include "types.h"

#define COMPONENT_VARIABLE_NULL_INITILIZER                                     \
	(component_variable_t) {                                                   \
		.name = NULL, .offset = 0, .type = 0, .flags = 0, .enum_values = NULL  \
	}

typedef struct {
	const string name;
	u32 offset;

	/*
	 * look at the following for more info
	 * src/core/types.h
	 * utils/math/vectors.h
	 * utils/math/matrices.h
	 */
	enum component_variable_type {
		component_variable_type_u8,
		component_variable_type_u16,
		component_variable_type_u32,
		component_variable_type_u64,
		component_variable_type_i8,
		component_variable_type_i16,
		component_variable_type_i32,
		component_variable_type_i64,
		component_variable_type_f32,
		component_variable_type_f64,
		component_variable_type_boolean,
		component_variable_type_string,
		component_variable_type_vector2,
		component_variable_type_vector3,
		component_variable_type_vector4,
		component_variable_type_matrix2,
		component_variable_type_matrix2x3,
		component_variable_type_matrix2x4,
		component_variable_type_matrix3,
		component_variable_type_matrix3x2,
		component_variable_type_matrix3x4,
		component_variable_type_matrix4,
		component_variable_type_matrix4x2,
		component_variable_type_matrix4x3,
		component_variable_type_enum,
		
		/* unused for now */
		component_variable_type_function
	} type;

	/*
	 * hidden should be a boolean, but is an enum
	 * for the potential of more flags later on
	 */
	enum component_variable_flags {
		/* is hidden from inspector */
		component_variable_flags_hidden = 1,
	} flags;

	/* only used when type == component_variable_type_enum */
	const string* enum_values;
} component_variable_t;

typedef struct {
	string name;
	component_t* (*create)();
	component_variable_t* variables;
	length id;
} component_definition_t;

typedef struct {
	component_definition_t* components;
	length count;
	length capacity;
} component_registry_t;

component_registry_t* component_registry_get();
component_definition_t* component_registry_get_component(string name);

void component_registry_free();

void component_registry_add(component_definition_t*);
